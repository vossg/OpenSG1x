#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGTypedFunctors.h>
#include <OSGQuaternion.h>
#include <OSGDrawAction.h>

#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

#include <OSGBackground.h>
#include <OSGForeground.h>
#include <OSGImage.h>

#include <OSGLight.h>

#include "OSGPerspectiveShadowMap.h"
#include "OSGShadowViewport.h"
#include "OSGTreeRenderer.h"


//--------------------------------------------------------------------
#ifndef GL_CLAMP_TO_EDGE
#   define GL_CLAMP_TO_EDGE    0x812F
#endif
#ifndef GL_CLAMP_TO_BORDER_ARB
#   define GL_CLAMP_TO_BORDER_ARB  0x812D
#endif
#ifndef GL_ARB_depth_texture
#   define GL_DEPTH_COMPONENT16_ARB    0x81A5
#   define GL_DEPTH_COMPONENT24_ARB    0x81A6
#   define GL_DEPTH_COMPONENT32_ARB    0x81A7
#   define GL_TEXTURE_DEPTH_SIZE_ARB   0x884A
#   define GL_DEPTH_TEXTURE_MODE_ARB   0x884B
#endif
#ifndef GL_ARB_shadow
#   define GL_TEXTURE_COMPARE_MODE_ARB 0x884C
#   define GL_TEXTURE_COMPARE_FUNC_ARB 0x884D
#   define GL_COMPARE_R_TO_TEXTURE_ARB 0x884E
#endif
#ifndef GL_SGIX_depth_texture
#   define GL_DEPTH_COMPONENT16_SGIX   0x81A5
#   define GL_DEPTH_COMPONENT24_SGIX   0x81A6
#   define GL_DEPTH_COMPONENT32_SGIX   0x81A7
#endif
#ifndef GL_SGIX_shadow
#   define GL_TEXTURE_COMPARE_SGIX             0x819A
#   define GL_TEXTURE_COMPARE_OPERATOR_SGIX    0x819B
#   define GL_TEXTURE_LEQUAL_R_SGIX            0x819C
#   define GL_TEXTURE_GEQUAL_R_SGIX            0x819D
#endif
#ifndef GL_DEPTH_COMPONENT_ARB
#   define GL_DEPTH_COMPONENT_ARB            0x1902
#endif

//--------------------------------------------------------------------

OSG_USING_NAMESPACE


PerspectiveShadowMap::PerspectiveShadowMap(void)
{
}

PerspectiveShadowMap::PerspectiveShadowMap(ShadowViewport *source)
: TreeRenderer(source)
{

    _tiledeco = TileCameraDecorator::create();
    addRefCP(_tiledeco);

	_matrixdeco = MatrixCameraDecorator::create();
	addRefCP(_matrixdeco);

    _blender = BlendChunk::create();
    addRefCP(_blender);
    beginEditCP(_blender);
    {
        _blender->setAlphaFunc(GL_GEQUAL);
        _blender->setAlphaValue(0.99);
    }
    endEditCP(_blender);

    _dummy = makeCoredNode<Group>();
    addRefCP(_dummy);

	matrixCam = MatrixCamera::create();
}

PerspectiveShadowMap::~PerspectiveShadowMap(void)
{
	subRefCP(_tiledeco);
	subRefCP(_blender);
    subRefCP(_dummy);
	subRefCP(_matrixdeco);

}


void PerspectiveShadowMap::calcPerspective(Matrix &_LPM, Matrix &_LVM, UInt32 num)
{

	Matrix CPM, CVM;
	shadowVP->getCamera()->getViewing(CVM,shadowVP->getParent()->getWidth(),shadowVP->getParent()->getHeight());
	shadowVP->getCamera()->getProjection(CPM,shadowVP->getParent()->getWidth(),shadowVP->getParent()->getHeight());
	Matrix eyeProjView = CPM;
	eyeProjView.mult(CVM);
	Matrix invEyeProjView = eyeProjView;
	invEyeProjView.invert();

	//lightDir holen
	DirectionalLightPtr tmpDir = DirectionalLightPtr::dcast(shadowVP->_lights[num]);
	Vec3f lightDir = tmpDir->getDirection();
	if(tmpDir->getBeacon() != NullFC)
	{
	    Matrix m = tmpDir->getBeacon()->getToWorld();
        m.mult(lightDir);
    }
	lightDir.normalize();

	//ViewDir holen
	Vec3f viewDir(0,0,-1);
	Matrix m3 = shadowVP->getCamera()->getBeacon()->getToWorld();
    m3.mult(viewDir);
	viewDir.normalize();

	//Kamerapunkt holen
	Pnt3f eyePos(0,0,0);
	Matrix m2 = shadowVP->getCamera()->getBeacon()->getToWorld();
    m2.mult(eyePos);

	//Scene AABox Extrempunkte holen
	Pnt3f sceneMax = shadowVP->getSceneRoot()->getVolume().getMax();
	Pnt3f sceneMin = shadowVP->getSceneRoot()->getVolume().getMin();

	std::vector<Pnt3f> points;
	calcHull(&points, invEyeProjView, sceneMin, sceneMax, lightDir);

	//Kopie erstellen
	std::vector<Pnt3f> pointsCopy;
	for(UInt32 i=0; i<points.size(); i++) pointsCopy.push_back(points[i]);


	Real32 dotProd = viewDir.dot(lightDir);
	Real32 sinGamma;
	sinGamma = sqrt(1.0-dotProd*dotProd);

	//up berechnen
	Vec3f up99;
	calcUpVec2(up99,viewDir,lightDir);

	Matrix lView22;
	MatrixLookAt(lView22,eyePos,eyePos+lightDir,up99);
	lView22.invert();

	// Punkte ins neue KKS transformieren
	for(UInt32 i = 0; i<points.size(); i++)
	{
		Pnt3f tmpPnt(points[i][0],points[i][1],points[i][2]);
		lView22.multFullMatrixPnt(tmpPnt,tmpPnt);
		points[i] = tmpPnt;
	}

	// BBox um Punkte bestimmen
	Pnt3f min99, max99;
	calcCubicHull2(min99,max99,&points);

	//Near und Far berechnen (Light Space Perspective Shadow Maps)
	Real32 nearDist = 1.0;//shadowVP->getCamera()->getNear();
	Real32 factor = 1.0/sinGamma;
	Real32 z_n = factor*nearDist; 
	Real32 d = osgabs(max99[1]-min99[1]); 
	Real32 z_f = z_n + d*sinGamma;
	Real32 n = (z_n+sqrt(z_f*z_n))/sinGamma;
	Real32 f = n+d;

	Pnt3f pos99;
	pos99[0] = eyePos[0] + (up99[0] * (-(n-nearDist)*factor)); 
	pos99[1] = eyePos[1] + (up99[1] * (-(n-nearDist)*factor));
	pos99[2] = eyePos[2] + (up99[2] * (-(n-nearDist)*factor));

	Matrix lView222;
	MatrixLookAt(lView222,pos99,pos99+lightDir,up99);
	lView222.invert();

	// Lisp-Matrix erstellen
	Matrix lispMtx99(1,0,0,0,
					 0,(f+n)/(f-n),0,-2*f*n/(f-n),
					 0,0,1,0,
					 0,1,0,0);

	for(UInt32 i = 0; i<pointsCopy.size(); i++)
	{
		Pnt3f tmpPnt = pointsCopy[i];
		lView222.multFullMatrixPnt(tmpPnt,tmpPnt);
		lispMtx99.multFullMatrixPnt(tmpPnt,tmpPnt);
		pointsCopy[i] = tmpPnt;
	}

	calcCubicHull2(min99,max99,&pointsCopy);
	
	Matrix lProj;
	scaleTranslateToFit2(lProj,min99,max99);

	lProj.mult(lispMtx99);
	
	points.clear();
	pointsCopy.clear();

	_LPM = lProj;
	_LVM.mult(lView222);
}

