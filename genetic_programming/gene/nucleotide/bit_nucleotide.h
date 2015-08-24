#pragma once

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
		template<typename T>
		class bit_nucleotide : public nucleotide<T> {
			friend class genetic_code<T>;
		public:
			virtual nucleotide_type<T> get() const = 0;
			virtual void set(const nucleotide_type<T> &type) = 0;

		private:
			bit_nucleotide(const target_type &nucleotide, const bit_index<T> &index) :
				p_value(&nucleotide), m_index(index)
			{}; //-- redundant check --
				// *p_value = nucleotide_type<T>::cast(*p_value);

			target_type *p_value;
			bit_index<T> m_index;
		};
	};
};