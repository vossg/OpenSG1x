

#include "OOCPLYFeeder.h"

#include <fstream>
#include <math.h>
#include <strings.h>

#include <OpenSG/OSGLog.h>

#include <OpenSG/OSGply.h>
#include <OpenSG/OSGZStream.h>

OSG_USING_NAMESPACE;

// PLY structures

// Code


OOCPLYFeeder::OOCPLYFeeder(char *filenames[], int nf) :
    OOCFeeder(filenames, nf)
{
}

OOCPLYFeeder::~OOCPLYFeeder()
{
}


/* user's vertex and face definitions for a polygonal object */

typedef struct Vertex 
{
    float x,y,z;
    void *other_props;       /* other properties */
} Vertex;

typedef struct Face 
{
    unsigned char nverts;    /* number of vertex indices in list */
    int *verts;              /* vertex index list */
    void *other_props;       /* other properties */
} Face;

char *elem_names[] = 
{ /* list of the kinds of elements in the user's  object */
    "vertex", "face"
};

PlyProperty vert_props[] = { /* list of property information for a vertex */
    {"x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0},
    {"y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0},
    {"z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0},
};

PlyProperty face_props[] = { /* list of property information for a face */
    {"vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
     1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts)},
};

void OOCPLYFeeder::feedBoth(GeoReceiver *rec, GeoReceiver::pntRec pfunc, 
                              GeoReceiver::triRec tfunc)
{
    std::istream *in = NULL;
    
    UInt32 vbase = 0;
    
    for(UInt32 f = 0; f < _filenames.size(); ++f)
    {
        UInt32 vcount = 0;
        
        std::fstream file(_filenames[f].c_str(), 
                          std::ios::binary|std::ios::in);

        if(!file.good())
        {
            FWARNING(("OOCPLYFeeder::doFeed: problems opening file '%s'!\n",
                        _filenames[f].c_str()));
            return;
        }
    #ifdef OSG_ZSTREAM_SUPPORTED
        zip_istream *unzipper = NULL;
    #endif

        if(isGZip(file))
        {
    #ifdef OSG_ZSTREAM_SUPPORTED
            unzipper = new zip_istream(file);

            in = unzipper;
    #else
            SFATAL << "Compressed streams are not supported in this executable!"
                   << endLog;
    #endif
        }
        else
        {
            in = &file;
        }

        std::vector<std::string> elems;
        PlyFile* ply = ply_read(in, elems);
        if (!ply)
        {
            FWARNING(("OOCPLYFeeder::doFeed: ply problems opening file '%s'!\n",
                        _filenames[f].c_str()));
            return;
        }

        if(!pfunc)
        {
            SLOG << "File " << f + 1 << "/" << _filenames.size() 
                 << " Skipping points: 0%..";
        }
        else
        {
            SLOG << "File " << f + 1 << "/" << _filenames.size()
                 << " Progress: 0%..";
        }

        Real32 next_progress = .1f, progress;

        for (size_t i = 0; i < elems.size(); i++) 
        {
            const std::string& elem_name = elems[i];
            int num_elems;
            std::vector<PlyProperty> props;
            if (!ply_get_element_description(ply, elem_name, &num_elems, props)) 
            {
                continue;
            }

            if (elem_name == "vertex") 
            {
                int nverts = num_elems;

                /* set up for getting vertex elements */
                ply_get_property (ply, elem_name, &vert_props[0]);
                ply_get_property (ply, elem_name, &vert_props[1]);
                ply_get_property (ply, elem_name, &vert_props[2]);

                Vertex v;

                /* grab all the vertex elements */
                for (int j = 0; j < num_elems; j++) 
                {                   
                    ply_get_element (ply, (void *) &v);

                    Pnt3f p(v.x, v.y, v.z);

                    if(pfunc)
                    {
                        pfunc(rec, p);
                    }

                    progress = j / (Real32)num_elems;
                    if(progress > next_progress)
                    {
                        PLOG << next_progress * 100 << "%..";
                        next_progress += 0.1;
                    }
                }

                PLOG << "100%" << endLog;
                // Do we also have to traverse the faces?
                if(tfunc == NULL)
                    break;

                SLOG << "Progress: 0%..";
                next_progress = .1f;
                vcount = num_elems;
            }
            else if (elem_name == "face") 
            {
                /* set up for getting face elements */

                ply_get_property (ply, elem_name, &face_props[0]);

               /* grab all the face elements */
                for (int j = 0; j < num_elems; ++j) 
                {
                    Face f;
                    ply_get_element (ply, (void *) &f);

                    if(tfunc)
                    {
                        if(f.nverts == 3)
                        {
                            tfunc(rec, f.verts[0] + vbase, 
                                       f.verts[1] + vbase, 
                                       f.verts[2] + vbase,
                                       0);
                        }
                        else if(f.nverts == 4)
                        {
                            tfunc(rec, f.verts[0] + vbase, 
                                       f.verts[1] + vbase, 
                                       f.verts[2] + vbase,
                                       0);
                            tfunc(rec, f.verts[2] + vbase, 
                                       f.verts[3] + vbase, 
                                       f.verts[0] + vbase,
                                       0);
                        }
                        else
                        {
                            FWARNING(("OOCPLYFeeder::doFeed: Found face with "
                                "more than 4 points, ignored.\n"));
                        }
                    }

                    free(f.verts);

                    progress = j / (Real32)num_elems;
                    if(progress > next_progress)
                    {
                        PLOG << next_progress * 100 << "%..";
                        next_progress += 0.1;
                    }
                }

                PLOG << "100%" << endLog;
            }
        }

        ply_close(ply);

        vbase += vcount;
        
#ifdef OSG_ZSTREAM_SUPPORTED
        if(unzipper != NULL)
        {
            delete unzipper;
        }
#endif
    } // for f
}
