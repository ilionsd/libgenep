#pragma once

#include <vector>

#include "helper.h"
#include "genetic_coder.h"

namespace genetic {
	namespace encoding {
		template<typename _Tsource, typename _Tstorage>
		class gray_coder : public genetic_coder<_Tsource, _Tstorage> {
		public:
			using base_t = genetic_coder<_Tsource, _Tstorage>;
			using source_t = typename base_t::source_t;
			using storage_t = typename base_t::storage_t;

			using container_t = typename storage_t::container_t;
			using codesize_t = typename base_t::codesize_t;


			inline gray_coder(const std::vector<source_t> &pointNumbers) :
				genetic_coder(pointNumbers)
			{};
			inline gray_coder(const unsigned int &spaceSize, const source_t &pointsNumber) :
				genetic_coder(spaceSize, pointsNumber)
			{};

			virtual storage_t encode(const std::vector<source_t> &points) const override {
				unsigned char prevRem, nextRem;
				source_t div;
				storage_t code(code_alloc_size());
				codesize_t base = 0;
				for (size_t dim = 0; dim < space_size(); ++dim) {
					div = points[dim];
					prevRem = div % 2;
					div /= 2;
					codesize_t bitIndex;
					for (bitIndex = 0; div != 0 && bitIndex < code_size(dim); ++bitIndex) {
						nextRem = div % 2;
						div /= 2;
						code[base + bitIndex] = static_cast<container_t>(prevRem ^ nextRem);
						prevRem = nextRem;
					}
					code[base + bitIndex] = static_cast<container_t>(prevRem ^ 0x0);
					base += code_size(dim);
					
				}
				return code;
			};
			virtual std::vector<source_t> decode(const storage_t &code) const override {
				std::vector<source_t> points(space_size());
				codesize_t maxCodeSize = 0;
				for (size_t dim = 0; dim < space_size(); ++dim)
					if (maxCodeSize < code_size(dim))
						maxCodeSize = code_size(dim);
				std::vector<source_t> power_list = helper<source_t>::pow_vector<2>(maxCodeSize);
				codesize_t base = -1;
				for (size_t dim = 0; dim < space_size(); ++dim) {
					base += code_size(dim);
					source_t point = 0;
					unsigned char xorSum = 0;
					typename storage_t::nucleotide_t::source_t sourceVal;
					for (codesize_t bitIndex = 0; bitIndex < code_size(dim); ++bitIndex) {
						typename storage_t::nucleotide_t nucleotideVal = code[base - bitIndex];
						sourceVal = nucleotideVal;
						xorSum ^= static_cast<unsigned char>(sourceVal);
						point += xorSum * power_list.at(code_size(dim) - 1 - bitIndex);
					}
					points[dim] = point;
				}
				return points;
			};

		private:

		};
	};
};