/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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


#ifndef _OSGFUNCTORS_H_
#define _OSGFUNCTORS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief OSGFunctorBase
 */

struct OSGDefaultFunctorSizeTraits
{
    typedef 
        void (                             *OSGFuncPointerT        )(void *);
    typedef 
        void (OSGDefaultFunctorSizeTraits::*OSGInstanceFuncPointerT)(void *);

    enum OSGSizesE
    { 
        _uiFuncPointerSize = OSGMax<sizeof(OSGFuncPointerT),
                                    sizeof(OSGInstanceFuncPointerT) >::iMax,

        _uiObjectSize      = 64
    };
};

enum OSGFunctorMethodCallTypeE
{
    OSGOnArgument,
    OSGOnStoredObject,
    
    OSGOnStoredCPtr,
    OSGOnCPtrArgument
};

template <class OSGRetT, class OSGObjectTypeT>
struct OSGFunctorBuildFuncType1
{
    typedef typename OSGObjectTypeT::OSGObjectType OSGObjectType;

    typedef OSGRetT (OSGObjectType::*OSGFunctionType)();
};

template <class OSGRetT, class OSGArg1T, class OSGObjectTypeT>
struct OSGFunctorBuildFuncType2
{
    typedef typename OSGObjectTypeT::OSGObjectType OSGObjectType;

    typedef          OSGRetT (OSGObjectType::*OSGFunctionType)(OSGArg1T);
};

template <class OSGRetT, class OSGArg1T, class OSGArg2T, class OSGObjectTypeT>
struct OSGFunctorBuildFuncType3
{
    typedef typename OSGObjectTypeT::OSGObjectType OSGObjectType;

    typedef          OSGRetT (OSGObjectType::*OSGFunctionType)(OSGArg1T,
                                                               OSGArg2T);
};

template <class OSGSizeTraitsT = OSGDefaultFunctorSizeTraits>
class OSGFunctorBase 
{     
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static const OSGUInt8 OSGObjectValid;
    static const OSGUInt8 OSGFuncPtrValid;

    static const OSGUInt8 OSGFunctorActive;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    // for testing

    char     _data1[OSGSizeTraitsT::_uiObjectSize];
    char     _data2[OSGSizeTraitsT::_uiFuncPointerSize];
    OSGUInt8 _flags;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctorBase(void);
    OSGFunctorBase(const OSGFunctorBase &source);

