/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include <OSGConfig.h>

#include "OSGDVRLookupTable.h"

OSG_USING_NAMESPACE

/*! \class osg::DVRLookupTable
Attachment for storing and handling Lookup-Tables for volume rendering.
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
DVRLookupTable::DVRLookupTable(void) :
    Inherited()
{
#if 0
    commonConstructor();
#endif
}

//! Copy Constructor
DVRLookupTable::DVRLookupTable(const DVRLookupTable &source) :
    Inherited(source)
{
#if 0
    commonConstructor();
#endif
}

//! Destructor
DVRLookupTable::~DVRLookupTable(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void DVRLookupTable::initMethod(void)
{
}

//! react to field changes
void DVRLookupTable::changed(BitVector whichField, UInt32 origin)
{
    SINFO << "DVRLookupTable::changed" << std::endl;

    if(whichField & DataFieldMask) 
    {
        // copy data from interleaved field to single fields
        UInt32 iter = 0;

        for(UInt32 i = 0; i < _sfDimension.getValue(); i++) 
        {
            for(UInt32 j = 0; j < _mfSize[i]; j++) 
            {
                for (UInt32 k = 0; k < _sfChannel.getValue(); k++) 
                {

#if 1
                    //!! TODO: REMOVE as soon as the loader works correctly
                    if(_mfDataR.size() < _mfData.size() / 4) 
                    {
                        int size = _mfData.size() / 4;

                        _mfDataR.resize(size);
                        _mfDataG.resize(size);
                        _mfDataB.resize(size);
                        _mfDataA.resize(size);
                    }
#endif
	    
                    //!! setValue ( <value>, index )
                    if(k == 0)
                    {
                        _mfDataR[j] = 
                            (Real32) _mfData[iter++] / 
                            (Real32) TypeTraits<UInt8>::getMax();
                    }
                    else if(k == 1)
                    {
                        _mfDataG[j] =
                            (Real32) _mfData[iter++] / 
                            (Real32) TypeTraits<UInt8>::getMax();
                    }
                    else if(k == 2)
                    {
                        _mfDataB[j] = 
                            (Real32) _mfData[iter++] / 
                            (Real32) TypeTraits<UInt8>::getMax();
                    }
                    else if(k == 3)
                    {
                        _mfDataA[j] =
                            (Real32) _mfData[iter++] / 
                            (Real32) TypeTraits<UInt8>::getMax();
                    }
                }
            }
        }
    }


    if(whichField & DataRFieldMask) 
    {
        // copy data from R field to channel 0 of interleaved field
        UInt32 iter        = 0;
        UInt32 numChannels = _sfChannel.getValue();

        for(UInt32 i = 0; i < _sfDimension.getValue(); i++) 
        {
            for(UInt32 j = 0; j < _mfSize[i]; j++) 
            {
                //!! setValue ( <value>, index )
                
                _mfData[iter] = 
                    UInt8(Real32(_mfDataR[j]) * 
                          Real32(TypeTraits<UInt8>::getMax()));

                iter += numChannels;
            }
        }
    }

    
    if(whichField & DataGFieldMask) 
    {
        // copy data from G field to channel 1 of interleaved field
        UInt32 iter        = 1;
        UInt32 numChannels = _sfChannel.getValue();

        for(UInt32 i = 0; i < _sfDimension.getValue(); i++) 
        {
            for(UInt32 j = 0; j < _mfSize[i]; j++) 
            {
                //!! setValue ( <value>, index )
                _mfData[iter] = 
                    UInt8(Real32(_mfDataG[j]) * 
                          Real32(TypeTraits<UInt8>::getMax()));

                iter += numChannels;
            }
        }
    }

    if(whichField & DataBFieldMask) 
    {
        // copy data from B field to channel 2 of interleaved field
        UInt32 iter        = 2;
        UInt32 numChannels = _sfChannel.getValue();
        
        for(UInt32 i = 0; i < _sfDimension.getValue(); i++) 
        {
            for(UInt32 j = 0; j < _mfSize[i]; j++) 
            {
                //!! setValue ( <value>, index )
                _mfData[iter] =
                    UInt8(Real32(_mfDataB[j]) * 
                          Real32(TypeTraits<UInt8>::getMax()));

                iter += numChannels;
            }
        }
    }

    
    if(whichField & DataAFieldMask) 
    {
        // copy data from A field to to channel 3 interleaved field
        UInt32 iter        = 3;
        UInt32 numChannels = _sfChannel.getValue();
        
        for(UInt32 i = 0; i < _sfDimension.getValue(); i++) 
        {
            for(UInt32 j = 0; j < _mfSize[i]; j++) 
            {
                //!! setValue ( <value>, index )
                _mfData[iter] = 
                    UInt8(Real32(_mfDataA[j]) * 
                          Real32(TypeTraits<UInt8>::getMax()));

                iter += numChannels;
            }
        }
    }

    
    if(whichField & (DimensionFieldMask | SizeFieldMask | ChannelFieldMask)) 
    {
        SINFO << "DVRLookupTable::changed - DimensionFieldMask | "
              << "SizeFieldMask | ChannelFieldMask " 
              << std::endl;

        if(whichField & DimensionFieldMask) 
        {
            SINFO << "DVRLookupTable::changed - dimension " 
                  << _sfDimension.getValue() 
                  << std::endl;
        }

        if(whichField & SizeFieldMask) 
        {
            SINFO << "DVRLookupTable::changed - size " 
                  << _mfSize[0] 
                  << std::endl;
        }

        if(whichField & ChannelFieldMask) 
        {
            SINFO << "DVRLookupTable::changed - channel " 
                  << _sfChannel.getValue() 
                  << std::endl;
        }

#if 0
        commonConstructor();
#endif
    }

    if(whichField & TouchedFieldMask) 
    {
        SINFO << "DVRLookupTable::changed - touched " << std::endl;
    }

#if 0
    // mark table as being changed
    setTouched( true );
#endif
    

    // notify parent if appearance 
    // CHECK
#if 0
    MFFieldContainerPtr *par = getMFParents();

    for(UInt32 i = 0; i < par->size(); i++) 
    {
    }
#endif

    Inherited::changed(whichField, origin);
}


//! output the instance for debug purposes
void DVRLookupTable::dump(      UInt32    uiIndent, 
                          const BitVector         ) const
{
    UInt32 col = 8; // print 8 values in each row
    UInt32   i = 0;

    DVRLookupTablePtr thisP(*this);
    thisP.dump(uiIndent, FCDumpFlags::RefCount);

    indentLog(uiIndent, PLOG);
    PLOG << "DVRLookupTable at " << this << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "dim: " 
         << (int) getDimension() 
         << " channel: "
         << (int) getChannel() 
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "sizes: ";

    for(MFUInt32::const_iterator   it  = _mfSize.begin(); 
                                   it != _mfSize.end  (); 
                                 ++it)
    {
        PLOG << std::dec << (int) *it << " ";
    }

    PLOG << std::endl;

    // Data
    indentLog(uiIndent, PLOG);
    PLOG << "Data:" << std::endl; 

    uiIndent += 4;

    indentLog(uiIndent, PLOG);
    for(i = 0; i < _mfData.size(); i++) 
    {
        PLOG << std::setw(9) << std::left << (int) _mfData[i] << " ";

        if((i + 1) % getChannel() == 0) 
        {
            PLOG << std::endl; indentLog(uiIndent, PLOG); 
        }
    }

    uiIndent -= 4;
    
    // DataR
    PLOG << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "DataR:" << std::endl; 
    
    uiIndent += 4;

    indentLog(uiIndent, PLOG);

    for(i = 0; i < _mfDataR.size(); i++) 
    {
        PLOG << std::setw(9) << std::left <<_mfDataR[i] << " ";

        if((i + 1) % col == 0) 
        {
            PLOG << std::endl; indentLog(uiIndent, PLOG); 
        }
    }

    uiIndent -= 4;

    // DataG
    PLOG << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "DataG:" << std::endl; 

    uiIndent += 4;

    indentLog(uiIndent, PLOG);
    
    for(i = 0; i < _mfDataG.size(); i++) 
    {
        PLOG << std::setw(9) << std::left << _mfDataG[i] << " ";

        if((i + 1) % col == 0) 
        {
            PLOG << std::endl; indentLog(uiIndent, PLOG); 
        }
    }

    uiIndent -= 4;

    // DataB
    PLOG << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "DataB:" << std::endl; 
    
    uiIndent += 4;

    indentLog(uiIndent, PLOG);

    for(i = 0; i < _mfDataB.size(); i++) 
    {
        PLOG << std::setw(9) << std::left << _mfDataB[i] << " ";

        if((i + 1) % col == 0)
        {
            PLOG << std::endl; indentLog(uiIndent, PLOG); 
        }
    }

    uiIndent -= 4;
    
    // DataA
    PLOG << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "DataA:" << std::endl; 

    uiIndent += 4;

    indentLog(uiIndent, PLOG);

    for(i = 0; i < _mfDataA.size(); i++) 
    {
        PLOG << std::setw(9) << std::left << _mfDataA[i] << " ";

        if((i + 1) % col == 0) 
        {
            PLOG << std::endl; indentLog(uiIndent, PLOG); 
        }
    }

    uiIndent -= 4;

    PLOG << std::endl;
}


//! used to initialize member variables - called by every constructor
void DVRLookupTable::commonConstructor(void)
{
    SLOG << "DVRLookupTable::commonConstructor" << std::endl;
    
    UInt32 size = _sfDimension.getValue();
  
    // set default size for every dimension
    _mfSize.resize(_sfDimension.getValue());

    for(UInt32 j = 0; j < _sfDimension.getValue(); j++) 
    {
        _mfSize[j] = 256;

        size *= _mfSize[j];
    }

    // allocate data field
    _mfData .resize(size * _sfChannel.getValue());
    _mfDataR.resize(size                        );
    _mfDataG.resize(size                        );
    _mfDataB.resize(size                        );
    _mfDataA.resize(size                        );

    // store default ramp
    UInt32 iter       = 0;
    UInt32 singleIter = 0;

    for(UInt32 i = 0; i < _sfDimension.getValue(); i++) 
    {
        for(UInt32 j = 0; j < _mfSize[i]; j++) 
        {
            //!! setValue ( <value>, index )

            _mfDataR[singleIter] = 
                (Real32) j / 
                (Real32) TypeTraits<UInt8>::getMax();

            _mfDataG[singleIter] = 
                (Real32) j / 
                (Real32) TypeTraits<UInt8>::getMax();

            _mfDataB[singleIter] = 
                (Real32) j / 
                (Real32) TypeTraits<UInt8>::getMax();

            _mfDataA[singleIter] = 
                (Real32) j / 
                (Real32) TypeTraits<UInt8>::getMax();
            
            singleIter++;
            
            for(UInt32 k = 0; k < _sfChannel.getValue(); k++) 
            {
                _mfData[iter++] = j;
            }
        }
    }
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGDVRLOOKUPTABLE_HEADER_CVSID;
    static char cvsid_inl[] = OSGDVRLOOKUPTABLE_INLINE_CVSID;
}

