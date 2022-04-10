#include "byte_buffer.h" 

ByteBuffer::ByteBuffer()
	:m_position(0)
{
}

ByteBuffer::ByteBuffer(const void* src, std::size_t size)
{
	write_data(src, size);
}

void ByteBuffer::write_data(const void* src, const std::size_t size)
{
	const uint8_t* ptr = reinterpret_cast<const uint8_t*>(src);
	m_data.insert(m_data.end(), ptr, ptr + size);
}

void ByteBuffer::read_data(void* dst, std::size_t size)
{
	if ((m_position + size) > this->size()) {
		throw std::runtime_error("subscript out of range");
	}

	memcpy(dst, &m_data[m_position], size);
	m_position += size;
}

void ByteBuffer::write_u8(uint8_t value)
{
	m_data.push_back(value);
}

void ByteBuffer::write_i16(int16_t value)
{
	write_data(&value, sizeof(value));
}

void ByteBuffer::write_i32(int32_t value)
{
	write_data(&value, sizeof(value));
}

void ByteBuffer::write_i64(int64_t value)
{
	write_data(&value, sizeof(value));
}

void ByteBuffer::write_float(float value)
{
	write_data(&value, sizeof(value));
}

void ByteBuffer::write_double(double value)
{
	write_data(&value, sizeof(value));
}

void ByteBuffer::write_string(const std::string& str)
{
	std::size_t length = str.length();
	write_i16(static_cast<int16_t>(length));

	if (length > 0) {
		write_data(str.data(), str.length());
	}
}

std::vector<uint8_t> ByteBuffer::read_bytes(std::size_t size)
{
	std::vector<uint8_t> bytes(size);
	read_data(bytes.data(), size);

	return bytes;
}

uint8_t ByteBuffer::read_u8()
{
	uint8_t retval;

	read_data(&retval, sizeof(retval));
	return retval;
}

int16_t ByteBuffer::read_i16()
{
	int16_t retval;

	read_data(&retval, sizeof(retval));
	return retval;
}

int32_t ByteBuffer::read_i32()
{
	int32_t retval;

	read_data(&retval, sizeof(retval));
	return retval;
}

int64_t ByteBuffer::read_i64()
{
	int64_t retval;

	read_data(&retval, sizeof(retval));
	return retval;
}

float ByteBuffer::read_float()
{
	float retval;

	read_data(&retval, sizeof(retval));
	return retval;
}

double ByteBuffer::read_double()
{
	double retval;

	read_data(&retval, sizeof(retval));
	return retval;
}

std::string ByteBuffer::read_string()
{
	std::size_t length = static_cast<std::size_t>(read_i16());
	return read_string(length);
}

std::string ByteBuffer::read_string(std::size_t length)
{
	if (length > 0) {
		std::vector<char> str(length);
		read_data(str.data(), length);

		return { str.begin(), str.end() };
	}
	return std::string();
}

const void* ByteBuffer::data() const
{
	return m_data.empty() ? nullptr : m_data.data();
}