    void operator =(const OSGFunctorBase &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~OSGFunctorBase(void); 
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGSizeTraitsT = OSGDefaultFunctorSizeTraits>
class OSGFunctor1Base : public OSGFunctorBase<OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctorBase<OSGSizeTraitsT> Inherited;


    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctor1Base(void);
    OSGFunctor1Base(const OSGFunctor1Base &source);
    
    virtual ~OSGFunctor1Base(void); 

    /*------------------------- your_category -------------------------------*/

    virtual OSGRetT call(OSGArg1T arg1);

    void operator =(const OSGFunctor1Base &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGArg1T, 
          class OSGSizeTraitsT>
class OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT> : 
    public OSGFunctorBase<OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctorBase<OSGSizeTraitsT> Inherited;


    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctor1Base(void);
    OSGFunctor1Base(const OSGFunctor1Base &source);
    
    virtual ~OSGFunctor1Base(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void call(OSGArg1T arg1);

    void operator =(const OSGFunctor1Base &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGRetT, 
          class OSGArg1T,
          class OSGSizeTraitsT = OSGDefaultFunctorSizeTraits>
class OSGFunctionFunctor1 : 
    public OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGRetT (*OSGFunctionP)(OSGArg1T);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGFunctionFunctor1 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctionFunctor1(void);
    OSGFunctionFunctor1(const OSGFunctionFunctor1 &source);
    
    virtual ~OSGFunctionFunctor1(void); 

    /*----------------------------- access ----------------------------------*/

    void setFunction(OSGFunctionP pFunc);

    /*------------------------- your_category -------------------------------*/

    virtual OSGRetT call(OSGArg1T arg1);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGArg1T,
          class OSGSizeTraitsT>
class OSGFunctionFunctor1<void, OSGArg1T, OSGSizeTraitsT> : 
    public OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void (*OSGFunctionP)(OSGArg1T);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGFunctionFunctor1 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctionFunctor1(void);
    OSGFunctionFunctor1(const OSGFunctionFunctor1 &source);
    
    virtual ~OSGFunctionFunctor1(void); 

    /*----------------------------- access ----------------------------------*/

    void setFunction(OSGFunctionP pFunc);

    /*------------------------- your_category -------------------------------*/

    virtual void call(OSGArg1T arg1);
};


template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType>
struct OSGFunctorTraits1
{
};


template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT,
                         OSGArg1T *, 
                         OSGObjectT, 
                         OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T *arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        return ((arg1)->*pFunc)();
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, char *, OSGArg1T *)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char *pData2, OSGArg1T *arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T *)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT,
                         OSGArg1T &, 
                         OSGObjectT, 
                         OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T &arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        return ((&arg1)->*pFunc)();
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, char *, OSGArg1T &)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char *pData2, OSGArg1T &arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T &)
    {

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T &, OSGObjectT, OSGOnCPtrArgument>
{
    typedef typename OSGObjectT::OSGObjectType OSGObjectType;

    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodT   )(void);
    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T &arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        return ((&(*arg1))->*pFunc)();
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, char *, OSGArg1T &)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char *pData2, OSGArg1T &arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        ((&(*arg1))->*pFunc)();
    }

    static void callObjectMethodVoid(char     *,
                                     char     *, 
                                     OSGArg1T &)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T, OSGObjectT &, OSGOnStoredCPtr>
{
    typedef typename OSGObjectT::OSGObjectType OSGObjectType;

    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodT   )(void);
    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, OSGArg1T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static OSGRetT callObjectMethod(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);
        
        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
        
        return (&(**pObj)->*pFunc)(arg1);
    }

    static void callObjectMethodVoid(char *, OSGArg1T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);
        
        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
        
        (&(**pObj)->*pFunc)(arg1);
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T &, OSGObjectT *, OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT *OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT **) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static OSGRetT callObjectMethod(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, OSGArg1T arg1)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T *, OSGObjectT *, OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT *OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT **) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((arg1)->*pFunc)();
    }

    static OSGRetT callObjectMethod(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, OSGArg1T arg1)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T, OSGObjectT *, OSGOnStoredObject>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT *OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT **) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, OSGArg1T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static OSGRetT callObjectMethod(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGObjectT *pObj = *((OSGObjectT **) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1);
    }


    static void callObjectMethodVoid(char *, OSGArg1T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGObjectT *pObj = *((OSGObjectT **) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
            
        (pObj->*pFunc)(arg1);
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T &, OSGObjectT &, OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static OSGRetT callObjectMethod(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, OSGArg1T arg1)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T *, OSGObjectT &, OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((arg1)->*pFunc)();
    }

    static OSGRetT callObjectMethod(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, OSGArg1T arg1)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, OSGArg1T arg1)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT>
struct OSGFunctorTraits1<OSGRetT, OSGArg1T, OSGObjectT &, OSGOnStoredObject>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(void);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, OSGArg1T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static OSGRetT callObjectMethod(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1);
    }

    static void callObjectMethodVoid(char *, OSGArg1T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, OSGArg1T arg1)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
        
        (pObj->*pFunc)(arg1);
    }
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGRetT, 
          class OSGArg1T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT = OSGDefaultFunctorSizeTraits>
class OSGObjectFunctor1 : 
    public OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef
        OSGFunctorTraits1<OSGRetT,
                          OSGArg1T, 
                          OSGObjectT, 
                          osgMethodCallType> OSGFunctorTrait;

    typedef typename OSGFunctorTrait::OSGObjectMethodT    OSGObjectMethodT;
    typedef typename OSGFunctorTrait::OSGObjectMethodPtrT OSGObjectMethodPtrT;
    typedef typename OSGFunctorTrait::OSGSetObjectT       OSGSetObjectT;


  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGObjectFunctor1 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGObjectFunctor1(void);
    OSGObjectFunctor1(const OSGObjectFunctor1 &source);
    
    virtual ~OSGObjectFunctor1(void); 

    /*------------------------- your_category -------------------------------*/

    void setMethod         (OSGObjectMethodT     pFunc);

    void setMethod         (OSGObjectMethodPtrT  pFunc);

    void setCalledObject   (OSGSetObjectT        pObj);

    void setObjectAndMethod(OSGSetObjectT        pObj, 
                            OSGObjectMethodPtrT  pFunc);

    virtual OSGRetT    call(OSGArg1T             arg1);

};






