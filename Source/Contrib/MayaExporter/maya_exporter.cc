// OpenSG exporter for Maya.
// Michael Babcock <mbabcock@la.creatureshop.henson.com>
// Copyright 2003 Jim Henson's Creature Shop

/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <maya/MPxFileTranslator.h>
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MItDag.h>
#include <maya/MFnMesh.h>
#include <maya/MDagPath.h>
#include <maya/MPointArray.h>
#include <maya/MFnSet.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MPlugArray.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MFnLambertShader.h>
#include <maya/MFnReflectShader.h>
#include <maya/MFnPhongShader.h>
#include <maya/MFnBlinnShader.h>
#include <maya/MFnTransform.h>
#include <maya/MFnSkinCluster.h>
#include <maya/MMatrix.h>
#include <maya/MDagPathArray.h>
#include <maya/MItMeshVertex.h>
#include <maya/MQuaternion.h>
#include <maya/MFnBlendShapeDeformer.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGOSGWriter.h>
#include <OpenSG/OSGBINWriter.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OSGContribDef.h>
#include "OSGDeformableGeometry.h"
#include "OSGSkinDeformer.h"
#include "OSGBlendShapeDeformer.h"

#include <fstream>
#include <map>
#include <set>

#define TEXTURESIZE "512"
#define TEXTUREFILE "/tmp/osg_export.tif"

class OpenSG_exporter : public MPxFileTranslator {
public:
    static void * creator () { return new OpenSG_exporter; }

    OpenSG_exporter () {}
    virtual ~OpenSG_exporter () {}

    virtual MStatus writer (const MFileObject & file, const MString & optionsString, FileAccessMode mode);

    virtual bool haveWriteMethod  () const { return true; }
    virtual MString defaultExtension () const { return "bin"; }

private:
    MStatus export_all (const MString & filename);
    bool is_visible (const MFnDagNode & fnDag);
    osg::MaterialPtr get_osg_material (const MDagPath& mesh, const MObject& set);
    MObject find_shader(const MObject& setNode);
    osg::NodePtr translate_mesh(const MDagPath & dagPath);
    osg::NodePtr translate_transform(const MDagPath & dagPath);
    osg::SkinDeformerPtr translate_skincluster(const MObject & o);
    void translate_blendshape(const MObject & o);

    osg::NodePtr get_osg_node(const MDagPath & dagPath);
    void add_osg_node(const MDagPath & dagPath, osg::NodePtr osg_node);

    std::map<MDagPath,osg::NodePtr> nodes_;
};

bool operator <  (const MDagPath & a, const MDagPath & b) {
    return std::string(a.fullPathName().asChar()) < std::string(b.fullPathName().asChar());
}

osg::NodePtr OpenSG_exporter::get_osg_node(const MDagPath & dagPath) {
    std::map<MDagPath,osg::NodePtr>::iterator i = nodes_.find(dagPath);
    if (i != nodes_.end())
        return i->second;
    else
        return osg::NullFC;
}

void OpenSG_exporter::add_osg_node(const MDagPath & dagPath, osg::NodePtr osg_node) {
    if (get_osg_node(dagPath) == osg::NullFC)
        nodes_.insert(std::make_pair(dagPath, osg_node));
    else
        MGlobal::displayWarning("add_osg_node: " + dagPath.partialPathName() + " already exists.");
}

MStatus OpenSG_exporter::writer (const MFileObject & file, const MString & optionsString, FileAccessMode mode) {
    MGlobal::displayInfo("Exporting to " + file.fullName());
    if (mode == kExportAccessMode) {
        return export_all(file.fullName());
    }
    else {
        return MStatus::kFailure;
    }
}

