#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>


namespace genetic {
	namespace test {
		template <typename _Tcode>
		class code_test 
		{
		public:
			using code_t = _Tcode;



			static bool known_size(const long long codeSize) {
				std::cout << std::endl << "Storage KNOWN SIZE test on " << typeid(code_t).name() << std::endl
					<< "The program will create vector and genetic code of the same size, fill code with values from vector and after that compare them" << std::endl;

				std::cout << "codeSize = " << codeSize << std::endl;
				code_t code(codeSize);
				std::vector<unsigned char> vec(codeSize);
				for (auto it = vec.begin(); it != vec.end(); ++it)
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
				std::cout << std::endl << "Storage RANDOM SIZE test on " << typeid(code_t).name() << std::endl
					<< "The program will create vector and genetic code of the same size, fill code with values from vector and after that compare them" << std::endl;
				std::cout << "seed = " << seed << std::endl;
				srand(seed);
				int codeSize = (double)rand() / (RAND_MAX + 1) * (maxSize - minSize) + minSize;
				std::cout << "codeSize = " << codeSize << std::endl;
				code_t code(codeSize);
				std::vector<char> vec(codeSize);
				for (auto it = vec.begin(); it != vec.end(); ++it)
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
