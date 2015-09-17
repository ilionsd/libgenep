#pragma once

#include <climits>
#include <type_traits>

namespace genetic {
	template<typename T>
	struct is_base_integer {
		typedef const T value_type;
		static const bool value = std::is_integral<value_type>::value && !std::is_same<value_type, bool>::value;
	};

	template<typename T>
	struct is_container {
		typedef const T value_type;
		static const bool value = is_base_integer<value_type>::value && std::is_unsigned<value_type>::value;
	};

	template<typename T>
	struct container {
		static_assert(is_container<T>::value, 
			"Template should be specialized by unsigned integer type");

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


	//-- http://coliru.stacked-crooked.com/a/eaeac2b9008a97d9 begin--

	template <template <typename...> class Base, typename Derived>
	struct is_base_of_template
	{
		using U = typename std::remove_cv<Derived>::type;

		template <typename... Args>
		static std::true_type test(Base<Args...>*);

		static std::false_type test(void*);

		using type = decltype(test(std::declval<U*>()));
	};

	template <template <typename...> class Base, typename Derived>
	using is_base_of_template_t = typename is_base_of_template<Base, Derived>::type;

	//-- http://coliru.stacked-crooked.com/a/eaeac2b9008a97d9 end --
};