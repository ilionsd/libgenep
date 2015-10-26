#pragma once

#include <vector>

#include "helper.h"
#include "genetic_encoder.h"
#include "binary_encoder.h"

namespace genetic {
	namespace encoding {
		template<typename _Tsource, typename _Tstorage>
		class gray_encoder : public genetic_encoder<_Tsource, _Tstorage> {
		public:
			using base_t = genetic_encoder<_Tsource, _Tstorage>;
			using source_t = typename base_t::source_t;
			using storage_t = typename base_t::storage_t;

			using container_t = typename storage_t::container_t;
			using codesize_t = typename base_t::codesize_t;


			inline gray_encoder(const codesize_t &codeSize, const int &spaceSize) :
				genetic_encoder(codeSize, spaceSize)
			{};
			inline gray_encoder(const source_t &points_number, const int &spaceSize) :
				genetic_encoder(points_number, spaceSize)
			{};

			virtual storage_t encode(const std::vector<source_t> &points) const override {
				unsigned char prevRem, nextRem;
				source_t div;
				storage_t code(code_size() * space_size());
				codesize_t nucleotideIndex = 0;
				for (int spaceSizeIndex = 0; spaceSizeIndex < space_size(); ++spaceSizeIndex) {
					div = points.at(spaceSizeIndex);
					prevRem = 0;
					while (div != 0) {
						nextRem = div % 2;
						div /= 2;
						code.at(nucleotideIndex++) = static_cast<container_t>(prevRem ^ nextRem);
						prevRem = nextRem;
					}
					code.at(nucleotideIndex++) = static_cast<container_t>(prevRem ^ 0);
				}
				return code;
			};
			virtual std::vector<source_t> decode(const storage_t &code) const override {
				std::vector<source_t> points(space_size());
				std::vector<source_t> power_list = helper<source_t>::pow_vector<2>(code_size());
				for (int spaceSizeIndex = 0; spaceSizeIndex < space_size(); ++spaceSizeIndex) {
					codesize_t lastIndex = code_size() * (spaceSizeIndex + 1) - 1;
					source_t point = 0;
					char xorSum = 0;
					for (ptrdiff_t shiftNucleotideIndex = 0; shiftNucleotideIndex < code_size(); ++shiftNucleotideIndex) {
						xorSum ^= code.at(lastIndex - shiftNucleotideIndex);
						point += xorSum * power_list.at(code_size() - shiftNucleotideIndex);
					}
					points.at(spaceSizeIndex) = point;
				}
				return points;
			};

		private:

		};
	};
};