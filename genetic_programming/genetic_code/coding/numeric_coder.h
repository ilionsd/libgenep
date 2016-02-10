#pragma once

#ifndef _GENETIC_CODING_NUMERIC_CODE_
#define _GENETIC_CODING_NUMERIC_CODE_

#include <cmath>
#include <vector>
#include <stdexcept>

#include "../../typedefs.h"
#include "coder.h"
#include "../storing/genetic_code.h"
#include "../../genetic_algorithm/space.h"

namespace genetic {
	namespace coding {

		class numeric_coder :
			public virtual coder<storing::numeric_code, std::vector<number>>
		{
		public:
			inline numeric_coder(std::vector<algotithm::dimension> &space) :
				space_(space)
			{};

			inline size_t space_size() const {
				return space_.size();
			};

			virtual std::vector<number> encode(const storing::numeric_code &val) const override {
#pragma message "Conversion from doubles to ints. Possible loss of data"
				check_size_and_throw_error(val);
				size_t spaceSize = space_size();
				std::vector<number> result(spaceSize);
				for (size_t dim = 0; dim < spaceSize; ++dim) {
					double t = (val[dim] - space_[dim].left_bound()) / space_[dim].splitting().interval_size();
					result[dim] = static_cast<number>(std::round(t));
				}
				return result;
			};

			virtual storing::numeric_code decode(const std::vector<number> &val) const override {
				check_size_and_throw_error(val);
				size_t spaceSize = space_size();
				storing::numeric_code result(spaceSize);
				for (size_t dim = 0; dim < spaceSize; ++dim) {
					result[dim] = val[dim] * space_[dim].splitting().interval_size() + space_[dim].left_bound();
				}
				return result;
			};

		private:
			template<typename T>
			inline void check_size_and_throw_error(const T &val) const {
				if (space_size() == val.size());
					throw std::invalid_argument("Argument size does not equals to space size");
			};
			std::vector<algotithm::dimension> space_;

		};
	};	//-- namespace coding --
};	//-- namespace genetic --

#endif