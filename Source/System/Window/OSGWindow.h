/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/


#ifndef _OSGWINDOW_H_
#define _OSGWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include <list>
#include <utility>

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include "OSGTypedFunctors.h"

#include "OSGWindowBase.h"

OSG_BEGIN_NAMESPACE

class DrawAction;
class RenderActionBase;

/*! \brief Window base class. See \ref PageSystemWindowWindow 
for a description. */

class OSG_SYSTEMLIB_DLLMAPPING Window : public WindowBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum GLObjectStatusE 
    {
        notused      = 1, 
        initialize, 
        reinitialize, 
        initialized,
        needrefresh, 
        destroy, 
        finaldestroy 
    };

    enum { invalidExtensionID = 0x7fffffff, invalidFunctionID = 0x7fffffff };

    // max status value = 7, 3 bit shift is enough 
    enum { statusShift = 3, statusMask = 7 }; 

    static const Real32 unknownConstant;    
    
    typedef ArgsCollector<UInt32>                      GLObjectFunctorArgs;

    typedef TypedVoidFunctor2Base<PtrCallArg<Window> , 
                                  GLObjectFunctorArgs> GLObjectFunctor;

    typedef void (*GLExtensionFunction)(void);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Window"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         UInt32     origin   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Viewport handling                             */
    /*! \{                                                                 */

    void addPort      (const ViewportPtr &portP);
    void insertPort   (      UInt32       portIndex,
                       const ViewportPtr &portP);

    void replacePort  (      UInt32       portIndex,
                       const ViewportPtr &portP);
    void replacePortBy(const ViewportPtr &portP,
                       const ViewportPtr &newPortP);

    void subPort      (const ViewportPtr &portP);
    void subPortByObj (const ViewportPtr &portP);
    void subPort      (      UInt32       portIndex);

    void clearPorts   (      void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Extension registration                           */
    /*! \{                                                                 */

    static UInt32   registerExtension ( const Char8 *s   );
    static void     ignoreExtensions  ( const Char8 *s   );

    static UInt32   registerFunction  ( const Char8 *s,  Int32 ext = -1,
                                                         UInt32 version = 0xffff);

    static void     registerConstant  (       GLenum val );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Extension handling                             */
    /*! \{                                                                 */

    static 
    inline void                 setGLLibraryName  (const Char8  *s   );

    inline UInt32               getGLVersion      (      void        );

    static 
    inline Int32                getExtensionId    (const Char8  *s   );
    inline bool                 hasExtension      (      UInt32  id  );
           bool                 hasExtension      (const Char8  *s   );
    static 
    inline bool                 hasCommonExtension(      UInt32  id  );
           GLExtensionFunction  getFunction       (      UInt32  id  );
           GLExtensionFunction  getFunctionNoCheck(      UInt32  id  );
           void                 dumpExtensions    (      void        );
           GLExtensionFunction  getFunctionByName (const Char8  *s   );
    inline Real32               getConstantValue  (      GLenum  val );
           const  Vec2f        &getConstantValuev (      GLenum  val );    
    
    static  
    inline const std::vector<std::string> &getRegisteredExtensions(void);   
    inline const std::vector<std::string> &getRegisteredFunctions (void);   
    inline const std::vector<std::string> &getExtensions          (void);
    inline const std::vector<std::string> &getIgnoredExtensions   (void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             GL object registration                           */
    /*! \{                                                                 */

    static UInt32   registerGLObject  (GLObjectFunctor functor, 
                                       UInt32 num = 1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               GL object handling                             */
    /*! \{                                                                 */

    void            validateGLObject    (UInt32 id);
    void            validateAllGLObjects(void);
    //GLObjectStatusE getGLObjectStatus   (UInt32 id);
    inline void     setGLObjectId       (UInt32 id, UInt32 id2);
    inline UInt32   getGLObjectId       (UInt32 id);
    static
    inline  UInt32  getGLObjectsSize    (void);

    static void     refreshGLObject     (UInt32 id);
    static void     refreshAllGLObjects (void);
    static void     reinitializeGLObject(UInt32 id);
    static void     reinitializeAllGLObjects(void);
    static void     destroyGLObject     (UInt32 id, UInt32 num = 1);
    static inline void unpackIdStatus   (UInt32 idstatus, UInt32 &id, 
                                                GLObjectStatusE &status);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Size handling                                */
    /*! \{                                                                 */

            bool isResizePending( void );

    virtual void resize         (int width, int height);
    virtual void resizeGL       (void);

            void setSize        (UInt16 width, UInt16 height);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Drawing                                   */
    /*! \{                                                                 */

    virtual void    frameInit        (void); 
    virtual void    frameExit        (void);

    virtual void    draw              ( DrawAction   *action = NULL );
    virtual void    drawAllViewports  ( DrawAction   *action = NULL );

    virtual void    render            (RenderActionBase *action = NULL);
    virtual void    renderAllViewports(RenderActionBase *action = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      Window system implementation functions                  */
    /*! \{                                                                 */

    virtual void init       ( void ) = 0;
    virtual void activate   ( void ) = 0;
    virtual void deactivate ( void ) = 0;
    virtual void swap       ( void ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Window(void);
    Window(const Window &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Window(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL setup handling                             */
    /*! \{                                                                 */

    virtual void setupGL(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL object handling                            */
    /*! \{                                                                 */

    static        void   initRegisterGLObject  (UInt32 id, UInt32 num);

    static inline UInt32 packIdStatus          (UInt32 id, 
                                                GLObjectStatusE status);

                  void   doInitRegisterGLObject(UInt32 id, UInt32 num);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name           GL object handling helper class                    */
    /*! \{                                                                 */

    class GLObject;

    friend class GLObject;

    class GLObject {

      public:
        GLObject(GLObjectFunctor funct);

        GLObjectFunctor& getFunctor(void                 );
        void             setFunctor(GLObjectFunctor funct);

        UInt32 getLastValidate(void      );
        void   setLastValidate(UInt32 val);

        UInt32 getRefCounter(void);
        UInt32 incRefCounter(void);
        UInt32 decRefCounter(void);
 
      protected:
        GLObjectFunctor _functor;
        volatile UInt32 _refCounter;
                 UInt32 _lastValidate;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            Map for GL cvonstant handling                     */
    /*! \{                                                                 */

#ifdef OSG_STL_HAS_HASH_MAP
    typedef 
        OSG_STDEXTENSION_NAMESPACE::hash_map<
            GLenum,  
            Vec2f> ConstHash;
#else
    typedef 
        std::map< GLenum,  Vec2f > ConstHash;
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef WindowBase Inherited;

    friend class FieldContainer;
    friend class WindowBase;

    static std::vector<WindowPtr> _allWindows;
    static UInt32                 _currentWindowId;

    static void initMethod(void);

    void onCreate      (const Window *source = NULL);
    void onCreateAspect(const Window *aspect0,
                        const Window *source = NULL);

    void onDestroy(void);

    static void staticAcquire(void);
    static void staticRelease(void);

    /*---------------------------------------------------------------------*/
    /*! \name   Static GL Object / Extension variables                     */
    /*! \{                                                                 */

    static Lock                      *_GLObjectLock;
    static Lock                      *_staticWindowLock;
    static std::vector<GLObject  *>   _glObjects;
    static const Char8               *_glLibraryName;

    static std::vector<std::string>   _registeredExtensions;
    static std::vector<std::string>   _ignoredExtensions;
    static std::vector<bool       >   _commonExtensions;
    static std::vector<std::string>   _registeredFunctions;
    static std::vector<Int32      >   _registeredFunctionExts;
    static std::vector<UInt32     >   _registeredFunctionVersions;

    static std::vector<GLenum     >   _registeredConstants;

    typedef std::pair<UInt32,UInt32>   DestroyEntry;
    std::list<DestroyEntry >  _glObjectDestroyList;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name        GL Object / Extension variables                       */
    /*! \{                                                                 */
    
    std::vector<UInt32             > _lastValidate;
    std::vector<UInt32             > _ids;

    UInt32                           _glVersion;
    std::vector<std::string        > _extensions;
    std::vector<bool               > _availExtensions;
    std::vector<GLExtensionFunction> _extFunctions;
    ConstHash                        _availConstants;
    UInt32                           _numAvailConstants;

    /*! \}                                                                 */

    UInt32                           _windowId;

    // prohibit default functions (move to 'public' if you need one)

    Window& operator =(const Window &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Window *WindowP;

OSG_END_NAMESPACE

#include "OSGWindowBase.inl"
#include "OSGWindow.inl"

#define OSGWINDOW_HEADER_CVSID "@(#)$Id:$"

#endif /* _OSGWINDOW_H_ */
