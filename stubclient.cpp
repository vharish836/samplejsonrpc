#include <iostream>

#include "stubclient.h"
#include <jsonrpccpp/client/connectors/httpbasicauthclient.h>

using namespace jsonrpc;
using namespace std;

int main()
{
    HttpBasicAuthClient httpclient("http://localhost:8383","username","password");
    StubClient c(httpclient);
    try
    {
        cout << c.sayHello("Peter") << endl;
        c.notifyServer();
    }
    catch (JsonRpcException e)
    {
        cerr << e.what() << endl;
    }
}
