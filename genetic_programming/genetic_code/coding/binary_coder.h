#pragma once

#ifndef _BINARY_CODER_
#define _BINARY_CODER_

#include <cmath>
#include <stack>

#include "helper.h"
#include "genetic_coder.h"

#include "../storing/genetic_code.h"

namespace genetic {
	namespace coding {
		class binary_coder : 
			public genetic_coder
		{
		public:
			inline binary_coder(const std::vector<number> &pointsNumber) :
				genetic_coder(pointsNumber)
			{};
			inline binary_coder(const size_t spaceSize, const number pointsNumber) :
				genetic_coder(spaceSize, pointsNumber)
			{};

			virtual bit_code encode(const std::vector<number> &points) const override {
				number rem;
				number div;
				bit_code code(code_alloc_size());
				size_t base = 0;
				for (size_t dim = 0; dim < space_size(); ++dim) {
					div = points[dim];
					for (size_t bitIndex = 0; div != 0 && bitIndex < code_size(dim); ++bitIndex) {
						rem = div % 2;
						div /= 2;
						code[base + bitIndex] = rem;
					}
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
				size_t nucleotideIndex = 0;
				size_t base = 0;
				number point;
				for (size_t dim = 0; dim < space_size(); ++dim) {
					point = 0;
					for (size_t bitIndex = 0; bitIndex < code_size(dim); ++bitIndex) {
						point += static_cast<number>(code[base + bitIndex]) * power_list[bitIndex];
					}
					base += code_size(dim);
					points[dim] = point;
				}
				return points;
			};
		};
	}; //-- namespace coding --
}; //-- namespace genetic --

#endif //-- _BINARY_CODER_ --