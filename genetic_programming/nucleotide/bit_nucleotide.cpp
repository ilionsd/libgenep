#pragma once

#include "bit_nucleotide.h"

namespace genetic {
	namespace primitive {
		template<typename T>
		nucleotide_type<T> bit_nucleotide<T>::get() const {
			T mask = 1 << m_index;
			T bit_value = (*p_value) & mask;
			nucleotide_type<T> ntype = bit_value >> m_index;
			return ntype;
		};

		template<typename T>
		void bit_nucleotide<T>::set(const nucleotide_type<T> &type) {
			T mask = ~(!type << m_index);
			(*p_value) &= mask;
		};
	};
};