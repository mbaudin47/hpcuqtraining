/*!
 * \file beam.h
 * \brief Definition of the beam object
*/
#ifndef BEAM_H
#define BEAM_H
#include <string>

// LibXML2
#include <libxml/xpathInternals.h>

/*!
 * \class beam
 * \brief The classe beam to compute and store the output from 4 parameters stored in a XML file
 *
 *This class implements the beam usecase.
 *
 *The formula of the deviation of a beam is given by:
 \f[
    y = \frac{FL^{3}}{3EI}
 \f]
 *where the variables are:
 *\li \f$ E\f$
 *\li \f$ F\f$
 *\li \f$ L\f$
 *\li \f$ I\f$
 *
 * The values of the 4 parameters are readed from the XML file.
 *
 *
 \code
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
 *
 * The deriavtes are computed in the \see computeDerivates method

 */

using namespace std;

class beam
{

    //---------------------------------------------
    /** @name Attributes to the constructor
     *
     * The alone parameter for the constructor is the XML file which contains the value of the 4 parameters.
     * The boolean flag _bVerbose to print the log
    * For example,
    \code
    <?xml version="1.0"?>
    <beam>
    <description name="beam" title="UseCase beam with XML input file" version="1.0" date="2014-04-07">
      <tool name="beam exe" version="1.0"/>
    </description>
    <inputs F= "321.0" E="3.0e9" L="2.5" I="4.0e-6">
    <derivate activate="on"/>
    <hessian activate="off"/>
    </inputs>
    </beam>
    \endcode
    **/
    //@{
    string _sFile;                  ///< The XML file to read the values of the 4 input parameters
    bool _bVerbose;                  ///< A boolean if printing the log
    //@}
    //---------------------------------------------

    //---------------------------------------------
    /** @name The inputs parameters
     *The values of 4 inputs parameters stored in the XML File.
     *This values can not be set by a set method.
    **/
    //@{
    double _dE;                     ///< The value of the E parameter (-1 default value)
    double _dF;                     ///< The value of the F parameter (-1 default value)
    double _dL;                     ///< The value of the L parameter (-1 default value)
    double _dI;                     ///< The value of the I parameter (-1 default value)
    //@}
    //---------------------------------------------

    //---------------------------------------------
    /** @name The computed informations
     *
     *\li The value of the deviation \f$ y\f$ given by the formula.
     *\li The derivates of the deviation \f$ y\f$ for each input parameter
     *This values will be stored in a XML file, different from the input XML file.
    **/
    //@{
    double _dY;                     ///< The value of deviation computed from the 4 parameters (-1 default value)
    double * _vecDerivate;          ///< The vector of derivates of the deviation \f$ y\f$ for each input parameters
    double **_matHessian;           ///< The matrix of hessian
    //@}
    //---------------------------------------------

public:
    //---------------------------------------------
    /** @name Constructor and destructor
    **/
    //@{
    /*!
     * \brief Constructor of the beam object with the XML File which contains the values of the 4 parameters
     * \param sFile (string) the XML file where the four parameters are stored
     * \param bVerbose (boolean) the flag to print the Log
     */
    beam(string sFile = "alpha.xml", bool bVerbose = false);
    /*!
     * \brief Destructor of the beam object
     *Delete the vector of derivates if not NULL
     **/
    ~beam();
    //@}
    //---------------------------------------------

    //---------------------------------------------
    /** @name Input/Output in XML format
    **/
    //@{
    /*!
     * \brief Read and set the values of the 4 parameters in the XML file.
     *
    For example,
\code
 <?xml version="1.0"?>
<beam>
<description name="beam" title="UseCase beam with XML input file" version="1.0" date="2014-04-07">
  <tool name="beam exe" version="1.0"/>
</description>
<inputs F= "321.0" E="3.0e9" L="2.5" I="4.0e-6">
<derivate activate="on"/>
<hessian activate="off"/>
</inputs>
</beam>
 \endcode
     *
     The XPath to read the value for each parameter is then:
     \li for \f$ E\f$ : \em "//inputs/@E"
     \li for \f$ F\f$ : \em "//inputs/@F"
     \li for \f$ L\f$ : \em "//inputs/@L"
     \li for \f$ I\f$ : \em "//inputs/@I"

     */
    void readXMLInputs();
    /*!
     * \brief Save the results in an XML output file
     *
     * \param sXMLFile (string) the name of the output XML file to store all the computations (deviation, derivates and hessian).
    */
    void writeXMLOutputs(string sXMLFile);
    //@}
    //---------------------------------------------


