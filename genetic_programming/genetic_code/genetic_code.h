#pragma once

#include <vector>
#include <memory>
#include <type_traits>

#include "../nucleotide/nucleotide.h"


namespace genetic {

	template<typename T>
	class genetic_code {
		static_assert(std::is_integral<T>::value, 
			"Template should be specialized by unsigned integer type");
		static_assert(std::is_unsigned<T>::value, 
			"Template should be specialized by unsigned integer type");
		static_assert(!std::is_same<T, bool>::value, 
			"Template should be specialized by unsigned integer type. Not bool");

	public:
		typedef typename T target_type;

		genetic_code(const target_type& size) :
			m_size(size)
		{};

		virtual std::unique_ptr< primitive::nucleotide<T> > at(const point_number &point_number) = 0;

	protected:
		target_type m_size;

	private:

	};
};