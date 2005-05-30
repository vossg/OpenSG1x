#include <OSGConfig.h>
#include <iostream>
#include <OSGLog.h>
#include <OSGNode.h>
#include <OSGPointConnection.h>
#include <OSGGroupConnection.h>
#include <OSGConnectionFactory.h>
#include <OSGRemoteAspect.h>
#include <OSGTransform.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>

OSG_USING_NAMESPACE RemoteAspect    *aspect;
PointConnection                     *connection;
bool                                verbose = false;
WindowPtr                           window;

int                                 nodes = 0;
int                                 transforms = 0;
int                                 geometries = 0;

/* */

bool createdFunction(FieldContainerPtr &fcp, RemoteAspect *)
{
    if(Node::getClassType() == fcp->getType())
        nodes++;
    if(Transform::getClassType() == fcp->getType())
        transforms++;
    if(Geometry::getClassType() == fcp->getType())
        geometries++;

    if(verbose)
    {
        printf("Created:%s %d\n", fcp->getType().getName().str(),
                       fcp.getFieldContainerId());
    }

    return true;
}

/** \brief Default destroyed functor
 */
bool destroyedFunction(FieldContainerPtr &fcp, RemoteAspect *)
{
    if(Node::getClassType() == fcp->getType())
        nodes--;
    if(Transform::getClassType() == fcp->getType())
        transforms--;
    if(Geometry::getClassType() == fcp->getType())
        geometries--;

    if(verbose)
    {
        printf("Destroyed:%s %d\n", fcp->getType().getName().str(),
                       fcp.getFieldContainerId());
    }

    return true;
}

/** \brief Default changed functor
 */
bool changedFunction(FieldContainerPtr &fcp, RemoteAspect *)
{
    if(verbose)
    {
        printf("Changed:%s %d\n", fcp->getType().getName().str(),
                       fcp.getFieldContainerId());
    }

    return true;
}

/* */
NodePtr createNode(void)
{
    TransformPtr    trans = Transform::create();
    NodePtr         transNode = Node::create();
    GeometryPtr     geo = makeBoxGeo(.6, .6, .6, 10, 10, 10);
    NodePtr         geoNode = Node::create();

    beginEditCP(geoNode);
    beginEditCP(trans);
    beginEditCP(transNode);

    transNode->setCore(trans);
    geoNode->setCore(geo);
    transNode->addChild(geoNode);

    endEditCP(trans);
    endEditCP(transNode);
    endEditCP(geoNode);
    endEditCP(transNode);

    return transNode;
}

/* */
void client(void)
{
    bool    finish = false;
    size_t  i, j;
    std::vector < NodePtr > nodes;

    connection->connectPoint("localhost:6789");
    OSG::Thread::getCurrentChangeList()->clearAll();

    // create change and remove in the same frame
    for(i = 0; i < 10; ++i)
    {
        NodePtr n = createNode();
        subRefCP(n);
    }

    aspect->sendSync(*connection, Thread::getCurrentChangeList());
    connection->putValue(finish);
    OSG::Thread::getCurrentChangeList()->clearAll();

    for(j = 0; j < 20; j++)
    {
        // create and change nodes, make sync and subref in next frame
        nodes.clear();
        for(i = 0; i < 200; ++i)
        {
            nodes.push_back(createNode());
        }

        aspect->sendSync(*connection, Thread::getCurrentChangeList());
        connection->putValue(finish);
        OSG::Thread::getCurrentChangeList()->clearAll();
        for(i = 0; i < nodes.size(); ++i)
        {
            subRefCP(nodes[i]);
        }

        aspect->sendSync(*connection, Thread::getCurrentChangeList());
        connection->putValue(finish);
        OSG::Thread::getCurrentChangeList()->clearAll();
    }

    // finish
    aspect->sendSync(*connection, Thread::getCurrentChangeList());
    finish = true;
    connection->putValue(finish);
    connection->flush();

    // wait for server to finish
    connection->selectChannel();
    connection->getValue(finish);
}

/* */
void server(void)
{
    bool                    finish;

    RemoteAspect::Functor   changed = osgTypedFunctionFunctor2CPtrRef < bool,
        FieldContainerPtr, RemoteAspect * > (changedFunction);

    RemoteAspect::Functor   destroyed = osgTypedFunctionFunctor2CPtrRef < bool,
        FieldContainerPtr, RemoteAspect * > (destroyedFunction);

    RemoteAspect::Functor   created = osgTypedFunctionFunctor2CPtrRef < bool,
        FieldContainerPtr, RemoteAspect * > (createdFunction);

    aspect->registerChanged(Node::getClassType(), changed);
    aspect->registerChanged(Transform::getClassType(), changed);
    aspect->registerChanged(Geometry::getClassType(), changed);

    aspect->registerDestroyed(Node::getClassType(), destroyed);
    aspect->registerDestroyed(Transform::getClassType(), destroyed);
    aspect->registerDestroyed(Geometry::getClassType(), destroyed);

    aspect->registerCreated(Node::getClassType(), created);
    aspect->registerCreated(Transform::getClassType(), created);
    aspect->registerCreated(Geometry::getClassType(), created);

    connection->bind("localhost:6789");
    connection->acceptPoint();
    connection->selectChannel();

    window = GLUTWindow::create();

    do
    {
        aspect->receiveSync(*connection);
        window->frameExit();
        OSG::Thread::getCurrentChangeList()->clearAll();
        connection->getValue(finish);
        printf("Nodes: %10d Transforms: %10d Geometries: %10d\n", nodes,
                       transforms, geometries);
    } while(!finish);

    // tell client finish
    connection->putValue(finish);
    connection->flush();
}

/* */
int main(int argc, char **argv)
{
    int     i;
    bool    runServer = false;

    ChangeList::setReadWriteDefault();
    osgInit(argc, argv);
    aspect = new RemoteAspect();
    connection = ConnectionFactory::the().createPoint("StreamSock");
    for(i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
            case 's':
                runServer = true;
                break;
            case 'v':
                verbose = true;
                break;
            }
        }
    }

    try
    {
        if(runServer)
            server();
        else
            client();
    }

    catch(OSG_STDEXCEPTION_NAMESPACE::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    delete connection;
    delete aspect;
    return 0;
}
