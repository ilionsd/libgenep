#pragma once

#include <vector>
#include <memory>
#include <type_traits>


namespace genetic {
	//typedef __int8 nucleotide;

	template<typename T>
	class genetic_code {
		static_assert(std::is_integral<T>::value);
		static_assert(!std::is_same<T, bool>::value);
	public:
		typedef typename std::make_unsigned<T>::type target_type;

		genetic_code(const target_type& size) :
			m_size(size)
		{};

		virtual nucleotide at(const point_number &point_number) = 0;

	protected:
		target_type m_size;

	private:

	};
};