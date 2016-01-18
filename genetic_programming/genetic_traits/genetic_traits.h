#pragma once

#include <climits>
#include <type_traits>
#include <utility>

namespace genetic {
	template<typename T>
	struct is_base_integer {
		typedef typename T value_type;
		static const bool value = std::is_integral<value_type>::value && !std::is_same<value_type, bool>::value;
	};

	template<typename T>
	struct is_container {
		typedef typename T value_type;
		static const bool value = is_base_integer<value_type>::value && std::is_unsigned<value_type>::value;
	};

	template<typename T>
	struct container {
		static_assert(is_container<T>::value, 
			"Template should be specialized by unsigned integer type");

		typedef typename T value_type;

		typedef size_t bitsize_t;
		static const bitsize_t bit_size = CHAR_BIT * sizeof(T);
	};

	//namespace detail
	//{
	//	template <template <typename > class C>
	//	struct is_base_of_any_helper
	//	{
	//		template <typename T>
	//		std::true_type operator()(const C<T>*) const;

	//		std::false_type operator() (...) const;

	//	};

	//}

	//template <template <typename > class C, typename T>
	//using is_base_of_any = typename decltype(detail::is_base_of_any_helper<C>{}(std::declval<const T*>()));


	


};