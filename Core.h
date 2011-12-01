#include <iostream>
#include <string>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>

using namespace gloox;

class Core : public ConnectionListener, public MessageSessionHandler, public MessageHandler
{
public:
// à la connexion
void doSomething();
void onConnect();
void onDisconnect(ConnectionError e);
bool onTLSConnect(const CertInfo& info);



//à la reception de messages
void handleMessageSession(MessageSession* session);
void handleMessage(const Message& msg, MessageSession* session=0);

};



