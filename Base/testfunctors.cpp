
#include <OSGConfig.h>

#include <stdio.h>
#include <vector>
#include <OSGFunctors.h>

OSG_USING_NAMESPACE

template <class ObjectTypeT>
class Pointer
{
  protected:

    ObjectTypeT *_pObject;

  public :

    typedef ObjectTypeT ObjectType;

    Pointer(void);

    virtual ~Pointer(void); 

          ObjectTypeT *operator->(void);
    const ObjectTypeT *operator->(void) const;

          ObjectTypeT &operator *(void);
    const ObjectTypeT &operator *(void) const;

    operator ObjectTypeT *(void);
    void operator =(      ObjectTypeT *source);
    void operator =(const Pointer     &source);

};

template <class ObjectTypeT> inline
Pointer<ObjectTypeT>::Pointer(void) :
    _pObject(NULL)
{
}
template <class ObjectTypeT> inline
Pointer<ObjectTypeT>::~Pointer(void)
{
}

template <class ObjectTypeT> inline
ObjectTypeT *Pointer<ObjectTypeT>::operator->(void)
{
    return _pObject;
}

template <class ObjectTypeT> inline
const ObjectTypeT *Pointer<ObjectTypeT>::operator->(void) const
{
    return _pObject;
}

template <class ObjectTypeT> inline
ObjectTypeT &Pointer<ObjectTypeT>::operator *(void)
{
    return *_pObject;
}
template <class ObjectTypeT> inline
const ObjectTypeT &Pointer<ObjectTypeT>::operator *(void) const
{
    return *_pObject;
}

template <class ObjectTypeT> inline
Pointer<ObjectTypeT>::operator ObjectTypeT *(void)
{
    return _pObject;
}

template <class ObjectTypeT> inline
void Pointer<ObjectTypeT>::operator =(const Pointer &source)
{
        if(this != &source)
    {
        _pObject = source._pObject;
    }
}

