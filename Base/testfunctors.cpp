
#include <OSGConfig.h>

#include <stdio.h>
#include <vector>
#include <OSGFunctors.h>

OSG_USING_NAMESPACE

template <class OSGObjectTypeT>
class OSGPointer
{
  protected:

    OSGObjectTypeT *_pObject;

  public :

    typedef OSGObjectTypeT OSGObjectType;

    OSGPointer(void);

    virtual ~OSGPointer(void); 

          OSGObjectTypeT *operator->(void);
    const OSGObjectTypeT *operator->(void) const;

          OSGObjectTypeT &operator *(void);
    const OSGObjectTypeT &operator *(void) const;

    operator OSGObjectTypeT *(void);
    void operator =(      OSGObjectTypeT *source);
    void operator =(const OSGPointer     &source);

};

template <class OSGObjectTypeT> inline
OSGPointer<OSGObjectTypeT>::OSGPointer(void) :
    _pObject(NULL)
{
}
template <class OSGObjectTypeT> inline
OSGPointer<OSGObjectTypeT>::~OSGPointer(void)
{
}

template <class OSGObjectTypeT> inline
OSGObjectTypeT *OSGPointer<OSGObjectTypeT>::operator->(void)
{
    return _pObject;
}

template <class OSGObjectTypeT> inline
const OSGObjectTypeT *OSGPointer<OSGObjectTypeT>::operator->(void) const
{
    return _pObject;
}

template <class OSGObjectTypeT> inline
OSGObjectTypeT &OSGPointer<OSGObjectTypeT>::operator *(void)
{
    return *_pObject;
}
template <class OSGObjectTypeT> inline
const OSGObjectTypeT &OSGPointer<OSGObjectTypeT>::operator *(void) const
{
    return *_pObject;
}

template <class OSGObjectTypeT> inline
OSGPointer<OSGObjectTypeT>::operator OSGObjectTypeT *(void)
{
    return _pObject;
}

template <class OSGObjectTypeT> inline
void OSGPointer<OSGObjectTypeT>::operator =(const OSGPointer &source)
{
        if(this != &source)
    {
        _pObject = source._pObject;
    }
}

template <class OSGObjectTypeT> inline
void OSGPointer<OSGObjectTypeT>::operator =(OSGObjectTypeT *source)
{
        if(this->_pObject != source)
    {
        _pObject = source;
    }
}


class A
{
    static int acount;

    int aid;

  public:

    A(void) : aid(acount++) {}
    virtual ~A(void) {} 

    void foo(void) { fprintf(stderr, "A::foo %d\n", aid); }
    void bar(A *)  { fprintf(stderr, "A::bar %d\n", aid); }
    OSGInt32 fooI(void) { fprintf(stderr, "A::fooI %d\n", aid); return 0; }
    OSGInt32 barI(A *)  { fprintf(stderr, "A::barI %d\n", aid); return 0; }

    void fooO(void) { fprintf(stderr, "A::fooO %d\n", aid); }
    void barO(A &)  { fprintf(stderr, "A::barO %d\n", aid); }

    void fooP(void) { fprintf(stderr, "A::fooP %d\n", aid); }
    void barP(OSGPointer<A> &)  { fprintf(stderr, "A::barP %d\n", aid); }

    OSGInt32 fooIP(void) { fprintf(stderr, "A::fooIP %d\n", aid); return 0; }
    OSGInt32 barIP(OSGPointer<A> &)  { fprintf(stderr, "A::barIP %d\n", aid); 
                                      return 0; }

    OSGInt32 fooIO(void) { fprintf(stderr, "A::fooIO %d\n", aid); return 0; }
    OSGInt32 barIO(A &)  { fprintf(stderr, "A::barIO %d\n", aid); return 0; }

    void     foo1(     OSGInt32 &arg1) 
    {
        fprintf(stderr, "A::foo1 %d %d\n", aid, arg1);
    };

    void     bar1(A *, OSGInt32 arg1)
    {
        fprintf(stderr, "A::bar1 %d %d\n", aid, arg1);
    };

