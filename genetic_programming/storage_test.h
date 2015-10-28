#pragma once

#include <cstdlib>

#include "genetic_code\storing\nucleotide.h"

namespace genetic {
	namespace test {
		template <typename _Tstorage>
		class storage_test 
		{
		public:
			using storage_t = _Tstorage;
			static bool known_size(const long long codeSize) {
				std::cout << std::endl << "Storage KNOWN SIZE test on " << typeid(storage_t).name() << std::endl
					<< "The program will create vector and genetic code of the same size, fill code with values from vector and after that compare them" << std::endl;

				std::cout << "codeSize = " << codeSize << std::endl;
				storage_t code(codeSize);
				std::cout << "Stogage size " << sizeof(code) << std::endl;
				std::vector<unsigned char> vec(codeSize);
				for (std::vector<unsigned char>::iterator it = vec.begin(); it != vec.end(); ++it)
					(*it) = (rand() > RAND_MAX / 2) ? 1 : 0;
				
				for (int k = 0; k < codeSize; ++k) {
					code.at(k) = (vec.at(k));
				}
				
				int errorCount = 0;
				for (int k = 0; k < codeSize; k++) {
					if (code.at(k).get() != vec.at(k)) {
						std::cout << "vector.at(" << k << ") = " << (int)vec.at(k) << " not equals code.at(" << k << ") = " << code.at(k) << std::endl;
						errorCount++;
					}
				}
				std::cout << "test end, errors - " << errorCount << std::endl;
				return !errorCount;
			};

			static bool random_size(unsigned int seed, unsigned int minSize, unsigned int maxSize) {
				std::cout << std::endl << "Storage RANDOM SIZE test on " << typeid(storage_t).name() << std::endl
					<< "The program will create vector and genetic code of the same size, fill code with values from vector and after that compare them" << std::endl;
				std::cout << "seed = " << seed << std::endl;
				srand(seed);
				int codeSize = (double)rand() / (RAND_MAX + 1) * (maxSize - minSize) + minSize;
				std::cout << "codeSize = " << codeSize << std::endl;
				storage_t code(codeSize);
				std::cout << "Stogage size " << sizeof(code) << std::endl;
				std::vector<char> vec(codeSize);
				for (std::vector<char>::iterator it = vec.begin(); it != vec.end(); ++it)
					(*it) = (rand() > RAND_MAX / 2) ? 1 : 0;

				for (int k = 0; k < codeSize; ++k) {
					code.at(k) = vec.at(k);
				}

				int errorCount = 0;
				for (int k = 0; k < codeSize; k++) {
					if (code.at(k).get() != vec.at(k)) {
						std::cout << "vector.at(" << k << ") = " << (int)vec.at(k) << " not equals code.at(" << k << ") = " << code.at(k) << std::endl;
						errorCount++;
					}
				}
				std::cout << "test end, errors - " << errorCount << std::endl;
				return !errorCount;
			};
		}; //-- class storage_test<T> --
	}; //-- namespace test --
}; //-- namespace genetic --
