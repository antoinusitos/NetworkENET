#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <enet/enet.h>
#include <thread>
#include "Client.h"

bool _isRunning = true;

void HandlesEvent(ENetHost * client)
{
	while (_isRunning)
	{

		/** HANDLES THE EVENT **/

		ENetEvent event;
		/* Wait up to 1000 milliseconds for an event. */
		while (enet_host_service(client, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n",
					event.peer->address.host,
					event.peer->address.port);
				/* Store any relevant client information here. */
				event.peer->data = "Client information";
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				/*printf("A packet of length %u containing %s was received from %s on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.peer->data,
					event.channelID);*/
				printf("%s \n", (char*)event.packet->data);
				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy(event.packet);

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", event.peer->data);
				/* Reset the peer's client information. */
				event.peer->data = NULL;
			}
		}
	}
}

void HandlesInput(ENetHost* client)
{
	while (_isRunning)
	{
		std::string strtmp;
		std::string name("testName");
		std::getline(std::cin, strtmp);
		name += " : " + strtmp;

		if (strtmp != "")
		{
			/* Create a reliable packet of size 7 containing "packet\0" */
			ENetPacket * packet = enet_packet_create(name.c_str(),
				strlen(name.c_str()) + 1,
				ENET_PACKET_FLAG_RELIABLE);
			/* Extend the packet so and append the string "foo", so it now */
			/* contains "packetfoo\0"                                      */
			enet_packet_resize(packet, strlen(name.c_str()) + 1);
			//strcpy(&packet->data[strlen("packet")], "foo");
			/* Send the packet to the peer over channel id 0. */
			/* One could also broadcast the packet by         */
			/* enet_host_broadcast (host, 0, packet);         */

			//enet_peer_send(peer, 0, packet);
			enet_host_broadcast(client, 0, packet);

			/* One could just use enet_host_service() instead. */
			enet_host_flush(client);
		}
	}
}

int main(int argc, char* argv[]) 
{
	Client* c = new Client();
	c->Run();

	if(c)
		delete c;
	return 0;
}