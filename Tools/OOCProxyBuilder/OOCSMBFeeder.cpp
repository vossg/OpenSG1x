
#include "OOCSMBFeeder.h"

#include <fstream>
#include <math.h>
#include <strings.h>
#include <stdio.h>

#include <OpenSG/OSGLog.h>

#include "smreader_smb.h"

OSG_USING_NAMESPACE;


OOCSMBFeeder::OOCSMBFeeder(char *filenames[], int nf) :
    OOCFeeder(filenames, nf)
{
    SMreader_smb reader;
    FILE *file;
    
    _bbmin.setValues(1e10,1e10,1e10);
    _bbmax.setValues(-1e10,-1e10,-1e10);
    _npts = _ntris = 0;
    
    for(UInt32 f = 0; f < _filenames.size(); ++f)
    {
        if(_filenames[f] == "stdin.smb")
            file = stdin;
        else
            file = fopen(_filenames[f].c_str(), "rb");
        
        if(!file)
        {
            FWARNING(("OOCSMBFeeder::doFeed: problems opening file '%s'!\n",
                        _filenames[f].c_str()));
            return;
        }

        reader.open(file);
        if(!reader.bb_min_f)
            continue;
            
        _bbmin[0] = osgMin(_bbmin[0], reader.bb_min_f[0]);
        _bbmin[1] = osgMin(_bbmin[1], reader.bb_min_f[1]);
        _bbmin[2] = osgMin(_bbmin[2], reader.bb_min_f[2]);
            
        _bbmax[0] = osgMax(_bbmax[0], reader.bb_max_f[0]);
        _bbmax[1] = osgMax(_bbmax[1], reader.bb_max_f[1]);
        _bbmax[2] = osgMax(_bbmax[2], reader.bb_max_f[2]);
        
        _npts += reader.nverts;
        _ntris += reader.nfaces;
    }
}

OOCSMBFeeder::~OOCSMBFeeder()
{
}

void OOCSMBFeeder::calcBasics(void)
{
   // Nothing to do, is done in constructor anyway 
}



void OOCSMBFeeder::feedBoth(GeoReceiver *rec, GeoReceiver::pntRec pfunc, 
                              GeoReceiver::triRec tfunc)
{
    SMreader_smb reader;
    FILE *file;
        
    UInt32 vbase = 0;
    
    for(UInt32 f = 0; f < _filenames.size(); ++f)
    {
        UInt32 vcount = 0, tcount = 0;
        
        file = fopen(_filenames[f].c_str(), "rb");
        
        if(!file)
        {
            FWARNING(("OOCSMBFeeder::doFeed: problems opening file '%s'!\n",
                        _filenames[f].c_str()));
            return;
        }

        reader.open(file);

        SMevent ev;

        SLOG << "File " << f + 1 << "/" << _filenames.size()
             << " Progress: ";

        Real32 progress, next_progress = 0;
        
        do
        {
            ev = reader.read_event();

            switch(ev)
            {
            case SM_VERTEX:     if(pfunc)
                                {
                                    Pnt3f p(reader.v_pos_f[0],
                                            reader.v_pos_f[1], 
                                            reader.v_pos_f[2]);
                                    pfunc(rec, p);
                                    
                                    vcount++;
                                    progress = vcount / (Real32)reader.nverts;
                                    if(progress > next_progress)
                                    {
                                        PLOG << next_progress * 100 << "%..";
                                        next_progress += 0.1;
                                    }
                                    
                                }
                                break;
            case SM_TRIANGLE:   if(tfunc)
                                {
                                    tfunc(rec, reader.t_idx[0] + vbase,
                                               reader.t_idx[1] + vbase,
                                               reader.t_idx[2] + vbase,
                                               0);
                                    
                                    tcount++;
                                    progress = tcount / (Real32)reader.nfaces;
                                    if(progress > next_progress)
                                    {
                                        PLOG << next_progress * 100 << "%..";
                                        next_progress += 0.1;
                                    }
                                    
                                }
                                break;
            case SM_FINALIZED:  break;
            case SM_EOF:        break;
            default:            SLOG << std::endl 
                                     << "OOCSMBFeeder::feedBoth: Got "
                                     << ev << " event!" << endLog;
                                break;
            }
        }
        while(ev != SM_EOF);

        PLOG << "100%" << endLog;

        reader.close();
        
        fclose(file);

        vbase += vcount;
    } // for f
}