MStatus OpenSG_exporter::export_all (const MString & filename) {
    nodes_.clear();
    MStatus status;
    MItDag itDag(MItDag::kDepthFirst, MFn::kInvalid, &status);
    if (status == MStatus::kFailure)
        return status;

    osg::NodePtr osg_root_node = osg::Node::create();
    osg::TransformPtr osg_trans = osg::Transform::create();
    osg::beginEditCP(osg_root_node, osg::Node::CoreFieldMask );
    {
        osg_root_node->setCore(osg_trans);
    }
    osg::endEditCP  (osg_root_node, osg::Node::CoreFieldMask );

    // For each DAG node.
    for (; !itDag.isDone(); itDag.next()) {
        MDagPath dagPath;
        status = itDag.getPath(dagPath);
        if (status == MStatus::kFailure)
            return status;

        //MGlobal::displayInfo("Processing " + dagPath.partialPathName());

        if (!is_visible(MFnDagNode(dagPath))) {
            // Don't bother with descendents if this node is invisible.
            itDag.prune();
            //MGlobal::displayInfo(" skipping invisible node");
            continue;
        }

        bool known_type = false;
        osg::NodePtr osg_node = osg::NullFC;

        if (dagPath.hasFn(MFn::kTransform)) {
            osg_node = translate_transform(dagPath);
            known_type = true;
        }
        else if (dagPath.hasFn(MFn::kMesh)) {
            osg_node = translate_mesh(dagPath);
            known_type = true;
        }

        if (osg_node != osg::NullFC) {
            // Parent the node.
            MDagPath parent_path(dagPath);
            if (parent_path.pop() == MStatus::kSuccess) {
                osg::NodePtr osg_parent_node = get_osg_node(parent_path);
                if (osg_parent_node == osg::NullFC) {
                    //MGlobal::displayInfo("Parenting " + dagPath.partialPathName() + " to the root.");
                    osg_parent_node = osg_root_node;
                }
                osg::beginEditCP(osg_parent_node, osg::Node::ChildrenFieldMask);
                {
                    osg_parent_node->addChild(osg_node);
                }
                osg::endEditCP  (osg_parent_node, osg::Node::ChildrenFieldMask);
            }
            else {
                MGlobal::displayWarning("Could not find Maya parent node for " + dagPath.partialPathName());
            }

            // Give the node a name.
            osg::NamePtr osg_name = osg::Name::create();
            osg::beginEditCP(osg_name);
            osg::beginEditCP(osg_node,osg::Node::AttachmentsFieldMask);
            {
                osg_name->getFieldPtr()->getValue().assign(dagPath.partialPathName().asChar());
                osg_node->addAttachment(osg_name);
            }
            osg::endEditCP(osg_node,osg::Node::AttachmentsFieldMask);
            osg::endEditCP(osg_name);

            // Add to our mapping of DAG paths to OpenSG nodes.
            add_osg_node(dagPath, osg_node);
        }
        else if (known_type) {
            MGlobal::displayWarning("Could not translate " + dagPath.partialPathName());
        }
    }

    // Now we have meshes and transforms, find supported deformers.
    MItDependencyNodes itDG(MFn::kInvalid);
    // Process blendshapes before skinclusters.
    for (; !itDG.isDone(); itDG.next()) {
        if (itDG.item().apiType() == MFn::kBlendShape) {
            translate_blendshape(itDG.item());
        }
    }
    for (itDG.reset(); !itDG.isDone(); itDG.next()) {
        if (itDG.item().apiType() == MFn::kSkinClusterFilter) {
            translate_skincluster(itDG.item());
        }
    }

    //if (!osg::SceneFileHandler::the().write(osg_root_node, filename.asChar())) {
    //    MGlobal::displayError("Error exporting to " + filename);
    //    return MStatus::kFailure;
    //}
    std::ofstream os(filename.asChar(), std::ios::binary);
    if(os)
    {
        MGlobal::displayInfo("Writing file " + filename);
        osg::OSGWriter * osg_writer = new osg::OSGWriter(os);
        osg_writer->write(osg_root_node);
        delete osg_writer;
        os.close();
        return MStatus::kSuccess;
    }
    else
    {
        MGlobal::displayError("Couldn't write to " + filename);
        return MStatus::kFailure;
    }
}


