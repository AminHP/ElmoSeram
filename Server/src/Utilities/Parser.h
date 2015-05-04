#ifndef __PARSER_H_
#define __PARSER_H_

#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::string>::iterator dat_itr;
typedef std::map<std::string, std::vector<std::string> >::iterator cmd_itr;

class Parser
{
private:
	std::map<std::string, std::string> mData;
	std::map<std::string, std::vector<std::string> > mCommand;

private:
	void fillCommand();

public:
	Parser();
	~Parser();

	void parseString(const std::string &msg);
	bool commandFound(const std::string &cmd);

	std::string &operator[](const std::string &key);
	std::string toStr();
};

#endif // __PARSER_H_
