#ifndef _OSGMANIPULATORMANAGER_H_
#define _OSGMANIPULATORMANAGER_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGNodeFields.h>

#include "OSGManipulator.h"
#include "OSGMoveManipulator.h"
#include "OSGRotateManipulator.h"
#include "OSGScaleManipulator.h"

class OSG_SYSTEMLIB_DLLMAPPING ManipulatorManager
{
public:
    enum    ManipulatorType { ROTATE, SCALE, TRANSLATE };
    
    NodePtr    createManipulator(ManipulatorType type);
    void    changeManipulator(ManipulatorType type);
    bool    activate(NodePtr n);
    
    void    setTarget            ( const NodePtr &value );
    void    setViewport            ( const ViewportPtr &value );
    bool    isActive            ( void );
    
    void    mouseMove            ( Int16 x, Int16 y );
    void    mouseButtonPress    ( UInt16 button, Int16 x, Int16 y );
    void    mouseButtonRelease    ( UInt16 button, Int16 x, Int16 y );
private:
    ManipulatorPtr    _maniC;
    ManipulatorType _currentType;
    NodePtr            _target;
    ViewportPtr        _viewport;
};

#endif // _OSGMANIPULATORMANAGER_H_