void OpenSG_exporter::translate_blendshape (const MObject & o) {
    MStatus status;
    MFnBlendShapeDeformer blendshape(o, &status);
    if (status == MStatus::kFailure)
        return;

    MGlobal::displayInfo("Exporting blendshape " + blendshape.name());

    MObjectArray base_objects;
    status = blendshape.getBaseObjects(base_objects);
    if (status != MStatus::kSuccess) {
        MGlobal::displayWarning(blendshape.name() + ": couldn't get blendshape base objects.");
        return;
    }

    unsigned int numWeights = blendshape.numWeights(&status);
    if (status != MStatus::kSuccess) {
        MGlobal::displayWarning(blendshape.name() + ": couldn't get blendshape weight count.");
        return;
    }

    MIntArray weight_indices;
    status = blendshape.weightIndexList(weight_indices);
    if (status != MStatus::kSuccess) {
        MGlobal::displayWarning(blendshape.name() + ": couldn't get blendshape weight indices.");
        return;
    }

    // Store original weights.
    MFloatArray weights(numWeights);
    for (unsigned int t = 0; t < numWeights; t++) {
        weights[t] = blendshape.weight(weight_indices[t]);
    }

    for (unsigned int i = 0; i < base_objects.length(); i++) {
        MObject base = base_objects[i];
        MFnMesh mesh(base, &status);
        if (status != MStatus::kSuccess) {
            MGlobal::displayWarning(blendshape.name() + ": base object " + (double)i + " is not a mesh.");
            continue;
        }

        MDagPath base_path;
        mesh.getPath(base_path);
        MGlobal::displayInfo(" base object " + base_path.partialPathName());
        osg::NodePtr osg_base = get_osg_node(base_path);
        if (osg_base == osg::NullFC) {
            MGlobal::displayWarning(blendshape.name() + ": couldn't find OpenSG node for " + base_path.partialPathName());
            continue;
        }

        osg::NodePtr child = osg_base->getChild(0);
        osg::DeformableGeometryPtr deform_geo = osg::DeformableGeometryPtr::dcast(child->getCore());
        if (deform_geo == osg::NullFC) {
            MGlobal::displayWarning(blendshape.name() + ": OpenSG base object is not a DeformableGeometry");
            continue;
        }

        osg::BlendShapeDeformerPtr osg_blendshape = osg::BlendShapeDeformer::create();
        osg::beginEditCP(osg_blendshape);
        {
            osg_blendshape->setGeometry(child);
            for (unsigned int t = 0; t < numWeights; t++) {
                // Set current target to full weight, all others to zero.
                for (unsigned int t2 = 0; t2 < numWeights; t2++) {
                    float weight = (t == t2) ? 1.0f : 0.0f;
                    blendshape.setWeight(weight_indices[t2], weight);
                }

                // Read current deformed vertex positions.

                MFnMesh fnMesh(base_path, &status);
                if (status != MStatus::kSuccess) {
                    MGlobal::displayWarning(blendshape.name() + ": couldn't get deformed mesh.");
                    continue;
                }

                MPointArray vertices;
                status = fnMesh.getPoints(vertices, MSpace::kObject);
                if (status != MStatus::kSuccess) {
                    MGlobal::displayWarning(blendshape.name() + ": couldn't get deformed vertices.");
                    continue;
                }

                MFloatVectorArray normals;
                status = fnMesh.getNormals(normals, MSpace::kObject);
                if (status != MStatus::kSuccess) {
                    MGlobal::displayWarning(blendshape.name() + ": couldn't get deformed normals.");
                    continue;
                }

                for (unsigned int v = 0; v < vertices.length(); v++) {
                    osg::Pnt3f base = deform_geo->getPositions()->getValue(v);
                    osg::Pnt3f target(vertices[v][0], vertices[v][1], vertices[v][2]);
                    osg::Vec3f offset = target - base;
                    if (offset.length() > 0.5f) {
                        osg_blendshape->getVertexIndices().push_back(v);
                        osg_blendshape->getTargetIndices().push_back(t);
                        osg_blendshape->getTargetVertices().push_back(target);
                    }
                }

                for (unsigned int n = 0; n < normals.length(); n++) {
                    osg::Vec3f base = deform_geo->getNormals()->getValue(n);
                    osg::Vec3f target(normals[n][0], normals[n][1], normals[n][2]);
                    osg::Vec3f offset = target - base;
                    if (offset.length() > 0.1f) {
                        osg_blendshape->getNormalIndices().push_back(n);
                        osg_blendshape->getNormalTargetIndices().push_back(t);
                        osg_blendshape->getTargetNormals().push_back(target);
                    }
                }

                // Set default target weight.
                osg_blendshape->getWeight().push_back(weights[t]);
            }

            MGlobal::displayInfo(blendshape.name() + ": " + (double)osg_blendshape->getVertexIndices().size()
                                 + " vertex ops, " + (double)osg_blendshape->getNormalIndices().size() + " normal ops.");

            // Give the deformer a name.
            osg::NamePtr osg_name = osg::Name::create();
            osg::beginEditCP(osg_name);
            {
                osg_name->getFieldPtr()->getValue().assign(blendshape.name().asChar());
            }
            osg::endEditCP(osg_name);
            osg_blendshape->addAttachment(osg_name);
        }
        osg::endEditCP(osg_blendshape);

        osg::beginEditCP(deform_geo);
        {
            deform_geo->getDeformers().push_back(osg_blendshape);
        }
        osg::endEditCP(deform_geo);

    }

    // Restore original weights.
    for (unsigned int t = 0; t < numWeights; t++) {
        blendshape.setWeight(weight_indices[t], weights[t]);
    }
}

