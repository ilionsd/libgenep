#pragma once

#ifndef _GRAY_CODER_
#define _GRAY_CODER_

#include <vector>

#include "../storing/genetic_code.h"

#include "helper.h"
#include "genetic_coder.h"

namespace genetic {
	namespace coding {

		class gray_coder : public genetic_coder {
		public:

			inline gray_coder(const std::vector<number> &pointsNumber) :
				genetic_coder(pointsNumber)
			{};
			inline gray_coder(const size_t spaceSize, const number pointsNumber) :
				genetic_coder(spaceSize, pointsNumber)
			{};

			virtual bit_code encode(const std::vector<number> &points) const override {
				unsigned char prevRem, nextRem;
				number div;
				bit_code code(code_alloc_size());
				size_t base = 0;
				for (size_t dim = 0; dim < space_size(); ++dim) {
					div = points[dim];
					prevRem = div % 2;
					div /= 2;
					size_t bitIndex;
					for (bitIndex = 0; div != 0 && bitIndex < code_size(dim); ++bitIndex) {
						nextRem = div % 2;
						div /= 2;
						code[base + bitIndex] = prevRem ^ nextRem;
						prevRem = nextRem;
					}
					code[base + bitIndex] = prevRem ^ 0x0;
					base += code_size(dim);
				}
				return code;
			};

			virtual std::vector<number> decode(const bit_code &code) const override {
				std::vector<number> points(space_size());
				size_t maxCodeSize = 0;
				for (size_t dim = 0; dim < space_size(); ++dim)
					if (maxCodeSize < code_size(dim))
						maxCodeSize = code_size(dim);
				std::vector<number> power_list = helper<number>::pow_vector<2>(maxCodeSize);
				size_t base = -1;
				for (size_t dim = 0; dim < space_size(); ++dim) {
					base += code_size(dim);
					number point = 0;
					unsigned char xorSum = 0;
					for (size_t bitIndex = 0; bitIndex < code_size(dim); ++bitIndex) {
						xorSum ^= static_cast<unsigned char>(code[base - bitIndex]);
						point += xorSum * power_list.at(code_size(dim) - 1 - bitIndex);
					}
					points[dim] = point;
				}
				return points;
			};

		private:

		}; //-- class gray_coder<T1, T2> --
	}; //-- namespace coding --
}; //-- namespace genetic --

#endif //-- _GRAY_CODER_ --