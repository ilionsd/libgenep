#pragma once

#include "nucleotide.h"

namespace genetic {
	namespace primitive {
		template<typename T>
		nucleotide<typename nucleotide<T>::container_t> 
			&nucleotide<T>::operator= (const typename nucleotide<T>::container_t &other) 
		{
			set(other);
			return *this;
		};

		template<typename T>
		bool nucleotide<T>::operator== (const typename nucleotide<T>::container_t &other) const {
			return get() == other;
		};

		template<typename T>
		bool nucleotide<T>::operator!= (const typename nucleotide<T>::container_t &other) const {
			return get() != other;
		};
	}; //-- namespace primitive --
}; //-- namespace genetic --