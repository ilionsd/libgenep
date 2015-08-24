#pragma once

#include "wide_nucleotide.h"

namespace genetic {
	namespace primitive {
		template<typename T>
		nucleotide_type<T> wide_nucleotide<T>::get() const {
			return nucleotide_type<T>::cast(*p_value);
		};

		template<typename T>
		void wide_nucleotide<T>::set(const nucleotide_type<T> &type) {
			*p_value = type;
		};

	}; //-- namespace primitive --
}; //-- namespace genetic --