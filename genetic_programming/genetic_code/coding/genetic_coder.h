#pragma once

#ifndef _GENETIC_CODER_
#define _GENETIC_CODER_

#include <cmath>
#include <vector>
#include <cstdlib>
#include <type_traits>

#include "../storing/genetic_code.h"
#include "../../genetic_traits/genetic_traits.h"
#include "coder.h"

namespace genetic {
	namespace coding {
		template<typename _Tsource, typename _Tstorage>
		class genetic_coder : public coder<std::vector<_Tsource>, _Tstorage>
		{
			/*static_assert(is_base_of_template_t<storing::genetic_code, _Tstorage>::value,
				"Storage should be derived from genetic_code");*/
			
		public:
			using storage_t = _Tstorage;
			using source_t = _Tsource;
			using container_t = typename storage_t::container_t;
			using codesize_t = typename storage_t::codesize_t;

			inline genetic_coder(const std::vector<source_t> &pointNumbers) :
				mDimCodeSize(pointNumbers.size()),
				codeAllocSize()
			{
				for (codesize_t k = 0; k < space_size(); ++k) {
					mDimCodeSize[k] = get_code_size(pointNumbers[k]);
					codeAllocSize += mDimCodeSize[k];
				}
			};

			inline genetic_coder(const unsigned int &spaceSize, const source_t &pointsNumber) :
				genetic_encoder(spaceSize, get_code_size(pointsNumber))
			{};


			codesize_t code_size(const size_t index) const {
				return mDimCodeSize[index];
			};
			source_t point_number(const size_t index) const {
				return static_cast<source_t>(0x1) << mDimCodeSize[index];
			};
			unsigned int space_size() const {
				return mDimCodeSize.size();
			};

			virtual storage_t encode(const std::vector<source_t> &point) const override = 0;
			virtual std::vector<source_t> decode(const storage_t &code) const override = 0;

		protected:
			explicit genetic_coder(const std::vector<codesize_t> dimCodeSizes) :
				mDimCodeSize(dimCodeSizes),
				codeAllocSize()
			{
				for (auto it = mDimCodeSize.begin(); it != mDimCodeSize.end(); ++it)
					codeAllocSize += *it;
			};

			explicit genetic_coder(const int &spaceSize, const codesize_t &codeSize) :
				mDimCodeSize(spaceSize, codeSize)
			{
				codeAllocSize = spaceSize * codeSize;
			};

			codesize_t code_alloc_size() const {
				return codeAllocSize;
			};

		private:
			inline static codesize_t get_code_size(const source_t &pointsNumber) {
				double log2PointsNumber = log2(pointsNumber);
				double ceilPointsNumber = ceil(log2PointsNumber);
				return static_cast<codesize_t>(ceilPointsNumber);
			};

			std::vector<codesize_t> mDimCodeSize;
			codesize_t codeAllocSize;
		};
	}; //-- namespace coding --
}; //-- namespace genetic --

#endif //-- _GENETIC_CODER --