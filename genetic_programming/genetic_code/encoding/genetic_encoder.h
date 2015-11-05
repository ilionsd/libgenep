#pragma once

#include <cmath>
#include <vector>
#include <cstdlib>
#include <type_traits>

#include "../storing/genetic_code.h"
#include "../../genetic_traits/genetic_traits.h"

namespace genetic {
	namespace encoding {
		template<typename _Tsource, typename _Tstorage>
		class genetic_encoder 
		{
			/*static_assert(is_base_of_template_t<storing::genetic_code, _Tstorage>::value,
				"Storage should be derived from genetic_code");*/
			
		public:
			using storage_t = _Tstorage;
			using source_t = _Tsource;
			using container_t = typename storage_t::container_t;
			using codesize_t = typename storage_t::codesize_t;

			inline genetic_encoder(const std::vector<source_t> pointNumbers) :
				mDimCodeSize(pointNumbers.size())
			{
				for (codesize_t k = 0; k < space_size(); ++k)
					mDimCodeSize[k] = get_code_size(pointNumbers[k]);
			};

			inline genetic_encoder(const unsigned int &spaceSize, const source_t &pointsNumber) :
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

			virtual storage_t encode(const std::vector<source_t> &point) const = 0;
			virtual std::vector<source_t> decode(const storage_t &code) const = 0;

		protected:
			explicit genetic_encoder(const std::vector<codesize_t> dimCodeSizes) :
				mDimCodeSize(dimCodeSizes),
				codeAllocSize()
			{
				for (auto it = mDimCodeSize.begin(); it != mDimCodeSize.end(); ++it)
					codeAllocSize += *it;
			};

			explicit genetic_encoder(const int &spaceSize, const codesize_t &codeSize) :
				mDimCodeSize(spaceSize, codeSize)
			{
				codeAllocSize = spaceSize * codeSize;
			};

			codesize_t code_alloc_size() {
				return codeAllocSize;
			};

		private:
			inline static codesize_t get_code_size(const source_t &points_number) {
				return static_cast<codesize_t>(ceil(log(points_number)));
			};

			std::vector<codesize_t> mDimCodeSize;
			codesize_t codeAllocSize;
		};
	}; //-- namespace encoding --
}; //-- namespace genetic --