#pragma once

#include <cmath>

#include "../genetic_code.h"
#include "../../nucleotide/bit_nucleotide.h"

namespace genetic {
	namespace storing {
		template<typename _Tcontainer>
		class bit_code : genetic_code < _Tcontainer > {
		public:
			typedef typename genetic_code<_Tcontainer> base_t;
			typedef typename primitive::bit_nucleotide<base_t::container_t> nucleotide_t;

			const static size_t container_size(sizeof(typename bit_code<_Tcontainer>::base_t::container_t));

			bit_code(const base_t::codesize_t& codeSize) :
				genetic_code(codeSize), code_(bit_code<_Tcontainer>::element_size(codeSize))
			{};

			virtual std::unique_ptr< base_t::nucleotide_t > at(const base_t::codesize_t &index) override {

			};

		private:
			inline static size_t element_size(const base_t::codesize_t& codeSize) {
				return static_cast<size_t>(
					std::ceil(static_cast<double>(codeSize) / bit_code<_Tcontainer>::container_size));
			};
		};
	};
};