#ifndef INIT_FILE_H_
#define INIT_FILE_H_
#include <map>
#include <string>

class InitFile
{
private:
	std::map<std::string, std::map<std::string, std::string>> m_data;

public:
	void write_data(std::string main, std::string key, std::string value);
	std::string read_data(std::string main, std::string key);

	void read_from_file(const std::string& filename);
	void write_to_file(const std::string& fielaname);
};

#endif /* INIT_FILE_H_ */
