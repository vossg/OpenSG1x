#include <iostream>
#include <stdlib.h>
#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGStreamSocket.h"
#include "OSGDgramSocket.h"
#include "OSGSocketSelection.h"

using namespace OSG;
using namespace std;

void streamClient()
{
    StreamSocket sock;

    SLOG << "Stream socket client: Start" << endl;
    sock.open();
    try 
    {
        sock.connect(SocketAddress("localhost",23344));
    }
    catch(SocketException &)
    {
        SWARNING << "Unable to connect to server" << endl;
        throw;
    }
    sock.send("hallo",6);
    sock.close();
    SLOG << "Stream socket client: OK" << endl;
}

void dgramClient()
{
    char buffer[6];
    DgramSocket sock;
    SocketAddress server;
    bool retry;

    SLOG << "Dgram socket client: Start" << endl;
    sock.open();
    // bind socket
    do
    {
        do
        {
            // write to server
            sock.sendTo("hallo",6,SocketAddress("localhost",23344));
        }
        while(sock.waitReadable(0.2)==false); // wait 0.2 sec for response
        try
        {
            sock.recvFrom(buffer,6,server);
            retry=false;
        }
        catch(SocketConnReset &)
        {
            // this could happen, when we have send a package to
            // a port which was unbound and the host responds
            // this with an icmp package. In this case, this is
            // not an error, because we whant to wait for this
            // port to be open.
            retry=true;
        }
    }
    while(retry);
    sock.close();
    SLOG << "Dgram socket client: OK" << endl;
}

void broadcastClient()
{
    char buffer[6];
    DgramSocket sock;
    SocketAddress server;
    SocketSelection sel;

    SLOG << "Dgram broadcast client: Start" << endl;
    sock.open();
    // broadcast until answer from server
    do
    {
        // write to server
        sock.sendTo("hallo",6,
                    SocketAddress(SocketAddress::BROADCAST,23344));
        // check for server response
        sel.setRead(sock);
    } 
    while(sel.select(0.2)==0); // wait 0.2 sec for response
    sock.recvFrom(buffer,6,server);
    sock.close();
    SLOG << "Dgram broadcast client: OK" << endl;
}

void multicastClient()
{
    char buffer[6];
    DgramSocket sock;
    SocketAddress server;
    SocketSelection sel;
    SocketAddress addr[3]={
        SocketAddress("224.0.0.50",23344),
        SocketAddress("224.0.0.53",23344),
        SocketAddress("224.0.0.50",23344)
    };
    char *msg[3]={
        "msg:1","msg:2","_END_"
    };
    int i;

    SLOG << "Dgram multicast client: Start" << endl;
    sock.open();
    for(i=0;i<3;i++)
    {
        // broadcast until answer from server
        do
        {
            // write to server
            sock.sendTo(msg[i],6,addr[i]);
            // check for server response
            sel.setRead(sock);
        } 
        while(sel.select(0.2)==0); // wait 0.2 sec for response
        sock.recvFrom(buffer,6,server);
    }
    sock.close();
    SLOG << "Dgram multicast client: OK" << endl;
}

int main(int argc,char **argv)
{
    try
    {
        streamClient();
        dgramClient();
        broadcastClient();
        multicastClient();
    }
    catch(exception &e)
    {
        SWARNING << e.what() << endl;
    }
	return 0;
}

