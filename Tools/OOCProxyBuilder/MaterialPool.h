// Material Pool keeper

#ifndef _MATERIALPOOL_H
#define _MATERIALPOOL_H

#include <map>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGMaterial.h>

class MaterialPool
{
  public:

    static OSG::UInt32 addMaterial(OSG::MaterialPtr mat);

    static OSG::MaterialPtr getMaterial(OSG::UInt32 ind);
    
  
  private:

    static std::vector<OSG::MaterialPtr> _mats;
    
    MaterialPool();
    ~MaterialPool();
    
    static MaterialPool *_the;
};

#endif
