#include <OSGConfig.h>
#include <OSGThreadManager.h>
#include <OSGBaseThread.h>
#include <OSGLock.h>
#include <OSGLog.h>
#include <OSGBaseFunctions.h>
#include <OSGConnection.h>
#include <OSGConnectionFactory.h>

using namespace OSG;

BaseThread              *connectThread;
std::vector<BaseThread*> acceptThread;
Lock                    *addressLock;
Barrier                 *mybarrier;
std::string              connectionType="Multicast";
int                      recvCount=4;
std::vector<std::string> recvAddress;
UInt32                   dataCount=100000;

void *connectProc(void *)
{
    UInt32 i,j,c;
    try
    {
        Connection *connection = 
            ConnectionFactory::the().create(connectionType);
        if(!connection)
        {
            SFATAL << "Unknown connection " << connectionType << std::endl;
            exit(0);
        }
        mybarrier->enter(recvCount+1);
        for(i=0;i<recvAddress.size();++i)
        {
            FLOG(("Connect to %s\n",recvAddress[i].c_str()));
            connection->connect(recvAddress[i]);
            FLOG(("Connect to %s OK\n",recvAddress[i].c_str()));
        }
        for(i=0;i<dataCount;i++)
        {
            connection->putValue(i);
        }
        connection->flush();
        SLOG << "send OK" << std::endl;
        for(c=0;c<recvCount;c++)
        {
            FLOG(("wait for %d\n",c));
            connection->selectChannel();
            FLOG(("read from %d\n",c));
            for(i=0;i<dataCount;i++)
            {
                connection->getValue(j);
                if(j!=i)
                {
                    FLOG(("Error: Unexpected data on channel %d\n",i));
                }
            }
            FLOG(("recv %d OK\n",c));
        }
        SLOG << "recv OK" << std::endl;
        connection->signal();
        delete connection;
    }
    catch(OSG_EXCEPTION_NAMESPACE::exception &e)
    {
        FFATAL(("Error while connecting: %s\n",e.what()));
    }
    return NULL;
}

void *acceptProc(void *)
{
    UInt32 i,j;

    try
    {
        Connection *connection = ConnectionFactory::the().create(connectionType);
        addressLock->aquire();
        std::string address=connection->bind("");
        recvAddress.push_back(address);
        addressLock->release();
        mybarrier->enter(recvCount+1);
        FLOG(("Accept connection %s\n",address.c_str()));
        connection->accept();
        connection->selectChannel();
        FLOG(("Accept connection %sOK\n",address.c_str()));
        for(i=0;i<dataCount;i++)
        {
            connection->getValue(j);
            if(j!=i)
            {
                SLOG << "Error: Unexpected data!!" << std::endl;
            }
        }
        SLOG << "recvB OK" << std::endl;
        for(i=0;i<dataCount;i++)
        {
            connection->putValue(i);
        }
        connection->flush();
        SLOG << "sendB OK" << std::endl;
        connection->wait();
        delete connection;
    }
    catch(OSG_EXCEPTION_NAMESPACE::exception &e)
    {
        FFATAL(("Error while connecting: %s\n",e.what()));
    }
    return NULL;
}

void testConnection(char *name)
{
    int i;

    connectionType=name;
    // create threads
    connectThread=BaseThread::get(NULL);
    connectThread->runFunction( connectProc, NULL );
    acceptThread.clear();
    recvAddress.clear();
    for(i=0;i<recvCount;++i)
    {
        acceptThread.push_back(BaseThread::get(NULL));
        (*acceptThread.rbegin())->runFunction( acceptProc, NULL );
    }
    // join threads                           
    BaseThread::join(connectThread);
    for(i=0;i<recvCount;++i)
    {
        BaseThread::join(acceptThread[i]);
    }
}

int main(int argc,char **argv)
{
 	// OSG init
    osgInit(argc, argv);
    // create barrier
    mybarrier = Barrier::get(NULL);
    // create lock
    addressLock=Lock::get(NULL);

    if(argc>1)
    {
        testConnection(argv[1]);
    }
    else
    {
        testConnection("Multicast");
        testConnection("StreamSock");
    }
    return 0;
}
