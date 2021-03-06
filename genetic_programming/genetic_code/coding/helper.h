#pragma once

#include <vector>

namespace genetic {
	namespace coding {
		template<typename T>
		struct helper {
			template<int base>
			static std::vector<T> pow_vector(const unsigned int &power) {
				std::vector<T> powers(power + 1);
				T mul = 1;
				for (int k = 0; k <= power; ++k) {
					powers.at(k) = mul;
					mul *= base;
				}
				return powers;
			};
		};
	};
};