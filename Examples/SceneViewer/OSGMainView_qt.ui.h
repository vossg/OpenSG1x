/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/

//////////////////////////////////////////////////////////////////
// init: called by the widget constructor                       //
//////////////////////////////////////////////////////////////////
void OSGMainView::init()
{
    int i,n;
    OSG::NodePtr node;
    OSG::NodeCorePtr core;
    sceneView = new OSGSceneView(_main_frame, "OSGSceneView");
    QVBoxLayout *l = new QVBoxLayout(_main_frame);
    l->addWidget(sceneView);

    root = OSG::Node::create();
    core = OSG::Group::create();
    
    OSG::beginEditCP(root);
        root->setCore(core);
    OSG::endEditCP(root);
    
    OSG::setName(root, "Root");

    // load all args
    for (i = 1; i < qApp->argc(); i++)
    {
        node = OSG::SceneFileHandler::the().read(qApp->argv()[i]);
        if (node != OSG::NullFC)
        {
            OSG::beginEditCP(root);
                root->addChild(node);
            OSG::endEditCP(root);
        }
    }

    sceneView->setRootNode(root);
    sceneView->createView(root);

    resize(1024, 768);
}

//////////////////////////////////////////////////////////////////
// destory: called by the widget destructor                     //
//////////////////////////////////////////////////////////////////
void OSGMainView::destroyMainView()
{
}

//////////////////////////////////////////////////////////////////
// fileExit: closs the app                                      //
//////////////////////////////////////////////////////////////////
void OSGMainView::fileExit()
{
    this->close();
}

//////////////////////////////////////////////////////////////////
// fileNew: delete the current scene                            //
//////////////////////////////////////////////////////////////////
void OSGMainView::fileNew()
{
    sceneView->deleteNode(root);
}

//////////////////////////////////////////////////////////////////
// fileOpen: load a new scene; replace the current              //
//////////////////////////////////////////////////////////////////
void OSGMainView::fileOpen()
{
    fileNew();
    sceneView->insertFromFile(root);
}

//////////////////////////////////////////////////////////////////
// fileOpen: load a new scene; does not replace the current     //
//////////////////////////////////////////////////////////////////
void OSGMainView::fileInsert()
{
    sceneView->insertFromFile(root);
}

//////////////////////////////////////////////////////////////////
// filePrint: print the scene                                   //
//////////////////////////////////////////////////////////////////
void OSGMainView::filePrint()
{
}

//////////////////////////////////////////////////////////////////
// filePrint: save the scene                                    //
//////////////////////////////////////////////////////////////////
void OSGMainView::fileSave()
{
    sceneView->exportToFile(root);
}

//////////////////////////////////////////////////////////////////
// filePrint: save the scene                                    //
//////////////////////////////////////////////////////////////////
void OSGMainView::fileSaveAs()
{
    sceneView->exportToFile(root);
}

//////////////////////////////////////////////////////////////////
// filePrint: view the about message box                        //
//////////////////////////////////////////////////////////////////
void OSGMainView::helpAbout()
{
    QMessageBox::about(this, "About SceneView",
                       "OpenSG Scene Viewer\n"
                       "http://www.opensg.org");
}

//////////////////////////////////////////////////////////////////
// filePrint: contents help                                     //
//////////////////////////////////////////////////////////////////
void OSGMainView::helpContents()
{
}

//////////////////////////////////////////////////////////////////
// filePrint: index help                                        //
//////////////////////////////////////////////////////////////////
void OSGMainView::helpIndex()
{
}

//////////////////////////////////////////////////////////////////
// filePrint: create a new 3d opensg view                       //
//////////////////////////////////////////////////////////////////

void OSGMainView::setStatistics( bool  val)
{
    sceneView->setStatistics(val);
}

void OSGMainView::shadowOff(void)
{
    sceneView->setShadowMode(OSG::ShadowViewport::NO_SHADOW);
}

void OSGMainView::shadowStandard(void)
{
    sceneView->setShadowMode(OSG::ShadowViewport::STD_SHADOW_MAP);
}

void OSGMainView::shadowPerspective(void)
{
    sceneView->setShadowMode(OSG::ShadowViewport::PERSPECTIVE_SHADOW_MAP);
}

void OSGMainView::shadowDither(void)
{
    sceneView->setShadowMode(OSG::ShadowViewport::DITHER_SHADOW_MAP);
}

void OSGMainView::shadowPCF(void)
{
    sceneView->setShadowMode(OSG::ShadowViewport::PCF_SHADOW_MAP);
}

void OSGMainView::shadowPCSS(void)
{
    sceneView->setShadowMode(OSG::ShadowViewport::PCSS_SHADOW_MAP);
}

void OSGMainView::shadowVariance(void)
{
    sceneView->setShadowMode(OSG::ShadowViewport::VARIANCE_SHADOW_MAP);
}

void OSGMainView::ocOff(void)
{
    sceneView->setOcclusionCullingMode(0);
}

void OSGMainView::ocStopAndWait(void)
{
    sceneView->setOcclusionCullingMode(OSG::RenderAction::OcclusionStopAndWait);
}

void OSGMainView::ocMultiFrame(void)
{
    sceneView->setOcclusionCullingMode(OSG::RenderAction::OcclusionMultiFrame);
}

void OSGMainView::ocHierarchicalMultiFrame(void)
{
    sceneView->setOcclusionCullingMode(OSG::RenderAction::OcclusionHierarchicalMultiFrame);
}

void OSGMainView::setHeadlight(bool s)
{
    sceneView->setHeadlight(s);
}

