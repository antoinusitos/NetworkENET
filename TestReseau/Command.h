#pragma once

#include <string>

class Command
{
public:
	Command(const std::string& theCommand);
	~Command();

	const std::string& GetCommand() const;

private:
	int _id;
	const std::string& _command;
};

