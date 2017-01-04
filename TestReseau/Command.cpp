#include "stdafx.h"
#include "Command.h"

Command::Command(std::string theCommand)
{
	_id = 123456;
	_command = theCommand;
}

Command::~Command()
{
}

std::string Command::GetCommand()
{
	return _command;
}
