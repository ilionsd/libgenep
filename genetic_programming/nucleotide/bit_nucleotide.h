#pragma once

#include <limits>

#include "nucleotide.h"
#include "nucleotide_type.h"
#include "bit_index.h"
#include "../genetic_code/genetic_code.h"

namespace genetic {
	namespace primitive {
		/// <summary>
		/// Wrapper class for bit compressed genetic code
		/// </summary>
		/// <typeparam name="T">Container type</param>
		/// <param name="*p_value">Pointer to container variable</param>
		/// <param name="m_index">Index of nucleotide bit in container variable</param>
		/// <seealso cref="bit_index{T}"/>
		template<typename _Tcontainer>
		class bit_nucleotide : public nucleotide<_Tcontainer> {
			friend class genetic_code<_Tcontainer>;
		public:
			typedef typename nucleotide<_Tcontainer> base_t;
			typedef typename bit_index<typename base_t::container_t> bit_index_t;

			virtual typename base_t::nucleotide_type_t get() const {
				typename base_t::container_t mask = 1 << mIndex_;
				typename base_t::container_t bitValue = (*pValue_) & mask;
				typename base_t::nucleotide_type_t ntype = bitValue >> mIndex_;
				return ntype;
			};
			virtual void set(const typename base_t::nucleotide_type_t &type) {
				typename base_t::container_t mask = ~(!type << mIndex_);
				(*pValue_) &= mask;
			};

		private:
			bit_nucleotide(const typename base_t::container_t &nucleotide, const typename bit_index_t &index) :
				pValue_(&nucleotide), mIndex_(index)
			{}; //-- redundant check --
				// *p_value = nucleotide_type<T>::cast(*p_value);

			typename base_t::container_t *pValue_;
			typename bit_index_t mIndex_;
		};
	};
};