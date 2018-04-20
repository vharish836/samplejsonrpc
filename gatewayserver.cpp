#include <iostream>

#include "abstractgatewayserver.h"
#include "platformclient.h"
#include <jsonrpccpp/server/connectors/httpbasicauthserver.h>
#include <jsonrpccpp/client/connectors/httpbasicauthclient.h>
#include "argh.h"

using namespace jsonrpc;
using namespace std;

class GatewayServer: public AbstractGatewayServer
{
    public:
    GatewayServer(AbstractServerConnector& connector,const string& rpcurl, const string& rpcuser, const string& rpcpassword);
    virtual Json::Value getinfo();

    private:
    string rpcurl;
    string rpcuser;
    string rpcpassword;
    Json::Value result;
    void getblockchaininfo();    
};

GatewayServer::GatewayServer(AbstractServerConnector& connector, const string& rpcurl, 
                             const string& rpcuser, const string& rpcpassword) :
    AbstractGatewayServer(connector), rpcuser(rpcuser), rpcurl(rpcurl), rpcpassword(rpcpassword)
{    
}

void GatewayServer::getblockchaininfo()
{
    HttpBasicAuthClient httpclient(rpcurl,rpcuser,rpcpassword);
    PlatformClient c(httpclient,JSONRPC_CLIENT_V1);
    try
    {
        result = c.getblockchaininfo();
    }
    catch (JsonRpcException e)
    {
        cerr << e.what() << "\n";
        result = Json::nullValue;
    }    
}

Json::Value GatewayServer::getinfo()
{
    getblockchaininfo();
    return result;
}

int main(int argc, char* argv[])
{
    argh::parser cmdl;
    cmdl.parse(argc,argv);
    if(!cmdl(6))
    {
        cerr << "Please provide all required arguments!" << "\n";
        cerr << "Usage: " << cmdl[0] << " <serverport> <username> <password> <rpcurl> <rpcuser> <rpcpassword>" << "\n";
        exit(1);
    }
    int port;
    cmdl(1,8383) >> port;
    HttpBasicAuthServer httpserver(port,cmdl[2],cmdl[3]);
    GatewayServer server(httpserver,cmdl[4],cmdl[5],cmdl[6]);
    server.StartListening();
    getchar();
    server.StopListening();
    return 0;
}