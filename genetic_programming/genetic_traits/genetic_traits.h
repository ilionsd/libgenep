#pragma once

#include <climits>
#include <type_traits>

namespace genetic {
	template<typename T>
	struct is_base_integer {
		typedef const T type;
		static const bool value = std::is_integral<type>::value && !std::is_same<type, bool>::value;
	};

	template<typename T>
	struct is_container {
		typedef const T type;
		static const bool value = is_base_integer<type>::value && std::is_unsigned<T>::value;
	};

	template<typename T>
	struct container {
		static_assert(is_container<T>::value, 
			"Template should be specialized by unsigned integer type");

		typedef size_t bitsize_t;
		static const bitsize_t bit_size = CHAR_BIT * sizeof(T);
	};

};