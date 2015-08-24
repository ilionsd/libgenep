#pragma once

#include "nucleotide.h"

namespace genetic {
	namespace primitive {
		template<typename T>
		nucleotide<T> &nucleotide<T>::operator= (const typename nucleotide<T>::target_type &other) {
			set(other);
			return *this;
		};

		template<typename T>
		bool nucleotide<T>::operator== (const typename nucleotide<T>::target_type &other) const {
			return get() == other;
		};

		template<typename T>
		bool nucleotide<T>::operator!= (const typename nucleotide<T>::target_type &other) const {
			return get() != other;
		};
	}; //-- namespace primitive --
}; //-- namespace genetic --