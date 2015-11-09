#pragma once

#include <iostream>
#include <ctime>
#include <limits>
#include <vector>
#include <cassert>
#include <string>


//-- genetic codes --
#include "genetic_code\storing\bit_code.h"
#include "genetic_code\storing\wide_code.h"

//-- genetic encoders --
#include "genetic_code\encoding\binary_encoder.h"



//-- tests --
#include "storage_test.h"
#include "encoding_test.h"

int main() {
	std::cout << "Genetic Algoritm Development Programm" << std::endl;


	unsigned int minSize = 1;
	unsigned int maxSize = 10000;
	namespace gt = genetic::test;


	namespace gs = genetic::storing;
	
	gt::storage_test<gs::bit_code<unsigned char>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned int>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned long>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned long long>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned long long>>::known_size(1);

	gt::storage_test<gs::bit_code<unsigned char>>::random_size(1, minSize, maxSize);
	gt::storage_test<gs::bit_code<unsigned int>>::random_size(5368, minSize, maxSize);
	gt::storage_test<gs::bit_code<unsigned long long>>::random_size((unsigned) time (NULL), minSize, maxSize);



	gt::storage_test<gs::wide_code<unsigned char>>::known_size(100);
	gt::storage_test<gs::wide_code<unsigned int>>::known_size(100);
	gt::storage_test<gs::wide_code<unsigned long>>::known_size(100);
	gt::storage_test<gs::wide_code<unsigned long long>>::known_size(100);
	gt::storage_test<gs::wide_code<unsigned long long>>::known_size(1);
	
	gt::storage_test<gs::wide_code<unsigned char>>::random_size(1, minSize, maxSize);
	gt::storage_test<gs::wide_code<unsigned int>>::random_size(5368, minSize, maxSize);
	gt::storage_test<gs::wide_code<unsigned long long>>::random_size((unsigned)time(NULL), minSize, maxSize);


	namespace ge = genetic::encoding;

	std::vector<unsigned char> example(3);
	example[0] = example[1] = example[2] = 16;
	gt::encoding_test<ge::binary_encoder<unsigned char, gs::bit_code<unsigned char>>>::known_size(3, example);

	unsigned dimSize = 10;
	std::vector<unsigned int> vec = gt::encoding_test<ge::binary_encoder<unsigned int, gs::bit_code<unsigned char>>>::dimPointsRandom(5, dimSize);
	gt::encoding_test<ge::binary_encoder<unsigned int, gs::bit_code<unsigned char>>>::known_size(3, vec);


	std::system("pause");
	return 0;
};
