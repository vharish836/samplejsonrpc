#include <iostream>

#include "stubclient.h"
#include <jsonrpccpp/client/connectors/httpbasicauthclient.h>
#include "argh.h"

using namespace jsonrpc;
using namespace std;

int main(int argc, char* argv[])
{
    argh::parser cmdl;
    cmdl.parse(argc,argv);
    if(!cmdl(3))
    {
        cerr << "Must provide all 3 arguments!" << "\n";
        cerr << "Usage: " << cmdl[0] << " url username password" << "\n";
        exit(1);
    }

    HttpBasicAuthClient httpclient(cmdl[1],cmdl[2],cmdl[3]);
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
