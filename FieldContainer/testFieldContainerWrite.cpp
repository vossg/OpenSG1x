#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <string>
#include <map>
#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGThread.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGChangeList.h>
#include <OSGFieldContainer.h>
#include <OSGGroup.h>

#include <OSGGeometry.h>
#include <OSGPointLight.h>

#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSimpleGeometry.h>

#include <OSGSceneFileHandler.h>

OSG_USING_NAMESPACE


class WriteSceneGraph
{
	public:
	WriteSceneGraph(ostream& stream, UInt32 indentStep=4);
	~WriteSceneGraph(void);
	void write( NodePtr node );
	
	private:
	void indentLine(void);
	void setIndentStep( UInt32 newStep );
	void doListFC( FieldContainerPtr fieldConPtr );
	void doPrintListedFC( FieldContainerPtr fieldConPtr );
	
	ostream& _outstream;
	
	struct SharedFCInfoHelper
	{
		Bool printed;
		Bool named;
		std::string name;
		static std::string buildName(FieldContainerPtr fcptr,
									 UInt32 num);
		SharedFCInfoHelper(void) : printed(false), named(false) {}
	};
	
	typedef map<FieldContainerPtr, SharedFCInfoHelper> SharedFCInfoMap;
	
	SharedFCInfoMap _fcmap;
	UInt32 _sharedFCCount;
	UInt32 _indention;
	UInt32 _indentStep;
};

WriteSceneGraph::WriteSceneGraph(ostream& stream, UInt32 indentStep) :
			 		_outstream(stream), _indentStep(indentStep)
{
	;
}

WriteSceneGraph::~WriteSceneGraph(void)
{
	;
}

void WriteSceneGraph::write(NodePtr node)
{
	_fcmap.clear();
	_sharedFCCount = 0;
	_indention = 0;
	
	doListFC(node);
	doPrintListedFC(node);	
}

void WriteSceneGraph::indentLine(void)
{
	for(UInt32 k=0; k<_indention; ++k)
	{
		_outstream << " ";
	}
}

void WriteSceneGraph::setIndentStep(UInt32 newStep)
{
	_indentStep = newStep;
}

void WriteSceneGraph::doListFC( FieldContainerPtr fieldConPtr )
{
	if( fieldConPtr == NullFC )
	{
		return;
	}
	
	if( _fcmap.insert(make_pair(fieldConPtr, SharedFCInfoHelper()) ).second ==
																		 true )
	{
		FieldContainerType &fcType = fieldConPtr->getType();
		for( UInt32 i=1; i <= fcType.getNumFieldDescs(); ++i )
		{
			FieldDescription* fDesc = fcType.getFieldDescription(i);
			Field *fieldPtr = fieldConPtr->getField(i);
			const FieldType &fType = fieldPtr->getType();
			if( !fDesc->isInternal() )
			{
				if( strstr(fType.getCName(), "Ptr") != NULL )
				{
					if( fieldPtr->getCardinality() == FieldType::SINGLE_FIELD )
					{
						doListFC( ((SFFieldContainerPtr *)
									  fieldPtr)->getValue() );
					}
					else if( fieldPtr->getCardinality() == 
													FieldType::MULTI_FIELD )
					{
						for( UInt32 j=0;
							j<((MFFieldContainerPtr *) fieldPtr)->getSize();
							++j )
						{
							doListFC( ((MFFieldContainerPtr *)
										  fieldPtr)->getValue(j) );
						}
					}
				}
			}
		}
	}
	else
	{
		SharedFCInfoMap::iterator iter = _fcmap.find( fieldConPtr );
		if( iter == _fcmap.end() )
		{
			cerr << "ERROR: This should not happen!" << endl;
		}
		if( (*iter).second.named == false )
		{
			(*iter).second.name = SharedFCInfoHelper::buildName((*iter).first, 
						 									_sharedFCCount++ );
			(*iter).second.named = true;
		}
	}
}


