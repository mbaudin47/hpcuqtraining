/*!
 * \file beam.cpp
 * \brief Implementation of the beam object
*/
#include "beam.h"
#include <iostream>

// LibXML2
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

beam::beam(string sFile, bool bVerbose):
    _sFile(sFile),_bVerbose(bVerbose),
    _dE(-1.0), _dF(-1.0), _dL(-1.0), _dI(-1.0),
    _dY(-1.0),
    _vecDerivate(NULL),
    _matHessian(NULL)
{
    if ( _bVerbose ) {
        cout << endl << "***********************************" << endl;
        cout << " ** Beam constructor object with an XML sFile" << endl;
        cout << " ** _sFile[" << _sFile << "]" << endl;
        cout << "***********************************" << endl << endl;
    }
}

beam::~beam()
{

    if ( _bVerbose ) {
        cout << endl << "***********************************" << endl;
        cout << " ** Destroy beam object" << endl;
    }

    if ( _vecDerivate != NULL )
        delete _vecDerivate;

    if ( _matHessian != NULL ) {
        for(int i=0; i<4; i++)
            delete _matHessian[i];
        delete _matHessian;
    }


    if ( _bVerbose )
        cout << "***********************************" << endl << endl;
}

void beam::readXMLInputs()
{
    if ( _bVerbose ) {
        cout << endl << "***********************************" << endl;
        cout << " ** readXMLInputs with XML file[" << _sFile << "] ... " << endl;
    }

    /* Init libxml */
    xmlInitParser();

    // Parsing of the file
    xmlDocPtr doc = xmlParseFile(_sFile.c_str ());
    if (doc == NULL)
    {
        cerr << "Error: unable to parse file \"" << _sFile << "\"" << endl;
        exit(-1);
    }

    // Create xpath evaluation context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL)
    {
        cerr << "Error: unable to create new XPath context" << endl;
        xmlFreeDoc(doc);
        exit(-1);
    }

    // Read the values of the inputs attributes from XPath string
    _dE = getValueFromXPath ("//inputs/@E", xpathCtx);
    _dF = getValueFromXPath ("//inputs/@F", xpathCtx);
    _dL = getValueFromXPath ("//inputs/@L", xpathCtx);
    _dI = getValueFromXPath ("//inputs/@I", xpathCtx);

    // Cleanup
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    /* Shutdown libxml */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();

    if ( _bVerbose ) {
        cout << " ** End Of readXMLInputs with XML file" << endl;
        cout << "***********************************" << endl << endl;
    }

}

double beam::getValueFromXPath (string sXPath, xmlXPathContextPtr xpathCtx)
{
    if ( _bVerbose ) {
        cout << " ** Searching sXPath[" << sXPath << "] in getValueFromXPath function ..." << endl;
    }
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar *)(sXPath.c_str ()), xpathCtx);
    if(xpathObj == NULL || xpathObj->nodesetval == NULL)
    {
        cerr << "Error: unable to evaluate xpath expression \"" << sXPath << "\"" << endl;
        exit(1);
    }
    xmlNodePtr cur = xpathObj->nodesetval->nodeTab[0];
    xmlXPathFreeObject(xpathObj);
    double value = atof((char *)xmlNodeGetContent(cur));

    if ( _bVerbose ) {
        cout << " ** sXPath[" << sXPath << "] value[" << value << "]" << endl;
    }

    return value;
}


