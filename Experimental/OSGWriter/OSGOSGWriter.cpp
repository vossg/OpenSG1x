/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

#define OSG_COMPILESYSTEMLIB

#include "OSGOSGWriter.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGOSGWriter.cpp,v 1.3 2001/10/07 09:32:36 vossg Exp $";
    static Char8 cvsid_hpp[] = OSGOSGWRITER_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSGWriter::SharedFCInfoHelper::SharedFCInfoHelper(void) : 
    printed(false), 
    named  (false),
    name   (     )
{
}

OSGWriter::OSGWriter(ostream &stream, UInt32 indentStep) :
    _fcmap        (          ),
    _sharedFCCount(0         ),
    _indention    (0         ),
    _indentStep   (indentStep),
    _outstream    (stream)
{
}

OSGWriter::~OSGWriter(void)
{
}

void OSGWriter::write(NodePtr node)
{
	_fcmap.clear();

	_sharedFCCount = 0;
	_indention     = 0;

	_outstream << "#OSG V1.0 " << endl;
	
	doListFC(node);
	doPrintListedFC(node);
}

void OSGWriter::write(vector<NodePtr> nodes)
{
	_fcmap.clear();

	_sharedFCCount = 0;
	_indention = 0;

	_outstream << "#OSG V1.0 " << endl;
	
	vector<NodePtr>::iterator iter = nodes.begin();

	for(; iter != nodes.end(); ++iter)
	{
		doListFC( *iter );
	}

	for(iter = nodes.begin(); iter != nodes.end(); ++iter)
	{
		doPrintListedFC( *iter );
	}
}

void OSGWriter::indentLine(void)
{
	for(UInt32 k = 0; k < _indention; ++k)
	{
		_outstream << " ";
	}
}

void OSGWriter::setIndentStep(UInt32 newStep)
{
	_indentStep = newStep;
}

void OSGWriter::doListFC(FieldContainerPtr fieldConPtr)
{
	if(fieldConPtr == NullFC)
		return;
	
	if(_fcmap.insert(make_pair(fieldConPtr, 
                               SharedFCInfoHelper())).second == true)
	{
		FieldContainerType &fcType = fieldConPtr->getType();

		for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
		{
			FieldDescription *fDesc    = fcType.getFieldDescription(i);
			Field            *fieldPtr = fieldConPtr->getField(i);

			const FieldType &fType = fieldPtr->getType();

			if(!fDesc->isInternal())
			{
				if( strstr(fType.getCName(), "Ptr") != NULL )
				{
					if( fieldPtr->getCardinality() == FieldType::SINGLE_FIELD )
					{
						doListFC(
                            ((SFFieldContainerPtr *) fieldPtr)->getValue());
					}
					else if(fieldPtr->getCardinality() == 
                            FieldType::MULTI_FIELD       )
					{
                        UInt32 j;

						for(  j = 0;
							  j < ((MFFieldContainerPtr*)fieldPtr)->getSize();
							++j)
						{
							doListFC( 
                                ((MFFieldContainerPtr*)fieldPtr)->getValue(j));
						}
					}
				}
			}
		}
	}
	else
	{
		SharedFCInfoMap::iterator iter = _fcmap.find(fieldConPtr);

		if(iter == _fcmap.end())
		{
			cerr << "ERROR: This should not happen!" << endl;
		}
		if(iter->second.named == false)
		{
			iter->second.name = 
                SharedFCInfoHelper::buildName(iter->first, 
                                              _sharedFCCount++);
			iter->second.named = true;
		}
	}
}


void OSGWriter::doPrintListedFC(FieldContainerPtr fieldConPtr)
{
	if(fieldConPtr == NullFC)
	{
		indentLine(); _outstream << "NULL" << endl;
		return;
	}

	SharedFCInfoMap::iterator iter = _fcmap.find(fieldConPtr);

	if(iter == _fcmap.end())
	{
		cerr << "ERROR: This should not happen!" << endl;
	}

	if(iter->second.printed == false)
	{
		iter->second.printed = true;

		FieldContainerType& fcType = fieldConPtr->getType();

		indentLine();

		if(iter->second.named == true)
		{
			_outstream << "DEF " << (*iter).second.name << " ";
		}

		_outstream << fieldConPtr->getTypeName()
				   << " {" 
                   << endl;

		for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
		{
			FieldDescription *fDesc    = fcType.getFieldDescription(i);
			Field            *fieldPtr = fieldConPtr->getField(i);

			const FieldType& fType = fieldPtr->getType();

			if(!fDesc->isInternal())
			{
				indentLine(); 
                _outstream << fDesc->getName();

				if(strstr(fType.getCName(), "Ptr") != NULL)
				{
					if(fieldPtr->getCardinality() == FieldType::SINGLE_FIELD)
					{
						_outstream << endl;
						_indention += _indentStep;

						doPrintListedFC( 
                            ((SFFieldContainerPtr *) fieldPtr)->getValue());

						_indention -= _indentStep;
					}
					else if(fieldPtr->getCardinality() ==
                            FieldType::MULTI_FIELD       )
					{
                        UInt32 j;

						_outstream << " [" << endl;
						_indention += _indentStep;

						for(  j = 0;
                              j < ((MFFieldContainerPtr*)fieldPtr)->getSize();
                            ++j)
						{
							doPrintListedFC( ((MFFieldContainerPtr *)
										  fieldPtr)->getValue(j) );
						}

						_indention -= _indentStep;

						indentLine(); 

                        _outstream << "]" <<endl;
					}	
				}
				else
				{
					string val;

					fieldPtr->getValueByStr(val);

					if( fieldPtr->getCardinality() == FieldType::SINGLE_FIELD )
					{
						_outstream << " " << val <<endl;
					}
					else
					{
						_outstream << " [" << endl;

						_indention += _indentStep;

						indentLine(); 

                        _outstream << val <<endl;

						_indention -= _indentStep;

						indentLine(); 
                        
                        _outstream << "]" << endl;
					}
				}
			}
		}
        
		indentLine(); 

        _outstream << "}" << endl;
	}
	else
	{
		if(iter->second.named == false)
		{
			cerr << "WARNING: FC is shared, but was not named!" << endl;
		}

		indentLine(); 
        
        _outstream << "USE " << iter->second.name << endl;
	}
}


string OSGWriter::SharedFCInfoHelper::buildName(FieldContainerPtr fcptr,
                                                UInt32            num)
{
	string temp;

	temp.assign("FCName");
	temp.append(TypeConstants<UInt32>::putToString(num));

	return temp;
}
