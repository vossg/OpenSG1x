/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef OSG_NOFUNCTORS
#include <OSGFunctors.h>
#endif

#include <OSGWindowBase.h>

OSG_BEGIN_NAMESPACE

class DrawAction;
class RenderAction;

//! The abstract base for all windows

class OSG_SYSTEMLIB_DLLMAPPING Window : public WindowBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum GLObjectStatusE {
        notused=1, initialize, reinitialize, initialized,
        needrefresh, destroy, finaldestroy };

#ifdef OSG_NOFUNCTORS
    typedef void (*FunctorFunc)(Window*, UInt32);

    struct GLObjectFunctor
    {
       public:

        FunctorFunc _func;

        virtual void call(Window *win, UInt32 uiOpt)
        {
            _func(win, uiOpt);
        }
    };

    static GLObjectFunctor osgFunctionFunctor2(FunctorFunc func)
    {
        GLObjectFunctor result;

        result._func = func;

        return result;
    }
#else
    typedef Functor2Base<void,Window*,UInt32> GLObjectFunctor;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Window"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                         ChangeMode from);

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

    Bool            hasExtension      ( UInt32 id );
    void           *getFunction       ( UInt32 id );
    void            dumpExtensions    ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             GL object registration                           */
    /*! \{                                                                 */

    static UInt32   registerGLObject  (GLObjectFunctor functor, UInt32 num);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               GL object handling                             */
    /*! \{                                                                 */

    void            validateGLObject    (UInt32 id);
    GLObjectStatusE getGLObjectStatus   (UInt32 id);
    static void     refreshGLObject     (UInt32 id);
    static void     reinitializeGLObject(UInt32 id);
    static void     destroyGLObject     (UInt32 id, UInt32 num);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Size handling                                */
    /*! \{                                                                 */

            Bool isResizePending( void );

    virtual void resize         (int width, int height);
    virtual void resizeGL       (void);

            void setSize        (UInt16 width, UInt16 height);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Drawing                                   */
    /*! \{                                                                 */

    virtual void    draw              ( DrawAction *action = NULL );
    virtual void    drawAllViewports  ( DrawAction *action = NULL );

    virtual void    render            ( RenderAction *action = NULL );
    virtual void    renderAllViewports( RenderAction *action = NULL );

    virtual void    frameInit        (void);
    virtual void    frameExit        (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name            GL implementation functions                       */
    /*! \{                                                                 */

    virtual void    (*getFunctionByName ( const Char8 *s ))() = 0;

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

    static const WindowPtr NullWindow;

    /*---------------------------------------------------------------------*/
    /*! \name           GL object handling helper class                    */
    /*! \{     
                                                                */
    class GLObject {

      public:
        GLObject( GLObjectFunctor funct ) :
            functor( funct ), refCounter( 0 )
        {}

        GLObjectFunctor& getFunctor ( void )
        {
            return ( functor );
        };

        void setFunctor ( GLObjectFunctor funct )
        {
            functor = funct;
        };

        UInt32 getRefCounter ( void )
        {
            return ( refCounter );
        }

        UInt32 incRefCounter ( void )
        {
            UInt32 val;

            if ( ! _GLObjectLock )
            {
                _GLObjectLock = ThreadManager::the()->getLock(NULL);
            }

            _GLObjectLock->aquire();
            val = refCounter = refCounter + 1;
            _GLObjectLock->release();

            return val;
        }

        UInt32 decRefCounter ( void )
        {
            UInt32 val;

            if ( ! _GLObjectLock )
            {
                _GLObjectLock = ThreadManager::the()->getLock(NULL);
            }

            _GLObjectLock->aquire();
            if ( refCounter )
                val = refCounter = refCounter - 1;
            else
                val = 0;
            _GLObjectLock->release();

            return val;
        }

      protected:
        GLObjectFunctor functor;
        volatile UInt32 refCounter;
    };

    friend class GLObject;

    /*! \}                                                                 */
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

    virtual void setupGL( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                GL object handling                            */
    /*! \{                                                                 */

    void doRefreshGLObject     ( UInt32 id );
    void doReinitializeGLObject( UInt32 id );

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef WindowBase Inherited;

    friend class FieldContainer;
    friend class WindowBase;

    static char cvsid[];

    /*! global window list, needed by static refreshGLObject */
    static vector<WindowPtr>          _allWindows;

    /*---------------------------------------------------------------------*/
    /*! \name   Static GL Object / Extension variables                     */
    /*! \{                                                                 */

    static vector<IDStringLink>         _registeredExtensions;
    static vector<IDStringLink>         _registeredFunctions;
    static Lock                      *_GLObjectLock;
    static vector<GLObject*>          _glObjects;
    static vector<UInt32>             _glObjectDestroyList;

    /*! \}                                                                 */

    static void initMethod( void );

    /*---------------------------------------------------------------------*/
    /*! \name        GL Object / Extension variables                       */
    /*! \{                                                                 */

    //! contains the split glGetString(GL_EXTENSIONS)
    vector<IDString>                  _extensions;

    /*! contains a boolean for every registered extension which
       indicates, whether an extensions is available for the Window's
       context or not  */
    vector<Bool>                      _availExtensions;

    //! contains the GL extension functions registered by the application
    vector<void*>                     _extFunctions;

    //! register/unregister the instance with the global list
    void onCreate(  const FieldContainer &  );
    void onDestroy( void );

    /*! \}                                                                 */

    // prohibit default functions (move to 'public' if you need one)

    Window& operator =(const Window &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Window *WindowP;

OSG_END_NAMESPACE

#include <OSGWindow.inl>
#include <OSGWindowBase.inl>

#endif /* _OSGWINDOW_H_ */