    //---------------------------------------------
    /** @name Computation
     *These methods apply computations (deviation, derivates and hessian).
    **/
    //@{
    /*!
     * \brief Compute the deviation of the beam
     *
     * The formula of the deviation is given \f[ Y= \frac{F*L^{3}}{3EI}\f]
     */
    void computeDeviation();
    /*!
     * \brief Compute the derivates of the deviation from all the 4 inputs parameters
     *
     * The derivates of the deviation \f$ y \f$ from each variables are :
        \li from \f$ E\f$
        \f[
        \frac{\partial y}{\partial E} \quad = \quad \frac{FL^{3}}{3I} \times \frac{-1.0}{E^2} \quad = \quad \frac{-1.0 \times y}{E}
        \f]
        \li from \f$ F\f$
        \f[
        \frac{\partial y}{\partial F} \quad = \quad \frac{L^{3}}{3EI} \quad = \quad \frac{y}{F}
        \f]
        \li from \f$ L\f$
        \f[
        \frac{\partial y}{\partial L} \quad = \quad \frac{F}{3EI} \times 3.0 L^{2}\quad = \quad \frac{3.0 \times y}{L}
        \f]
        \li from \f$ I\f$
        \f[
        \frac{\partial y}{\partial I} \quad = \quad \frac{FL^{3}}{3E} \times \frac{-1.0}{I^2} \quad = \quad \frac{-1.0 \times y}{I}
        \f]
     */
    void computeDerivates();
    /*!
     \brief Compute the hessian;

     We use essentially \f[ (\frac{u}{v})^{'} \quad = \quad \frac{u^{'} v - u v^{'}}{v^2}\f]

     \li The first derivate of \f$ y \f$ from \f$ E \f$ is : \f$ \frac{\partial y}{\partial E} = -1.0 \quad \frac{y}{E}\f$
     \f[
     \frac{\partial^2 y}{\partial E\partial E} \quad = \quad -1.0 \quad \frac{ -1.0 * y - y * 1.0 }{E^2} \quad = \quad \frac{ 2.0 * y}{E^2}
     \f]
     \f[
     \frac{\partial^2 y}{\partial F\partial E} \quad = \quad \frac{-1.0}{E} \quad \frac{\partial y}{\partial F} \quad = \quad \frac{ -1.0 * y}{E F}
     \f]
     \f[
     \frac{\partial^2 y}{\partial L\partial E} \quad = \quad \frac{-1.0}{E} \quad \frac{\partial y}{\partial L} \quad = \quad \frac{ -3.0 * y}{E L}
     \f]
     \f[
     \frac{\partial^2 y}{\partial I\partial E} \quad = \quad \frac{-1.0}{E} \quad \frac{\partial y}{\partial I} \quad = \quad \frac{y}{E I}
     \f]
     \li The first derivate of \f$ y \f$ from \f$ F \f$ is : \f$ \frac{\partial y}{\partial F} \quad = \quad \frac{y}{F}\f$
     \f[
     \frac{\partial^2 y}{\partial F\partial F} \quad = \quad \frac{ y - y }{F^2} \quad = \quad 0.0
     \f]
     \f[
     \frac{\partial^2 y}{\partial L\partial F} \quad = \quad \frac{1.0}{F} \quad \frac{\partial y}{\partial L} \quad = \quad \frac{ 3.0 * y}{F L}
     \f]
     \f[
     \frac{\partial^2 y}{\partial I\partial F} \quad = \quad \frac{1.0}{F} \quad \frac{\partial y}{\partial I} \quad = \quad \frac{ -1.0 * y}{F I}
     \f]
     \li The first derivate of \f$ y \f$ from \f$ L \f$ is : \f$ \frac{\partial y}{\partial L} \quad = \quad \frac{3.0 \times y}{L}\f$
     \f[
     \frac{\partial^2 y}{\partial L\partial L} \quad = \quad 3.0 \quad \frac{ 3.0 \times y - y }{L^2} \quad = \quad \frac{6.0 \times y}{L^2}
     \f]
     \f[
     \frac{\partial^2 y}{\partial I\partial L} \quad = \quad \frac{3.0}{L} \quad \frac{\partial y}{\partial I} \quad = \quad \frac{ -3.0 \times y}{L I}
     \f]
     \li The first derivate of \f$ y \f$ from \f$ I \f$ is : \f$ \frac{\partial y}{\partial E} = -1.0 \quad \frac{y}{I}\f$
     \f[
     \frac{\partial^2 y}{\partial I\partial I} \quad = \quad -1.0 \quad \frac{ -1.0 * y - y * 1.0 }{I^2} \quad = \quad \frac{ 2.0 * y}{I^2}
     \f]
     */
    void computeHessian();
    //@}
    //---------------------------------------------

    //---------------------------------------------
    /** @name Treat the Log
    **/
    //@{
    /*!
    /*! * \brief Print the log with the current values of the attributes
    /*! */
    void printLog();
    /*!
     * \brief Set the boolean log attribute to \em true
     */
    void setUnsilent(){ _bVerbose = true;}
    /*!
     * \brief Set the boolean log attribute to \em false
     */
    void setSilent() { _bVerbose = false;}
    //@}
    //---------------------------------------------

private:
    /*!
     * \brief getValueFromXPath
     * \param sXPath the XPath where stored the inputs parameter
     * \param xpathCtx the XML XPath context by the XML file
     * \return the double value of the balise in the XML XPath context
     */
    double getValueFromXPath(string sXPath, xmlXPathContextPtr xpathCtx);


};

#endif // BEAM_H
