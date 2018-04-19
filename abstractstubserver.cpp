#include <iostream>

#include "abstractstubserver.h"
#include <jsonrpccpp/server/connectors/httpbasicauthserver.h>
#include "argh.h"

using namespace jsonrpc;
using namespace std;

class MyStubServer : public AbstractStubServer
{
    public:
        MyStubServer(AbstractServerConnector &connector);

        virtual void notifyServer();
        virtual std::string sayHello(const std::string& name);
};

MyStubServer::MyStubServer(AbstractServerConnector &connector) :
    AbstractStubServer(connector)
{
}
void MyStubServer::notifyServer()
{
    cout << "Server got notified" << endl;
}
string MyStubServer::sayHello(const string &name)
{
    cout << "hello called with: " << name << endl;
    return "Hello " + name;
}

int main(int argc, char* argv[])
{
    argh::parser cmdl({"-p", "--port"});
    cmdl.parse(argc,argv);
    if(!cmdl(2))
    {
        cerr << "Must provide atleast 2 arguments" << "\n";
        cerr << "Usage: " << cmdl[0] << " username password [-p/--port <port>]" << "\n";
        exit(1);
    }
    string user;
    string pass;
    int port;
    cmdl(1,"username") >> user;
    cmdl(2,"password") >> pass;
    cmdl({"-p","--port"},8383) >> port;
    HttpBasicAuthServer httpserver(port,user,pass);
    MyStubServer s(httpserver);
    s.StartListening();
    getchar();
    s.StopListening();
    return 0;
}