void beam::writeXMLOutputs (string sXMLFile)
{
    if ( _bVerbose ) {
        cout << endl << "***********************************" << endl;
        cout << " ** writeXMLOutputs in the XML file[" << sXMLFile << "] ... " << endl;
    }

    /* Init libxml */
    xmlInitParser();

    // Parsing of the file
    xmlDocPtr doc = xmlParseFile(_sFile.c_str ());
    if (doc == NULL)
    {
        cerr << "Error: unable to parse file \"" << _sFile << "\"" << endl;
        exit(-1);
    }

    xmlNodePtr cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        cerr << "Error: empty document in the XML file[" << _sFile << "]" << endl;
        xmlFreeDoc(doc);
        exit(-1);
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) "beam")) {
        cerr << "Error: document in the XML file[" << _sFile << "] of the wrong type, root node != beam" << endl;
        xmlFreeDoc(doc);
        exit(-1);
    }

   xmlNodePtr nodeOuputs = xmlNewTextChild (cur, NULL, (const xmlChar *) "outputs", NULL);

   // Deviation
   char sValue[20]; sprintf(sValue, "%.9e", _dY);
   xmlAttrPtr newattr = xmlNewProp (nodeOuputs, (const xmlChar *) "deviation", (const xmlChar *) sValue);


   // Derivates if computed
   if ( _vecDerivate != NULL ) {
       xmlNodePtr nodeDerivates  = xmlNewChild(nodeOuputs, 0, (const xmlChar*)"derivates", 0);
       sprintf(sValue, "%.9e", _vecDerivate[0]);
       xmlNewProp(nodeDerivates, (const xmlChar*)"partialE", (const xmlChar*)sValue);
       sprintf(sValue, "%.9e", _vecDerivate[1]);
       xmlNewProp(nodeDerivates, (const xmlChar*)"partialF", (const xmlChar*)sValue);
       sprintf(sValue, "%.9e", _vecDerivate[2]);
       xmlNewProp(nodeDerivates, (const xmlChar*)"partialL", (const xmlChar*)sValue);
       sprintf(sValue, "%.9e", _vecDerivate[3]);
       xmlNewProp(nodeDerivates, (const xmlChar*)"partialI", (const xmlChar*)sValue);

       // Hessian
       if ( _matHessian != NULL ) {
           xmlNodePtr nodeHessian  = xmlNewChild(nodeOuputs, 0, (const xmlChar*)"hessian", 0);

           xmlNodePtr nodeHessianFromE  = xmlNewChild(nodeHessian, 0, (const xmlChar*)"partialE", 0);
           sprintf(sValue, "%.9e", _matHessian[0][0]);
           xmlNewProp(nodeHessianFromE, (const xmlChar*)"partialE", (const xmlChar*)sValue);
           sprintf(sValue, "%.9e", _matHessian[0][1]);
           xmlNewProp(nodeHessianFromE, (const xmlChar*)"partialF", (const xmlChar*)sValue);
           sprintf(sValue, "%.9e", _matHessian[0][2]);
           xmlNewProp(nodeHessianFromE, (const xmlChar*)"partialL", (const xmlChar*)sValue);
           sprintf(sValue, "%.9e", _matHessian[0][3]);
           xmlNewProp(nodeHessianFromE, (const xmlChar*)"partialI", (const xmlChar*)sValue);

           xmlNodePtr nodeHessianFromF  = xmlNewChild(nodeHessian, 0, (const xmlChar*)"partialF", 0);
           sprintf(sValue, "%.9e", _matHessian[1][1]);
           xmlNewProp(nodeHessianFromF, (const xmlChar*)"partialF", (const xmlChar*)sValue);
           sprintf(sValue, "%.9e", _matHessian[1][2]);
           xmlNewProp(nodeHessianFromF, (const xmlChar*)"partialL", (const xmlChar*)sValue);
           sprintf(sValue, "%.9e", _matHessian[1][3]);
           xmlNewProp(nodeHessianFromF, (const xmlChar*)"partialI", (const xmlChar*)sValue);

           xmlNodePtr nodeHessianFromL  = xmlNewChild(nodeHessian, 0, (const xmlChar*)"partialL", 0);
           sprintf(sValue, "%.9e", _matHessian[2][2]);
           xmlNewProp(nodeHessianFromL, (const xmlChar*)"partialL", (const xmlChar*)sValue);
           sprintf(sValue, "%.9e", _matHessian[2][3]);
           xmlNewProp(nodeHessianFromL, (const xmlChar*)"partialI", (const xmlChar*)sValue);

           xmlNodePtr nodeHessianFromI  = xmlNewChild(nodeHessian, 0, (const xmlChar*)"partialI", 0);
           sprintf(sValue, "%.9e", _matHessian[3][3]);
           xmlNewProp(nodeHessianFromI, (const xmlChar*)"partialI", (const xmlChar*)sValue);
       }
   }

   // Dump the XML tree in a ASCII file
   xmlSaveFormatFile (sXMLFile.c_str (), doc, 1);
   // Cleanup
   xmlFreeDoc(doc);
   // Shutdown libxml
   xmlCleanupParser();

   // This is to debug memory for regression tests
   xmlMemoryDump();

    if ( _bVerbose ) {
        cout << " ** End Of writeXMLOutputs with XML file" << endl;
        cout << "***********************************" << endl << endl;
    }

}



