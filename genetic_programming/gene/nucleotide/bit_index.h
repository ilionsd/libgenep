#pragma once

#include <climits>
#include <type_traits>
#include <stdexcept>
#include <sstream>

namespace genetic {
	namespace primitive {
		template<typename T>
		class bit_index {
			static_assert(std::is_integral<T>::value, 
				"Template should be specialized by unsigned integer type");
			static_assert(std::is_unsigned<T>::value, 
				"Template should be specialized by unsigned integer type");
			static_assert(!std::is_same<T, bool>::value, 
				"Template should be specialized by unsigned integer type");

		public:
			typedef size_t bitsize_t;

			static const bitsize_t bit_size;

			bit_index() :
				intex(0)
			{};

			bit_index(const bitsize_t &) {
				if (value < bit_size)
					index = value;
				else {
					std::ostringstream error_message;
					error_message << "value should be less than " << std::to_string(bit_size) << ", given " << std::to_string(value) << ".";
					throw std::out_of_range(error_message.str());
				}
			};

			operator bitsize_t() {
				return index;
			};

		private:
			bitsize_t index;
		};

		template<typename T>
		bit_index<T>::bitsize_t static const bit_index<T>::bit_size = CHAR_BIT * sizeof(T);

	}; //-- namespace primitive --
}; //-- namespace genetic --