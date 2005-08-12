
#include <OSGConfig.h>


#include <iostream>

#ifdef __linux
#include <time.h>
#endif

#include <OSGBaseFunctions.h>
//#include "OSGFunctors.h"

using namespace OSG;

Int32 repeats;
Int32 worksize;
Real32 lowtime,hightime;

#define WORK(res) \
{                                           \
    (res) = 0;                              \
    for (Int32 i=0; i < worksize; i++ )     \
        (res) = (res) + ( i / 100.0f );     \
}

#ifndef WIN32

#include <time.h>
#include <sys/times.h>

struct tms t_struct;

// return current time
#define now()   ( times( &t_struct), t_struct.tms_utime )
// time difference in seconds

#ifdef __linux
#define delta(a,b)  ( ( a - b ) / float(sysconf(_SC_CLK_TCK)) )
#else
#define delta(a,b)  ( ( a - b ) / float(CLK_TCK) )
#endif

#else /* use system time. Not a good idea, but better than nothing */

#include <OSGTime.h>

// return current time
#define now()   getSystemTime()
// time difference in seconds
#define delta(a,b)  ( a - b )

#endif

// print the result

#define pres(text,time)                             \
    cerr << text << ": " << float((time) - basetime) / float(repeats) * 1e6 \
         << " us " << endl


// test sets

// simple function

Real32 function( Int32 )
{
    Real32 result;
    WORK(result);
    return result;
}

// method & virtual method

struct test
{
    virtual ~test() {}

    Real32 method( Int32 );

    virtual Real32 vmethod( Int32 );
};

Real32 test::method( Int32 )
{
    Real32 result;
    WORK(result);
    return result;
}

Real32 test::vmethod( Int32 )
{
    Real32 result;
    WORK(result);
    return result;
}


// Functors

//typedef Functor1Base<Real32, Int32> benchFunctor;


int main( int argc, char *argv[] )
{
#if 0
    Real32 result = 0;
    Int32 l;

    osgInit(argc, argv);

#ifdef WIN32
    cerr << "Warning: using wallclock time, results might be skewed!" << endl;
#endif

    repeats = 1000000;
    lowtime = 10;
    hightime = 12;

    // simple minded, good enough for this
    switch ( argc )
    {
    case 4: lowtime = atof( argv[2] );
            hightime = atof( argv[3] );
            cerr << "Times set to " << lowtime << " secs -> " << hightime
                 << " secs " << endl;
    case 2: repeats = atoi( argv[1] );
            cerr << "Repeats set to " << repeats << endl;
            break;
    case 1: break;
    default: cerr << "Usage: " << argv[0] << " [repeats [lowtime hightime]]" << endl;
            exit(1);
    }

    UInt32 start, stop;
    Real32 dur, basetime;

    // adjust worksize so that the loop is between LOWTIME and HIGHTIME seconds
    worksize = 10;
    Int32 lastworksize = worksize;
    cerr << "Calibrating..";
    do
    {
        cerr << ".";
        start = now();
        for ( l = 0; l < repeats; l++ )
            WORK(result);
        stop = now();
        dur = delta( stop, start );

        worksize = worksize * float( hightime + lowtime ) / 2.0f / float(dur);

        if ( worksize == lastworksize )
            worksize += ( dur < lowtime ) ? 1 : -1;

        lastworksize = worksize;
    }
    while ( dur < lowtime || dur > hightime );

    cerr << " worksize=" << worksize << endl;

    // run the tests

    // direct loop, for base timing
    start = now();
    {
    for ( l = 0; l < repeats; l++ )
        WORK(result);
    }
    stop = now();
    basetime = delta(stop,start);


    // simple function
    start = now();
    for ( l = 0; l < repeats; l++ )
        result += function( l );
    stop = now();
    pres("Simple function", delta(stop,start));

    test t;
    test *tp = &t;

    // method
    start = now();
    for ( l = 0; l < repeats; l++ )
        t.method( l );
    stop = now();
    pres("Method", delta(stop,start));

    // method via pionter
    start = now();
    for ( l = 0; l < repeats; l++ )
        tp->method( l );
    stop = now();
    pres("Method via pointer", delta(stop,start));

    // virtual method via pionter
    start = now();
    for ( l = 0; l < repeats; l++ )
        tp->vmethod( l );
    stop = now();
    pres("Virtual method via pointer", delta(stop,start));


    // Functors

    benchFunctor f;
    benchFunctor *fp = &f;      // needed for polymorphy

    // simple function functor
    f = osgFunctionFunctor1( function );
    start = now();
    for ( l = 0; l < repeats; l++ )
        fp->call( l );
    stop = now();
    pres("Function functor", delta(stop,start));

    // method functor
    f = osgMethodFunctor1Ptr( &t, &test::method );
    start = now();
    for ( l = 0; l < repeats; l++ )
        fp->call( l );
    stop = now();
    pres("Method functor", delta(stop,start));

    // virtual method functor
    f = osgMethodFunctor1Ptr( &t, &test::vmethod );
    start = now();
    for ( l = 0; l < repeats; l++ )
        fp->call( l );
    stop = now();
    pres("Virtual method functor", delta(stop,start));

    // just use result, otherwise naked is optimized away
    return result > 0 ? 1 : 0;
#endif
    return 0;
}
