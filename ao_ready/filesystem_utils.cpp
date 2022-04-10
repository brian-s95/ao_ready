#include <fstream>

#include "filesystem_utils.h"

std::vector<uint8_t> FileSystem::read_all_bytes(const std::string& path)
{
	std::ifstream r_file(path, std::iostream::in | std::iostream::binary);
	if (!r_file.good())
		return {};
	
	std::vector<uint8_t> bytes;
	std::size_t size;

	r_file.seekg(0, std::iostream::end);
	size = r_file.tellg();
	r_file.seekg(0, std::iostream::beg);

	bytes.resize(size);
	r_file.read(reinterpret_cast<char*>(bytes.data()), size);

	r_file.close();
	return bytes;
}
