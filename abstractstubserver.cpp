#include <iostream>

#include "abstractstubserver.h"
#include <jsonrpccpp/server/connectors/httpbasicauthserver.h>


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

int main()
{
    HttpBasicAuthServer httpserver(8383,"username","password");
    MyStubServer s(httpserver);
    s.StartListening();
    getchar();
    s.StopListening();
    return 0;
}
