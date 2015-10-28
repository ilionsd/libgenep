#pragma once

#include <iostream>
#include <ctime>
#include <limits>
#include <vector>
#include <cassert>
#include <string>


//-- genetic alg --
#include "genetic_code\storing\bit_code.h"
#include "genetic_code\storing\wide_code.h"


//-- tests --
#include "storage_test.h"

int main() {
	std::cout << "Genetic Algoritm Development Programm" << std::endl;

	namespace gs = genetic::storing;
	namespace gt = genetic::test;

	gt::storage_test<gs::bit_code<unsigned char>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned int>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned long>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned long long>>::known_size(100);
	gt::storage_test<gs::bit_code<unsigned long long>>::known_size(1);


	unsigned int minSize = 1;
	unsigned int maxSize = 10000;
	gt::storage_test<gs::bit_code<unsigned char>>::random_size(1, minSize, maxSize);
	gt::storage_test<gs::bit_code<unsigned int>>::random_size(5368, minSize, maxSize);
	gt::storage_test<gs::bit_code<unsigned long long>>::random_size((unsigned) time (NULL), minSize, maxSize);

	gt::storage_test<gs::wide_code<unsigned char>>::known_size(100);

	std::system("pause");
	return 0;
};
