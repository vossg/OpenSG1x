
#include "OSGAnimTest.h"

#include "OSGGenericInterpolator.h"

OSG_BEGIN_NAMESPACE

//Animation *_animations = 0;           //!< list of _animations

/*! Add/Create a animation
    \param objname name of the destination object
    \param destNr number of the destination field/matrix
    \return v2a animation object
*/

Animation *addAnim(InterpolatorBase::InterpolType  type, 
                   char                           *name, 
                   char                           *objname,
                   int                             destNr, 
                   float                           duration)
{       
    std::cerr << "addAnim(type=" << InterpolatorBase::type2String(type)
              << ", name="       << name
              << ", target="     <<  objname
              << ", duration="   << duration 
              << " )"            << std::endl;
         
    InterpolatorBase*           interpol   = 0;
    PositionInterpolatorPtr     posInterpol=0;
    OrientationInterpolatorPtr      oriInterpol=0;

    std::string                 sname   (name);
    std::string                 sobjname(objname);

    if(type == InterpolatorBase::Position)
    {
        posInterpol = new PositionInterpolator(type);

        interpol    = posInterpol;
    }
    else if( type == InterpolatorBase::Orientation )
    {
        oriInterpol = new OrientationInterpolator(type);

        interpol    = oriInterpol;
    }   
    
    if(interpol)
    {
        interpol->setName      (sname   );
        interpol->setTargetName(sobjname);
        interpol->setDuration  (duration);

        if(destNr >= 0)     //hack: is a position interpolator
        {
            interpol->setScaleInterpol(false);
        }
        else if(destNr == -1)
        {
            interpol->setScaleInterpol(true);
        }       

        if(Animation::getAnim())
        {
            Animation::getAnim()->addInterpolator(interpol);
        }
        else
        {
            std::cerr 
                << "OSGAnimTest::addAnim()\t Animation::getAnim() is NULL\n";
        }
    } 
    
    return Animation::getAnim();
}

OSG_END_NAMESPACE
