#pragma once

#include <cmath>
#include <vector>
#include <utility>

#include "../../genetic_traits/genetic_traits.h"
#include "genetic_code.h"
#include "nucleotide.h"
#include "bit_index.h" 
#include "utility.h"

namespace genetic {
	namespace storing {

		///<summary>
		///Class for bit property
		///</summary>
		template<typename _Tcontainer>
		class bit_property :
			public utility::reference_property< nucleotide<_Tcontainer> >
		{
		public:
			using container_t = _Tcontainer;
			using nucleotide_t = nucleotide<container_t>;

			using bitindex_t = primitive::bit_index<container_t>;

			bit_property(const container_t &container, const bitindex_t &index) :
				mContainerPtr(&container),
				mIndex(index)
			{};

			virtual nucleotide_t get() const override {
				container_t bitValue = (*mContainerPtr) & access_mask(mIndex);
				return static_cast<nucleotide_t>(trim(bitValue, mIndex));
			};

			virtual void set(const nucleotide_t &value) override {
				(*mContainerPtr) &= mutate_mask(value, mIndex);
			};

		protected:
			inline static container_t access_mask(const bitindex_t &index) {
				return static_cast<container_t>(1) << static_cast<typename bitindex_t::bitsize_t>(index);
			};

			inline static container_t mutate_mask(const nucleotide_t &value, const bitindex_t &index) {
				return ~(static_cast<container_t>(!value) << static_cast<typename bitindex_t::bitsize_t>(index));
			};

			inline static container_t right_shift(const container_t &value, const bitindex_t &index) {
				return value >> static_cast<typename bitindex_t::bitsize_t>(index);
			};

		private:
			container_t *mContainerPtr;
			bitindex_t mIndex;
		};



		template<typename _Tcontainer>
		class bit_code : 
			genetic_code < _Tcontainer, bit_code<_Tcontainer>, bit_property<_Tcontainer> > 
		{
			static_assert(is_container<_Tcontainer>::value,
				"Template should be specialized by unsigned integer type");

		public:
			using container_t = _Tcontainer;
			using reference_property = bit_property<container_t>;
			using base_t = genetic_code< container_t, bit_code< container_t >,  reference_property >;
			
			using codesize_t = typename base_t::codesize_t;
			using nucleotide_t = typename reference_property::nucleotide_t;

			using nucleotide_cref = typename base_t::nucleotide_cref;
			using nucleotide_ref = typename base_t::nucleotide_ref;

			
			bit_code(const codesize_t& codeSize) :
				genetic_code(codeSize), 
				mCode(bit_code<container_t>::element_size(codeSize))
			{};

			virtual nucleotide_cref at(const codesize_t &index) const override
			{
				size_t elementIndex = index / container<container_t>::bit_size;
				bitindex_t bitIndex = index % container<container_t>::bit_size;
				nucleotide_cref cRef(mCode[elementIndex], bitIndex);
				return cRef;
			};

			virtual nucleotide_ref at(const codesize_t &index) override 
			{
				size_t elementIndex = index / container<container_t>::bit_size;
				bitindex_t bitIndex = index % container<container_t>::bit_size;
				nucleotide_ref ref(mCode[elementIndex], bitIndex);
				return ref;
			};

			

		private:
			inline static size_t element_size(const codesize_t& codeSize) 
			{
				return static_cast<size_t>(
					std::ceil(static_cast<double>(codeSize) / bit_code<container_t>::container_size));
			};

			std::vector<container_t> mCode;
		};

		
	};
};