#pragma once

#include <iostream>
#include <ctime>
#include <limits>
#include <vector>
#include <cassert>
#include <string>


//-- genetic alg --
#include "genetic_code\storing\bit_code.h"
#include "genetic_code\storing\genetic_code.h"


//-- tests --
#include "storage_test.h"


//-- logger --


int main() {
	std::cout << "Genetic Algoritm Development Programm" << std::endl;
	srand((unsigned)time(NULL));

	namespace gs = genetic::storing;

	genetic::test::storage_test<gs::bit_code<unsigned char>>::known_size_test(100);

	return 0;
};
