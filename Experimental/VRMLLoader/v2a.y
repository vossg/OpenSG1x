%{

#ifdef WIN32
#include <malloc.h>
#endif

#include <stdio.h>
//#include "vrml2anim.h"
#include "OSGAnimTest.h"
#include "OSGAnimation.h"
#include "OSGMFVecTypes.h"
#include "OSGGenericInterpolator.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* global variables */
int   v2aLineNumber = 1;
float v2aDuration;
int   v2aKeySize;

/* functions */
int v2a_error (char *s);  
extern int v2a_lex ();  

%}

%union
{
    float fval;
    char sval[1024];
}

%start v2a

%token POSITION ORIENTATION COORDINATE SCALAR COLOR NORMAL C_OPEN C_CLOSE E_OPEN E_CLOSE COMMA KEY KEYVALUE KEYSIZE
%token DURATION
%token <sval> STRING 
%token <fval> NUMBER

%type <sval> anim_def posanim_def orianim_def coordanim_def scanim_def colanim_def noranim_def duration

%%


v2a         :   /* leer */
            |   v2a anim_def 
            ;


anim_def    :   posanim_def
            |   orianim_def 
            |   coordanim_def
            |   scanim_def
            |   colanim_def
            |   noranim_def
            |   duration
            ;

duration    :   DURATION NUMBER
                {
                    v2aDuration = $2;
                }
            ;
            
posanim_def :   STRING STRING NUMBER POSITION 
                {
                    OSG::addAnim( OSG::InterpolatorBase::Position, $1, $2, (int)$3,
                                     v2aDuration );
                }
                C_OPEN  
                key_def
                posval_def
                C_CLOSE
                {
                }
            ;

coordanim_def   :   STRING STRING NUMBER COORDINATE 
                {
                    OSG::addAnim( OSG::InterpolatorBase::Position, $1, $2, (int)$3,
                                     v2aDuration );
                }
                C_OPEN
                keysize_def 
                key_def
                coordval_def
                C_CLOSE
                {
                }
            ;
                
keysize_def     :   KEYSIZE NUMBER
                {
                    v2aKeySize=(int) $2;
                }
                ;               

orianim_def :   STRING STRING NUMBER ORIENTATION 
                {
                    OSG::addAnim( OSG::InterpolatorBase::Orientation, $1, $2, (int)$3,
                                     v2aDuration );
                }
                C_OPEN  
                key_def
                orival_def
                C_CLOSE
                {
                }
            ;
            
scanim_def  :   STRING STRING NUMBER SCALAR 
                {
                    OSG::addAnim( OSG::InterpolatorBase::Other, $1, $2, (int)$3,
                                     v2aDuration );
                }
                C_OPEN  
                key_def
                scval_def
                C_CLOSE
                {
                }
            ;
            
colanim_def :   STRING STRING NUMBER COLOR
                {
                    OSG::addAnim( OSG::InterpolatorBase::Other, $1, $2, (int)$3,
                                     v2aDuration );
                }
                C_OPEN  
                key_def
                colval_def
                C_CLOSE
                {
                }
            ;

noranim_def :   STRING STRING NUMBER NORMAL 
                {
                    OSG::addAnim( OSG::InterpolatorBase::Other, $1, $2, (int)$3,
                                     v2aDuration );
                }
                C_OPEN
                keysize_def 
                key_def
                norval_def
                C_CLOSE
                {
                }
            ;
                
key_def     :   KEY E_OPEN key_list E_CLOSE
            ;
            
key_list    :   /* leer */
            |   key_list NUMBER opt_comma
            {
                if ( OSG::Animation::getAnim() )
                    OSG::Animation::getAnim()->currentInterpolator()->addKey( $2 );
            }
            ;
            
opt_comma   :   /* leer */
            |   COMMA
            ;
            
            
posval_def  :   KEYVALUE E_OPEN posval_list E_CLOSE
            ;
            
posval_list :   /* leer */
            |   posval_list NUMBER NUMBER NUMBER opt_comma
            {
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->currentInterpolator()))
                {                   
                    OSG::Vec3f   value;
                    OSG::PositionInterpolatorPtr currInterpol;
                    
                    currInterpol = dynamic_cast<OSG::PositionInterpolatorPtr>
                                        ( OSG::Animation::getAnim()->currentInterpolator() );
                                        
                    if( currInterpol->nrOfKeyValues() <= currInterpol->nrOfKeys() )
                    {
                        value.setValues( $2, $3, $4 );
                        currInterpol->addKeyValue( value );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys for position!\n");
                }
            }
            ;

coordval_def    :   KEYVALUE E_OPEN coordval_list E_CLOSE
            ;

