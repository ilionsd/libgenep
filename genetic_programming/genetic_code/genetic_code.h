#pragma once

#include <vector>
#include <memory>

#include "../genetic_traits/genetic_traits.h"
#include "../nucleotide/nucleotide.h"


namespace genetic {

	template<typename _Tcontainer>
	class genetic_code {
		static_assert(is_container<_Tcontainer>::value, 
			"Template should be specialized by unsigned integer type");

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