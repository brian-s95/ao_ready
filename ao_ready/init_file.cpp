#include <fstream>
#include <stdexcept>
#include <iostream>

#include "init_file.h"

namespace
{
	std::string to_lower(const std::string& str)
	{
		std::string retval = str;
		for(auto& c : retval)
		{
			c = tolower(c);
		}

		return retval;
	}
}


void InitFile::write_data(std::string main, std::string key, std::string value)
{
	m_data[to_lower(main)][to_lower(key)] = value;
}

std::string InitFile::read_data(std::string main, std::string key)
{
	return m_data[to_lower(main)][to_lower(key)];
}

void InitFile::read_from_file(const std::string &filename)
{
	std::ifstream file(filename);
	std::string line, main;

	while(std::getline(file, line))
	{
		if(line.empty())
			continue;
		if(line[0] == '\'' || line[0] == '#' || line[0] == '\\')
			continue;

		if(line[0] == '[')
		{
			auto pos = line.find(']');
			if(pos != std::string::npos)
			{
				main = to_lower(line.substr(1, pos - 1));
			}
		}
		else
		{
			auto pos = line.find('=');
			if(pos != std::string::npos)
			{
				std::string key = line.substr(0, pos);
				std::string value = line.substr(pos +1);

				m_data[main][to_lower(key)] = value;
			}
		}
	}
}

void InitFile::write_to_file(const std::string &filename)
{
	std::ofstream file(filename);

	for(auto&k : m_data)
	{
		file << "[" << k.first << "]\n";
		for(auto& kk : k.second)
		{
			file << kk.first << "=" << kk.second << "\n";
		}
		file << std::endl;
	}
}
