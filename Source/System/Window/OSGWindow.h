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

#include <OSGConfig.h>

#include <list>
#include <utility>

#include <OSGTypedFunctors.h>

#include <OSGWindowBase.h>

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
    void subPort      (      UInt32       portIndex);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Extension registration                           */
    /*! \{                                                                 */

    static UInt32   registerExtension ( const Char8 *s );
    static UInt32   registerFunction  ( const Char8 *s );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Extension handling                             */
    /*! \{                                                                 */

    bool                 hasExtension      (      UInt32  id);
    void                *getFunction       (      UInt32  id);
    void                *getFunctionNoCheck(      UInt32  id);
    void                 dumpExtensions    (      void      );
    GLExtensionFunction  getFunctionByName (const Char8  *s );
    
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
    GLObjectStatusE getGLObjectStatus   (UInt32 id);
    static void     refreshGLObject     (UInt32 id);
    static void     reinitializeGLObject(UInt32 id);
    static void     destroyGLObject     (UInt32 id, UInt32 num);
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

    // is this really needed???    friend class GLObject;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef WindowBase Inherited;

    friend class FieldContainer;
    friend class WindowBase;

    static std::vector<WindowPtr> _allWindows;
    static UInt32                 _currentWindowId;

    static void initMethod( void );

    void onCreate      (const Window *source = NULL);
    void onCreateAspect(const Window *source = NULL);

    void onDestroy( void );

    /*---------------------------------------------------------------------*/
    /*! \name   Static GL Object / Extension variables                     */
    /*! \{                                                                 */

    static Lock                      *_GLObjectLock;
    static std::vector<std::string>   _registeredExtensions;
    static std::vector<std::string>   _registeredFunctions;
    static std::vector<GLObject   *>  _glObjects;

    typedef std::pair<UInt32,UInt32>   DestroyEntry;
    static  std::list<DestroyEntry >  _glObjectDestroyList;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name        GL Object / Extension variables                       */
    /*! \{                                                                 */

    std::vector<UInt32     > _lastValidate;
  
    std::vector<std::string> _extensions;
    std::vector<bool       > _availExtensions;
    std::vector<void      *> _extFunctions;

    /*! \}                                                                 */

    UInt32                   _windowId;

    // prohibit default functions (move to 'public' if you need one)

    Window& operator =(const Window &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Window *WindowP;

OSG_END_NAMESPACE

#include <OSGWindowBase.inl>
#include <OSGWindow.inl>

#define OSGWINDOW_HEADER_CVSID "@(#)$Id:$"

#endif /* _OSGWINDOW_H_ */