osg::SkinDeformerPtr OpenSG_exporter::translate_skincluster(const MObject & o) {
    MStatus status;
    MFnSkinCluster skin(o, &status);
    if (status == MStatus::kFailure)
        return osg::NullFC;

    MGlobal::displayInfo("Exporting skincluster " + skin.name());

    MDagPathArray influences;
    unsigned int infl_count = skin.influenceObjects(influences, &status);
    if (status == MStatus::kFailure || infl_count == 0) {
        MGlobal::displayError("Couldn't get skincluster influence objects");
        return osg::NullFC;
    }

    for (unsigned int i = 0; i < infl_count; i++) {
        osg::NodePtr osg_node = get_osg_node(influences[i]);
        if (osg_node == osg::NullFC) {
            MGlobal::displayError(" couldn't find OpenSG transform node for " + influences[i].partialPathName());
            return osg::NullFC;
        }
    }

    unsigned int geo_count = skin.numOutputConnections();
    for (unsigned int i = 0; i < geo_count; i++) {
        unsigned int geo_index = skin.indexForOutputConnection(i, &status);
        if (status == MStatus::kFailure) {
            MGlobal::displayError(" Couldn't get skincluster geometry index");
            return osg::NullFC;
        }

        MDagPath geo_path;
        status = skin.getPathAtIndex(geo_index, geo_path);
        if (status == MStatus::kFailure) {
            MGlobal::displayError(" Couldn't get skincluster geometry path");
            return osg::NullFC;
        }

        MGlobal::displayInfo(" deforming geometry " + geo_path.partialPathName());

        osg::NodePtr osg_node = get_osg_node(geo_path);
        if (osg_node == osg::NullFC) {
            MGlobal::displayError(" couldn't find OpenSG geometry node for " + geo_path.partialPathName());
            return osg::NullFC;
        }

        osg::NodePtr child = osg_node->getChild(0);
        osg::DeformableGeometryPtr deform_geo = osg::DeformableGeometryPtr::dcast(child->getCore());
        if (deform_geo == osg::NullFC) {
            MGlobal::displayError(" OpenSG target object is not a DeformableGeometry");
            return osg::NullFC;
        }

        osg::SkinDeformerPtr osg_skin = osg::SkinDeformer::create();
        osg::beginEditCP(osg_skin);
        {
            osg_skin->setGeometry(child);
            for (unsigned int i = 0; i < infl_count; i++) {
                osg::NodePtr osg_node = get_osg_node(influences[i]);
                if (osg_node == osg::NullFC) {
                    MGlobal::displayError(" couldn't find OpenSG transform node for " + influences[i].partialPathName());
                    return osg::NullFC;
                }
                osg_skin->getInfluences().push_back(osg_node);
                osg_skin->getBaseMatrices().push_back(osg_node->getToWorld());
            }


            MItMeshVertex gIter(geo_path);
            MFnMesh fnmesh(geo_path);

            for (; !gIter.isDone(); gIter.next()) {
                MObject comp = gIter.vertex(&status);
                if (status == MStatus::kFailure) {
                    MGlobal::displayError(" Couldn't get geometry component");
                    return osg::NullFC;
                }

                // Get the weights for this vertex (one per influence object)
                //
                MFloatArray weights;
                unsigned int weight_count;
                status = skin.getWeights(geo_path, comp, weights, weight_count);
                if (status == MStatus::kFailure || weight_count == 0) {
                    MGlobal::displayError(" Couldn't get weights for component");
                    return osg::NullFC;
                }

                //MGlobal::displayInfo(MString(" component ") + (double)gIter.index() + " weights");
                for (unsigned int w = 0; w < weight_count ; w++) {
                    //MGlobal::displayInfo(MString(" ") + (double)w + " " + weights[w]);
                    if (weights[w] > 0.0f) {
                        // Vertices.
                        osg_skin->getVertexIndices().push_back(gIter.index());
                        osg_skin->getInfluenceIndices().push_back(w);
                        osg_skin->getInfluenceWeights().push_back(weights[w]);

                        // Normals.
                        std::set<int> vertex_normals; // Normal Ids at vertex (more than one if not smooth).

                        // This is an awkward way to get Maya's normals at vertex.
                        MIntArray connected_faces;
                        status = gIter.getConnectedFaces(connected_faces);
                        if (status != MStatus::kSuccess) {
                            MGlobal::displayWarning(" couldn't get connected faces");
                            continue;
                        }
                        for (unsigned int f = 0; f < connected_faces.length(); f++) {
                            MIntArray face_vertices, face_normals;
                            status = fnmesh.getPolygonVertices(connected_faces[f], face_vertices);
                            if (status != MStatus::kSuccess) {
                                MGlobal::displayWarning(" couldn't get face vertices");
                                break;
                            }
                            status = fnmesh.getFaceNormalIds(connected_faces[f], face_normals);
                            if (status != MStatus::kSuccess) {
                                MGlobal::displayWarning(" couldn't get face normals");
                                break;
                            }
                            if (face_vertices.length() != face_normals.length()) {
                                MGlobal::displayWarning(" different number of face vertices and normals!");
                                break;
                            }
                            int count = 0;
                            for (unsigned int fv = 0; fv < face_vertices.length(); fv++) {
                                if (face_vertices[fv] == gIter.index()) {
                                    //MGlobal::displayInfo(MString("using normal ") + (double)face_normals[fv]);
                                    count++;
                                    vertex_normals.insert(face_normals[fv]);
                                }
                            }
                            if (count == 0) {
                                MGlobal::displayWarning("couldn't find normal for face vertex");
                            }
                            else if (count > 1) {
                                MGlobal::displayWarning("found too many normals for face vertex");
                            }
                        }

                        for (std::set<int>::const_iterator i = vertex_normals.begin(); i != vertex_normals.end(); ++i) {
                            osg_skin->getNormalIndices().push_back(*i);
                            osg_skin->getNormalInfluenceIndices().push_back(w);
                            osg_skin->getNormalInfluenceWeights().push_back(weights[w]);
                        }
                    }
                }
            }
        }
        osg::endEditCP(osg_skin);
        MGlobal::displayInfo(skin.name() + ": " + (double)osg_skin->getVertexIndices().size() + " vertex ops, " +
                             (double)osg_skin->getNormalIndices().size() + " normal ops");

        // Give the deformer a name.
        osg::NamePtr osg_name = osg::Name::create();
        osg::beginEditCP(osg_name);
        {
            osg_name->getFieldPtr()->getValue().assign(skin.name().asChar());
        }
        osg::endEditCP(osg_name);
        osg_skin->addAttachment(osg_name);

        // Attach this skin deformer to the geometry so it will be saved with the scene and we can find it later.
        osg::beginEditCP(deform_geo);
        {
            deform_geo->getDeformers().push_back(osg_skin);
        }
        osg::endEditCP(deform_geo);

        // There should be only one output geometry for skinCluster nodes, so just return the first one.
        return osg_skin;
    }

    return osg::NullFC;
}

