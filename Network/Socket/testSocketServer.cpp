#include <iostream>
#include <stdlib.h>
#include "OSGStreamSocket.h"
#include "OSGDgramSocket.h"
#include "OSGSocketSelection.h"

using namespace OSG;
using namespace std;

void streamServer()
{
    char buffer[6];
    SocketSelection sel,res;
    StreamSocket sock,client;

    cout << "Stream socket server: Start" << endl;
    // open socket
    sock.open();
    // reuse port. Might be dangerous
    sock.setReusePort(true);
    // bind to port
    sock.bind(SocketAddress(SocketAddress::ANY,23344));
    // listen to port
    sock.listen();
    // Wait for Client. This is optional!
    // every 2 seconds a message is printed
    sel.setRead(sock);
    while(!sel.select(2,res))
    {
        cout << "Waiting for client on port:" << sock.getAddress().getPort() << endl;
    }
    // accept client
    client=sock.accept();
    client.recv(buffer,6);
    sock.close();
    client.close();
    cout << "Stream socket server: OK" << endl;
}

void dgramServer()
{
    char buffer[6];
    DgramSocket sock;
    SocketAddress client;

    cout << "Dgram socket server: start" << endl;
    sock.open();
    // reuse port. Optional and can cause problems with other apps
    sock.setReusePort(true);
    // bind socket to port 23344
    sock.bind(SocketAddress(SocketAddress::ANY,23344));
    // read from client
    sock.recvFrom(buffer,6,client);
    // replay to client
    sock.sendTo(buffer,6,client);
    sock.close();
    cout << "Dgram socket server: OK" << endl;
}

void broadcastServer()
{
    char buffer[6];
    DgramSocket sock;
    SocketAddress client;

    cout << "Dgram broadcast server: Start" << endl;
    sock.open();
    sock.setReusePort(true);
    sock.bind(SocketAddress(SocketAddress::ANY,23344));
    sock.recvFrom(buffer,6,client);
    sock.sendTo(buffer,6,client);
    sock.close();
    cout << "Dgram broadcast server: OK" << endl;
}

void multicastServer()
{
    char buffer[6];
    DgramSocket sock;
    SocketAddress client;

    cout << "Dgram multicast server: Start" << endl;
    sock.open();
    sock.setReusePort(true);
    sock.bind(SocketAddress(SocketAddress::ANY,23344));
    sock.join(SocketAddress("224.0.0.50"));
    sock.join(SocketAddress("224.0.0.52"));
    sock.join(SocketAddress("224.0.0.53"));
    sock.leave(SocketAddress("224.0.0.52"));
    do
    {
        sock.recvFrom(buffer,6,client);
        sock.sendTo(buffer,6,client);
        cout << client.getHost() << " " << buffer << endl;
    } while(strcmp(buffer,"_END_"));
    sock.close();
    cout << "Dgram multicast server: OK" << endl;
}

int main(int argc,char **argv)
{
    try
    {
        streamServer();
        dgramServer();
        broadcastServer();
        multicastServer();
    }
    catch(exception &e)
    {
        cerr << "Error" << endl;
        cerr << e.what() << endl;
    }
}