void WriteSceneGraph::doPrintListedFC( FieldContainerPtr fieldConPtr )
{
	if( fieldConPtr == NullFC )
	{
		indentLine(); _outstream << "NULL" << endl;
		return;
	}
	SharedFCInfoMap::iterator iter = _fcmap.find(fieldConPtr);
	if( iter == _fcmap.end() )
	{
		cerr << "ERROR: This should not happen!" << endl;
	}
	if( (*iter).second.printed == false )
	{
		(*iter).second.printed = true;
		FieldContainerType& fcType = fieldConPtr->getType();
		indentLine();
		if( (*iter).second.named == true )
		{
			_outstream << "DEF " << (*iter).second.name << " ";
									 
		}
		_outstream << fieldConPtr->getTypeName()
				   << " {" << endl;
		for( UInt32 i=1; i <= fcType.getNumFieldDescs(); ++i )
		{
			FieldDescription* fDesc = fcType.getFieldDescription(i);
			Field* fieldPtr = fieldConPtr->getField(i);
			const FieldType& fType = fieldPtr->getType();
			if( !fDesc->isInternal() )
			{
				indentLine(); _outstream << fDesc->getName();
				if( strstr(fType.getCName(), "Ptr") != NULL )
				{
					if( fieldPtr->getCardinality() == FieldType::SINGLE_FIELD )
					{
						_outstream << endl;
						_indention += _indentStep;
						doPrintListedFC( ((SFFieldContainerPtr *)
										  fieldPtr)->getValue() );
						_indention -= _indentStep;
					}
					else if( fieldPtr->getCardinality() ==
									 FieldType::MULTI_FIELD )
					{
						_outstream << " [" << endl;
						_indention += _indentStep;
						for( UInt32 j=0;
					   	  j<((MFFieldContainerPtr *) fieldPtr)->getSize(); ++j )
						{
							doPrintListedFC( ((MFFieldContainerPtr *)
										  fieldPtr)->getValue(j) );
						}
						_indention -= _indentStep;
						indentLine(); _outstream << "]" <<endl;
					}	
				}
				else
				{
					std::string val;
					fieldPtr->getValueByStr(val);
					if( fieldPtr->getCardinality() == FieldType::SINGLE_FIELD )
					{
						_outstream << " " << val <<endl;
					}
					else
					{
						_outstream << " [" << endl;
						_indention += _indentStep;
						indentLine(); _outstream << val <<endl;
						_indention -= _indentStep;
						indentLine(); _outstream << "]" << endl;
					}
				}
			}
		}
		indentLine(); _outstream << "}" << endl;
	}
	else
	{
		if( (*iter).second.named == false )
		{
			cerr << "WARNING: FC is shared, but was not named!" << endl;
		}
		indentLine(); _outstream << "USE "
							 	 << (*iter).second.name << endl;
	}
}


std::string WriteSceneGraph::SharedFCInfoHelper::buildName(
											FieldContainerPtr fcptr,
									 		UInt32 num)
{
	std::string temp;
	temp.assign( "FCName" );
	temp.append( TypeConstants<UInt32>::putToString(num) );
	return temp;
}



int main (int argc, char *argv[])
{
	for ( int i = 0; i < argc; i++ )
		cout << "Param " << i << ":" << argv[i] << endl;

    osgInit(argc, argv);
   
  	
	NodePtr node1, node2;
	
	node1 = makePlane( 2,2, 1,1 );
	node2 = makePlane( 1,1, 1,1 );
	
	NodePtr node11=Node::create(), node12= makeBox( 2,2,2, 1,1,1 );
	PointLightPtr node11Core = PointLight::create();
	beginEditCP(node11);
	node11->setCore(node11Core);
	endEditCP(node11);
	
	if( argc >=2 && *(argv[1]) == '1' )
	{
		cout << "Sharing the positions..." << endl;
		beginEditCP( node2 );
		GeometryPtr::dcast(node2->getCore())->setPositions(
					GeometryPtr::dcast(node1->getCore())->getPositions() );
		endEditCP( node2 );
	}
	else if( argc >=2 && *(argv[1]) == '2' )
	{
		node2 = Node::create();
		cout << "Sharing the core..." << endl;
		beginEditCP( node2 );
		node2->setCore( node1->getCore() );
		endEditCP( node2 );
	}
	beginEditCP(node1);
	node1->addChild(node11);
	node1->addChild(node12);
	endEditCP(node1);
	NodePtr root = Node::create();
	GroupPtr rootCore = Group::create();
	beginEditCP(root);
	root->setCore( rootCore );
	root->addChild( node1 );
	root->addChild( node2 );
	endEditCP(root);

	cerr << "STARTING PRINTOUT:" << endl;
	WriteSceneGraph writer( cout, 4 );
	writer.write( root );

	if( argc >= 3 )
			writer.write( SceneFileHandler::the().read(argv[2], 0) );
	
		
	return 0;
}