//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGArg1T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT>
class OSGObjectFunctor1<void, 
                        OSGArg1T, 
                        OSGObjectT, 
                        osgMethodCallType,
                        OSGSizeTraitsT> : 
    public OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef
        OSGFunctorTraits1<void,
                          OSGArg1T, 
                          OSGObjectT, 
                          osgMethodCallType> OSGFunctorTrait;

    typedef typename OSGFunctorTrait::OSGObjectMethodT    OSGObjectMethodT;
    typedef typename OSGFunctorTrait::OSGObjectMethodPtrT OSGObjectMethodPtrT;
    typedef typename OSGFunctorTrait::OSGSetObjectT       OSGSetObjectT;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGObjectFunctor1 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGObjectFunctor1(void);
    OSGObjectFunctor1(const OSGObjectFunctor1 &source);
    
    virtual ~OSGObjectFunctor1(void); 

    /*------------------------- your_category -------------------------------*/

    void setMethod         (OSGObjectMethodT     pFunc);

    void setMethod         (OSGObjectMethodPtrT  pFunc);

    void setCalledObject   (OSGSetObjectT        pObj);

    void setObjectAndMethod(OSGSetObjectT        pObj, 
                            OSGObjectMethodPtrT  pFunc);

    virtual void    call(OSGArg1T             arg1);
};


template <class OSGRetT, class OSGArg1T> inline
OSGFunctionFunctor1<OSGRetT, OSGArg1T> osgFunctionFunctor1( 
    OSGRetT (*pFunc)(OSGArg1T));

template <class OSGRetT, class OSGArg1T> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor1Ref(
    OSGRetT (OSGArg1T::*pFunc)());


template <class OSGRetT, class OSGArg1T, class OSGObjectT> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T, 
                  OSGObjectT &,
                  OSGOnStoredObject> osgMethodFunctorRef(
    OSGObjectT &obj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T));


template <class OSGRetT, class OSGArg1T> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T *, 
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor1Ptr(
    OSGRetT (OSGArg1T::*pFunc)());


template <class OSGRetT, class OSGArg1T, class OSGObjectT> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T, 
                  OSGObjectT *,
                  OSGOnStoredObject> osgMethodFunctor1Ptr(
    OSGObjectT *pObj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T));

template <class OSGRetT, class OSGArg1T> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg1T,
                  OSGOnCPtrArgument> osgMethodFunctor1CPtr(
   typename OSGFunctorBuildFuncType1<OSGRetT, 
                                     OSGArg1T>::OSGFunctionType pFunc);

template <class OSGRetT, class OSGArg1T, class OSGObjectT> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T, 
                  OSGObjectT &,
                  OSGOnStoredCPtr> osgMethodFunctor1CPtr(
    OSGObjectT &obj, 
    typename OSGFunctorBuildFuncType2<OSGRetT, 
                                      OSGArg1T, 
                                      OSGObjectT>::OSGFunctionType pFunc);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGSizeTraitsT = OSGDefaultFunctorSizeTraits>