void PerspectiveShadowMap::calcPerspectiveSpot(Matrix &_LPM, Matrix &_LVM, UInt32 num)
{

	Matrix CPM, CVM;
	shadowVP->getCamera()->getViewing(CVM,shadowVP->getParent()->getWidth(),shadowVP->getParent()->getHeight());
	shadowVP->getCamera()->getProjection(CPM,shadowVP->getParent()->getWidth(),shadowVP->getParent()->getHeight());

	Matrix LPM,LVM;
	shadowVP->_lightCameras[num]->getViewing(LVM,shadowVP->getParent()->getWidth(),shadowVP->getParent()->getHeight());
	shadowVP->_lightCameras[num]->getProjection(LPM,shadowVP->getParent()->getWidth(),shadowVP->getParent()->getHeight());
	Matrix LPVM;
	LPVM = LPM;
	LPVM.mult(LVM);

	Matrix eyeProjView = CPM;
	eyeProjView.mult(CVM);
	Matrix invEyeProjView = eyeProjView;
	invEyeProjView.invert();

	//Scene AABox Extrempunkte holen (Weltkoordinaten)
	Pnt3f sceneMax = shadowVP->getSceneRoot()->getVolume().getMax();
	Pnt3f sceneMin = shadowVP->getSceneRoot()->getVolume().getMin();

	Pnt3f bb0(sceneMin[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb1(sceneMax[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb2(sceneMax[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb3(sceneMin[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb4(sceneMin[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb5(sceneMax[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb6(sceneMax[0],sceneMax[1],sceneMax[2]);
	Pnt3f bb7(sceneMin[0],sceneMax[1],sceneMax[2]);

	//LightPos holen
	Pnt3f lPos;

	if(shadowVP->_lights[num]->getType() == PointLight::getClassType())
	{
		PointLightPtr tmpPoint;
		tmpPoint = PointLightPtr::dcast(shadowVP->_lights[num]);

		lPos = tmpPoint->getPosition();
	
		if(tmpPoint->getBeacon() != NullFC)
		{
			Matrix m = tmpPoint->getBeacon()->getToWorld();
			m.mult(lPos);
		}
	}

	if(shadowVP->_lights[num]->getType() == SpotLight::getClassType())
    {
        SpotLightPtr tmpSpot;
        tmpSpot = SpotLightPtr::dcast(shadowVP->_lights[num]);
        lPos = tmpSpot->getPosition();
        if(tmpSpot->getBeacon() != NullFC)
        {
			Matrix m = tmpSpot->getBeacon()->getToWorld();
            m.mult(lPos);
        }
    }

	//Wenn Lichtposition innerhalb der Scene-BB ist standard Shadow Mapping verwenden
	if(lPos[0] > sceneMin[0] && lPos[1] > sceneMin[1] && lPos[2] > sceneMin[2] && lPos[0] < sceneMax[0] && lPos[1] < sceneMax[1] && lPos[2] < sceneMax[2])
	{
		_LPM = LPM;
		_LVM = LVM;
	}

	//beleuchtet das Spotlight die komplette Szene? Wenn nicht -> standard Shadow Mapping
	else if(shadowVP->_lights[num]->getType() == SpotLight::getClassType() && !bbInsideFrustum(sceneMin,sceneMax,LPVM))
	{
		_LPM = LPM;
		_LVM = LVM;
	}

	else
	{

	//Lichtrichtung im Post-Perspektivischen Raum des Lichtes
	Vec3f lightDir(0,0,1);
	
	//Kamerapunkt holen
	Pnt3f eyePos(0,0,0);
	Matrix m2 = shadowVP->getCamera()->getBeacon()->getToWorld();
    m2.mult(eyePos);
	LPVM.multFullMatrixPnt(eyePos,eyePos);
	
	//Ist die Kamera hinter der Lichtquelle?
	bool cBehindL = false;
	if(eyePos[2] < -1) cBehindL = true;
	else if(eyePos[2] > 1) cBehindL = true;
	
	if(cBehindL)
	{
		//Trick: Near = -Far / Far = Near
		//Gibt leider Probleme im Grenzbereich ...
		/*double tmpNear;
		tmpNear = shadowVP->_lightCameras[num]->getNear();
		shadowVP->_lightCameras[num]->setNear(-shadowVP->_lightCameras[num]->getFar());
        shadowVP->_lightCameras[num]->setFar(tmpNear);
		shadowVP->_lightCameras[num]->getProjection(LPM,shadowVP->getParent()->getWidth(),shadowVP->getParent()->getHeight());
		LPVM = LPM;
		LPVM.mult(LVM);
		lightDir = Vec3f(0,0,-1);*/

		//Standard Shadow Mapping benutzen
		_LVM = LVM;
		_LPM = LPM;
	}

	else
	{

	//ViewDir
	Vec3f viewDir(0,0,-1);
	Matrix m3 = shadowVP->getCamera()->getBeacon()->getToWorld();
    m3.multMatrixVec(viewDir);
	LPVM.multMatrixVec(viewDir,viewDir);
	viewDir.normalize();
	
	//Body berechnen
	std::vector<Pnt3f> points;
	calcHull2(&points, invEyeProjView, sceneMin, sceneMax,LPVM);

	//Kopie erstellen
	std::vector<Pnt3f> pointsCopy;
	for(UInt32 i=0; i<points.size(); i++) pointsCopy.push_back(points[i]);
	
	bool correctAngle = false;
	if((osgabs(viewDir[0]) - osgabs(lightDir[0])) < 0.01 && (osgabs(viewDir[1]) - osgabs(lightDir[1])) < 0.01 && (osgabs(viewDir[2]) - osgabs(lightDir[2])) < 0.01)
	{
		viewDir[0] += 0.01;
		printf("LDir fast gleich VDir!\n");
		correctAngle = true;
	}

	double dotProd = viewDir.dot(lightDir);
	double sinGamma;
	sinGamma = sqrt(1.0-dotProd*dotProd);
	if(correctAngle) viewDir[0] -= 0.01;

	//up berechnen
	Vec3f up99;
	calcUpVec2(up99,viewDir,lightDir);
	
	Matrix lView22;
	MatrixLookAt(lView22,eyePos,eyePos+lightDir,up99);
	lView22.invert();

	// Punkte ins neue KKS transformieren
	for(UInt32 i = 0; i<points.size(); i++)
	{
		Pnt3f tmpPnt(points[i][0],points[i][1],points[i][2]);
		lView22.multFullMatrixPnt(tmpPnt,tmpPnt);
		points[i] = tmpPnt;
	}

	// BBox um Punkte bestimmen
	Pnt3f min99, max99;
	calcCubicHull2(min99,max99,&points);

	Real32 factor = 1.0/sinGamma;

	Real32 nearDist = 1.0-sinGamma;
	if(nearDist < 0.01) nearDist = 0.01;
	
	Real32 z_n = factor*nearDist; //often 1 
	Real32 d = osgabs(max99[1]-min99[1]); //perspective transform depth //light space y extents
	Real32 z_f = z_n + d*sinGamma;
	Real32 n = (z_n+sqrt(z_f*z_n))/sinGamma;
	Real32 f = n+d;

	Pnt3f pos99;

	pos99[0] = eyePos[0] + (up99[0] * -(n-nearDist));
	pos99[1] = eyePos[1] + (up99[1] * -(n-nearDist));
	pos99[2] = eyePos[2] + (up99[2] * -(n-nearDist));

	Matrix lView222;
	MatrixLookAt(lView222,pos99,pos99+lightDir,up99);
	lView222.invert();


	// Lisp-Matrix erstellen
	Matrix lispMtx99(1,0,0,0,
					 0,(f+n)/(f-n),0,-2*f*n/(f-n),
					 0,0,1,0,
					 0,1,0,0);

	for(UInt32 i = 0; i<pointsCopy.size(); i++)
	{
		Pnt3f tmpPnt = pointsCopy[i];
		lView222.multFullMatrixPnt(tmpPnt,tmpPnt);
		lispMtx99.multFullMatrixPnt(tmpPnt,tmpPnt);
		pointsCopy[i] = tmpPnt;
	}

	calcCubicHull2(min99,max99,&pointsCopy);

	Matrix lProj;
	scaleTranslateToFit2(lProj,min99,max99);
	
	Matrix rh2lh;
	rh2lh.setIdentity();
	rh2lh.setScale(1.0,1.0,-1.0);
	
	lProj.mult(lispMtx99);
	lProj.multLeft(rh2lh);

	points.clear();
	pointsCopy.clear();

	_LPM = lProj;
	_LPM.mult(lView222);
	_LPM.mult(LPM);
	_LVM = LVM;
	}
	}
}


void PerspectiveShadowMap::calcHull(std::vector<Pnt3f> *points, Matrix invEyeProjMatrix, Pnt3f sceneMin, Pnt3f sceneMax, Vec3f lightDir) 
{
	//Unit Cube
	Pnt3f vf0(-1,-1,-1);
	Pnt3f vf1(1,-1,-1);
	Pnt3f vf2(1,1,-1);
	Pnt3f vf3(-1,1,-1);
	Pnt3f vf4(-1,-1,1);
	Pnt3f vf5(1,-1,1);
	Pnt3f vf6(1,1,1);
	Pnt3f vf7(-1,1,1);

	//transform to World Coordinates
	invEyeProjMatrix.multFullMatrixPnt(vf0);
	invEyeProjMatrix.multFullMatrixPnt(vf1);
	invEyeProjMatrix.multFullMatrixPnt(vf2);
	invEyeProjMatrix.multFullMatrixPnt(vf3);
	invEyeProjMatrix.multFullMatrixPnt(vf4);
	invEyeProjMatrix.multFullMatrixPnt(vf5);
	invEyeProjMatrix.multFullMatrixPnt(vf6);
	invEyeProjMatrix.multFullMatrixPnt(vf7);

	//Scene Bounding Box Points
	Pnt3f bb0(sceneMin[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb1(sceneMax[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb2(sceneMax[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb3(sceneMin[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb4(sceneMin[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb5(sceneMax[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb6(sceneMax[0],sceneMax[1],sceneMax[2]);
	Pnt3f bb7(sceneMin[0],sceneMax[1],sceneMax[2]);

	Pnt3f bboxSidesPnts[6][4];
	//Front
	bboxSidesPnts[0][0] = bb0;
	bboxSidesPnts[0][1] = bb1;
	bboxSidesPnts[0][2] = bb2;
	bboxSidesPnts[0][3] = bb3;
	//Back
	bboxSidesPnts[1][0] = bb4;
	bboxSidesPnts[1][1] = bb5;
	bboxSidesPnts[1][2] = bb6;
	bboxSidesPnts[1][3] = bb7;
	//Left
	bboxSidesPnts[2][0] = bb0;
	bboxSidesPnts[2][1] = bb4;
	bboxSidesPnts[2][2] = bb7;
	bboxSidesPnts[2][3] = bb3;
	//Right
	bboxSidesPnts[3][0] = bb1;
	bboxSidesPnts[3][1] = bb5;
	bboxSidesPnts[3][2] = bb6;
	bboxSidesPnts[3][3] = bb2;
	//Top
	bboxSidesPnts[4][0] = bb3;
	bboxSidesPnts[4][1] = bb2;
	bboxSidesPnts[4][2] = bb6;
	bboxSidesPnts[4][3] = bb7;
	//Bottom
	bboxSidesPnts[5][0] = bb0;
	bboxSidesPnts[5][1] = bb1;
	bboxSidesPnts[5][2] = bb5;
	bboxSidesPnts[5][3] = bb4;



	//Build Planes of BBox
	Plane bboxSides[6];
	//Front
	bboxSides[0] = Plane(bb0,bb1,bb2);
	//Back
	bboxSides[1] = Plane(bb7,bb6,bb5);
	//Left
	bboxSides[2] = Plane(bb0,bb3,bb7);
	//Right
	bboxSides[3] = Plane(bb2,bb1,bb5);
	//Top
	bboxSides[4] = Plane(bb6,bb7,bb3);
	//Bottom
	bboxSides[5] = Plane(bb5,bb1,bb0);

	//Build Planes of View Frustum
	//Front
	Pnt3f vfI[6][20];
	Pnt3f vfO[20];
	UInt32 outCount;

	//Define View Frustum as Clip Polygons
	//Front
	vfI[0][0] = vf0;
	vfI[0][1] = vf1;
	vfI[0][2] = vf2;
	vfI[0][3] = vf3;
	//Back
	vfI[1][0] = vf4;
	vfI[1][1] = vf5;
	vfI[1][2] = vf6;
	vfI[1][3] = vf7;
	//Left
	vfI[2][0] = vf0;
	vfI[2][1] = vf4;
	vfI[2][2] = vf7;
	vfI[2][3] = vf3;
	//Right
	vfI[3][0] = vf1;
	vfI[3][1] = vf5;
	vfI[3][2] = vf6;
	vfI[3][3] = vf2;
	//Top
	vfI[4][0] = vf3;
	vfI[4][1] = vf2;
	vfI[4][2] = vf6;
	vfI[4][3] = vf7;
	//Bottom
	vfI[5][0] = vf0;
	vfI[5][1] = vf1;
	vfI[5][2] = vf5;
	vfI[5][3] = vf4;

	//Punktgroesse merken
	UInt32 vfSize[6];
	for(UInt32 i=0;i<6;i++) vfSize[i] = 4;

	UInt32 sum = 0;
	Pnt3f allPoints[100];

	// speichert die anzahl der durchgeführten Clips
	UInt32 sumClip = 0;

	for (UInt32 i = 0; i<6; i++)
	{
	//Kamerafrustum
	outCount = vfSize[i];

		for (UInt32 j = 0; j<6; j++)
		{
		//BBox
			if (vfSize[i] != 0)
			{
				outCount = bboxSides[j].clip(vfI[i],vfO,vfSize[i]);
				sumClip++;
				vfSize[i] = outCount;

				for (UInt32 k=0;k<outCount;k++)
				{
					vfI[i][k] = vfO[k];
				}
			}
		}

		for (UInt32 k=0;k<vfSize[i];k++)
		{
			points->push_back(vfO[k]);
		}
	}

	UInt32 oldSize;
	oldSize = points->size();

	if(pntInFrontOf(vf0,vf1,vf2,bb0) && pntInFrontOf(vf7,vf6,vf5,bb0) && pntInFrontOf(vf0,vf3,vf7,bb0) && pntInFrontOf(vf2,vf1,vf5,bb0) && pntInFrontOf(vf6,vf7,vf3,bb0) && pntInFrontOf(vf5,vf1,vf0,bb0)) points->push_back(bb0);
	if(pntInFrontOf(vf0,vf1,vf2,bb1) && pntInFrontOf(vf7,vf6,vf5,bb1) && pntInFrontOf(vf0,vf3,vf7,bb1) && pntInFrontOf(vf2,vf1,vf5,bb1) && pntInFrontOf(vf6,vf7,vf3,bb1) && pntInFrontOf(vf5,vf1,vf0,bb1)) points->push_back(bb1);
	if(pntInFrontOf(vf0,vf1,vf2,bb2) && pntInFrontOf(vf7,vf6,vf5,bb2) && pntInFrontOf(vf0,vf3,vf7,bb2) && pntInFrontOf(vf2,vf1,vf5,bb2) && pntInFrontOf(vf6,vf7,vf3,bb2) && pntInFrontOf(vf5,vf1,vf0,bb2)) points->push_back(bb2);
	if(pntInFrontOf(vf0,vf1,vf2,bb3) && pntInFrontOf(vf7,vf6,vf5,bb3) && pntInFrontOf(vf0,vf3,vf7,bb3) && pntInFrontOf(vf2,vf1,vf5,bb3) && pntInFrontOf(vf6,vf7,vf3,bb3) && pntInFrontOf(vf5,vf1,vf0,bb3)) points->push_back(bb3);
	if(pntInFrontOf(vf0,vf1,vf2,bb4) && pntInFrontOf(vf7,vf6,vf5,bb4) && pntInFrontOf(vf0,vf3,vf7,bb4) && pntInFrontOf(vf2,vf1,vf5,bb4) && pntInFrontOf(vf6,vf7,vf3,bb4) && pntInFrontOf(vf5,vf1,vf0,bb4)) points->push_back(bb4);
	if(pntInFrontOf(vf0,vf1,vf2,bb5) && pntInFrontOf(vf7,vf6,vf5,bb5) && pntInFrontOf(vf0,vf3,vf7,bb5) && pntInFrontOf(vf2,vf1,vf5,bb5) && pntInFrontOf(vf6,vf7,vf3,bb5) && pntInFrontOf(vf5,vf1,vf0,bb5)) points->push_back(bb5);
	if(pntInFrontOf(vf0,vf1,vf2,bb6) && pntInFrontOf(vf7,vf6,vf5,bb6) && pntInFrontOf(vf0,vf3,vf7,bb6) && pntInFrontOf(vf2,vf1,vf5,bb6) && pntInFrontOf(vf6,vf7,vf3,bb6) && pntInFrontOf(vf5,vf1,vf0,bb6)) points->push_back(bb6);
	if(pntInFrontOf(vf0,vf1,vf2,bb7) && pntInFrontOf(vf7,vf6,vf5,bb7) && pntInFrontOf(vf0,vf3,vf7,bb7) && pntInFrontOf(vf2,vf1,vf5,bb7) && pntInFrontOf(vf6,vf7,vf3,bb7) && pntInFrontOf(vf5,vf1,vf0,bb7)) points->push_back(bb7);
	
	//Punkte gegen Lichtrichtung hinzufügen

	UInt32 sumPoints = points->size();
	for (UInt32 i = 0; i<sumPoints; i++)
	{
		for(UInt32 j=0; j<6; j++)
		{
			//schneitet ein Vektor von dem Punkt gegen die Lichtrichtung die BBox? Eventuell zufügen!
			Pnt3f pntCut1,pntCut2;
			pntCut1 = (*points)[i];
			pntCut2 = (*points)[i];
			pntCut2[0] += (-1000*lightDir[0]);
			pntCut2[1] += (-1000*lightDir[1]);
			pntCut2[2] += (-1000*lightDir[2]);

			Line line(pntCut2,pntCut1);
			Pnt3f inter;
			if(bboxSides[j].intersect(line,inter))
			{
				Vec3f side1,side2,side3,side4;
				side1 = bboxSidesPnts[j][1]-bboxSidesPnts[j][0];
				side2 = bboxSidesPnts[j][2]-bboxSidesPnts[j][1];
				side3 = bboxSidesPnts[j][3]-bboxSidesPnts[j][2];
				side4 = bboxSidesPnts[j][0]-bboxSidesPnts[j][3];

				Vec3f pntLine1,pntLine2,pntLine3,pntLine4;
				pntLine1 = inter - bboxSidesPnts[j][0];
				pntLine2 = inter - bboxSidesPnts[j][1];
				pntLine3 = inter - bboxSidesPnts[j][2];
				pntLine4 = inter - bboxSidesPnts[j][3];

				//Liegt der Punkt auf der BBox-Seite? Dann zufügen
				if( side1.dot(pntLine1) >= 0 && 
					side2.dot(pntLine2) >= 0 &&
					side3.dot(pntLine3) >= 0 &&
					side4.dot(pntLine4) >= 0)
				{
					points->push_back(inter);
				}
			}
		}
	}

	//printf("\nPoints hat insgesammt %u Punkte!\n",points->size());
}

void PerspectiveShadowMap::calcHull2(std::vector<Pnt3f> *points, Matrix invEyeProjMatrix, Pnt3f sceneMin, Pnt3f sceneMax, Matrix LPVM) 
{
	//Die Funktion clippt das Kamera Frustum mit der Szenen Bounding Box und liefert eine Punktmenge zurück

	//Unit Cube
	Pnt3f vf0(-1,-1,-1);
	Pnt3f vf1(1,-1,-1);
	Pnt3f vf2(1,1,-1);
	Pnt3f vf3(-1,1,-1);
	Pnt3f vf4(-1,-1,1);
	Pnt3f vf5(1,-1,1);
	Pnt3f vf6(1,1,1);
	Pnt3f vf7(-1,1,1);

	//transform to World Coordinates
	invEyeProjMatrix.multFullMatrixPnt(vf0);
	invEyeProjMatrix.multFullMatrixPnt(vf1);
	invEyeProjMatrix.multFullMatrixPnt(vf2);
	invEyeProjMatrix.multFullMatrixPnt(vf3);
	invEyeProjMatrix.multFullMatrixPnt(vf4);
	invEyeProjMatrix.multFullMatrixPnt(vf5);
	invEyeProjMatrix.multFullMatrixPnt(vf6);
	invEyeProjMatrix.multFullMatrixPnt(vf7);

	//Scene Bounding Box Points
	Pnt3f bb0(sceneMin[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb1(sceneMax[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb2(sceneMax[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb3(sceneMin[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb4(sceneMin[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb5(sceneMax[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb6(sceneMax[0],sceneMax[1],sceneMax[2]);
	Pnt3f bb7(sceneMin[0],sceneMax[1],sceneMax[2]);

	//Build Planes of BBox
	Plane bboxSides[6];
	//Front
	bboxSides[0] = Plane(bb0,bb1,bb2);
	//Back
	bboxSides[1] = Plane(bb7,bb6,bb5);
	//Left
	bboxSides[2] = Plane(bb0,bb3,bb7);
	//Right
	bboxSides[3] = Plane(bb2,bb1,bb5);
	//Top
	bboxSides[4] = Plane(bb6,bb7,bb3);
	//Bottom
	bboxSides[5] = Plane(bb5,bb1,bb0);

	//Build Planes of View Frustum
	//Front
	Pnt3f vfI[6][20];
	Pnt3f vfO[20];
	UInt32 outCount;

	//Define View Frustum as Clip Polygons
	//Front
	vfI[0][0] = vf0;
	vfI[0][1] = vf1;
	vfI[0][2] = vf2;
	vfI[0][3] = vf3;
	//Back
	vfI[1][0] = vf4;
	vfI[1][1] = vf5;
	vfI[1][2] = vf6;
	vfI[1][3] = vf7;
	//Left
	vfI[2][0] = vf0;
	vfI[2][1] = vf4;
	vfI[2][2] = vf7;
	vfI[2][3] = vf3;
	//Right
	vfI[3][0] = vf1;
	vfI[3][1] = vf5;
	vfI[3][2] = vf6;
	vfI[3][3] = vf2;
	//Top
	vfI[4][0] = vf3;
	vfI[4][1] = vf2;
	vfI[4][2] = vf6;
	vfI[4][3] = vf7;
	//Bottom
	vfI[5][0] = vf0;
	vfI[5][1] = vf1;
	vfI[5][2] = vf5;
	vfI[5][3] = vf4;

	//Punktgroesse merken
	UInt32 vfSize[6];
	for(UInt32 i=0;i<6;i++) vfSize[i] = 4;

	UInt32 sum = 0;
	Pnt3f allPoints[100];

	// speichert die anzahl der durchgeführten Clips
	UInt32 sumClip = 0;

	for (UInt32 i = 0; i<6; i++)
	{
	//Kamerafrustum
	outCount = vfSize[i];

		for (UInt32 j = 0; j<6; j++)
		{
		//BBox
			if (vfSize[i] != 0)
			{
				outCount = bboxSides[j].clip(vfI[i],vfO,vfSize[i]);
				sumClip++;
				vfSize[i] = outCount;

				for (UInt32 k=0;k<outCount;k++)
				{
					vfI[i][k] = vfO[k];
				}
			}
		}

		for (UInt32 k=0;k<vfSize[i];k++)
		{
			points->push_back(vfO[k]);
		}
	}

	//TODO: check, unter der Szene klappts manchmal nicht
	UInt32 oldSize;
	oldSize = points->size();

	if(pntInFrontOf(vf0,vf1,vf2,bb0) && pntInFrontOf(vf7,vf6,vf5,bb0) && pntInFrontOf(vf0,vf3,vf7,bb0) && pntInFrontOf(vf2,vf1,vf5,bb0) && pntInFrontOf(vf6,vf7,vf3,bb0) && pntInFrontOf(vf5,vf1,vf0,bb0)) points->push_back(bb0);
	if(pntInFrontOf(vf0,vf1,vf2,bb1) && pntInFrontOf(vf7,vf6,vf5,bb1) && pntInFrontOf(vf0,vf3,vf7,bb1) && pntInFrontOf(vf2,vf1,vf5,bb1) && pntInFrontOf(vf6,vf7,vf3,bb1) && pntInFrontOf(vf5,vf1,vf0,bb1)) points->push_back(bb1);
	if(pntInFrontOf(vf0,vf1,vf2,bb2) && pntInFrontOf(vf7,vf6,vf5,bb2) && pntInFrontOf(vf0,vf3,vf7,bb2) && pntInFrontOf(vf2,vf1,vf5,bb2) && pntInFrontOf(vf6,vf7,vf3,bb2) && pntInFrontOf(vf5,vf1,vf0,bb2)) points->push_back(bb2);
	if(pntInFrontOf(vf0,vf1,vf2,bb3) && pntInFrontOf(vf7,vf6,vf5,bb3) && pntInFrontOf(vf0,vf3,vf7,bb3) && pntInFrontOf(vf2,vf1,vf5,bb3) && pntInFrontOf(vf6,vf7,vf3,bb3) && pntInFrontOf(vf5,vf1,vf0,bb3)) points->push_back(bb3);
	if(pntInFrontOf(vf0,vf1,vf2,bb4) && pntInFrontOf(vf7,vf6,vf5,bb4) && pntInFrontOf(vf0,vf3,vf7,bb4) && pntInFrontOf(vf2,vf1,vf5,bb4) && pntInFrontOf(vf6,vf7,vf3,bb4) && pntInFrontOf(vf5,vf1,vf0,bb4)) points->push_back(bb4);
	if(pntInFrontOf(vf0,vf1,vf2,bb5) && pntInFrontOf(vf7,vf6,vf5,bb5) && pntInFrontOf(vf0,vf3,vf7,bb5) && pntInFrontOf(vf2,vf1,vf5,bb5) && pntInFrontOf(vf6,vf7,vf3,bb5) && pntInFrontOf(vf5,vf1,vf0,bb5)) points->push_back(bb5);
	if(pntInFrontOf(vf0,vf1,vf2,bb6) && pntInFrontOf(vf7,vf6,vf5,bb6) && pntInFrontOf(vf0,vf3,vf7,bb6) && pntInFrontOf(vf2,vf1,vf5,bb6) && pntInFrontOf(vf6,vf7,vf3,bb6) && pntInFrontOf(vf5,vf1,vf0,bb6)) points->push_back(bb6);
	if(pntInFrontOf(vf0,vf1,vf2,bb7) && pntInFrontOf(vf7,vf6,vf5,bb7) && pntInFrontOf(vf0,vf3,vf7,bb7) && pntInFrontOf(vf2,vf1,vf5,bb7) && pntInFrontOf(vf6,vf7,vf3,bb7) && pntInFrontOf(vf5,vf1,vf0,bb7)) points->push_back(bb7);
	
	//Body in LK transformieren
	for(UInt32 i = 0; i<points->size(); i++)
	{
		Pnt3f tmpPnt((*points)[i]);
		LPVM.multFullMatrixPnt(tmpPnt,tmpPnt);
		(*points)[i] = tmpPnt;
	}

	UInt32 sumPoints = points->size();
	for (UInt32 i = 0; i<sumPoints; i++)
	{
		Pnt3f pntCut2 = (*points)[i];
		pntCut2[2] = -1.0;
		points->push_back(pntCut2);
	}
}


void PerspectiveShadowMap::calcBodyVec(Vec3f &dir, Pnt3f eyePos, std::vector<Pnt3f> *points) 
{
	for(UInt32 i = 0; i < points->size(); i++) {
		Vec3f p;
		for(UInt32 j = 0; j < 3; j++) 
		{
			p[j] = (*points)[i][j]-eyePos[j];
		}
		dir[0] += p[0];
		dir[1] += p[1];
		dir[2] += p[2];
	}
	dir.normalize();
}

void PerspectiveShadowMap::printMatrix(Matrix m)
{
	printf("Printing Matrix...\n");
	Real32 *mPtr = m.getValues();
	printf(" %f, %f, %f, %f \n %f, %f, %f, %f \n %f, %f, %f, %f \n %f, %f, %f, %f \n",mPtr[0], mPtr[1], mPtr[2], mPtr[3], mPtr[4], mPtr[5], mPtr[6], mPtr[7], mPtr[8], mPtr[9], mPtr[10], mPtr[11], mPtr[12], mPtr[13], mPtr[14], mPtr[15]);
}

void PerspectiveShadowMap::printPoint(Pnt3f p)
{
	printf("Printing Point...\n");
	printf("%f, %f, %f\n",p.x(),p.y(),p.z());
}

void PerspectiveShadowMap::calcUpVec2(Vec3f &up, Vec3f viewDir, Vec3f lightDir) 
{
	Vec3f left;
	left = lightDir.cross(viewDir);
	up = left.cross(lightDir);
	up.normalize();
}

// p1 bis p3 gegen den Uhrzeigersinn angeben
bool PerspectiveShadowMap::pntInFrontOf(Pnt3f p1, Pnt3f p2, Pnt3f p3, Pnt3f p) 
{
	Vec3f dir1, dir2, testdir, norm;
	dir1 = p2 - p1;
	dir2 = p3 - p2;
	dir1.normalize();
	dir2.normalize();
	norm = dir1.cross(dir2);
	norm.normalize();
	testdir = p2 - p;
	testdir.normalize();
	if (testdir.dot(norm) < 0) return false;
	else return true;
}

void PerspectiveShadowMap::calcCubicHull2(Pnt3f &min, Pnt3f &max, std::vector<Pnt3f> *points) 
{
	min = (*points)[0];
	max = (*points)[0];
	
	for(UInt32 i = 1; i < points->size(); i++) 
	{
		for(UInt32 j = 0; j < 3; j++) 
		{
			if((*points)[i][j] < min[j]) min[j] = (*points)[i][j];
			if((*points)[i][j] > max[j]) max[j] = (*points)[i][j];
		}
	}
}

void PerspectiveShadowMap::scaleTranslateToFit2(Matrix &mat, const Pnt3f vMin, const Pnt3f vMax) 
{
	Real32 output[16];
	output[ 0] = 2/(vMax[0]-vMin[0]);
	output[ 4] = 0;
	output[ 8] = 0;
	output[12] = -(vMax[0]+vMin[0])/(vMax[0]-vMin[0]);

	output[ 1] = 0;
	output[ 5] = 2/(vMax[1]-vMin[1]);
	output[ 9] = 0;
	output[13] = -(vMax[1]+vMin[1])/(vMax[1]-vMin[1]);

	output[ 2] = 0;
	output[ 6] = 0;
	output[10] = 2/(vMax[2]-vMin[2]);
	output[14] = -(vMax[2]+vMin[2])/(vMax[2]-vMin[2]);

	output[ 3] = 0;
	output[ 7] = 0;
	output[11] = 0;
	output[15] = 1;
	mat.setValueTransposed(output[0],output[1],output[2],output[3],output[4],output[5],output[6],output[7],output[8],output[9],output[10],output[11],output[12],output[13],output[14],output[15]);
}


bool PerspectiveShadowMap::bbInsideFrustum(Pnt3f sceneMin, Pnt3f sceneMax, Matrix LPVM)
{
	Matrix iLPVM(LPVM);
	iLPVM.invert();

	LPVM.multFullMatrixPnt(sceneMin);
	LPVM.multFullMatrixPnt(sceneMax);

	//Scene Bounding Box Points
	Pnt3f bb0(sceneMin[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb1(sceneMax[0],sceneMin[1],sceneMin[2]);
	Pnt3f bb2(sceneMax[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb3(sceneMin[0],sceneMax[1],sceneMin[2]);
	Pnt3f bb4(sceneMin[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb5(sceneMax[0],sceneMin[1],sceneMax[2]);
	Pnt3f bb6(sceneMax[0],sceneMax[1],sceneMax[2]);
	Pnt3f bb7(sceneMin[0],sceneMax[1],sceneMax[2]);

	bool isIn[8];
	for(UInt32 i = 0; i<8; i++) isIn[i] = false;

	if(bb0[0] < 1 && bb0[0] > -1 && bb0[1] < 1 && bb0[1] > -1 && bb0[2] < 1 && bb0[2] > -1) isIn[0] = true;
	if(bb1[0] < 1 && bb1[0] > -1 && bb1[1] < 1 && bb1[1] > -1 && bb1[2] < 1 && bb1[2] > -1)	isIn[1] = true;
	if(bb2[0] < 1 && bb2[0] > -1 && bb2[1] < 1 && bb2[1] > -1 && bb2[2] < 1 && bb2[2] > -1)	isIn[2] = true;
	if(bb3[0] < 1 && bb3[0] > -1 && bb3[1] < 1 && bb3[1] > -1 && bb3[2] < 1 && bb3[2] > -1) isIn[3] = true;
	if(bb4[0] < 1 && bb4[0] > -1 && bb4[1] < 1 && bb4[1] > -1 && bb4[2] < 1 && bb4[2] > -1) isIn[4] = true;
	if(bb5[0] < 1 && bb5[0] > -1 && bb5[1] < 1 && bb5[1] > -1 && bb5[2] < 1 && bb5[2] > -1) isIn[5] = true;
	if(bb6[0] < 1 && bb6[0] > -1 && bb6[1] < 1 && bb6[1] > -1 && bb6[2] < 1 && bb6[2] > -1) isIn[6] = true;
	if(bb7[0] < 1 && bb7[0] > -1 && bb7[1] < 1 && bb7[1] > -1 && bb7[2] < 1 && bb7[2] > -1) isIn[7] = true;
	
	if(isIn[0] && isIn[1] && isIn[2] && isIn[3] && isIn[4] && isIn[5] && isIn[6] && isIn[7]) return true;
	else return false;
}


void PerspectiveShadowMap::createShadowMaps(RenderActionBase* action)
{
    Real32 vpTop,vpBottom,vpLeft,vpRight;
    
    // Saving original Viewport-Dimensions
    vpTop = shadowVP->getTop();
    vpBottom = shadowVP->getBottom();
    vpLeft = shadowVP->getLeft();
    vpRight = shadowVP->getRight();

    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_TRUE);

    // disable all lights more speed
    for(UInt32 i = 0; i < shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
            shadowVP->_lights[i]->setOn(false);
    }
    
    // deactivate exclude nodes:
    for(UInt32 i = 0; i < shadowVP->getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(false);
    }
    
	for(UInt32 i = 0; i< shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
        {
            // we use a tiledecorator to create shadow maps with
            // a higher resolutions than the viewport or the screen.
			Matrix LPM, LVM;// = MatrixCameraPtr::dcast(shadowVP->_lightCameras[i])->getProjectionMatrix();
			Matrix CPM,CVM,CVPM;

			matrixCam->setProjectionMatrix(_perspectiveLPM[i]);
			matrixCam->setModelviewMatrix(_perspectiveLVM[i]);
			
			beginEditCP(_tiledeco);
            _tiledeco->setDecoratee(matrixCam);
            _tiledeco->setFullSize(shadowVP->getMapSize(), shadowVP->getMapSize());
			endEditCP(_tiledeco);

			action->setCamera    (_tiledeco.getCPtr());

			Real32 imgHeight = shadowVP->getMapSize();
			Real32 winHeight = shadowVP->getParent()->getHeight();
			Real32 imgWidth = shadowVP->getMapSize();
			Real32 winWidth = shadowVP->getParent()->getWidth();
			UInt32 x1, x2, y1, y2, tw, th;
				
			for (y1=0; y1 < imgHeight; y1 += winHeight)
				{
					y2 = osgMin((float)(y1+winHeight-1), (float)(imgHeight-1));
					th = y2 - y1 + 1;
					
					for (x1=0; x1 < imgWidth; x1 += winWidth)
					{
						x2 = osgMin((float)(x1+winWidth-1), (float)(imgWidth-1));
						tw = x2 - x1 + 1;
						
						// set tile size to maximal renderable size
						beginEditCP(_tiledeco);
							_tiledeco->setSize(  x1/(float)imgWidth,     y1/(float)imgHeight,	(x2+1)/(float)imgWidth, (y2+1)/(float)imgHeight);
						endEditCP(_tiledeco);
						
						beginEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
											  shadowVP->BottomFieldMask | shadowVP->TopFieldMask);
							shadowVP->setSize(0, 0, tw-1, th-1);
						endEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
											shadowVP->BottomFieldMask | shadowVP->TopFieldMask);
						
						glClear(GL_DEPTH_BUFFER_BIT);
						shadowVP->_poly->activate(action,0);

						action->apply(shadowVP->getRoot());
						// check is this necessary.
						action->getWindow()->validateGLObject(shadowVP->_texChunks[i]->getGLId());

						shadowVP->_poly->deactivate(action,0);
        
						//----------Shadow-Texture-Parameters and Indices-------------
                
						//glBindTexture(GL_TEXTURE_2D,shadowVP->_texChunks[i]->getGLId());
                        glBindTexture(GL_TEXTURE_2D, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
						if(glGetError() != GL_NO_ERROR)
						    SWARNING << "Error on binding Texture!" << endLog;    


							glCopyTexSubImage2D(GL_TEXTURE_2D, 0, x1, y1, 0, 0, tw, th);
						
					
							if(glGetError() != GL_NO_ERROR)
						   SWARNING << "Error on copying Texture!" << endLog;    
        
						glBindTexture(GL_TEXTURE_2D,0);
						if(glGetError() != GL_NO_ERROR)
						    SWARNING << "Error on releasing Texture!" << endLog;    
        
						if(glGetError() != GL_NO_ERROR)
						    SWARNING << "Error while Texture-Creation!" << endLog;
						
					}
				}

			}
		}


    // activate exclude nodes:
    for(UInt32 i = 0; i < shadowVP->getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(true);
    }

    // enable all lights.
    for(UInt32 i = 0; i< shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
            shadowVP->_lights[i]->setOn(true);
    }

    //-------Restoring old states of Window and Viewport----------
    
    beginEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
                          shadowVP->BottomFieldMask | shadowVP->TopFieldMask);
    {
        shadowVP->setSize(vpLeft,vpBottom,vpRight,vpTop);
    }
    endEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
                        shadowVP->BottomFieldMask | shadowVP->TopFieldMask);

    action->setCamera(shadowVP->getCamera().getCPtr());
    
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glShadeModel(GL_SMOOTH);
}

void PerspectiveShadowMap::projectShadowMaps(RenderActionBase* action)
{

    Matrix viewMatrix, projectionMatrix, biasMatrix;
    Vec4f s,t,r,q;

    biasMatrix.setIdentity();
    biasMatrix.setScale(0.5);
    biasMatrix.setTranslate(0.5,0.5,0.5);

    GLint pl=shadowVP->getPixelLeft(), pr=shadowVP->getPixelRight(), pb=shadowVP->getPixelBottom(), 
    pt=shadowVP->getPixelTop();
    GLint pw=pr-pl+1,ph=pt-pb+1;
    bool full = shadowVP->isFullWindow();

    glViewport(pl, pb, pw, ph);
    glScissor(pl, pb, pw, ph);

    if(!full)
        glEnable(GL_SCISSOR_TEST);

    // draw background
    shadowVP->getBackground()->clear(action, shadowVP);

    //---Draw/Render-Pass with ambient light only & no shadows------

    std::vector<int>     light_state;
    std::vector<Color4f> _light_specular;
    std::vector<Color4f> _light_diffuse;
    std::vector<Color4f> _light_ambient;
    Color4f shadow_color = shadowVP->getShadowColor() * (1.0 / Real32(shadowVP->_lights.size()));

    for(UInt32 j=0;j<shadowVP->_lights.size();++j) // Switching off specular highlights
    {
        _light_specular.push_back(shadowVP->_lights[j]->getSpecular());
        _light_diffuse.push_back(shadowVP->_lights[j]->getDiffuse());
        _light_ambient.push_back(shadowVP->_lights[j]->getAmbient());

        shadowVP->_lights[j]->setSpecular(0.0,0.0,0.0,1.0);
        shadowVP->_lights[j]->setDiffuse(shadow_color);
    }

    // render
    action->apply(shadowVP->getRoot());

    // get all lights
    for(UInt32 j=0;j<shadowVP->_lights.size();++j) // Switching on specular highlights
    {
        shadowVP->_lights[j]->setSpecular(_light_specular[j]);
        shadowVP->_lights[j]->setDiffuse(_light_diffuse[j]);
        shadowVP->_lights[j]->setAmbient(0.0,0.0,0.0,1.0);
    } 
	for(UInt32 j=0;j<shadowVP->_allLights.size();++j) {
        light_state.push_back(shadowVP->_allLights[j]->getOn());
        shadowVP->_allLights[j]->setOn(false);
    }

    beginEditCP(_blender);
    {
        _blender->setSrcFactor(GL_ONE);
        _blender->setDestFactor(GL_ONE);
        _blender->setAlphaFunc(GL_GEQUAL);
        _blender->setAlphaValue(0.99);
    }
    endEditCP(_blender);

	// switch off all transparent geos
    for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
        shadowVP->_transparent[t]->setActive(false);

    beginEditCP(shadowVP->_offset);
    shadowVP->_offset->setOffsetBias(-1);
    shadowVP->_offset->setOffsetFactor(0);
    shadowVP->_offset->setOffsetFill(true);
    endEditCP(shadowVP->_offset);

    glDepthFunc(GL_LESS);

    //---Render-Pass with Shadow-----------------------------    
    for(UInt32 i=0;i<shadowVP->_lights.size();++i)
    {
        if(shadowVP->_lightStates[i] != 0)
        {
            Matrix textureMatrix = biasMatrix;
			textureMatrix.mult(_perspectiveLPM[i]);
            textureMatrix.mult(_perspectiveLVM[i]);
            
            textureMatrix.transpose();
            Vec4f ps = textureMatrix[0];
            Vec4f pt = textureMatrix[1];
            Vec4f pr = textureMatrix[2];
            Vec4f pq = textureMatrix[3];

            beginEditCP(shadowVP->_texGen);
                shadowVP->_texGen->setGenFuncSPlane(ps);
                shadowVP->_texGen->setGenFuncTPlane(pt);
                shadowVP->_texGen->setGenFuncRPlane(pr);
                shadowVP->_texGen->setGenFuncQPlane(pq);
            endEditCP(shadowVP->_texGen);
            
            shadowVP->_lights[i]->setOn(true);
        
            shadowVP->_texChunks[i]->activate(action,3);

            shadowVP->_texGen->activate(action,3);

            _blender->activate(action,0);

			shadowVP->_offset->activate(action,0);
            action->apply(shadowVP->getRoot());
			shadowVP->_offset->deactivate(action,0);

            _blender->deactivate(action,0);

            shadowVP->_texGen->deactivate(action,3);

            shadowVP->_texChunks[i]->deactivate(action,3);
        
            shadowVP->_lights[i]->setOn(false);

			// increase offset for next light
            beginEditCP(shadowVP->_offset);
            shadowVP->_offset->setOffsetBias(shadowVP->_offset->getOffsetBias() - 1);
            endEditCP(shadowVP->_offset);
        }
    }

    glDepthFunc(GL_LEQUAL);

    // switch on all transparent geos
    for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
        shadowVP->_transparent[t]->setActive(true);

    for(UInt32 i=0;i<shadowVP->_lights.size();++i) // Switching on ambient 
    {
        shadowVP->_lights[i]->setAmbient(_light_ambient[i]);
    }

    for(UInt32 j=0;j<shadowVP->_allLights.size();++j) 
    {
        shadowVP->_allLights[j]->setOn(light_state[j]);
    }
	

}


void PerspectiveShadowMap::render(RenderActionBase* action)
{
	GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

	for (int i=0; i<shadowVP->_lights.size(); i++)
	{
		if(shadowVP->_lightStates[i] != 0)
        {
			if(shadowVP->_lights[i]->getType() == DirectionalLight::getClassType())
			{
				Matrix _LPM, _LVM;
				calcPerspective(_LPM,_LVM,i);
				_perspectiveLPM.push_back(_LPM);
				_perspectiveLVM.push_back(_LVM);
			}
			else
			{
				Matrix _LPM, _LVM;
				calcPerspectiveSpot(_LPM,_LVM,i);
				_perspectiveLPM.push_back(_LPM);
				_perspectiveLVM.push_back(_LVM);
			}
		}
		else
		{
			Matrix _LPM, _LVM;
			_LPM.setIdentity();
			_LVM.setIdentity();
			_perspectiveLPM.push_back(_LPM);
			_perspectiveLVM.push_back(_LVM);
		}
	}


    if(shadowVP->getMapAutoUpdate())
    {
        createShadowMaps(action);
    }
    else
    {
        if(shadowVP->_trigger_update)
        {
            createShadowMaps(action);
            shadowVP->_trigger_update = false;
        }
    }
    
    if(!shadowVP->_lights.empty() && !shadowVP->_lightCameras.empty())
    {
        projectShadowMaps(action);
    }
    else
    {
        FDEBUG(("Rendering without Shadows\n"));
        shadowVP->Viewport::render(action);
    }

    // render the foregrounds.
    for(UInt16 i=0; i < shadowVP->getForegrounds().size(); ++i)
	{
        shadowVP->getForegrounds(i)->draw(action, shadowVP);
	}
	_perspectiveLPM.clear();
	_perspectiveLVM.clear();
	
}