    OSGInt32 foo2(OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 bar2(A *, OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };


    void     foo1O(     OSGInt32 &arg1) 
    {
        fprintf(stderr, "A::foo1O %d %d\n", aid, arg1);
    };

    void     bar1O(A &, OSGInt32 &arg1)
    {
        fprintf(stderr, "A::bar1O %d %d\n", aid, arg1);
    };


    void     foo1P(     OSGInt32 &arg1) 
    {
        fprintf(stderr, "A::foo1P %d %d\n", aid, arg1);
    };

    void     bar1P(OSGPointer<A> &, OSGInt32 &arg1)
    {
        fprintf(stderr, "A::bar1P %d %d\n", aid, arg1);
    };



    OSGInt32 foo2O(OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::foo2O %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 bar2O(A &, OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::bar2O %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 foo2P(OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::foo2P %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 bar2P(OSGPointer<A> &, OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::bar2P %d %d\n", aid, arg1); 
        return 0;
    };
};

int A::acount = 0;


class A1
{
    static int acount;

    int aid;

  public:

    A1(void) : aid(acount++) {}
    virtual ~A1(void) {} 

    void foo(void) { fprintf(stderr, "A::foo %d\n", aid); }
    void bar(A *)  { fprintf(stderr, "A::bar %d\n", aid); }
    OSGInt32 fooI(void) { fprintf(stderr, "A::fooI %d\n", aid); return 0; }
    OSGInt32 barI(A *)  { fprintf(stderr, "A::barI %d\n", aid); return 0; }

    void fooO(void) { fprintf(stderr, "A::fooO %d\n", aid); }
    void barO(A &)  { fprintf(stderr, "A::barO %d\n", aid); }

    void fooP(void) { fprintf(stderr, "A::fooP %d\n", aid); }
    void barP(OSGPointer<A> &)  { fprintf(stderr, "A::barP %d\n", aid); }

    OSGInt32 fooIP(void) { fprintf(stderr, "A::fooIP %d\n", aid); return 0; }
    OSGInt32 barIP(OSGPointer<A> &)  { fprintf(stderr, "A::barIP %d\n", aid); 
                                      return 0; }

    OSGInt32 fooIO(void) { fprintf(stderr, "A::fooIO %d\n", aid); return 0; }
    OSGInt32 barIO(A &)  { fprintf(stderr, "A::barIO %d\n", aid); return 0; }

    void     foo1(     OSGInt32 arg1) 
    {
        fprintf(stderr, "A::foo1 %d %d\n", aid, arg1);
    };

    void     bar1(A *, OSGInt32 &arg1)
    {
        fprintf(stderr, "A::bar1 %d %d\n", aid, arg1);
    };

    OSGInt32 foo2(OSGInt32 arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 bar2(A *, OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };


    void     foo1O(     OSGInt32 arg1) 
    {
        fprintf(stderr, "A::foo1O %d %d\n", aid, arg1);
    };

    void     bar1O(A &, OSGInt32 &arg1)
    {
        fprintf(stderr, "A::bar1O %d %d\n", aid, arg1);
    };


    void     foo1P(     OSGInt32 &arg1) 
    {
        fprintf(stderr, "A::foo1P %d %d\n", aid, arg1);
    };

    void     bar1P(OSGPointer<A> &, OSGInt32 &arg1)
    {
        fprintf(stderr, "A::bar1P %d %d\n", aid, arg1);
    };



    OSGInt32 foo2O(OSGInt32 arg1) 
    { 
        fprintf(stderr, "A::foo2O %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 bar2O(A &, OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::bar2O %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 foo2P(OSGInt32 arg1) 
    { 
        fprintf(stderr, "A::foo2P %d %d\n", aid, arg1); 
        return 0;
    };

    OSGInt32 bar2P(OSGPointer<A> &, OSGInt32 &arg1) 
    { 
        fprintf(stderr, "A::bar2P %d %d\n", aid, arg1); 
        return 0;
    };
};

int A1::acount = 0;

class B : public A
{
  public:

    B() : A() {}
    ~B() {}

    static void     foo (A *) { fprintf(stderr, "B::foo\n"); };
    static OSGInt32 fooI(A *) { fprintf(stderr, "B::fooI\n"); return 0; };

    static void     fooO (A &) { fprintf(stderr, "B::fooO\n"); };
    static OSGInt32 fooIO(A &) { fprintf(stderr, "B::fooIO\n"); return 0; };

    static void     fooP  (OSGPointer<A> &) { fprintf(stderr, "B::fooP\n"); };
    static OSGInt32 fooIP (OSGPointer<A> &) { fprintf(stderr, "B::fooIP\n"); 
                                              return 0; };

    static OSGInt32 bar(A*, OSGInt32 &uiArg2)
    {
        fprintf(stderr, "B::bar : %d\n", uiArg2);
        return 0;
    }

    static void foobar(A*, OSGInt32 &uiArg2)
    {
        fprintf(stderr, "B::foobar : %d\n", uiArg2);
    }

    static OSGInt32 barO(A &, OSGInt32 &uiArg2)
    {
        fprintf(stderr, "B::barO : %d\n", uiArg2);
        return 0;
    }

    static OSGInt32 barP(OSGPointer<A> &, OSGInt32 &uiArg2)
    {
        fprintf(stderr, "B::barP : %d\n", uiArg2);
        return 0;
    }

    static void foobarO(A &, OSGInt32 &uiArg2)
    {
        fprintf(stderr, "B::foobarO : %d\n", uiArg2);
    }

    static void foobarP(OSGPointer<A> &, OSGInt32 &uiArg2)
    {
        fprintf(stderr, "B::foobarP : %d\n", uiArg2);
    }

    OSGInt32 foo2P(OSGInt32 &arg1) 
    { 
        fprintf(stderr, "B::foo2P %d\n", arg1); 
        return 0;
    };
};


void foo(A*)
{
    fprintf(stderr, "foo\n");
}

void fooO(A &)
{
    fprintf(stderr, "fooO\n");
}

void fooP(OSGPointer<A> &pA)
{
    fprintf(stderr, "fooP\n");
    pA->foo();
}

OSGInt32 fooIP(OSGPointer<A> &pA)
{
    fprintf(stderr, "fooIP\n");
    pA->foo();
    return 0;
}

OSGInt32 fooI(A*)
{
    fprintf(stderr, "fooI\n");
    return 0;
}

OSGInt32 fooIO(A &)
{
    fprintf(stderr, "fooIO\n");
    return 0;
}

OSGInt32 bar(A *, OSGInt32 &uiArg2)
{
    fprintf(stderr, "bar : %d\n", uiArg2);
    return 0;
}

void foobar(A *, OSGInt32 &uiArg2)
{
    fprintf(stderr, "foobar : %d\n", uiArg2);
}

OSGInt32 barO(A &, OSGInt32 &uiArg2)
{
    fprintf(stderr, "barO : %d\n", uiArg2);
    return 0;
}

void foobarO(A &, OSGInt32 &uiArg2)
{
    fprintf(stderr, "foobarO : %d\n", uiArg2);
}

OSGInt32 barP(OSGPointer<A> &, OSGInt32 &uiArg2)
{
    fprintf(stderr, "barP : %d\n", uiArg2);
    return 0;
}

void foobarP(OSGPointer<A> &, OSGInt32 &uiArg2)
{
    fprintf(stderr, "foobarP : %d\n", uiArg2);
}


typedef OSGFunctor1Base<void,     A &> OSGFunctor1O;
typedef OSGFunctor1Base<OSGInt32, A &> OSGFunctor1IO;

typedef OSGFunctor1Base<void,     A *> OSGFunctor1;
typedef OSGFunctor1Base<OSGInt32, A *> OSGFunctor1I;

typedef OSGFunctor2Base<void,     A &, OSGInt32 &> OSGFunctor2O;
typedef OSGFunctor2Base<OSGInt32, A &, OSGInt32 &> OSGFunctor2IO;

typedef OSGFunctor2Base<void,     A *, OSGInt32 &> OSGFunctor2;
typedef OSGFunctor2Base<OSGInt32, A *, OSGInt32 &> OSGFunctor2I;

typedef OSGFunctor1Base<void,     OSGPointer<A> &> OSGFunctor1P;
typedef OSGFunctor1Base<OSGInt32, OSGPointer<A> &> OSGFunctor1IP;

typedef OSGFunctor2Base<void,     OSGPointer<A> &, OSGInt32 &> OSGFunctor2P;
typedef OSGFunctor2Base<OSGInt32, OSGPointer<A> &, OSGInt32 &> OSGFunctor2IP;

void testfunctor1(void)
{
    fprintf(stderr, "testfunctor1 started\n");
    
    vector<OSGFunctor1> funcVec;
    vector<OSGFunctor1I> funcVecI;

    A a1;
    A1 a2;    

    unsigned int i;

    funcVec.push_back(osgFunctionFunctor1(foo));
    funcVec.push_back(osgFunctionFunctor1(B::foo));
    funcVec.push_back(osgMethodFunctor1Ptr(&A::foo));
    funcVec.push_back(osgMethodFunctor1Ptr(&a2, &A1::bar));

    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVec[i].call(&a1);
    }

    funcVecI.push_back(osgFunctionFunctor1(fooI));
    funcVecI.push_back(osgFunctionFunctor1(B::fooI));
    funcVecI.push_back(osgMethodFunctor1Ptr(&A::fooI));
    funcVecI.push_back(osgMethodFunctor1Ptr(&a2, &A1::barI));

    for(i = 0; i < funcVecI.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVecI[i].call(&a1);
    }

    fprintf(stderr, "testfunctor1 end\n");
}

void testfunctor1a(void)
{
    fprintf(stderr, "testfunctor1a started\n");
    
    vector<OSGFunctor1O> funcVec;
    vector<OSGFunctor1IO> funcVecI;

    A a1;
    A1 a2;

    unsigned int i;

    funcVec.push_back(osgFunctionFunctor1(fooO));
    funcVec.push_back(osgFunctionFunctor1(B::fooO));
    funcVec.push_back(osgMethodFunctor1Ref(&A::fooO));
    funcVec.push_back(osgMethodFunctor1Ref(a2, &A1::barO));

    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVec[i].call(a1);
    }

    funcVecI.push_back(osgFunctionFunctor1(fooIO));
    funcVecI.push_back(osgFunctionFunctor1(B::fooIO));
    funcVecI.push_back(osgMethodFunctor1Ref(&A::fooIO));
    funcVecI.push_back(osgMethodFunctor1Ref(a2, &A1::barIO));

    for(i = 0; i < funcVecI.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVecI[i].call(a1);
    }

    fprintf(stderr, "testfunctor1a end\n");
}


void testfunctor2(void)
{
    fprintf(stderr, "testfunctor2 started\n");

    vector<OSGFunctor2>  funcVec;
    vector<OSGFunctor2I> funcVecI;

    A a1;
    A1 a2;

    OSGInt32 j;
    unsigned int i;

    funcVecI.push_back(osgMethodFunctor2Ptr(&A::foo2));
    funcVecI.push_back(osgMethodFunctor2Ptr(&a2, &A1::bar2));
    funcVecI.push_back(osgFunctionFunctor2(bar));
    funcVecI.push_back(osgFunctionFunctor2(&B::bar));

    for(i = 0; i < funcVecI.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        j = i;
        funcVecI[i].call(&a1, j);
    }


    funcVec.push_back(osgMethodFunctor2Ptr(&A::foo1));
    funcVec.push_back(osgMethodFunctor2Ptr(&a2, &A1::bar1));
    funcVec.push_back(osgFunctionFunctor2(foobar));
    funcVec.push_back(osgFunctionFunctor2(&B::foobar));

    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i); 
        j = i;
        funcVec[i].call(&a1, j);
    }

    fprintf(stderr, "testfunctor2 end\n");    
}

void testfunctor2a(void)
{
    fprintf(stderr, "testfunctor2a started\n");

    vector<OSGFunctor2O>  funcVec;
    vector<OSGFunctor2IO> funcVecI;

    A a1;
    A1 a2;

    OSGInt32 j;
    unsigned int i;

    funcVecI.push_back(osgMethodFunctor2Ref(&A::foo2O));
    funcVecI.push_back(osgMethodFunctor2Ref(a2, &A1::bar2O));
    funcVecI.push_back(osgFunctionFunctor2(barO));
    funcVecI.push_back(osgFunctionFunctor2(&B::barO));

    for(i = 0; i < funcVecI.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        j = i;
        funcVecI[i].call(a1, j);
    }


    funcVec.push_back(osgMethodFunctor2Ref(&A::foo1O));
    funcVec.push_back(osgMethodFunctor2Ref(a2, &A1::bar1O));
    funcVec.push_back(osgFunctionFunctor2(foobarO));
    funcVec.push_back(osgFunctionFunctor2(&B::foobarO));

    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        j = i;
        funcVec[i].call(a1, j);
    }

    fprintf(stderr, "testfunctor2a end\n");    
}



void testpointer1(void)
{
    OSGUInt32 i;

    fprintf(stderr, "testpointer1 start\n");    
    
    A a;
    A1 a1;

    OSGPointer<A> pA;
    OSGPointer<A1> pA1;

    pA = &a;
    pA1 = &a1;

    vector<OSGFunctor1P> funcVec;

    funcVec.push_back(osgFunctionFunctor1(fooP));
    funcVec.push_back(osgFunctionFunctor1(&B::fooP));
    funcVec.push_back(osgMethodFunctor1CPtr<void, OSGPointer<A> >(&A::fooP));
    funcVec.push_back(osgMethodFunctor1CPtr<void, 
                                            OSGPointer<A> &,
                                            OSGPointer<A1> >(pA1, &A1::barP));


    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVec[i].call(pA);
    }
    

    fprintf(stderr, "testpointer1 end\n");    
}

void testpointer1a(void)
{
    OSGUInt32 i;

    fprintf(stderr, "testpointer1a start\n");    
    
    A a;
    A1 a1;

    OSGPointer<A> pA;
    OSGPointer<A1> pA1;

    pA = &a;
    pA1 = &a1;

    vector<OSGFunctor1IP> funcVec;

    funcVec.push_back(osgFunctionFunctor1(fooIP));
    funcVec.push_back(osgFunctionFunctor1(&B::fooIP));
    funcVec.push_back(osgMethodFunctor1CPtr<OSGInt32, 
                                            OSGPointer<A> >(&A::fooIP));
    funcVec.push_back(osgMethodFunctor1CPtr<OSGInt32, 
                                            OSGPointer<A> &,
                                            OSGPointer<A1> >(pA1, &A1::barIP));

    
    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVec[i].call(pA);
    }
    

