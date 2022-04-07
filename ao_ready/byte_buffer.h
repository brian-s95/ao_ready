#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

class ByteBuffer
{
private:
	std::vector<uint8_t> m_data;
	std::size_t m_position;

public:
	ByteBuffer();

	void write_data(const void* src, std::size_t size);
	void read_data(void* dst, std::size_t size);

	void write_u8(uint8_t value);
	void write_i16(int16_t value);
	void write_i32(int32_t value);
	void write_i64(int64_t value);

	void write_float(float value);
	void write_double(double value);

	void write_string(const std::string& str);
	std::vector<uint8_t> read_bytes(std::size_t size);

	uint8_t read_u8();
	int16_t read_i16();
	int32_t read_i32();
	int64_t read_i64();

	float read_float();
	double read_double();

	std::string read_string();
	std::string read_string(std::size_t length);

	const void* data() const;
	void skip(std::size_t offset) { m_position += offset; }

	std::size_t position() const { return m_position; }
	std::size_t size() const { return m_data.size(); }
};