osg::NodePtr OpenSG_exporter::translate_transform(const MDagPath & dagPath) {
    MStatus status;
    MFnTransform fnTransform(dagPath, &status);
    if (status == MStatus::kFailure)
        return osg::NullFC;

    MGlobal::displayInfo("Exporting transform " + fnTransform.partialPathName());
    osg::Matrix::VectorType3f translation, scale, center;
    osg::Matrix::QuaternionType rotation, scaleOrientation;

#if 1
    MMatrix matrix = fnTransform.transformationMatrix(); //transformation().asMatrix();
    osg::Matrix osg_matrix(matrix.matrix[0][0], matrix.matrix[1][0], matrix.matrix[2][0], matrix.matrix[3][0],
                           matrix.matrix[0][1], matrix.matrix[1][1], matrix.matrix[2][1], matrix.matrix[3][1],
                           matrix.matrix[0][2], matrix.matrix[1][2], matrix.matrix[2][2], matrix.matrix[3][2],
                           matrix.matrix[0][3], matrix.matrix[1][3], matrix.matrix[2][3], matrix.matrix[3][3]);
    MTransformationMatrix tm = fnTransform.transformation();
    MPoint sp = tm.scalePivot(MSpace::kPreTransform);
    MPoint rp = tm.rotatePivot(MSpace::kPreTransform);
    if (!sp.isEquivalent(rp))
        MGlobal::displayWarning(fnTransform.name() + ": scale pivot does not equal rotate pivot. Using rotate pivot.");
    center[0] = rp[0]; center[1] = rp[1]; center[2] = rp[2];

    MTransformationMatrix::RotationOrder rotation_order = fnTransform.rotationOrder();
    if (rotation_order != MTransformationMatrix::kXYZ)
        MGlobal::displayWarning(fnTransform.name() + ": rotation order is not XYZ.");

    osg_matrix.getTransform(translation, rotation, scale, scaleOrientation, center);
    //osg::Matrix so;
    //scaleOrientation.getValue(so);
    //so.transpose();
    //scaleOrientation.setValue(so);

    //osg::Matrix so, rot, proj;
    //if (osg_matrix.factor(so, scale, rot, translation, proj)) {
    //    //so.invert();
    //    scaleOrientation.setValue(so);
    //    rotation.setValue(rot);
    //}
    //else {
    //    MGlobal::displayError(fnTransform.name() + ": couldn't decompose matrix.");
    //    return osg::NullFC;
    //}
#else
    MTransformationMatrix tm = fnTransform.transformation();
    MVector mt;
    double ms[3];
    MQuaternion mr;
    mt = tm.translation(MSpace::kPreTransform);
    tm.getScale(ms, MSpace::kPreTransform);
    mr = tm.rotationOrientation() * tm.rotation();
    translation[0] = mt[0]; translation[1] = mt[1]; translation[2] = mt[2];
    scale[0] = ms[0]; scale[1] = ms[1]; scale[2] = ms[2];
    rotation[0] = mr[0]; rotation[1] = mr[1]; rotation[2] = mr[2]; rotation[3] = mr[3];
    MPoint sp = tm.scalePivot(MSpace::kPreTransform);
    MPoint rp = tm.rotatePivot(MSpace::kPreTransform);
    if (!sp.isEquivalent(rp))
        MGlobal::displayWarning(fnTransform.name() + ": scale pivot does not equal rotate pivot. Using rotate pivot");
    center[0] = rp[0]; center[1] = rp[1]; center[2] = rp[2];
#endif
#if 1
    osg::ComponentTransformPtr osg_transform = osg::ComponentTransform::create();
#else
    osg::TransformPtr osg_transform = osg::Transform::create();
#endif
    osg::beginEditCP(osg_transform);
    {
#if 0
        osg_transform->setMatrix(osg_matrix); // Might as well?
#else
        osg_transform->setTranslation(translation);
        osg_transform->setRotation(rotation);
        osg_transform->setScale(scale);
        osg_transform->setScaleOrientation(scaleOrientation);
        osg_transform->setCenter(center);
#endif
    }
    osg::endEditCP(osg_transform);

    osg::NodePtr osg_node = osg::Node::create();
    osg::beginEditCP(osg_node, osg::Node::CoreFieldMask );
    {
        osg_node->setCore(osg_transform);
    }
    osg::endEditCP  (osg_node, osg::Node::CoreFieldMask );

    return osg_node;
}

