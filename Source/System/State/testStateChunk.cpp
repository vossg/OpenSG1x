
#include <OSGLog.h>

#include "OSGStateChunk.h"
#include "OSGTransformChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGLightChunk.h"
#include "OSGTextureChunk.h"

OSG_USING_NAMESPACE


int main( int argc, char *argv[] )
{
    osgInit(argc, argv);

    StateChunkClass::iterator it;

    std::cerr << "StateChunk classes:" << std::endl;

    for ( it = StateChunkClass::begin(); it != StateChunkClass::end(); it++ )
    {
        std::cerr << *it << std::endl;
    }

    // test values

    Matrix m1,m2;
    m1.setTranslate( 1,2,3 );

    Real32 r1 = 123.45, r2;
    UInt32 ui1 = 12345, ui2;

    Vec3f v31(1, 2, 3), v32;
    Vec4f v41(1, 2, 3, 4), v42;
    Color4f c41(1, 2, 3, 4), c42;

    // Test macros for simple set/get correspondence

#define testField( name, set,get, v1,v2,comp )                        \
    set(v1);                                                          \
    v2 = get();                                                       \
    std::cerr << name;                                                \
    if ( ! (comp) )                                                     \
    {                                                                 \
        std::cerr << " " << v1 << "!=" << v2 << "!!!" << std::endl;   \
        exit(1);                                                      \
    }                                                                 \
    else                                                              \
        std::cerr << " ok" << std::endl

#define testMatrixField( name, set, get )   \
    testField( name, set, get, m1, m2, m1.equals( m2, Eps ) )

#define testVec3fField( name, set, get )    \
    testField( name, set, get, v31, v32, v31.equals( v32, Eps ) )

#define testVec4fField( name, set, get )    \
    testField( name, set, get, v41, v42, v41.equals( v42, Eps ) )

#define testColor4fField( name, set, get )      \
    testField( name, set, get, c41, c42, (c41 == c42) )

#define testRealField( name, set, get )     \
    testField( name, set, get, r1, r2, r1 == r2 )

#define testUInt32Field( name, set, get )   \
    testField( name, set, get, ui1, ui2, r1 == r2 )

    // Transform Chunk

    TransformChunkPtr tchunk = TransformChunk::create();

    std::cerr << "Transform chunk class: " << tchunk->getClass()->getName()
              << ", id "
              << tchunk->getClassId() << ", numslots "
              << tchunk->getClass()->getNumSlots()
              << std::endl;

    testMatrixField( "TransformChunk: matrix", tchunk->setMatrix,
                     tchunk->getMatrix );

    // Material Chunk

    MaterialChunkPtr mchunk = MaterialChunk::create();

    std::cerr << "Material chunk class: " << mchunk->getClass()->getName()
              << ", id "
              << mchunk->getClassId() << ", numslots "
              << tchunk->getClass()->getNumSlots()
              << std::endl;

    testColor4fField( "MaterialChunk: diffuse", mchunk->setDiffuse,
                      mchunk->getDiffuse );
    testColor4fField( "MaterialChunk: ambient",
                      mchunk->setAmbient, mchunk->getAmbient );
    testColor4fField( "MaterialChunk: specular",
                      mchunk->setSpecular, mchunk->getSpecular );
    testColor4fField( "MaterialChunk: emission",
                      mchunk->setEmission, mchunk->getEmission );
    testRealField( "MaterialChunk: shininess",
                   mchunk->setShininess, mchunk->getShininess );

    // Light chunk

    LightChunkPtr lchunk = LightChunk::create();

    std::cerr << "Light chunk class: " 
              << lchunk->getClass()->getName() << ", id "
              << lchunk->getClassId() << ", numslots "
              << lchunk->getClass()->getNumSlots()
              << std::endl;

    testColor4fField( "LightChunk: diffuse", lchunk->setDiffuse,
                      lchunk->getDiffuse );
    testColor4fField( "LightChunk: ambient", lchunk->setAmbient,
                      lchunk->getAmbient );
    testColor4fField( "LightChunk: specular", lchunk->setSpecular,
                      lchunk->getSpecular );
    testVec4fField( "LightChunk: position", lchunk->setPosition,
                    lchunk->getPosition );
    testVec3fField( "LightChunk: direction", lchunk->setDirection,
                    lchunk->getDirection );
    testRealField( "LightChunk: exponent", lchunk->setExponent,
                   lchunk->getExponent);
    testRealField( "LightChunk: cutoff", lchunk->setCutoff, lchunk->getCutoff );
    testRealField( "LightChunk: exponent", lchunk->setExponent,
                   lchunk->getExponent );
    testRealField( "LightChunk: constant attenuation",
                   lchunk->setConstantAttenuation,
                   lchunk->getConstantAttenuation );
    testRealField( "LightChunk: linear attenuation",
                   lchunk->setLinearAttenuation,
                   lchunk->getLinearAttenuation );
    testRealField( "LightChunk: quadratic attenuation",
                   lchunk->setQuadraticAttenuation,
                   lchunk->getQuadraticAttenuation );


    // Texture chunk

    TextureChunkPtr xchunk = TextureChunk::create();

    std::cerr << "Texture chunk class: " << xchunk->getClass()->getName()
              << ", id "
              << xchunk->getClassId() << ", numslots "
              << xchunk->getClass()->getNumSlots()
              << std::endl;

    testUInt32Field( "TextureChunk: minFilter", xchunk->setMinFilter,
                     xchunk->getMinFilter );
    testUInt32Field( "TextureChunk: magFilter", xchunk->setMagFilter,
                     xchunk->getMagFilter );
    testUInt32Field( "TextureChunk: wrapR", xchunk->setWrapR,
                     xchunk->getWrapR );
    testUInt32Field( "TextureChunk: wrapS", xchunk->setWrapS,
                     xchunk->getWrapS );
    testUInt32Field( "TextureChunk: wrapT", xchunk->setWrapT,
                     xchunk->getWrapT );


    return 0;
}
