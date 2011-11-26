#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>

#include <iostream>
#include <string>

using namespace gloox;



class MyClass : public ConnectionListener, MessageSessionHandler, MessageHandler
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

void MyClass::doSomething()
{
	JID jid( "bot@lutix.org/cptalk" );
	Client* client = new Client( jid, "fab99999" );
	client->registerConnectionListener( this );
	client->registerMessageSessionHandler( this, 0 );
	client->connect();
}

void MyClass::onConnect()
		 {
				 std::cout << "connecté en mode normal!" << std::endl ;			//             // presence info
		}

void MyClass::onDisconnect(ConnectionError e)
		 {
				 std::cout << "deconnecté!" << std::endl;			//             // presence info
				//             // presence info
		}

bool MyClass::onTLSConnect(const CertInfo& info)
		 {
				std::cout << "connecté en TLS!" << std::endl;			//             // presence info
				//             // presence info
				return 1;
		}


void MyClass::handleMessageSession(MessageSession* session)
{
  
session->registerMessageHandler(this);
session->send( "Messaage de session!", "No Subject" );

}



void MyClass::handleMessage(const Message& msg, MessageSession* session)
{

session->send( "Message de message!", "No Subject" );
}


int main() {

		std::cout << "######## Demarrage de cptalk ########" << std::endl; 
		MyClass exemple;
		exemple.doSomething();
		return 0;
}