osg::NodePtr OpenSG_exporter::translate_mesh(const MDagPath & dagPath) {
    MStatus status;
    MFnMesh fnMesh(dagPath, &status);
    if (status == MStatus::kFailure)
        return osg::NullFC;


    MGlobal::displayInfo("Exporting mesh " + fnMesh.partialPathName());

    // Vertices.
    MPointArray vertices;
    status = fnMesh.getPoints(vertices, MSpace::kObject);
    if (status != MStatus::kSuccess)
        return osg::NullFC;

    // Normals.
    MFloatVectorArray normals;
    status = fnMesh.getNormals(normals, MSpace::kObject);
    if (status != MStatus::kSuccess)
        return osg::NullFC;

    // UVs.
    bool have_uvs = false;
    MFloatArray uArray, vArray;
    status = fnMesh.getUVs(uArray, vArray);
    if (status == MStatus::kSuccess && uArray.length() > 0)
        have_uvs = true;

    //dagPath.extendToShape();
    int instance = 0;
    if (dagPath.isInstanced())
        instance = dagPath.instanceNumber();

    MObjectArray sets, comps;
    status = fnMesh.getConnectedSetsAndMembers(instance, sets, comps, true);
    if (status == MStatus::kFailure)
        return osg::NullFC;

    int numSets = sets.length();
    //if (numSets > 1) // Don't include last set of multiset meshes (its redundant). Not always.
    //    numSets--;

    // Group all OpenSG geometry that represents a single Maya mesh under a Group node.
    osg::GroupPtr osg_group = osg::Group::create();
    osg::NodePtr osg_group_node = osg::Node::create();
    osg::beginEditCP(osg_group_node, osg::Node::CoreFieldMask );
    {
        osg_group_node->setCore(osg_group);
    }
    osg::endEditCP  (osg_group_node, osg::Node::CoreFieldMask );

    osg::GeoPositions3fPtr osg_points = osg::GeoPositions3f::create();
    osg::GeoNormals3fPtr osg_normals = osg::GeoNormals3f::create();
    osg::GeoTexCoords2fPtr osg_uvs;
    if (have_uvs)
        osg_uvs = osg::GeoTexCoords2f::create();

    osg::beginEditCP(osg_points, osg::GeoPositions3f::GeoPropDataFieldMask);
    {
        for (unsigned int v = 0; v < vertices.length(); v++) {
            osg_points->addValue(osg::Pnt3f(vertices[v][0], vertices[v][1], vertices[v][2]));
        }
    }

    osg::beginEditCP(osg_normals, osg::GeoNormals3f::GeoPropDataFieldMask);
    {
        for (unsigned int n = 0; n < normals.length(); n++) {
            osg_normals->addValue(osg::Vec3f(normals[n].x, normals[n].y, normals[n].z));
        }
    }
    osg::endEditCP  (osg_normals, osg::GeoNormals3f::GeoPropDataFieldMask);

    if (have_uvs) {
        osg::beginEditCP(osg_uvs, osg::GeoTexCoords2f::GeoPropDataFieldMask);
        {
            for (unsigned int uv = 0; uv < uArray.length(); uv++) {
                osg_uvs->addValue(osg::Vec2f(uArray[uv], vArray[uv]));
            }
        }
        osg::endEditCP  (osg_uvs, osg::GeoTexCoords2f::GeoPropDataFieldMask);
    }

    // Create base positions and normals for deformable geometry.
    osg::GeoPositionsPtr osg_base_points = osg_points->clone();
    osg::GeoNormalsPtr osg_base_normals = osg_normals->clone();


    // For each (shader) set.
    std::set<std::string> set_names;
    for (int s = 0; s < numSets; s++) {
        MObject set = sets[s];
        MObject components = comps[s];
        MFnSet fnset(set, &status);
        if (status == MStatus::kFailure)
            return osg::NullFC;
        MItMeshPolygon itpoly(dagPath, components, &status);
        if (status == MStatus::kFailure)
            return osg::NullFC;

        // Maya returns redundant sets sometimes. Check for them using names.
        if (set_names.find(std::string(fnset.name().asChar())) != set_names.end()) {
            MGlobal::displayInfo(" Ignoring redundant set " + fnset.name());
            continue;
        }
        set_names.insert(std::string(fnset.name().asChar()));

        MGlobal::displayInfo(" Exporting set " + fnset.name());

        osg::DeformableGeometryPtr osg_geo = osg::DeformableGeometry::create();
        osg::GeoPTypesPtr osg_primitive_types = osg::GeoPTypesUI8::create();
        osg::GeoPLengthsPtr osg_lengths = osg::GeoPLengthsUI32::create();
        osg::GeoIndicesUI32Ptr osg_indices = osg::GeoIndicesUI32::create();

        // For each polygon.
        for (itpoly.reset(); !itpoly.isDone(); itpoly.next()) {
            osg::beginEditCP(osg_primitive_types, osg::GeoPTypesUI8::GeoPropDataFieldMask);
            {
                osg_primitive_types->addValue(GL_POLYGON);
            }
            osg::endEditCP  (osg_primitive_types, osg::GeoPTypesUI8::GeoPropDataFieldMask);


            int vertex_count = itpoly.polygonVertexCount(&status);
            if (status != MStatus::kSuccess)
                return osg::NullFC;

            osg::beginEditCP(osg_lengths, osg::GeoPLengthsUI32::GeoPropDataFieldMask);
            {
                osg_lengths->addValue(vertex_count);
            }
            osg::endEditCP  (osg_lengths, osg::GeoPLengthsUI32::GeoPropDataFieldMask);

            osg::beginEditCP(osg_indices, osg::GeoIndicesUI32::GeoPropDataFieldMask);
            {
                for (int i = 0; i < vertex_count; i++) {
                    int vertex_index = itpoly.vertexIndex(i, &status);
                    if (status != MStatus::kSuccess)
                        return osg::NullFC;
                    int normal_index = itpoly.normalIndex(i, &status);
                    if (status != MStatus::kSuccess)
                        return osg::NullFC;
                    int uv_index;
                    if (have_uvs) {
                        status = itpoly.getUVIndex(i, uv_index);
                        if (status != MStatus::kSuccess)
                            uv_index = 0;
                    }

                    osg_indices->addValue(vertex_index);
                    osg_indices->addValue(normal_index);
                    if (have_uvs)
                        osg_indices->addValue(uv_index);
                }
            }
            osg::endEditCP(osg_indices, osg::GeoIndicesUI32::GeoPropDataFieldMask);
        }

        // Set material.
        osg::MaterialPtr osg_mat = get_osg_material(dagPath, set);

        osg::beginEditCP(osg_geo);
        {
            osg_geo->setTypes(osg_primitive_types);
            osg_geo->setLengths(osg_lengths);
            osg_geo->setIndices(osg_indices);
            osg_geo->getIndexMapping().push_back(osg::Geometry::MapPosition);
            osg_geo->getIndexMapping().push_back(osg::Geometry::MapNormal);
            if (have_uvs)
                osg_geo->getIndexMapping().push_back(osg::Geometry::MapTexCoords);
            osg_geo->setPositions(osg_points);
            osg_geo->setNormals(osg_normals);
            if (have_uvs)
                osg_geo->setTexCoords(osg_uvs);
            osg_geo->setMaterial(osg_mat);
            osg_geo->setBasePositions(osg_base_points);
            osg_geo->setBaseNormals(osg_base_normals);
        }
        osg::endEditCP  (osg_geo);

        // Optimize geometry a little bit. (Problematic for deformable geometry.)
        //osg::createSharedIndex(osg_geo);
        //osg::createSingleIndex(osg_geo);
        //osg::createOptimizedPrimitives(osg_geo, 5);

        //osg::calcVertexNormals(osg_geo);

        // Put the geometry core into a node.
        osg::NodePtr osg_node = osg::Node::create();
        osg::beginEditCP(osg_node, osg::Node::CoreFieldMask);
        {
            osg_node->setCore(osg_geo);
        }
        osg::endEditCP  (osg_node, osg::Node::CoreFieldMask);

        // Parent it to the mesh group node.
        osg::beginEditCP(osg_group_node, osg::Node::ChildrenFieldMask);
        {
            osg_group_node->addChild(osg_node);
        }
        osg::endEditCP  (osg_group_node, osg::Node::ChildrenFieldMask);
    }
    return osg_group_node;
}

