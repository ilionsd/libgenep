#pragma once

#include <iostream>
#include <ctime>
#include <limits>
#include <vector>
#include <cassert>


//-- genetic alg --
#include "genetic_code\storing\wide_code.h"
#include "genetic_code\encoding\binary_encoder.h"

int main() {
	std::cout << "Genetic Algoritm Development Programm" << std::endl;
	srand((unsigned)time(NULL));
	return 0;
};

template<typename T>
void storageTest() {
	std::cout << "Code storage " + typeid(T).name() + "test begin" << std::endl;
	int codeSize = (double)rand() / (RAND_MAX + 1) * std::numeric_limits<int>::max();
	T code(codeSize);
	std::cout << sizeof(code) << std::endl;
	std::vector<char> vec(codeSize);
	for (std::vector<char>::iterator it = vec.begin(); it != vec.end(); ++it)
		(*it) = (rand() > RAND_MAX / 2) ? 1 : 0;

	for (int k = 0; k < codeSize; ++k) {
		code.at(k) = vec.at(k);
	}

	for (int k = 0; k < codeSize; ++k) {
		assert(code.at(k) == vec.at(k));
	}

	std::cout << "Code storage " + typeid(T).name() + "test passed" << std::endl;
};

void binaryEncodingTest() {
	std::cout << "Binary Encoding test begin" << std::endl;
	namespace ge = genetic::encoding;
	namespace gs = genetic::storing;
	int spaceSize = 6;
	ge::binary_encoder<int, gs::wide_code<unsigned char>> wideBinaryEncoder(sizeof(int) * 8, spaceSize);
	std::cout << "Binary Encoding test passed" << std::endl;
};