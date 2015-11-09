#pragma once

#include <typeinfo>
#include <vector>
#include <limits>

namespace genetic {
	namespace test {

		using std::cout;
		using std::endl;

		template<typename _Tencoder>
		class encoding_test
		{
		public:
			using encoder_t = _Tencoder;
			using source_t = typename encoder_t::source_t;
			using storage_t = typename encoder_t::storage_t;

			static std::vector<source_t> dimPointsRandom(const unsigned int seed, const unsigned int dimSize) {
				srand(seed);
				source_t max = std::numeric_limits<source_t>::max();
				source_t min = 10;
				std::vector<source_t> vec(dimSize);
				for (auto it = vec.begin(); it != vec.end(); ++it)
					(*it) = (double)rand() / (RAND_MAX + 1) * (max - min) + min;
				return vec;
			};

			static bool known_size(const unsigned int seed, const std::vector<source_t> dimPointsNumber)
			{
				cout << endl << "Encoder KNOWN SIZE test on " << typeid(encoder_t).name() << " with " << typeid(storage_t).name() << endl
					<< "This programm will create vector of specifed size with unsigned integer values and convert it into genetic code. After that genetic code will be decoded into the same vector and compare values of them" << endl;
				size_t spaceSize = dimPointsNumber.size();
				cout << "Space size = " << spaceSize << endl;
				std::vector<source_t> srcVec(spaceSize);
				srand(seed);
				for (size_t k = 0; k < spaceSize; k++) {
					srcVec[k] = (double)rand() / (RAND_MAX + 1) * dimPointsNumber[k];
				}

				encoder_t encoder(dimPointsNumber);
				storage_t code = encoder.encode(srcVec);
				std::vector<source_t> dstVec = encoder.decode(code);

				int errorCount = 0;
				for (int k = 0; k < spaceSize; ++k) {
					if (srcVec[k] != dstVec[k]) {
						cout << "srcVec[" << k << "] = " << srcVec[k] << " not equals dstVec[" << k << "] = " << dstVec[k] << endl;
						errorCount++;
					}
				}
				cout << "test end, errors - " << errorCount << endl;
				return !errorCount;
			};
		}; //-- class encoding_test<T> --

	}; //-- namespace test --
}; //-- namespace genetic --