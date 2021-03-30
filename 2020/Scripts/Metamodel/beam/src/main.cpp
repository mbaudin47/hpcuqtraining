/*!
 * \file main.cpp
 * \brief Main command for the beam use case
 *
 *Treat the \b Beam use case to compute the beam deviation.
 *The 4 input parameters are stored in an XML file.
 *The outputs (deviation, derivates, hessian) are stored in another XML file.
 *the output file is composed from the same input XML file, which we add the output information in the \b output balise.
 *
 */

/*!
\mainpage Use Case Beam program

\par Compilation

The build process in the sources gives :

\verbatim
cmake .
\endverbatim

which gives

\verbatim
-- The C compiler identification is GNU 4.4.7
-- The CXX compiler identification is GNU 4.4.7
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Looking for LibXml2...
-- Looking for LibXml2... -  Found
--   >> Building beam usecase code...
--     >> LIBXML2_INCLUDE_DIR /usr/include/libxml2
--     >> LIBXML2_DEFINITION
--     >> LIBXML2_LIBRARIES /usr/lib64/libxml2.so
--   >> Building beam code... - Built
-- Configuring done
-- Generating done
-- Build files have been written to: /export/home/fgaudier/JOB/beam
\endverbatim

and after, the classical instructions to make and install the external code:

\verbatim
make
make install
\endverbatim

\par Usage

\code
beam -h

 ** Usage: beam [-v] [-h|-?] [-x [file]]
      -v : Pass to the verbose mode
   -h|-? : Print the usage message
      -x : Set the input file with XML format [beam_input_with_xml.in]
\endcode 

 \par The XML input file
 The input file in XML format must contain the XPath /inputs/\@E for the E parameter, and so on for the three other parameters.

 \code
more beam.xml

<?xml version="1.0"?>
<beam>
<description name="beam" title="UseCase beam with XML input file" version="1.0" date="2014-04-07">
    <tool name="beam exe" version="1.0"/>
</description>
<inputs F= "321.0" E="3.0e9" L="2.5" I="4.0e-6"/>
<computation>
    <derivate activate="on"/>
    <hessian activate="off"/>
</computation>
</beam>
 \endcode



\par Instruction

the \b beam program is in \em "silent" mode, that it says nothing during his process
\code
beam -x beam.xml
\endcode
which gives nothing in the consale, but creates the XML output file \b "_beam_outputs_.xml"
\code
more _beam_outputs_.xml

<?xml version="1.0"?>
<beam>
<description name="beam" title="UseCase beam with XML input file" version="1.0" date="2014-04-07">
    <tool name="beam exe" version="1.0"/>
</description>
<inputs F="321.0" E="3.0e9" L="2.5" I="4.0e-6"/>
<computation>
    <derivate activate="on"/>
    <hessian activate="off"/>
</computation>
<outputs deviation="1.393229167e-01"><derivates partialE="-4.644097222e-11" partialF="4.340277778e-04" partialL="1.671875000e-01" partialI
="-3.483072917e+04"/><hessian><partialE partialE="3.096064815e-20" partialF="-1.446759259e-13" partialL="-5.572916667e-11" partialI="1.161
024306e-05"/><partialF partialF="0.000000000e+00" partialL="5.208333333e-04" partialI="-1.085069444e+02"/><partialL partialL="1.337500000e
-01" partialI="-4.179687500e+04"/><partialI partialI="1.741536458e+10"/></hessian></outputs></beam>
\endcode

To pass to the verbose mode, useconds_t the \b -v option
\code
beam -v -x beam.xml
\endcode

to obtain
\verbatim
************************
 ** The Bean use case
 ** Nb Argument [4]
 **  argument (0/4) [beam]
 **  argument (1/4) [-v]
 **  argument (2/4) [-x]
 **  argument (3/4) [beam.xml]
 ** verbose mode
 ** XML Input File[beam.xml]
************************


***********************************
 ** Beam constructor object with an XML sFile
 ** _sFile[beam.xml]
***********************************


***********************************
 ** readXMLInputs with XML file[beam.xml] ...
 ** Searching sXPath[//inputs/@E] in getValueFromXPath function ...
 ** sXPath[//inputs/@E] value[3e+09]
 ** Searching sXPath[//inputs/@F] in getValueFromXPath function ...
 ** sXPath[//inputs/@F] value[321]
 ** Searching sXPath[//inputs/@L] in getValueFromXPath function ...
 ** sXPath[//inputs/@L] value[2.5]
 ** Searching sXPath[//inputs/@I] in getValueFromXPath function ...
 ** sXPath[//inputs/@I] value[4e-06]
 ** End Of readXMLInputs with XML file
***********************************

 ** computeDeviation
 ** computeDerivates
 ** computeHessian

***********************************
 ** writeXMLOutputs in the XML file[_beam_outputs_.xml] ...
 ** End Of writeXMLOutputs with XML file
***********************************


************************
 **  beam::printLog
 ** _sFile[beam.xml]
 ** Inputs : E[3e+09] F[321] _L[2.5] I[4e-06]
 ************
 ** Output :
 **   Deviation[0.139323]
 ** Derivates :
 **   E[-4.6441e-11]
 **   F[0.000434028]
 **   L[0.167187]
 **   I[-34830.7]
 ** Hessian :
 **   i[0] : 3.09606e-20  -1.44676e-13  -5.57292e-11  1.16102e-05
 **   i[1] : -1.44676e-13  0  0.000520833  -108.507
 **   i[2] : -5.57292e-11  0.000520833  0.13375  -41796.9
 **   i[3] : 1.16102e-05  -108.507  -41796.9  1.74154e+10
************************


***********************************
 ** Destroy beam object
***********************************
\endverbatim

\par Validation of the external code

We test these external code \b beam on a LHS DoE of 1000 patterns with the Uranie macro macroLauncher.C in the \em Examples tabular.
\image html beamExternalCodeDrawPairs.png
 \example macroLauncher.C
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "beam.h"

using namespace std;

/*!
 * \brief Print the usage help command instruction
 * \param scmd (const char*) the name of the command
 */