template <class ObjectTypeT> inline
void Pointer<ObjectTypeT>::operator =(ObjectTypeT *source)
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
    Int32 fooI(void) { fprintf(stderr, "A::fooI %d\n", aid); return 0; }
    Int32 barI(A *)  { fprintf(stderr, "A::barI %d\n", aid); return 0; }

    void fooO(void) { fprintf(stderr, "A::fooO %d\n", aid); }
    void barO(A &)  { fprintf(stderr, "A::barO %d\n", aid); }

    void fooP(void) { fprintf(stderr, "A::fooP %d\n", aid); }
    void barP(Pointer<A> &)  { fprintf(stderr, "A::barP %d\n", aid); }

    Int32 fooIP(void) { fprintf(stderr, "A::fooIP %d\n", aid); return 0; }
    Int32 barIP(Pointer<A> &)  { fprintf(stderr, "A::barIP %d\n", aid); 
                                      return 0; }

    Int32 fooIO(void) { fprintf(stderr, "A::fooIO %d\n", aid); return 0; }
    Int32 barIO(A &)  { fprintf(stderr, "A::barIO %d\n", aid); return 0; }

    void     foo1(     Int32 &arg1) 
    {
        fprintf(stderr, "A::foo1 %d %d\n", aid, arg1);
    };

    void     bar1(A *, Int32 arg1)
    {
        fprintf(stderr, "A::bar1 %d %d\n", aid, arg1);
    };

    Int32 foo2(Int32 &arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 bar2(A *, Int32 &arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };


    void     foo1O(     Int32 &arg1) 
    {
        fprintf(stderr, "A::foo1O %d %d\n", aid, arg1);
    };

    void     bar1O(A &, Int32 &arg1)
    {
        fprintf(stderr, "A::bar1O %d %d\n", aid, arg1);
    };


    void     foo1P(     Int32 &arg1) 
    {
        fprintf(stderr, "A::foo1P %d %d\n", aid, arg1);
    };

    void     bar1P(Pointer<A> &, Int32 &arg1)
    {
        fprintf(stderr, "A::bar1P %d %d\n", aid, arg1);
    };



    Int32 foo2O(Int32 &arg1) 
    { 
        fprintf(stderr, "A::foo2O %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 bar2O(A &, Int32 &arg1) 
    { 
        fprintf(stderr, "A::bar2O %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 foo2P(Int32 &arg1) 
    { 
        fprintf(stderr, "A::foo2P %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 bar2P(Pointer<A> &, Int32 &arg1) 
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
    Int32 fooI(void) { fprintf(stderr, "A::fooI %d\n", aid); return 0; }
    Int32 barI(A *)  { fprintf(stderr, "A::barI %d\n", aid); return 0; }

    void fooO(void) { fprintf(stderr, "A::fooO %d\n", aid); }
    void barO(A &)  { fprintf(stderr, "A::barO %d\n", aid); }

    void fooP(void) { fprintf(stderr, "A::fooP %d\n", aid); }
    void barP(Pointer<A> &)  { fprintf(stderr, "A::barP %d\n", aid); }

    Int32 fooIP(void) { fprintf(stderr, "A::fooIP %d\n", aid); return 0; }
    Int32 barIP(Pointer<A> &)  { fprintf(stderr, "A::barIP %d\n", aid); 
                                      return 0; }

    Int32 fooIO(void) { fprintf(stderr, "A::fooIO %d\n", aid); return 0; }
    Int32 barIO(A &)  { fprintf(stderr, "A::barIO %d\n", aid); return 0; }

    void     foo1(     Int32 arg1) 
    {
        fprintf(stderr, "A::foo1 %d %d\n", aid, arg1);
    };

    void     bar1(A *, Int32 &arg1)
    {
        fprintf(stderr, "A::bar1 %d %d\n", aid, arg1);
    };

    Int32 foo2(Int32 arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 bar2(A *, Int32 &arg1) 
    { 
        fprintf(stderr, "A::foo2 %d %d\n", aid, arg1); 
        return 0;
    };


    void     foo1O(     Int32 arg1) 
    {
        fprintf(stderr, "A::foo1O %d %d\n", aid, arg1);
    };

    void     bar1O(A &, Int32 &arg1)
    {
        fprintf(stderr, "A::bar1O %d %d\n", aid, arg1);
    };


    void     foo1P(     Int32 &arg1) 
    {
        fprintf(stderr, "A::foo1P %d %d\n", aid, arg1);
    };

    void     bar1P(Pointer<A> &, Int32 &arg1)
    {
        fprintf(stderr, "A::bar1P %d %d\n", aid, arg1);
    };



    Int32 foo2O(Int32 arg1) 
    { 
        fprintf(stderr, "A::foo2O %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 bar2O(A &, Int32 &arg1) 
    { 
        fprintf(stderr, "A::bar2O %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 foo2P(Int32 arg1) 
    { 
        fprintf(stderr, "A::foo2P %d %d\n", aid, arg1); 
        return 0;
    };

    Int32 bar2P(Pointer<A> &, Int32 &arg1) 
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
    static Int32 fooI(A *) { fprintf(stderr, "B::fooI\n"); return 0; };

    static void     fooO (A &) { fprintf(stderr, "B::fooO\n"); };
    static Int32 fooIO(A &) { fprintf(stderr, "B::fooIO\n"); return 0; };

    static void     fooP  (Pointer<A> &) { fprintf(stderr, "B::fooP\n"); };
    static Int32 fooIP (Pointer<A> &) { fprintf(stderr, "B::fooIP\n"); 
                                              return 0; };

    static Int32 bar(A*, Int32 &uiArg2)
    {
        fprintf(stderr, "B::bar : %d\n", uiArg2);
        return 0;
    }

    static void foobar(A*, Int32 &uiArg2)
    {
        fprintf(stderr, "B::foobar : %d\n", uiArg2);
    }

    static Int32 barO(A &, Int32 &uiArg2)
    {
        fprintf(stderr, "B::barO : %d\n", uiArg2);
        return 0;
    }

    static Int32 barP(Pointer<A> &, Int32 &uiArg2)
    {
        fprintf(stderr, "B::barP : %d\n", uiArg2);
        return 0;
    }

    static void foobarO(A &, Int32 &uiArg2)
    {
        fprintf(stderr, "B::foobarO : %d\n", uiArg2);
    }

    static void foobarP(Pointer<A> &, Int32 &uiArg2)
    {
        fprintf(stderr, "B::foobarP : %d\n", uiArg2);
    }

    Int32 foo2P(Int32 &arg1) 
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

void fooP(Pointer<A> &pA)
{
    fprintf(stderr, "fooP\n");
    pA->foo();
}

Int32 fooIP(Pointer<A> &pA)
{
    fprintf(stderr, "fooIP\n");
    pA->foo();
    return 0;
}

Int32 fooI(A*)
{
    fprintf(stderr, "fooI\n");
    return 0;
}

Int32 fooIO(A &)
{
    fprintf(stderr, "fooIO\n");
    return 0;
}

Int32 bar(A *, Int32 &uiArg2)
{
    fprintf(stderr, "bar : %d\n", uiArg2);
    return 0;
}

void foobar(A *, Int32 &uiArg2)
{
    fprintf(stderr, "foobar : %d\n", uiArg2);
}

Int32 barO(A &, Int32 &uiArg2)
{
    fprintf(stderr, "barO : %d\n", uiArg2);
    return 0;
}

void foobarO(A &, Int32 &uiArg2)
{
    fprintf(stderr, "foobarO : %d\n", uiArg2);
}

Int32 barP(Pointer<A> &, Int32 &uiArg2)
{
    fprintf(stderr, "barP : %d\n", uiArg2);
    return 0;
}

void foobarP(Pointer<A> &, Int32 &uiArg2)
{
    fprintf(stderr, "foobarP : %d\n", uiArg2);
}


typedef Functor1Base<void,     A &> Functor1O;
typedef Functor1Base<Int32, A &> Functor1IO;

typedef Functor1Base<void,     A *> Functor1;
typedef Functor1Base<Int32, A *> Functor1I;

typedef Functor2Base<void,     A &, Int32 &> Functor2O;
typedef Functor2Base<Int32, A &, Int32 &> Functor2IO;

typedef Functor2Base<void,     A *, Int32 &> Functor2;
typedef Functor2Base<Int32, A *, Int32 &> Functor2I;

typedef Functor1Base<void,     Pointer<A> &> Functor1P;
typedef Functor1Base<Int32, Pointer<A> &> Functor1IP;

typedef Functor2Base<void,     Pointer<A> &, Int32 &> Functor2P;
typedef Functor2Base<Int32, Pointer<A> &, Int32 &> Functor2IP;

void testfunctor1(void)
{
    fprintf(stderr, "testfunctor1 started\n");
    
    vector<Functor1> funcVec;
    vector<Functor1I> funcVecI;

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
    
    vector<Functor1O> funcVec;
    vector<Functor1IO> funcVecI;

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

    vector<Functor2>  funcVec;
    vector<Functor2I> funcVecI;

    A a1;
    A1 a2;

    Int32 j;
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

    vector<Functor2O>  funcVec;
    vector<Functor2IO> funcVecI;

    A a1;
    A1 a2;

    Int32 j;
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
    UInt32 i;

    fprintf(stderr, "testpointer1 start\n");    
    
    A a;
    A1 a1;

    Pointer<A> pA;
    Pointer<A1> pA1;

    pA = &a;
    pA1 = &a1;

    vector<Functor1P> funcVec;

    funcVec.push_back(osgFunctionFunctor1(fooP));
    funcVec.push_back(osgFunctionFunctor1(&B::fooP));
    funcVec.push_back(osgMethodFunctor1CPtr<void, Pointer<A> >(&A::fooP));
    funcVec.push_back(osgMethodFunctor1CPtr<void, 
                                            Pointer<A> &,
                                            Pointer<A1> >(pA1, &A1::barP));


    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVec[i].call(pA);
    }
    

    fprintf(stderr, "testpointer1 end\n");    
}

void testpointer1a(void)
{
    UInt32 i;

    fprintf(stderr, "testpointer1a start\n");    
    
    A a;
    A1 a1;

    Pointer<A> pA;
    Pointer<A1> pA1;

    pA = &a;
    pA1 = &a1;

    vector<Functor1IP> funcVec;

    funcVec.push_back(osgFunctionFunctor1(fooIP));
    funcVec.push_back(osgFunctionFunctor1(&B::fooIP));
    funcVec.push_back(osgMethodFunctor1CPtr<Int32, 
                                            Pointer<A> >(&A::fooIP));
    funcVec.push_back(osgMethodFunctor1CPtr<Int32, 
                                            Pointer<A> &,
                                            Pointer<A1> >(pA1, &A1::barIP));

    
    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        funcVec[i].call(pA);
    }
    

    fprintf(stderr, "testpointer1a end\n");    
}


void testpointer2(void)
{
    UInt32 i;

    fprintf(stderr, "testpointer2 start\n");    
    
    A a;
    A1 a1;
    
    Pointer<A> pA;
    Pointer<A1> pA1;

    pA = &a;
    pA1 = &a1;

    Int32 j;

    vector<Functor2P> funcVec;
    vector<Functor2IP> funcVecI;

    funcVec.push_back(osgFunctionFunctor2(foobarP));
    funcVec.push_back(osgFunctionFunctor2(&B::foobarP));

    funcVec.push_back(osgMethodFunctor2CPtr<void, 
                                           Pointer<A>,
                                           Int32 &>(&A::foo1P));
    funcVec.push_back(osgMethodFunctor2CPtr<void, 
                                            Pointer<A> &, 
                                            Int32      &, 
                                            Pointer<A1> >(pA1, &A1::bar1P));

    for(i = 0; i < funcVec.size(); i++)
    {
        fprintf(stderr, "%d : \t", i);
        j = i;
        funcVec[i].call(pA, j);
    }
    
    funcVecI.push_back(osgMethodFunctor2BaseCPtr<Int32, 
                                                 Pointer<A>,
                                                 Pointer<B>, 
                                                 Int32 &>(&B::foo2P));

    funcVecI.push_back(osgMethodFunctor2CPtr<Int32, 
                                             Pointer<A> &, 
                                             Int32      &,
                                             Pointer<A1> >(pA1, 
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
