
#include <stdio.h>

#pragma set woff 1116,3201,3303

#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <Inventor/fields/SoFields.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/nodes/SoNodes.h>

#include <Performer/pf/pfNode.h>
#include <Performer/pf/pfGroup.h>
#include <Performer/pf/pfSwitch.h>
#include <Performer/pf/pfDCS.h>
#include <Performer/pf/pfGeode.h>
#include <Performer/pr/pfGeoSet.h>
#include <Performer/pr/pfGeoState.h>
#include <Performer/pr/pfGeoMath.h>
#include <Performer/pr/pfLinMath.h>
#include <Performer/pr/pfMaterial.h>

#include <Cosmo3D/csLinMath.h>
#include <Cosmo3D/csGeoMath.h>
#include <Cosmo3D/csNode.h>
#include <Cosmo3D/csGroup.h>
#include <Cosmo3D/csSwitch.h>
#include <Cosmo3D/csTransform.h>
#include <Cosmo3D/csGeoSet.h>
#include <Cosmo3D/csGeometry.h>
#include <Cosmo3D/csAppearance.h>
#include <Cosmo3D/csFields.h>
#include <Cosmo3D/csIndexedFaceSet.h>

#include <OSGBaseTypes.h>
#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGVolume.h>
#include <OSGBoxVolume.h>
#include <OSGSphereVolume.h>
#include <OSGFrustumVolume.h>
#include <OSGDynamicVolume.h>
#include <OSGField.h>
#include <OSGSFSysTypes.h>
#include <OSGSFVecTypes.h>
#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGGeometry.h>

using namespace osg;

void _pline(char *name, char *iname, int isize, char *pname, int psize, 
	char *cname, int csize, char *oname, int osize );
	
#define print( name, inv, perf, cosmo, opsg ) \
_pline( name, #inv, sizeof(inv), #perf, sizeof(perf), #cosmo, sizeof(cosmo), #opsg, \
	sizeof(opsg) )

int main( int argc, char *argv[] )
{

	cout << endl << endl << "Sizes: some common datastructure sizes." << endl;
	cout << "note: these are simple sizeof() sizes, so " 
		 << "referenced structures are not counted." << endl
		 << "Not all of them have exactly the same functions, "
		 << "they are just similar." << endl		 
		 << "Structure         Inventor        Performer       Cosmo3D         OpenSG" << endl << endl;

	print( "Vec3f", SbVec3f, pfVec3, csVec3f, OSGVec3f );
	print( "Matrix", SbMatrix, pfMatrix, csMatrix4f, OSGMatrix );
	print( "Box", SbBox3f, pfBox, csBoxBound, OSGBoxVolume);
	print( "Sphere", SbSphere, pfSphere, csSphereBound, OSGSphereVolume);
	print( "Frustum", SbViewVolume, pfFrustum, csFrustum, OSGFrustumVolume);
	print( "Dynamic Volume", void*, void*, void*, OSGDynamicVolume);
	print( "Field", SoField, void*, csField, OSGField);
	print( "Int8 SField", void*, void*, void*, OSGSFUInt8);
	print( "Int32 SField", SoSFInt32, void*, csSFInt, OSGSFInt32);
	print( "Vec3f SField", SoSFVec3f, void*, csSFVec3f, OSGSFVec3f);
	print( "String SField", SoSFString, void*, csSFString, OSGSFString);
	print( "Volume SField", void*, void*, void*, OSGSFVolume);
	print( "NodePtr SField", void*, void*, void*, OSGSFNodePtr);
	print( "NodeCorePtr SField", void*, void*, void*, OSGSFNodeCorePtr);
	print( "Int8 MField", void*, void*, csMFByte, OSGMFInt8);
	print( "Int32 MField", SoMFInt32, void*, csMFByte, OSGMFInt8);
	print( "Vec3f MField", SoMFVec3f, void*, csMFVec3f, OSGMFVec3f);
	print( "NodePtr MField", void*, void*, void*, OSGMFNodePtr);
	print( "FieldContainer", SoFieldContainer, void*, void*, OSGFieldContainer);
	print( "Node", SoNode, pfNode, csNode, OSGNode);
	print( "NodeCore", void*, void*, void*, OSGNodeCore);
	print( "Group", SoGroup, pfGroup, csGroup, OSGGroup);
	print( "Switch", SoSwitch, pfSwitch, csSwitch, void*);
	print( "Transform", SoTransform, pfDCS, csTransform, OSGTransform);
	print( "Geometry", SoIndexedFaceSet, pfGeode, csGeometry, OSGGeometry);
	print( "GeoSet", void*, pfGeoSet, csGeoSet, void*);
	print( "Material", SoMaterial, pfMaterial, csAppearance, void*);

	cout << endl << "Some general stuff" << endl << endl;
	
	cout << "map<OSGUInt32, OSGPropertyPtr> " << sizeof(map<OSGUInt32, OSGPropertyPtr>) << endl;
	
	cout << endl;

	return 0;
}



#define NSIZE 15
#define FSIZE 15
#define LINELEN (FSIZE+1 + 4 * (NSIZE+1) + 1)

void pfield( char *base, char *name, int size )
{
	char buf[FSIZE+1];

	if ( ! strcmp(name, "void*" ) )
		return;
	
	if ( size > 100 )
		sprintf(buf,  "%d ",size );
	else if ( size > 10 )
		sprintf(buf, " %d ",size );
	else
		sprintf(buf,"  %d ",size );
	
	if ( strlen( name ) > FSIZE-4 )
		strncpy( buf+4, name + strlen(name) - (FSIZE-4), FSIZE-4 );
	else
		strcpy( buf+4, name );

	buf[FSIZE] = 0;
	memcpy( base, buf, strlen( buf ) );
}

void _pline(char *name, char *iname, int isize, char *pname, int psize, 
	char *cname, int csize, char *oname, int osize )
{
	char line[LINELEN];

	memset( line, ' ', LINELEN-1 );
	line[LINELEN-1] = 0;

	memcpy( line, name, min( (int)strlen(name), 15 ) );

	pfield( line + NSIZE+1, iname, isize );
	pfield( line + NSIZE+1 + 1 * (FSIZE+1), pname, psize );
	pfield( line + NSIZE+1 + 2 * (FSIZE+1), cname, csize );
	pfield( line + NSIZE+1 + 3 * (FSIZE+1), oname, osize );
	
	cout << line << endl;
}
