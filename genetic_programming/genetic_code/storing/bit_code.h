#pragma once

#include <cmath>
#include <vector>
#include <utility>

#include "../../genetic_traits/genetic_traits.h"
#include "genetic_code.h"
#include "../../nucleotide/bit_nucleotide.h"
#include "../../nucleotide/bit_index.h" 
#include "utility.h"

namespace genetic {
	namespace storing {
		template<typename _Tcontainer>
		class bit_code : genetic_code < bit_code<_Tcontainer> > {
		public:
			using container_t = _Tcontainer;

			using base_t = genetic_code< bit_code< container_t > >;
			
			using codesize_t = base_t::codesize_t;
			using nucleotide_t = base::nucleotide_t;
			using bitindex_t = primitive::bit_index<container_t>;
			
			using nucleotide_cref = base_t::nucleotide_cref;
			using nucleotide_ref = base_t::nucleotide_ref;

			///<summary>
			///Base class for bit accessor and mutator
			///</summary>
			class bit_property
			{
			public:
				bit_property(const container_t &container, const bitindex_t &index) :
					mContainerPtr(&container),
					mIndex(index)
				{};

			protected:
				inline static container_t access_mask(const bitindex_t &index) {
					return static_cast<container_t>(1) << static_cast<typename bitindex_t::bitsize_t>(index);
				};

				inline static container_t mutate_mask(const nucleotide_t &value, const bitindex_t &index) {
					return ~(static_cast<container_t>(!value) << static_cast<typename bitindex_t::bitsize_t>(index);
				};

				inline static container_t right_shift(const container_t &value, const bitintex_t &index) {
					return value >> static_cast<typename bitindex_t::bitsize_t>(index);
				};

				container_t *mContainerPtr;
				bitindex_t mIndex;
			};

			///<summary>
			///Bit accessor class
			///</summary>
			class nucleotide_accessor :
				private bit_property,
				public virtual utility::accessor<nucleotide_t>
			{
			public:
				nucleotide_accessor(const container_t &container, const bitindex_t &index) :
					bit_property(container, index)
				{};

			protected:
				virtual nucleotide_t get() const override {
					container_t bitValue = (*mContainerPtr) & access_mask(mIndex);
					return static_cast<nucleotide_t>(trim(bitValue, mIndex));
				};

			private:
				
			};

			///<summary>
			///Bit mutator class
			///</summary>
			class nucleotide_mutator :
				private bit_property,
				public virtual utility::mutator<nucleotide_t>
			{
			public:
				nucleotide_mutator(const container_t &container, const bitindex_t &index) :
					bit_property(container, index)
				{};

			protected:
				virtual void set(const nucleotide_t &value) override {
					(*mContainerPtr) &= mutate_mask(value, mIndex);
				};

			private:
				
				
			};


			bit_code(const codesize_t& codeSize) :
				genetic_code(codeSize), 
				mCode(bit_code<container_t>::element_size(codeSize))
			{};

			virtual std::unique_ptr<base_t::nucleotide_cref> at(const codesize_t &index) const override
			{
				size_t elementIndex = index / container<container_t>::bit_size;
				bitindex_t bitIndex = index % container<container_t>::bit_size;

				nucleotide_cref nucleotideCRef 

				std::unique_ptr<typename base_t::nucleotide_t> nucleotidePtr(new nucleotide_t(mCode.at(elementIndex), bitIndex));
				return nucleotidePtr;
			};

			virtual std::unique_ptr<base_t::nucleotide_ref> at(const codesize_t &index) override 
			{
				size_t elementIndex = index / container<container_t>::bit_size;
				bitindex_t bitIndex = index % container<container_t>::bit_size;
				nucleotide_t nucleotide
				std::unique_ptr<typename base_t::nucleotide_t> nucleotidePtr(new nucleotide_t(mCode.at(elementIndex), bitIndex));
				return nucleotidePtr;
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