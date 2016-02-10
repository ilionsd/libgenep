#pragma once

#ifndef _GENETIC_CODER_
#define _GENETIC_CODER_

#include <cmath>
#include <vector>
#include <cstdlib>

#include "../../typedefs.h"
#include "coder.h"
#include "../storing/genetic_code.h"



namespace genetic {
	namespace coding {

		using storing::bit_code;

		inline size_t CodeSize(const number pointsNumber) {
			double log2PointsNumber = log2(pointsNumber);
			double ceilPointsNumber = ceil(log2PointsNumber);
			return static_cast<size_t>(ceilPointsNumber);
		}

		class genetic_coder :
			public coder<std::vector<number>, storing::bit_code>
		{	
		public:
			inline genetic_coder(const std::vector<number> &pointsNumber) :
				dim_code_size_(pointsNumber.size()),
				code_alloc_size_()
			{
				for (size_t k = 0; k < space_size(); ++k) {
					dim_code_size_[k] = CodeSize(pointsNumber[k]);
					code_alloc_size_ += dim_code_size_[k];
				}
			};

			inline genetic_coder(const size_t spaceSize, const number pointsNumber) :
				dim_code_size_(spaceSize, CodeSize(pointsNumber)),
				code_alloc_size_(spaceSize * CodeSize(pointsNumber))
			{};

			size_t code_size(const size_t dim) const {
				return dim_code_size_[dim];
			};
			size_t point_number(const size_t dim) const {
				return static_cast<size_t>(0x1) << dim_code_size_[dim];
			};
			size_t space_size() const {
				return dim_code_size_.size();
			};

			//virtual storing::bit_code encode(const std::vector<number> &val) const = 0;
			//virtual std::vector<number> decode(const storing::bit_code &val) const = 0;

		protected:
			size_t code_alloc_size() const {
				return code_alloc_size_;
			};

		private:
			std::vector<size_t> dim_code_size_;
			size_t code_alloc_size_;

		};
	};	//-- namespace coding --
};	//-- namespace genetic --

#endif	//-- _GENETIC_CODER_ --