    fprintf(stderr, "testpointer1a end\n");    
}


void testpointer2(void)
{
    OSGUInt32 i;

    fprintf(stderr, "testpointer2 start\n");    
    
    A a;
    A1 a1;
    
    OSGPointer<A> pA;
    OSGPointer<A1> pA1;

    pA = &a;
    pA1 = &a1;

    OSGInt32 j;

    vector<OSGFunctor2P> funcVec;
    vector<OSGFunctor2IP> funcVecI;

    funcVec.push_back(osgFunctionFunctor2(foobarP));
    funcVec.push_back(osgFunctionFunctor2(&B::foobarP));

    funcVec.push_back(osgMethodFunctor2CPtr<void, 
                                           OSGPointer<A>,
                                           OSGInt32 &>(&A::foo1P));
    funcVec.push_back(osgMethodFunctor2CPtr<void, 
                                            OSGPointer<A> &, 
                                            OSGInt32      &, 
                                            OSGPointer<A1> >(pA1, &A1::bar1P));

    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        j = i;
        funcVec[i].call(pA, j);
    }
    
    funcVecI.push_back(osgMethodFunctor2BaseCPtr<OSGInt32, 
                                                 OSGPointer<A>,
                                                 OSGPointer<B>, 
                                                 OSGInt32 &>(&B::foo2P));

    funcVecI.push_back(osgMethodFunctor2CPtr<OSGInt32, 
                                             OSGPointer<A> &, 
                                             OSGInt32      &,
                                             OSGPointer<A1> >(pA1, 
                                                              &A1::bar2P));


    funcVecI.push_back(osgFunctionFunctor2(barP));
    funcVecI.push_back(osgFunctionFunctor2(&B::barP));

    for(i = 0; i < funcVecI.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        j = i;
        funcVecI[i].call(pA, j);
    }

    fprintf(stderr, "testpointer2 end\n");    
}



void main(void)
{
    testfunctor1();
    testfunctor1a();
    testfunctor2();
    testfunctor2a();

    testpointer1();
    testpointer1a();

    testpointer2();
}
