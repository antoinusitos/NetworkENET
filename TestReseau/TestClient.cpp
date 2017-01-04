#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <enet/enet.h>
#include <thread>
#include "Client.h"

int main(int argc, char* argv[]) 
{
	Client* c = new Client();
	c->Run();

	if(c)
		delete c;
	return 0;
}