#ifndef SHA1_HPP
#define SHA1_HPP

#include <iostream>
#include <string>

class Encript
{
public:
	Encript();
	void update(const std::string &s);
	void update(std::istream &is);
	std::string final();
	static std::string from_file(const std::string &filename);

private:
	typedef unsigned long int uint32;
	typedef unsigned long long uint64;

	static const unsigned int DIGEST_INTS = 5;
	static const unsigned int BLOCK_INTS = 16;
	static const unsigned int BLOCK_BYTES = BLOCK_INTS * 4;

	uint32 digest[DIGEST_INTS];
	std::string buffer;
	uint64 transforms;

	void reset();
	void transform(uint32 block[BLOCK_BYTES]);

	static void buffer_to_block(const std::string &buffer, uint32 block[BLOCK_BYTES]);
	static void read(std::istream &is, std::string &s, int max);
};

std::string sha1(const std::string &string);
#endif