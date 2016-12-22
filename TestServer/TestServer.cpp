#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <enet/enet.h>

int main(int argc, char* argv[])
{
	/** INITIALIZE THE LIBRARY **/

	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	/** CREATE OF THE SERVER **/

	ENetAddress address;
	ENetHost* server;
	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	/* enet_address_set_host (& address, "x.x.x.x"); */
	address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	address.port = 1234;
	server = enet_host_create(&address /* the address to bind the server host to */,
		32      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		fprintf(stderr,	"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
	
	while (true)
	{

		/** HANDLES THE EVENT **/

		ENetEvent event;
		/* Wait up to 1000 milliseconds for an event. */
		while (enet_host_service(server, &event, 1000) > 0)
		{
			/* Create a reliable packet of size 7 containing "packet\0" */
			ENetPacket* packet;

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
				printf("A packet of length %u containing %s was received from %s on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.peer->data,
					event.channelID);

					/** SEND BACK THE PACKET TO ALL CLIENT **/

					packet = enet_packet_create((char*)event.packet->data, strlen((char*)event.packet->data) + 1, ENET_PACKET_FLAG_RELIABLE);
					/* Extend the packet so and append the string "foo", so it now */
					/* contains "packetfoo\0"                                      */
					enet_packet_resize(packet, strlen((char*)event.packet->data) + 1);
					//strcpy(&packet->data[strlen("packet")], "foo");
					/* Send the packet to the peer over channel id 0. */
					/* One could also broadcast the packet by         */
					/* enet_host_broadcast (host, 0, packet);         */

					//enet_peer_send(peer, 0, packet);
					enet_host_broadcast(server, 0, packet);

					/* One could just use enet_host_service() instead. */
					enet_host_flush(server);


				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy(event.packet);

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", event.peer->data);
				/* Reset the peer's client information. */
				event.peer->data = NULL;
				break;
			}
		}
	}

	//...

	enet_host_destroy(server);

	return 0; 
}