void usage(const char *scmd)
{
    printf(" ** Usage: %s [-v] [-h|-?] [-x [file]] \n", scmd);
    printf("      -v : Pass to the verbose mode\n");
    printf("   -h|-? : Print the usage message\n");
    printf("      -x : Set the input file with XML format [beam_input_with_xml.in]\n");
}

/*!
 * \brief main
 * \param argc (int) the number of argument
 * \param argv (char *) the list of arguments
 * \return (int) 0 if success else -1 in case of error.
 */
int main(int argc, char *argv[])
{
    // Set global attributes with default values
    bool _bFileByXML = false;
    bool _bVerbose = false;
    string _sInputFile;

    // Treat the arguments
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-v")) {
            _bVerbose = true;
        }
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "-?")) {
            usage(argv[0]);
            exit(0);
        }
        if (!strcmp(argv[i], "-x")) {
            _bFileByXML = true;
            if ( i != argc-1 )
                _sInputFile = argv[i+1];
            else
                _sInputFile = "beam_input_with_xml.in";
        }
    }

    // Case of verbose mode, print the log information
    if ( _bVerbose ) {
        cout << endl << endl << "************************" << endl;
        cout << " ** The Bean use case" << endl;
        cout << " ** Nb Argument [" << argc << "]" << endl;
        for (int i = 0; i < argc; i++) {
            cout <<" **  argument (" <<i<<"/"<<argc<<") [" << argv[i] << "]" <<endl;
        }
        cout << " ** verbose mode"<<endl;
        if ( _bFileByXML) {
            cout << " ** XML Input File[" << _sInputFile << "]"<<endl;
        }
        cout << "************************" << endl << endl;
    }

    // After passing the arguments,
    //   verify that all is OK
    //   else exit
    if (_bFileByXML == false ) {
        cout << " ** ERROR : You must select the [-x] option to specify your XML file" << endl;
        usage ( argv[0]);
        exit(-1);
    }

    // Create the Beam objet to compute the deviation and so on
    beam * useCaseBeam = new beam(_sInputFile, _bVerbose);

    // Read the input attributes in the XML input file
    useCaseBeam->readXMLInputs ();

    // Compute the deviation of a beam
    useCaseBeam->computeDeviation ();

    // Compute the derivates
    useCaseBeam->computeDerivates ();

    // Compute the hessian
    useCaseBeam->computeHessian ();

    // Write the output XML File
    useCaseBeam->writeXMLOutputs ("_beam_outputs_.xml");

    if ( _bVerbose ) {
        useCaseBeam->printLog();
    }

    // Clean
    delete useCaseBeam;

    return 0;
}

