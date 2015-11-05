#pragma once

#include <cmath>
#include <stack>

#include "helper.h"
#include "genetic_encoder.h"

#include "../storing/genetic_code.h"

namespace genetic {
	namespace encoding {
		template<typename _Tsource, typename _Tstorage>
		class binary_encoder : 
			public genetic_encoder<_Tsource, _Tstorage> 
		{
		public:
			using base_t = genetic_encoder<_Tsource, _Tstorage>;
			using source_t = typename base_t::source_t;
			using storage_t = typename base_t::storage_t;

			using container_t = typename storage_t::container_t;
			using codesize_t = typename base_t::codesize_t;

			inline binary_encoder(const codesize_t &codeSize, const int &spaceSize) :
				genetic_encoder(codeSize, spaceSize)
			{};
			inline binary_encoder(const source_t &points_number, const int &spaceSize) :
				genetic_encoder(points_number, spaceSize)
			{};

			virtual storage_t encode(const std::vector<source_t> &points) const override {
				container_t rem;
				source_t div;
				storage_t code(code_alloc_size());
				codesize_t offset = 0;
				for (size_t dim = 0; dim < space_size(); ++dim) {
					div = points[k];
					for (codesize_t bitIndex = 0; div != 0 && bitIndex < code_size(dim); ++bitIndex) {
						rem = div % 2;
						div /= 2;
						code[offset + bitIndex] = rem;
					}
					offset += code_size(dim);
				}
				return code;
			};
			virtual std::vector<source_t> decode(const storage_t &code) const override {
				std::vector<source_t> points(space_size());
				std::vector<source_t> power_list = helper<source_t>::pow_vector<2>(code_size());
				codesize_t nucleotideIndex = 0;
				codesize_t offset = 0;
				source_t point;
				typename storage_t::nucleotide_t::source_t sourceVal;
				for (int dim = 0; dim < space_size(); ++dim) {
					point = 0;
					for (size_t bitIndex = 0; bitIndex < code_size(dim); ++bitIndex) {
						sourceVal = code[offset + bitIndex];
						point += static_cast<source_t>(sourceVal) * power_list[bitIndex];
					}
					offset += code_size(dim);
					points[dim] = point;
				}
				return points;
			};
		};
	}; //-- namespace encoding --
}; //-- namespace genetic --