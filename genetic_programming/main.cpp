#pragma once

#include <iostream>
#include <ctime>
#include <limits>
#include <vector>
#include <cassert>
#include <string>


//-- genetic alg --
#include "genetic_code\storing\wide_code.h"
#include "genetic_code\storing\bit_code.h"
#include "genetic_code\encoding\binary_encoder.h"
#include "genetic_code\encoding\gray_encoder.h"

template<typename T> void storageTest();

int main() {
	std::cout << "Genetic Algoritm Development Programm" << std::endl;
	srand((unsigned)time(NULL));

	namespace ge = genetic::encoding;
	namespace gs = genetic::storing;

	storageTest<gs::wide_code<unsigned char>>();
	storageTest<gs::wide_code<unsigned int>>();
	storageTest<gs::bit_code<unsigned char>>();
	storageTest<gs::bit_code<unsigned int>>();

	return 0;
};

template<typename T>
void storageTest() {
	std::cout << std::string("Code storage ") + std::string(typeid(T).name()) + std::string(" test begin") << std::endl;
	int codeSize = (double)rand() / (RAND_MAX + 1) * std::numeric_limits<int>::max();
	T code(codeSize);
	std::cout << sizeof(code) << std::endl;
	std::vector<char> vec(codeSize);
	for (std::vector<char>::iterator it = vec.begin(); it != vec.end(); ++it)
		(*it) = (rand() > RAND_MAX / 2) ? 1 : 0;

	for (int k = 0; k < codeSize; ++k) {
		(*code.at(k)) = vec.at(k);
	}

	for (int k = 0; k < codeSize; ++k) {
		assert((*code.at(k)) == vec.at(k));
	}

	std::cout << std::string("Code storage ") + std::string(typeid(T).name()) + std::string(" test passed") << std::endl;
};

void binaryEncodingTest() {
	std::cout << "Binary Encoding test begin" << std::endl;
	namespace ge = genetic::encoding;
	namespace gs = genetic::storing;
	int spaceSize = 6;
	ge::binary_encoder<int, gs::wide_code<unsigned char>> wideBinaryEncoder(sizeof(int) * 8, spaceSize);
	std::cout << "Binary Encoding test passed" << std::endl;
};