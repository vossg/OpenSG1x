#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <map>
#include <sstream>

#include <OSGConfig.h>
#include <OSGStreamSocket.h>
#include <OSGBaseTypes.h>
#include <OSGNode.h>
#include <OSGIDString.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING WebInterface {
    /*==========================  PUBLIC  =================================*/
public:
    typedef std::map<IDString,IDString> ParameterT;
    typedef void (WebInterface::*MethodT)(      std::ostream &,
                                          const char*,
                                                ParameterT   &);

    typedef std::map<IDString, MethodT> HandlerT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WebInterface(UInt32 port=8888);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WebInterface();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  request handling                            */
    /*! \{                                                                 */

    void handleRequests(void              );
    bool waitRequest   (double duration=-1);
    void flush         (void              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void    setRoot(NodePtr root);
    void    setChangeList(ChangeList *clist);
    
    void                setHeader(const std::string &header);
    void                setFooter(const std::string &footer);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          NodePtr        getRoot  (void);
    
    const std::string   &getHeader(void);
    const std::string   &getFooter(void);
    
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

    std::string createFCViewReference(      FieldContainerPtr fcPtr,
                                            UInt32            id=0  );

    const char *getParam             (      ParameterT       &param,
                                      const char             *name  );

    void        setParam             (      ParameterT       &param,
                                      const char             *name ,
                                      const char             *value );
                                      
    void        treeViewNode         (std::ostream     &os,
                                      NodePtr           node,
                                      ParameterT       &param );
                                      
    const char *getNodeName          (const FieldContainerPtr &fcPtr);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool        checkRequest         (std::string &url        );
    std::string getDefaultHeader     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  web page handler                            */
    /*! \{                                                                 */

    void rootHandler      (std::ostream &os,
                           const char   *path,ParameterT &param);
    void changelistHandler(std::ostream &os,
                           const char   *path,ParameterT &param);
    void fcViewHandler    (std::ostream &os,
                           const char   *path,ParameterT &param);
    void fcEditHandler    (std::ostream &os,
                           const char   *path,ParameterT &param);
    void treeViewHandler  (std::ostream &os,
                           const char   *path,ParameterT &param);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  private members                             */
    /*! \{                                                                 */

    StreamSocket      _socket;
    StreamSocket      _accepted;
    std::stringstream _body;
    HandlerT          _handler;
    NodePtr           _root;
    std::string       _header;
    std::string       _footer;
    ChangeList       *_clist;
    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#endif
