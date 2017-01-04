#pragma once

#include <string>

class Command
{
public:
	Command(std::string theCommand);
	~Command();

	std::string GetCommand();

private:
	int _id;
	std::string _command;
};

