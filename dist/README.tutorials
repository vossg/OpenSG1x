
  OpenSG Tutorial Examples
  ========================

These programs show you how to do things in OpenSG. They are not meant to be
complete applications, they rather demonstrate separate aspects of the
system and should be used as a starting point for your own tests and
experiments using OpenSG.

They are all based on the same framework, so you can interact with all of
them in the same way. The left mouse button rotates the scene, the
middle button translates, the right button (or both buttons on
two-button mice) zooms in or out.

The available examples are:

hello:                  The simplest OpenSG program. Just creates a torus.

move:                   How to use transformations.

share:                  Sharing the cores between different nodes.

hiertransform:          Demonstrates the hierarchical accumulative effects of
                        multiple transformations.

geometry:               Simple non-indexed geometry node construction.

indexgeometry:          Using single indices for geometry.

multiindexgeometry:     Using multiple indices for different attributes.

materials:              Creating materials to specify the surface properties
                        of the objects.

traverse:               How to traverse the scenegraph and work on the nodes.

loading:                Loading models.

picking:                Using a ray test to select objects/faces.

ClusterServer/ClusterClient: How to display the results of an OpenSG application
                        on another machine.

switch:                 How to use the switch node to seectively displa/hide nodes

attachments:            How to attach additional data like names to Nodes and other 
                        structures

lights:                 How to define and use additional light sources in a scene

deepclone:              Shows how to create a copy of a scenegraph.

openg_slave:            It is often necessary to mix non-OpenSG code with OpenSG.
                        This is a quick way to melt such code-bases together.

LocalLights:            This example shows how to create use local light sources.
                        It creates four light sources (red, green, blue, white)
                        each light source lights only its subtree.

MaterialSort:           This example shows how to manually change the render order of materials.
                        For intersecting geometries transparent sorting doesn't work so
                        we set for each material a sort key.

Shadows:                This example shows realtime shadows via shadow maps.

Shader:                 This example shows how to use GLSL shaders.
                        It creates a bouncing ball animation (completely calculated on the GPU).
                        You need a graphics card supporting the GL_ARB_shading_language_100 extension
                        to run this tutorial.

videotexturebackground: This example shows how to use the TextureBackground to show animated
                        pictures behind the 3D graphics, and how to do it as efficiently as 
                        possible.


The directory contains a test image that can be passed to materials to be used
as a texture: osg_power_trans.rgb, which is the "Powered by OpenSG" logo
image. 

It also contains (in Data) two little test models: a set of dolphins in OBJ
format and a TIE fighter in VRML97 format. loading and picking can load them.

The TIE fighter model was taken from the AC3D website (www.ac3d.org),
which lists its origin as 'found on the web as VRML'. As it's been
distributed as part of AC3D for quite a while now, we think that it's ok
to use it as a simple test model.

The dolphins were downloaded from 3D Cafe (www.3dcafe.com) and converted to
OBJ offline. Visit them for a lot of other nice models.
