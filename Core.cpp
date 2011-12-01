#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>

#include "Core.h"



void Core::doSomething()
{

}

void Core::onConnect()
		 {
				 std::cout << "connecté en mode normal!" << std::endl ;			//             // presence info
		}

void Core::onDisconnect(ConnectionError e)
		 {
				 std::cout << "deconnecté!" << std::endl;			//             // presence info
				//             // presence info
		}

bool Core::onTLSConnect(const CertInfo& info)
		 {
				std::cout << "connecté en TLS!" << std::endl;			//             // presence info
				//             // presence info
				return 1;
		}


void Core::handleMessageSession(MessageSession* session)
{
  
session->registerMessageHandler(this);
session->send( "Message de session!", "No Subject" );

}



void Core::handleMessage(const Message& msg, MessageSession* session)
{
		std::cout << "un message a été envoyé automatiquement" << std::endl;
session->send( "Message de message!", "No Subject" );
}