class OSGFunctor2Base : public OSGFunctorBase<OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctorBase<OSGSizeTraitsT> Inherited;


    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctor2Base(void);
    OSGFunctor2Base(const OSGFunctor2Base &source);
    
    virtual ~OSGFunctor2Base(void); 

    /*------------------------- your_category -------------------------------*/

    virtual OSGRetT call(OSGArg1T arg1, OSGArg2T arg2);

    void operator =(const OSGFunctor2Base &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGArg1T, 
          class OSGArg2T,
          class OSGSizeTraitsT>
class OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT> : 
    public OSGFunctorBase<OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctorBase<OSGSizeTraitsT> Inherited;


    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctor2Base(void);
    OSGFunctor2Base(const OSGFunctor2Base &source);
    
    virtual ~OSGFunctor2Base(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void call(OSGArg1T arg1, OSGArg2T);

    void operator =(const OSGFunctor2Base &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGSizeTraitsT = OSGDefaultFunctorSizeTraits>
class OSGFunctionFunctor2 : 
    public OSGFunctor2Base<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGRetT (*OSGFunctionP)(OSGArg1T, OSGArg2T);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor2Base<OSGRetT, 
                            OSGArg1T, 
                            OSGArg2T,
                            OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGFunctionFunctor2 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctionFunctor2(void);
    OSGFunctionFunctor2(const OSGFunctionFunctor2 &source);
    
    virtual ~OSGFunctionFunctor2(void); 

    /*----------------------------- access ----------------------------------*/

    void setFunction(OSGFunctionP pFunc);

    /*------------------------- your_category -------------------------------*/

    virtual OSGRetT call(OSGArg1T arg1, OSGArg2T arg2);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGArg1T,
          class OSGArg2T,
          class OSGSizeTraitsT>
class OSGFunctionFunctor2<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT> : 
    public OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void (*OSGFunctionP)(OSGArg1T, OSGArg2T);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor2Base<void, 
                            OSGArg1T, 
                            OSGArg2T, 
                            OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGFunctionFunctor2 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFunctionFunctor2(void);
    OSGFunctionFunctor2(const OSGFunctionFunctor2 &source);
    
    virtual ~OSGFunctionFunctor2(void); 

    /*----------------------------- access ----------------------------------*/

    void setFunction(OSGFunctionP pFunc);

    /*------------------------- your_category -------------------------------*/

    virtual void call(OSGArg1T arg1, OSGArg2T arg2);
};


template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType>
struct OSGFunctorTraits2
{
};


template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT,
                         OSGArg1T *, 
                         OSGArg2T,
                         OSGObjectT, 
                         OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, 
                                    OSGArg1T *arg1, 
                                    OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        return ((arg1)->*pFunc)(arg2);
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char     *, 
                                    char     *, 
                                    OSGArg1T *,
                                    OSGArg2T  )
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char     *pData2, 
                                     OSGArg1T *arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        ((arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T *,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT,
                        OSGArg1T &, 
                        OSGArg2T,
                        OSGObjectT, 
                        OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char     *pData2, 
                                    OSGArg1T &arg1,
                                    OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        return ((&arg1)->*pFunc)(arg2);
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char     *, 
                                    char     *, 
                                    OSGArg1T &,
                                    OSGArg2T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char     *pData2, 
                                     OSGArg1T &arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        ((&arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T &,
                                     OSGArg2T)
    {

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT,    
                         OSGArg1T &,      
                         OSGArg2T,
                         OSGObjectT, 
                         OSGOnCPtrArgument>
{
    typedef typename OSGObjectT::OSGObjectType OSGObjectType;

    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodT   )(OSGArg2T);
    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodPtrT)(OSGArg1T,
                                                                   OSGArg2T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char     *pData2, 
                                    OSGArg1T &arg1,
                                    OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);
        typedef typename OSGObjectT::OSGObjectType OSGObjectType;

        return (((OSGObjectType *)(&(*arg1)))->*pFunc)(arg2);
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char     *, 
                                    char     *, 
                                    OSGArg1T &,
                                    OSGArg2T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char     *pData2, 
                                     OSGArg1T &arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) pData2);

        ((&(*arg1))->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *,
                                     char     *, 
                                     OSGArg1T &,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT, 
                         OSGArg1T, 
                         OSGArg2T,  
                         OSGObjectT &, 
                         OSGOnStoredCPtr>
{
    typedef typename OSGObjectT::OSGObjectType OSGObjectType;
    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodT   )(OSGArg2T);
    typedef          OSGRetT (OSGObjectType::*OSGObjectMethodPtrT)(OSGArg1T,
                                                                  OSGArg2T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char     *, 
                                    OSGArg1T  ,
                                    OSGArg2T  )
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static OSGRetT callObjectMethod(char     *pData1, 
                                    char     *pData2, 
                                    OSGArg1T  arg1,
                                    OSGArg2T  arg2)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);
        
        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
        
        return (&(**pObj)->*pFunc)(arg1, arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     OSGArg1T  ,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, 
                                     char *pData2, 
                                     OSGArg1T arg1,
                                     OSGArg2T arg2)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);
        
        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
        
        (&(**pObj)->*pFunc)(arg1, arg2);
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T, 
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT, 
                         OSGArg1T &, 
                         OSGArg2T, 
                         OSGObjectT *, 
                         OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT *OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT **) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1, OSGArg2T arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static OSGRetT callObjectMethod(char     *, 
                                    char     *, 
                                    OSGArg1T  ,
                                    OSGArg2T )
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char     *pData2, 
                                     OSGArg1T  arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((&arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T  ,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT, 
                         OSGArg1T *, 
                         OSGArg2T, 
                         OSGObjectT *, 
                         OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT *OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT **) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1, OSGArg2T arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((arg1)->*pFunc)(arg2);
    }

    static OSGRetT callObjectMethod(char     *, 
                                    char     *, 
                                    OSGArg1T  ,
                                    OSGArg2T )
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char     *pData2, 
                                     OSGArg1T  arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T  ,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT, 
                         OSGArg1T, 
                         OSGArg2T, 
                         OSGObjectT *, 
                         OSGOnStoredObject>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT *OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT **) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, OSGArg1T , OSGArg2T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static OSGRetT callObjectMethod(char     *pData1, 
                                    char     *pData2, 
                                    OSGArg1T  arg1,
                                    OSGArg2T  arg2)
    {
        OSGObjectT *pObj = *((OSGObjectT **) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1, arg2);
    }


    static void callObjectMethodVoid(char     *, 
                                     OSGArg1T  ,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char     *pData1, 
                                     char     *pData2, 
                                     OSGArg1T  arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectT *pObj = *((OSGObjectT **) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
            
        (pObj->*pFunc)(arg1, arg2);
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT, 
                         OSGArg1T &, 
                         OSGArg2T,
                         OSGObjectT &, 
                         OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1, OSGArg2T arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static OSGRetT callObjectMethod(char     *, 
                                    char     *, 
                                    OSGArg1T  ,
                                    OSGArg2T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char     *pData2, 
                                     OSGArg1T  arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T  ,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT, 
                         OSGArg1T *, 
                         OSGArg2T,
                         OSGObjectT &, 
                         OSGOnArgument>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

    static OSGRetT callObjectMethod(char *pData2, OSGArg1T arg1, OSGArg2T arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        return ((arg1)->*pFunc)();
    }

    static OSGRetT callObjectMethod(char     *, 
                                    char     *, 
                                    OSGArg1T  ,
                                    OSGArg2T  )
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char     *pData2, 
                                     OSGArg1T  arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectMethodT pFunc = *((OSGObjectMethodT *) _data2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     OSGArg1T  ,
                                     OSGArg2T  )
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT>
struct OSGFunctorTraits2<OSGRetT, 
                         OSGArg1T, 
                         OSGArg2T,
                         OSGObjectT &, 
                         OSGOnStoredObject>
{
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodT   )(OSGArg2T);
    typedef OSGRetT (OSGObjectT::*OSGObjectMethodPtrT)(OSGArg1T, OSGArg2T);

    typedef OSGObjectT &OSGSetObjectT;

    static void setCalledObject(char *pData, OSGSetObjectT obj)
    {
        *((OSGObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static OSGRetT callObjectMethod(char *, OSGArg1T , OSGArg2T)
    {
        OSGRetT returnValue;

        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static OSGRetT callObjectMethod(char     *pData1, 
                                    char     *pData2, 
                                    OSGArg1T  arg1,
                                    OSGArg2T  arg2)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1, arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     OSGArg1T  ,
                                     OSGArg2T)
    {
        SWARNING << "OSGFunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char     *pData1, 
                                     char     *pData2, 
                                     OSGArg1T  arg1,
                                     OSGArg2T  arg2)
    {
        OSGObjectT *pObj = ((OSGObjectT *) pData1);

        OSGObjectMethodPtrT pFunc = *((OSGObjectMethodPtrT *) pData2);
        
        (pObj->*pFunc)(arg1, arg2);
    }
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGRetT, 
          class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT = OSGDefaultFunctorSizeTraits>
class OSGObjectFunctor2 : 
    public OSGFunctor2Base<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef
        OSGFunctorTraits2<OSGRetT,
                          OSGArg1T, 
                          OSGArg2T,
                          OSGObjectT, 
                          osgMethodCallType> OSGFunctorTrait;

    typedef typename OSGFunctorTrait::OSGObjectMethodT    OSGObjectMethodT;
    typedef typename OSGFunctorTrait::OSGObjectMethodPtrT OSGObjectMethodPtrT;
    typedef typename OSGFunctorTrait::OSGSetObjectT       OSGSetObjectT;


  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor2Base<OSGRetT, 
                            OSGArg1T, 
                            OSGArg2T, 
                            OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGObjectFunctor2 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGObjectFunctor2(void);
    OSGObjectFunctor2(const OSGObjectFunctor2 &source);
    
    virtual ~OSGObjectFunctor2(void); 

    /*------------------------- your_category -------------------------------*/

    void setMethod         (OSGObjectMethodT     pFunc);

    void setMethod         (OSGObjectMethodPtrT  pFunc);

    void setCalledObject   (OSGSetObjectT        pObj);

    void setObjectAndMethod(OSGSetObjectT        pObj, 
                            OSGObjectMethodPtrT  pFunc);

    virtual OSGRetT    call(OSGArg1T             arg1,
                            OSGArg2T             arg2);

};






//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class OSGArg1T,
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT>
class OSGObjectFunctor2<void, 
                        OSGArg1T, 
                        OSGArg2T,
                        OSGObjectT, 
                        osgMethodCallType,
                        OSGSizeTraitsT> : 
    public OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef
        OSGFunctorTraits2<void,
                          OSGArg1T, 
                          OSGArg2T,
                          OSGObjectT, 
                          osgMethodCallType> OSGFunctorTrait;

    typedef typename OSGFunctorTrait::OSGObjectMethodT    OSGObjectMethodT;
    typedef typename OSGFunctorTrait::OSGObjectMethodPtrT OSGObjectMethodPtrT;
    typedef typename OSGFunctorTrait::OSGSetObjectT       OSGSetObjectT;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFunctor2Base<void, 
                            OSGArg1T, 
                            OSGArg2T, 
                            OSGSizeTraitsT> Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void operator =(const OSGObjectFunctor2 &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGObjectFunctor2(void);
    OSGObjectFunctor2(const OSGObjectFunctor2 &source);
    
    virtual ~OSGObjectFunctor2(void); 

    /*------------------------- your_category -------------------------------*/

    void setMethod         (OSGObjectMethodT     pFunc);

    void setMethod         (OSGObjectMethodPtrT  pFunc);

    void setCalledObject   (OSGSetObjectT        pObj);

    void setObjectAndMethod(OSGSetObjectT        pObj, 
                            OSGObjectMethodPtrT  pFunc);

    virtual void    call(OSGArg1T             arg1,
                         OSGArg2T             arg2);
};

template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGFunctionFunctor2<OSGRetT, OSGArg1T, OSGArg2T> osgFunctionFunctor2( 
    OSGRetT (*pFunc)(OSGArg1T, OSGArg2T));

template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg2T,
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor2Ref(
    OSGRetT (OSGArg1T::*pFunc)(OSGArg2T));


template <class OSGRetT, class OSGArg1T, 
          class OSGArg2T, class OSGObjectT> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T, 
                  OSGArg2T,
                  OSGObjectT &,
                  OSGOnStoredObject> osgMethodFunctor2Ref(
    OSGObjectT &obj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T, OSGArg2T));


template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T *, 
                  OSGArg2T,
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor2Ptr(
    OSGRetT (OSGArg1T::*pFunc)(OSGArg2T));


template <class OSGRetT,  class OSGArg1T, 
          class OSGArg2T, class OSGObjectT> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T, 
                  OSGArg2T,
                  OSGObjectT *,
                  OSGOnStoredObject> osgMethodFunctor2Ptr(
    OSGObjectT *pObj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T, OSGArg2T));

template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg2T, 
                  OSGArg1T,
                  OSGOnCPtrArgument> osgMethodFunctor2CPtr(
    typename OSGFunctorBuildFuncType2<OSGRetT, 
                                      OSGArg2T,
                                      OSGArg1T>::OSGFunctionType pFunc);

#ifdef __sgi
#pragma set woff 1424
#endif

template <class OSGRetT,    class OSGArg1T, 
          class OSGObjectT, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg2T, 
                  OSGObjectT,
                  OSGOnCPtrArgument> osgMethodFunctor2BaseCPtr(
    typename OSGFunctorBuildFuncType2<OSGRetT, 
                                      OSGArg2T,
                                      OSGObjectT>::OSGFunctionType pFunc);

#ifdef __sgi
#pragma reset woff 1424
#endif

template <class OSGRetT,  class OSGArg1T, 
          class OSGArg2T, class OSGObjectT> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T, 
                  OSGArg2T,
                  OSGObjectT &,
                  OSGOnStoredCPtr> osgMethodFunctor2CPtr(
    OSGObjectT &obj,
    typename OSGFunctorBuildFuncType3<OSGRetT, 
                                      OSGArg1T, 
                                      OSGArg2T, 
                                      OSGObjectT>::OSGFunctionType pFunc);

OSG_END_NAMESPACE

#include <OSGFunctors.inl>

#endif /* _CLASSNAME_H_ */