bool OpenSG_exporter::is_visible (const MFnDagNode & fnDag) {
    if(fnDag.isIntermediateObject())
        return false;

    MStatus status;
    MPlug visPlug = fnDag.findPlug("visibility", &status);
    if (status == MStatus::kSuccess) {
        bool visible = false;
        status = visPlug.getValue(visible);
        if (status != MStatus::kSuccess) {
            MGlobal::displayError("MPlug::getValue");
            return false;
        }
        //MGlobal::displayInfo(fnDag.name() + ".visibility " + (double)visible);
        return visible;
    }
    else {
        MGlobal::displayError("MPlug::findPlug");
        return false;
    }
}

MObject OpenSG_exporter::find_shader (const MObject& setNode) {
    MFnDependencyNode fnNode(setNode);
    MPlug shaderPlug = fnNode.findPlug("surfaceShader");

    MStatus status;
    if (!shaderPlug.isNull()) {
        MPlugArray connectedPlugs;
        shaderPlug.connectedTo(connectedPlugs, true, false, &status);
        if (status != MStatus::kSuccess) {
            MGlobal::displayError("MPlug::connectedTo");
            return MObject::kNullObj;
        }

        if (connectedPlugs.length() != 1) {
            MGlobal::displayError(fnNode.name() + ": couldn't find surface shader");
        } else {
            return connectedPlugs[0].node();
        }
    }

    return MObject::kNullObj;
}