void beam::computeDeviation ()
{
    if ( _bVerbose )
        cout << " ** computeDeviation" << endl;
    _dY = ( _dF * _dL * _dL * _dL ) / ( 3.0 * _dE * _dI);
}

void beam::computeDerivates ()
{
    if ( _bVerbose )
        cout << " ** computeDerivates" << endl;
    if ( _vecDerivate != NULL )
        delete _vecDerivate;
    _vecDerivate = new double[4];
    for(int i=0; i<4; i++)
        _vecDerivate[i] = 0.0;

    // From E
    _vecDerivate[0] = -1.0 * _dY / ( _dE);
    // From F
    _vecDerivate[1] = _dY / ( _dF);
    // From L
    _vecDerivate[2] = 3.0 * _dY / ( _dL);
    // From I
    _vecDerivate[3] = -1.0 * _dY / ( _dI);
}


void beam::computeHessian ()
{
    if ( _bVerbose )
        cout << " ** computeHessian" << endl;
    if ( _matHessian != NULL ) {
        for(int i=0; i<4; i++)
            delete _matHessian[i];
        delete _matHessian;
    }
    _matHessian = new double *[4];
    for(int i=0; i<4; i++) {
        _matHessian[i] = new double[4];
        for(int j=0; j<4; j++)
            _matHessian[i][j] = 10*i + 2*j;
    }
    // Case of E: \frac{\partial y}{E} = -1.0  \frac{y}{E}
    _matHessian[0][0] =  2.0 * _dY / ( _dE * _dE);
    _matHessian[0][1] = _matHessian[1][0] = -1.0 * _dY / ( _dE * _dF);
    _matHessian[0][2] = _matHessian[2][0] = -3.0 * _dY / ( _dE * _dL);
    _matHessian[0][3] = _matHessian[3][0] =  1.0 * _dY / ( _dE * _dI);
    // Case of F : \frac{\partial y}{\partial F} = \frac{y}{F}
    _matHessian[1][1] = 0.0;
    _matHessian[1][2] = _matHessian[2][1] =  3.0 * _dY / ( _dF * _dL);
    _matHessian[1][3] = _matHessian[3][1] = -1.0 * _dY / ( _dF * _dI);
    // Case of L : \frac{\partial y}{\partial L} = \frac{3.0 y}{L}
    _matHessian[2][2] =  6.0 * _dY / ( _dL * _dL);
    _matHessian[2][3] = _matHessian[3][2] = -3.0 * _dY / ( _dL * _dI);
    // Case of I: \frac{\partial y}{I} = -1.0  \frac{y}{I}
    _matHessian[3][3] =  2.0 * _dY / ( _dI * _dI);
}


void beam::printLog ()
{
    cout << endl << "************************" << endl;
    cout << " **  beam::printLog " << endl;
    cout << " ** _sFile[" << _sFile << "]" << endl;
    cout << " ** Inputs : E[" << _dE << "] F[" << _dF << "] _L[" << _dL << "] I[" << _dI << "]" << endl;
    cout << " ************" << endl;
    cout << " ** Output :" << endl;
    cout << " **   Deviation[" << _dY << "]" << endl;
    if ( _vecDerivate != NULL ) {
        cout << " ** Derivates :" << endl;
        cout << " **   E[" << _vecDerivate[0] << "]"<< endl;
        cout << " **   F[" << _vecDerivate[1] << "]"<< endl;
        cout << " **   L[" << _vecDerivate[2] << "]"<< endl;
        cout << " **   I[" << _vecDerivate[3] << "]" << endl;
    } else {
        cout << " ** No Derivate computing"<< endl;
    }

    if ( _matHessian != NULL ) {
        cout << " ** Hessian :"<<endl;
        for(int i=0; i<4; i++) {
            cout << " **   i[" << i <<"] : ";
            for(int j=0; j<4; j++)
                cout << _matHessian[i][j] << "  ";
            cout << endl;
        }
    } else {
        cout << " ** No Hessian computing"<< endl;
    }
    cout << "************************" << endl << endl;

}
