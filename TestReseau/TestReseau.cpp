#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <enet/enet.h>
#include <thread>

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
		std::string name(client->name);
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
	/** INITIALIZE THE LIBRARY **/

	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	/** CREATE OF THE CLIENT **/

	ENetHost * client;
	client = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
		14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
	if (client == NULL)
	{
		fprintf(stderr,	"An error occurred while trying to create an ENet client host.\n");
		exit(EXIT_FAILURE);
	}

	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;

	/* Connect to some.server.net:1234. */
	enet_address_set_host(&address, "localhost");
	address.port = 1234;
	/* Initiate the connection, allocating the two channels 0 and 1. */
	peer = enet_host_connect(client, &address, 2, 0);
	if (peer == NULL)
	{
		fprintf(stderr,
			"No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Enter Your Name : \n");

	std::string name;
	std::getline(std::cin, name);
	char* cstr = new char[name.length() + 1];
	strcpy_s(cstr, strlen(cstr) + 1, name.c_str());

	client->name = cstr;

	/* Wait up to 5 seconds for the connection attempt to succeed. */
	if (enet_host_service(client, &event, 5000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		puts("Connection to some.server.net:1234 succeeded.");

		std::thread first(HandlesEvent, client);
		std::thread second(HandlesInput, client);
		
		first.join();               
		second.join();			
		
		while (true)
		{
			//HandlesEvent(client);
			//HandlesInput(client);

		}

	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		enet_peer_reset(peer);
		puts("Connection to some.server.net:1234 failed.");
	}

	

	//...

	enet_host_destroy(client);

	return 0;
}