#pragma once

#include <vector>
#include <memory>
#include <type_traits>

#include "../nucleotide/nucleotide.h"


namespace genetic {

	template<typename _Tcontainer>
	class genetic_code {
		static_assert(std::is_integral<_Tcontainer>::value, 
			"Template should be specialized by unsigned integer type");
		static_assert(std::is_unsigned<_Tcontainer>::value,
			"Template should be specialized by unsigned integer type");
		static_assert(!std::is_same<_Tcontainer, bool>::value,
			"Template should be specialized by unsigned integer type. Not bool");

	public:
		typedef typename _Tcontainer container_t;
		typedef typename size_t codesize_t;
		typedef typename primitive::nucleotide<container_t> nucleotide_t;

		genetic_code(const codesize_t &codeSize) :
			codeSize_(codeSize)
		{};

		virtual std::unique_ptr<nucleotide_t> at(const codesize_t &index) = 0;

		inline codesize_t codesize() {
			return codeSize_;
		};

	protected:
		

	private:
		codesize_t codeSize_;
	};
};