coordval_list   :   /* leer */
            |   coordval_list NUMBER NUMBER NUMBER opt_comma
            {
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    static v2aCoordinateField *coordField=NULL;
                    static int index=0;
                    
                    if (index==v2aKeySize) index=0; // loop the index
                    
                    if (index==0)       // start of a new keyValue
                    {
                        float key;
                        int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                        if (pos<OSG::Animation::getAnim()->getKeys()->size())
                        {
                            key=(*OSG::Animation::getAnim()->getKeys())[pos];
                            coordField=new v2aCoordinateField();
                            OSG::Animation::getAnim()->addListItem(
                                        new v2aListItem( key, coordField ) );
                        }
                        else
                        {
                            fprintf(stderr, "v2a_parse(): not enough keys!\n");
                            coordField=NULL;
                        }
                    }
                    
                    // add the new coordinate
                    if (coordField)
                    {
                        coordField->addCoord( $2, $3, $4 );
                        index++;
                    }
                }
                */
                cerr << "v2a_parse.y::ignoring coordinate-interpolator (temporarly)\n";
            }
            ;   
            
orival_def  :   KEYVALUE E_OPEN orival_list E_CLOSE
            ;
            
orival_list :   /* leer */
            |   orival_list NUMBER NUMBER NUMBER NUMBER opt_comma
            {
                
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->currentInterpolator()))
                {
                    OSG::Quaternion     value;
                    OSG::OrientationInterpolatorPtr currInterpol;
                    OSG::Real32         x,y,z,w;

                    currInterpol = dynamic_cast<OSG::OrientationInterpolatorPtr>
                                        ( OSG::Animation::getAnim()->currentInterpolator() );   
                    
                    if( currInterpol->nrOfKeyValues() <= currInterpol->nrOfKeys() )
                    {

                        //cerr << $2 << ", " << $3 << ", " << $4 << ", " << $5 << endl;
                        value.setValueAsAxisRad( OSG::Vec3f($2, $3, $4), $5 );
                        //cerr << "#" << value << endl;
                        value.getValueAsAxisRad( x,y,z,w );
                        //cerr << "#" << x << ", " << y << ", " << z << ", " << w << endl;
                        currInterpol->addKeyValue( value );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys for orientation!\n");
                }
            }
            ;

scval_def   :   KEYVALUE E_OPEN scval_list E_CLOSE
            ;
            
scval_list  :   /* leer */
            |   scval_list NUMBER opt_comma
            {
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    float key;
                    v2aScalarField *field;
                    int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                    if (pos<OSG::Animation::getAnim()->getKeys()->size())
                    {
                        key=(*OSG::Animation::getAnim()->getKeys())[pos];
                        field=new v2aScalarField( $2 );
                        OSG::Animation::getAnim()->addListItem( new v2aListItem(key, field) );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys!\n");
                }
                */
                cerr << "v2a_parse.y::ignoring scalar-interpolators\n";
            }
            ;

colval_def  :   KEYVALUE E_OPEN colval_list E_CLOSE
            ;

colval_list :   /* leer */
            |   colval_list NUMBER NUMBER NUMBER opt_comma
            {
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    float key;
                    v2aColorField *field;
                    int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                    if (pos<OSG::Animation::getAnim()->getKeys()->size())
                    {
                        key=(*OSG::Animation::getAnim()->getKeys())[pos];
                        field=new v2aColorField( $2, $3, $4 );
                        OSG::Animation::getAnim()->addListItem( new v2aListItem( key, field ) );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys!\n");
                }
                */
                cerr << "v2a_parse.y::ignoring color-interpolators\n";              
            }
            ;

norval_def  :   KEYVALUE E_OPEN norval_list E_CLOSE
            ;

norval_list :   /* leer */
            |   norval_list NUMBER NUMBER NUMBER opt_comma
            {
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    static v2aNormalField *normalField=NULL;
                    static int index=0;
                    
                    if (index==v2aKeySize) index=0; // loop the index
                    
                    if (index==0)       // start of a new keyValue
                    {
                        float key;
                        int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                        if (pos<OSG::Animation::getAnim()->getKeys()->size())
                        {
                            key=(*OSG::Animation::getAnim()->getKeys())[pos];
                            normalField=new v2aNormalField();
                            OSG::Animation::getAnim()->addListItem(
                                        new v2aListItem( key, normalField ) );
                        }
                        else
                        {
                            fprintf(stderr, "v2a_parse(): not enough keys!\n");
                            normalField=NULL;
                        }
                    }
                    
                    // add the new coordinate
                    if (normalField)
                    {
                        normalField->addNormal( $2, $3, $4 );
                        index++;
                    }
                }
                */
                cerr << "v2a_parse.y::ignoring normal-interpolators\n";             
            }
            ;   

        
%%


int v2a_error (char *s)  /* Called by v2a_parse on error */
{
  printf ("-----> %s in Line %d \n", s, v2aLineNumber);
  return v2aLineNumber;
}

#ifdef __cplusplus
}
#endif


