#include <OSGConfig.h>
#include <OSGDVRShader.h>
#include <OSGDrawActionBase.h>
#include <OSGDVRVolume.h>
#include <OSGDVRVolumeTexture.h>
#include <OSGDVRIsoSurface.h>
#include <OSGSlicer.h>
#include <OSGWindow.h>
#include <OSGCamera.h>
#include <OSGColor.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
#include "OSGDVRIsoShader.h"

OSG_USING_NAMESPACE

Vec4f cToV (Color4f & col)
{
    return Vec4f(col.red(), col.green(), col.blue(), col.alpha());
}


// setup state for shading with fragment program
void DVRIsoShader::activate_FragmentProgramShading(DVRVolume      *volume, 
                                                   DrawActionBase *action)
{
    // Initialize the fragment program 
    if(m_pFragProg == NullFC) 
    {
        FDEBUG(("Initializing fragment program "));
        m_pFragProg = FragmentProgramChunk::create();

        addRefCP( m_pFragProg );

        FDEBUG((" - DONE\n"));

        // Load the appropriate program
        switch(m_shadingMode) 
        {
            case SM_FRAGMENT_PROGRAM_3D:
                // SLOG << "Loading ... isoFragProg3D.asm" << std::endl;

                beginEditCP(m_pFragProg);
                {
                    m_pFragProg->setProgram(_fragProg3D);
                    // m_pFragProg->read( "isoFragProg3D.asm" );
                }
                endEditCP  (m_pFragProg);

                break;

            case SM_FRAGMENT_PROGRAM_2D:

                // SLOG << "Loading ... isoFragProg2D.asm" << std::endl;
                
                beginEditCP(m_pFragProg);
                {
                    m_pFragProg->setProgram(_fragProg2D);
                    // m_pFragProg->read( "isoFragProg2D.asm" );
                }
                endEditCP(m_pFragProg);

                break;

            default:
                FFATAL(("Texture mode for fragment programs not supported "
                        "by DVRSimpleLUTShader"));
                return;
                // break;
        }
    }
    
    // get parameters from isosurface attachment if available
    Real32 isoValue;
    UInt32 alphaMode;
    bool   doSpecular;

    DVRIsoSurfacePtr isoParam = DVRVOLUME_PARAMETER(volume, DVRIsoSurface);

    if(isoParam != NullFC)
    {
        isoValue   = isoParam->getIsoValue        ();
        alphaMode  = isoParam->getAlphaMode       ();
        doSpecular = isoParam->getSpecularLighting();
    }
    else
    {
        isoValue   = 1.0;
        alphaMode  = GL_GREATER;
        doSpecular = false;
    }

    unsigned int maxDiffuseLights  = 6; // Hard-coded in the fragment program
    unsigned int maxSpecularLights = 6;
    
    // Set light parameters
    DirLightList diffuseLights;
    DirLightList specularLights;
    Color4f      ambientLight;

    getLightSources(diffuseLights, specularLights, ambientLight);

    beginEditCP(m_pFragProg, ProgramChunk::ParamValuesFieldMask);
    {
        m_pFragProg->setParameter((short int) 0, 
                                  cToV(ambientLight)); // ambient color

        // Diffuse lights
        unsigned int i;

        DirLightList::iterator l = diffuseLights.begin();

        for(i = 0; i < maxDiffuseLights && l != diffuseLights.end(); i++)
        { 
            Vec3f tmp;

            Slicer::rotateToLocal(action,l->dir,tmp);

            tmp.normalize();

            // diffuse direction
            m_pFragProg->setParameter(1 + 2 * i,     Vec4f(tmp));

            // diffuse color
            m_pFragProg->setParameter(1 + 2 * i + 1, cToV(l->color)); 

            ++l;
        }

        for(; i < maxDiffuseLights; i++) 
        {
            // diffuse direction
            m_pFragProg->setParameter(1 + 2 * i,     Vec4f(0, 0, 0, 0));

            // diffuse color
            m_pFragProg->setParameter(1 + 2 * i + 1, Vec4f(0, 0, 0, 0)); 
        }
        
        // Specular lights
        unsigned int firstSpecId = 1 + 2 * maxDiffuseLights;

        i = 0;

        if(doSpecular) 
        {
            // get and classify the slicing direction
            Vec3f  viewDir;

            Slicer::getSlicingDirection(action, &viewDir);

            viewDir.normalize();
            
            DirLightList::iterator ls = specularLights.begin();

            for(i = 0; 
                i < maxSpecularLights && ls != specularLights.end(); 
                i++)
            { 
                Vec3f tmp;

                Slicer::rotateToLocal(action,ls->dir,tmp);

                tmp.normalize();

                // calc halfway
                tmp += viewDir;
                tmp.normalize();

                // halfway vector
                m_pFragProg->setParameter(firstSpecId + 2 * i,     
                                          Vec4f(tmp));
                // specular color
                m_pFragProg->setParameter(firstSpecId + 2 * i + 1, 
                                          cToV(ls->color));  

                ++ls;
            }
        }

        for(; i < maxSpecularLights; i++) 
        {
            // specular direction
            m_pFragProg->setParameter(firstSpecId + 2 * i,     
                                      Vec4f(0, 0, 0, 0)); 

            // specular color
            m_pFragProg->setParameter(firstSpecId + 2 * i + 1, 
                                      Vec4f(0, 0, 0, 0)); 
        }
    }
    endEditCP(m_pFragProg, ProgramChunk::ParamValuesFieldMask);

    
    glPushAttrib(GL_ENABLE_BIT);

    // activate fragment program chunk
    m_pFragProg->activate(action);

    // no blending and lighting
    glDisable(GL_BLEND   );
    glDisable(GL_LIGHTING);
    
    // Enable Alpha Test for isosurface
    glEnable   (GL_ALPHA_TEST      ); 
    glAlphaFunc(alphaMode, isoValue);
}

