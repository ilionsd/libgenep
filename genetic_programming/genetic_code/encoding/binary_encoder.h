#pragma once

#include <cmath>
#include <stack>

#include "helper.h"
#include "genetic_encoder.h"

namespace genetic {
	namespace encoding {
		template<typename _Tsource, typename _Tstorage>
		class binary_encoder : public genetic_encoder<_Tsource, _Tstorage> {
		public:
			inline binary_encoder(const codesize_t &codeSize, const int &spaceSize) :
				genetic_encoder(codeSize, spaceSize)
			{};
			inline binary_encoder(const source_t &points_number, const int &spaceSize) :
				genetic_encoder(points_number, spaceSize)
			{};

			virtual storage_t encode(const std::vector<source_t> &points) const override {
				typename container_t rem;
				typename source_t div;
				typename storage_t code(code_size() * space_size());
				typename codesize_t nucleotideIndex = 0;
				
				for (size_t k = 0; k < space_size(); ++k) {
					div = points.at(k);
					while (div != 0) {
						rem = div % 2;
						div /= 2;
						code.at(nucleotideIndex++) = rem;
					}
				}
				return code;
			};
			virtual std::vector<source_t> decode(const storage_t &code) const override {
				std::vector<source_t> points(space_size());
				std::vector<source_t> power_list = helper<typename source_t>::pow_vector<2>(code_size());
				typename codesize_t nucleotideIndex = 0;
				for (int spaceSizeIndex = 0; spaceSizeIndex < space_size(); ++spaceSizeIndex) {
					typename source_t point = 0;
					for (size_t codeSizeIndex = 0; codeSizeIndex < code_size(); ++codeSizeIndex) {
						point += code.at(nucleotideIndex). * power_list.at(codeSizeIndex);
					}
					points.at(spaceSizeIndex) = point;
				}
				return points;
			};
		};
	}; //-- namespace encoding --
}; //-- namespace genetic --