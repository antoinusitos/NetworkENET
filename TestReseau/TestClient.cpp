#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <enet/enet.h>
#include <thread>
#include "Client.h"

int main(int argc, char* argv[]) 
{
	Client c;
	c.Run();

	return 0;
}