// cleanup state for shading with fragment program
void DVRIsoShader::deactivate_FragmentProgramShading(
    DVRVolume      *volume, 
    DrawActionBase *action)
{
    glPopAttrib();
    
    // de-activate fragment program chunk
    m_pFragProg->deactivate(action);
}

// render a slice for 2D multitexture fragment program shading
void DVRIsoShader::renderSlice_FragmentProgramShading(
    DVRVolume      *volume, 
    DrawActionBase *action,
    Real32         *data, 
    UInt32          vertices, 
    UInt32          values  )
{
    SLOG << "DVRIsoShader::renderSlice for fragment program shading NI"
         << std::endl;
}

// render a clipped slice for 2D multitexture fragment program shading
void DVRIsoShader::renderSlice_FragmentProgramShading(
    DVRVolume      *volume, 
    DrawActionBase *action,
    DVRRenderSlice *clippedSlice)
{
    SLOG << "DVRIsoShader::renderSlice for fragment program shading NI"
         << std::endl;
}


char DVRIsoShader::_fragProg2D[] =
         "!!ARBfp1.0 \n"
         "PARAM scaleBias = {2, -1, 0, 0};\n"
         "TEMP volume, normal, intensity, color;\n"
         "\n"
         "TEX volume, fragment.texcoord[0], texture[0], 2D;\n"
         "MAD normal.xyz, volume, scaleBias.x, scaleBias.y;\n"
         "\n"
         "# Ambient color color\n"
         "MOV color, program.local[0]; # ambient color\n"
         "\n"
         "# Diffuse lighting\n"
         "DP3_SAT intensity, program.local[1], normal;\n"
         "MAD color, intensity, program.local[2], color;\n"
         "DP3_SAT intensity, program.local[3], normal;\n"
         "MAD color, intensity, program.local[4], color;\n"
         "DP3_SAT intensity, program.local[5], normal;\n"
         "MAD color, intensity, program.local[6], color;\n"
//         "DP3_SAT intensity, program.local[7], normal;\n"
//         "MAD color, intensity, program.local[8], color;\n" 
//         "DP3_SAT intensity, program.local[9], normal;\n"
//         "MAD color, intensity, program.local[10], color;\n"
//         "DP3_SAT intensity, program.local[11], normal;\n"
//         "MAD color, intensity, program.local[12], color;\n"
         "\n"
         "# Specular lighting - coefficient 4\n"
         "DP3_SAT intensity, program.local[13], normal;\n"
         "MUL intensity, intensity, intensity;\n"
         "MUL intensity, intensity, intensity;\n"
         "MAD color, intensity, program.local[14], color;\n" 
//          "DP3_SAT intensity, program.local[15], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[16], color;\n"
//          "DP3_SAT intensity, program.local[17], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[18], color;\n"
//          "DP3_SAT intensity, program.local[19], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[20], color;\n"
//          "DP3_SAT intensity, program.local[21], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[22], color;\n" 
//          "DP3_SAT intensity, program.local[23], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[24], color;\n"
         "\n"
         "MOV result.color, volume;\n"
         "MOV result.color.xyz, color;\n"
         "END\n";

char DVRIsoShader::_fragProg3D[] = 
         "!!ARBfp1.0 \n"
         "PARAM scaleBias = {2, -1, 0, 0};\n"
         "TEMP volume, normal, intensity, color;\n"
         "\n"
         "TEX volume, fragment.texcoord[0], texture[0], 3D;\n"
         "MAD normal.xyz, volume, scaleBias.x, scaleBias.y;\n"
         "\n"
         "# Ambient color color\n"
         "MOV color, program.local[0]; # ambient color\n"
         "\n"
         "# Diffuse lighting\n"
         "DP3_SAT intensity, program.local[1], normal;\n"
         "MAD color, intensity, program.local[2], color;\n"
         "DP3_SAT intensity, program.local[3], normal;\n"
         "MAD color, intensity, program.local[4], color;\n"
         "DP3_SAT intensity, program.local[5], normal;\n"
         "MAD color, intensity, program.local[6], color;\n"
//         "DP3_SAT intensity, program.local[7], normal;\n"
//         "MAD color, intensity, program.local[8], color;\n" 
//         "DP3_SAT intensity, program.local[9], normal;\n"
//         "MAD color, intensity, program.local[10], color;\n"
//         "DP3_SAT intensity, program.local[11], normal;\n"
//         "MAD color, intensity, program.local[12], color;\n"
         "\n"
         "# Specular lighting - coefficient 4\n"
         "DP3_SAT intensity, program.local[13], normal;\n"
         "MUL intensity, intensity, intensity;\n"
         "MUL intensity, intensity, intensity;\n"
         "MAD color, intensity, program.local[14], color;\n" 
//          "DP3_SAT intensity, program.local[15], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[16], color;\n"
//          "DP3_SAT intensity, program.local[17], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[18], color;\n"
//          "DP3_SAT intensity, program.local[19], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[20], color;\n"
//          "DP3_SAT intensity, program.local[21], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[22], color;\n" 
//          "DP3_SAT intensity, program.local[23], normal;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MUL intensity, intensity, intensity;\n"
//          "MAD color, intensity, program.local[24], color;\n"
         "\n"
         "MOV result.color, volume;\n"
         "MOV result.color.xyz, color;\n"
         "END\n";
