#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGManipulatorManager.h"


// TODO: der ManipulatorManager merkt sich den Core, nicht den Node des
// Manipulators. Damit besteht ein Problem mit Multi-Parents, das nicht waere,
// wenn der ManipulatorManager sich den Node merken wuerde!?!

NodePtr ManipulatorManager::createManipulator(ManipulatorType type)
{
    NodePtr maniN = Node::create();
    
    switch (type)
    {
        case ROTATE:
            _maniC = RotateManipulator::create();
            break;
        case SCALE:
            _maniC = ScaleManipulator::create();
            break;
        case TRANSLATE:
            _maniC = MoveManipulator::create();    
            break;
    }
    
    _currentType = type;
    
    beginEditCP(maniN);
    {    
        maniN->setCore( _maniC );
    }
    endEditCP(  maniN);
    
    return maniN;
}


// TODO: 
void ManipulatorManager::changeManipulator(ManipulatorType type)
{
    if (type != _currentType)
    {
        MFNodePtr parents;
        NodePtr   maniN;
        
        parents = _maniC->getParents();        
        if ( !parents.isEmpty() )
        {
            maniN = parents[0];
            
            beginEditCP( maniN );
            {    
                maniN->setCore( NullFC ); // TODO: delete ok?
            }
            endEditCP(   maniN );
            
            _maniC = NullFC;

            switch (type)
            {
                case TRANSLATE:
                    _maniC = MoveManipulator::create();
                    break;
                case ROTATE:
                    _maniC = RotateManipulator::create();
                    break;
                case SCALE:
                    _maniC = ScaleManipulator::create();
                    break;
            }
            
            _currentType = type;

            beginEditCP(maniN);
            {
                maniN->setCore( _maniC );
             }
            endEditCP(maniN);    

            beginEditCP(_maniC);
            {
                _maniC->setTarget(   _target );
                _maniC->setViewport( _viewport );
            }
            endEditCP(_maniC);
        }
        else
        {
            maniN = NullFC;
        }
    }
}

void ManipulatorManager::setTarget( const NodePtr &value )
{
    _maniC->setTarget(value);
    _target = value;
}

void ManipulatorManager::setViewport( const ViewportPtr &value )
{
    _maniC->setViewport(value);
    _viewport = value;
}

bool ManipulatorManager::isActive()
{
    return _maniC->getActive();
}

void ManipulatorManager::mouseMove( Int16 x, Int16 y )
{
    _maniC->mouseMove(x, y);
}

void ManipulatorManager::mouseButtonPress( UInt16 button, Int16 x, Int16 y )
{
    _maniC->mouseButtonPress(button, x, y);
}

void ManipulatorManager::mouseButtonRelease( UInt16 button, Int16 x, Int16 y )
{
    _maniC->mouseButtonRelease(button, x, y);
}

bool ManipulatorManager::activate(NodePtr n)
{
    if ( _maniC->hasSubHandle(n) )
    {
        _maniC->setActiveSubHandle(n);
        return true;
    }
    else
    {
        return false;
    }
}
