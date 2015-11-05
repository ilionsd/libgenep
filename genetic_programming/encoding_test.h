#pragma once

#include <typeinfo>
#include <vector>

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

			static bool known_size(const std::vector<source_t> dimPointsNumber)
			{
				cout << endl << "Encoder KNOWN SIZE test on " << typeid(encoder_t).name() << " with " << typeid(storage_t).name() << endl
					<< "This programm will create vector of specifed size with unsigned integer values and convert it into genetic code. After that genetic code will be decoded into the same vector and compare values of them" << endl;
				cout << "Space size = " << dimPointsNumber.size() << endl;
				cout << "Max point number = " << dimPointsNumber << endl;
				std::vector<source_t> vec(dimPointsNumber.size());
				srand((unsigned)time(NULL));
				for (auto it = vec.begin(); it != vec.end(); it++) {
					(*it) = (double)rand() / (RAND_MAX + 1) * maxPointNumber;
				}

				encoder_t encoder(spaceSize);
				storage_t code = encoder.encode(vec);
				return true;
			};
		}; //-- class encoding_test<T> --

	}; //-- namespace test --
}; //-- namespace genetic --