osg::MaterialPtr OpenSG_exporter::get_osg_material (const MDagPath& mesh, const MObject& set) {
    MStatus status;
    MObject shaderNode = find_shader(set);
    if (MObject::kNullObj == shaderNode) {
        return osg::getDefaultMaterial();
    }

    MFnLambertShader fnLambert(shaderNode, &status);
    if (status == MStatus::kFailure)
        return osg::getDefaultMaterial();

    MColor color = fnLambert.color();
    MColor ambient = fnLambert.ambientColor();
    MColor transpar = fnLambert.transparency();
    MColor incand = fnLambert.incandescence();
    float diffuse = fnLambert.diffuseCoeff();
    //float transluc = fnLambert.translucenceCoeff();

    MColor specular(0.0f, 0.0f, 0.0f);
    osg::Real32 shininess = 0.0f;

    MFnReflectShader fnReflect(shaderNode, &status);
    if (status == MStatus::kSuccess) {
        specular = fnReflect.specularColor();
    }

    MFnPhongShader fnPhong(shaderNode, &status);
    if (status == MStatus::kSuccess) {
        shininess = fnPhong.cosPower();
    }

    MFnBlinnShader fnBlinn(shaderNode, &status);
    if (status == MStatus::kSuccess) {
        shininess = -98.0f*fnBlinn.eccentricity()+100.0f; // FIXME: 0..1 eccentricity -> 100..2 cosPower.
    }

    osg::SimpleTexturedMaterialPtr osg_mat = osg::SimpleTexturedMaterial::create();
    osg::beginEditCP(osg_mat);
    {
        osg_mat->setAmbient(osg::Color3f(ambient.r, ambient.g, ambient.b));
        osg_mat->setDiffuse(osg::Color3f(color.r*diffuse, color.g*diffuse, color.b*diffuse));
        osg_mat->setSpecular(osg::Color3f(specular.r, specular.g, specular.b));
        osg_mat->setEmission(osg::Color3f(incand.r, incand.g, incand.b));
        osg_mat->setShininess(shininess);
        osg_mat->setTransparency((transpar.r + transpar.g + transpar.b) / 3.0f);
    }
    osg::endEditCP(osg_mat);

    // See if there is a texture connected to the color attribute.
    MPlug colorPlug = MFnDependencyNode(shaderNode).findPlug("color", &status);
    if (MS::kFailure == status) {
        MGlobal::displayError("MFnDependencyNode::findPlug(color)");
    }
    else if (!colorPlug.isNull() && colorPlug.isConnected()) {
        // Create a texture file.
        status = MGlobal::executeCommand(MString("$f = `convertSolidTx -rx ") + TEXTURESIZE + " -ry " + TEXTURESIZE + " -fileFormat tif -fileImageName "
                                         + "\"" + TEXTUREFILE + "\" " + MFnDependencyNode(shaderNode).name() + ".color "
                                         + mesh.partialPathName() + "`; delete $f;");
        if (status == MStatus::kFailure) {
            MGlobal::displayError("Error executing convertSolidTx command.");
        }
        else {
            osg::ImagePtr osg_image = osg::Image::create();
            if (!osg_image->read(TEXTUREFILE)) {
                MGlobal::displayError(MString("Error reading texture image ") + TEXTUREFILE);
            }
            else {
                osg::beginEditCP(osg_mat);
                {
                    osg_mat->setDiffuse(osg::Color3f(diffuse, diffuse, diffuse));
                    osg_mat->setImage(osg_image);
                    osg_mat->setEnvMode(GL_MODULATE);
                    //osg_mat->setEnvMap(true);
                }
                osg::endEditCP(osg_mat);
            }
        }
    }

    return osg_mat;
}

OSG_CONTRIBLIB_DLLMAPPING MStatus initializePlugin (MObject obj) {
    osg::osgInit(0, 0);
    MFnPlugin plugin(obj, "Michael Babcock", "0.1", "Any");
    return plugin.registerFileTranslator("OpenSG", "", OpenSG_exporter::creator, "", "", false);
}

OSG_CONTRIBLIB_DLLMAPPING MStatus uninitializePlugin (MObject obj) {
    osg::osgExit();
    MFnPlugin plugin(obj);
    return plugin.deregisterFileTranslator("OpenSG");
}
