#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <map>
#include <sstream>

#include <OSGConfig.h>
#include <OSGStreamSocket.h>
#include <OSGBaseTypes.h>
#include <OSGNode.h>

using namespace osg;

class OSG_SYSTEMLIB_DLLMAPPING WebInterface {
    /*==========================  PUBLIC  =================================*/
public:
    typedef std::map<std::string,std::string> ParameterT;
    typedef void (WebInterface::*MethodT)(std::ostream &,std::string &,ParameterT &);
    typedef std::map<std::string,MethodT> HandlerT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WebInterface(UInt32 port=8888);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~WebInterface();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  request handling                            */
    /*! \{                                                                 */

    void handleRequests(void              );
    bool waitRequest   (double duration=-1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setRoot(NodePtr root);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:
    /*---------------------------------------------------------------------*/
    /*! \name                handler management                            */
    /*! \{                                                                 */

    void addHandler(char *key,MethodT method);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                url encoding/decoding                         */
    /*! \{                                                                 */

    std::string encodeUrl(const std::string &path,
                          const ParameterT  &param);
    void        decodeUrl(const std::string &url,
                                std::string &path,
                                ParameterT  &param);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    std::string createFCViewReference(FieldContainerPtr fcPtr,
                                      UInt32            id=0  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool        checkRequest         (std::string &url        );
    void        treeViewNode         (std::ostream     &os,
                                      NodePtr           node,
                                      ParameterT       &param );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  web page handler                            */
    /*! \{                                                                 */

    void rootHandler      (std::ostream &os,
                           std::string  &path,ParameterT &param);
    void changelistHandler(std::ostream &os,
                           std::string  &path,ParameterT &param);
    void fcViewHandler    (std::ostream &os,
                           std::string  &path,ParameterT &param);
    void fcEditHandler    (std::ostream &os,
                           std::string  &path,ParameterT &param);
    void treeViewHandler  (std::ostream &os,
                           std::string  &path,ParameterT &param);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  private members                             */
    /*! \{                                                                 */

    StreamSocket      _socket;
    StreamSocket      _accepted;
    std::stringstream _body;
    HandlerT          _handler;
    NodePtr           _root;

    /*! \}                                                                 */
};

#endif
