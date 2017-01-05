#include "stdafx.h"
#include "Command.h"

Command::Command(const std::string& theCommand)
	: _command(theCommand)
	, _id(123456)
{
}

Command::~Command()
{
}

const std::string& Command::GetCommand() const
{
	return _command;
}
