#include <algorithm>

#include <OSGConfig.h>
#include <OSGThreadManager.h>
#include <OSGBaseThread.h>
#include <OSGLock.h>
#include <OSGTime.h>
#include <OSGLog.h>
#include <OSGBaseFunctions.h>
#include <OSGGroupConnection.h>
#include <OSGDgramSocket.h>
#include <OSGPointConnection.h>
#include <OSGConnectionFactory.h>

int syncCount  = 10000;
int readCount  = 100;
int writeCount = 10000;

OSG_USING_NAMESPACE

char connectionType[256];

void findPoints(std::set<std::string> &address,int count)
{
    char response[256];
    DgramSocket sock;
    SocketAddress server;

    sock.open();
    sock.bind();
    while(address.size()<count)
    {
        sock.sendTo(&connectionType[0],255,SocketAddress("239.12.32.50",23344));
        if(!sock.waitReadable(.5))
            if(address.size() < count)
                continue;
            else
                return;
        sock.recv(response,256);
        if(!address.count(response))
        {
            address.insert(response);
            printf("got %s\n",response);
        }
    }
    sock.close();
}

void testSocketGroup(int maxServers)
{
    std::set<std::string> address;
    findPoints(address,maxServers);

    Time t,max;
    int count;
    GroupConnection *group = ConnectionFactory::the().createGroup(connectionType);

    if(strcmp(connectionType,"Multicast") == 0)
        group->setDestination("225.123.123.123");

    std::set<std::string>::iterator aI;
    for(aI=address.begin() ; aI != address.end() ;aI++)
    {
        printf("try to connect to %s\n",aI->c_str());
        group->connectPoint(*aI);
    }

    group->signal();
    group->wait();

    osgsleep(1000);

    // check sync
    t=-getSystemTime();
    max=0;
    for(count = 0 ; count < syncCount ; ++count)
    {
        Time t2=-getSystemTime();
        group->wait();
        group->signal();
        t2+=getSystemTime();
        if(t2>max)
            max=t2;
        if(t2>0.01)
            printf("%10.7f\n",t2);
    }
    group->wait();
    t+=getSystemTime();
    printf("Syncs/sec %10.2f  min %10.2f\n",syncCount/t,1.0/max);

    // check send
    t=-getSystemTime();
    char data[10000];
//    sprintf(data,"hallo ....1....2....3....4\n"); // !!!
    for(count = 0 ; count < writeCount ; ++count)
    {
//        sprintf(data,"hallo %d ....1....2....3....4\n",count); // !!!
        group->put(data,10000);
        group->flush();
    }
    group->wait();
    t+=getSystemTime();
    printf("Write Bytes/sec %10.2f  Sum/sec %10.2f\n",count*10000.0/t,address.size()*count*10000.0/t);

    // check read
    GroupConnection::Channel channel;
    t=-getSystemTime();
    for(count = 0 ; count < readCount ; ++count)
    {
        while(group->getSelectionCount())
        {
            channel = group->selectChannel();
            group->get(data,10000);
//            printf(data); // !!
            group->subSelection(channel);
        }
        group->resetSelection();
    }
    group->wait();
    t+=getSystemTime();
    printf("Read Bytes/sec %10.2f  Sum/sec %10.2f\n",count*10000.0/t,address.size()*count*10000.0/t);
/*
    // check timouts
    printf("start wait\n");
    if(!group->wait(4))
    {
        printf("wait ok\n");
    }
    printf("end wait\n");
*/
    group->signal();

    fflush(stdout);
    delete group;
}

void testSocketPoint()
{
    DgramSocket sock;
    SocketAddress client;
    char response[256];
    std::string lastType,newType;

    int count;
    PointConnection *point = NULL;
    std::string address;
    sock.open();
    sock.setTTL(1);
    sock.setReusePort(true);
    sock.bind(SocketAddress(SocketAddress::ANY,23344));
    sock.join(SocketAddress("239.12.32.50"));
    do
    {
        if(sock.waitReadable(0.2))
        {
            sock.recvFrom(&connectionType[0],255,client);
            newType = connectionType;
            printf("%s\n",connectionType);
            std::cout << newType << " " << lastType << std::endl;
            if(lastType != newType)
            {
                printf("create point %p\n",point);
                if(point)
                    delete point;
                point = ConnectionFactory::the().createPoint(connectionType);
                printf("create point %p\n",point);
                address = point->bind("");
                lastType = newType;
            }
            printf("bb\n");
            sprintf(response,"%.255s%c",address.c_str(),0);
            sock.sendTo(response,256,client);
            printf("%s %d\n",client.getHost().c_str(),client.getPort());
        }
    }
    while(!point || point->acceptGroup(.2)<0);
    sock.close();

    point->wait();
    point->signal();

    for(count = 0 ; count < syncCount ; ++count)
    {
        point->signal();
        point->wait();
    }
    char data[10000];
    point->signal();
    printf("read data\n");
    for(count = 0 ; count < writeCount ; ++count)
    {
        point->get(data,10000);
//        printf("got:%d %d %s\n",(int)data[0],(int)data[1],data); // !!
    }
    point->signal();
    printf("write data\n");
    sprintf(data,"hallo ....1....2....3....4\n"); // !!!
    for(count = 0 ; count < readCount ; ++count)
    {
        point->put(data,10000);
        point->flush();
    }
    point->signal();
    point->wait();

    delete point;
}

int main(int argc,char **argv)
{
    try 
    {
        osgInit(argc,argv);
        if(argc>2)
        {
            sprintf(connectionType,"%s",argv[1]);
            testSocketGroup(atoi(argv[2]));
        }
        else
            testSocketPoint();
    }
    catch(std::exception &e)
    {
        printf("error %s\n",e.what());
    }
    fflush(stdout);
}
