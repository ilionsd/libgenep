#pragma once

#include "nucleotide_type.h"

namespace genetic {
	namespace primitive {

		template<typename T>
		const char nucleotide_type<T>::sc_zero_ = 0;

		template<typename T>
		const char nucleotide_type<T>::sc_one_ = 1;

		template<typename T>
		nucleotide_type<T> static nucleotide_type<T>::cast(const T &value) {
			return nucleotide_type<T>(value);
		};

		template<typename T>
		nucleotide_type<T> &nucleotide_type<T>::operator=(const nucleotide_type<T> &other) {
			type_ = other.type_;
			return *this;
		};

		template<typename T>
		nucleotide_type<T> nucleotide_type<T>::operator!() const {
			return ((*this) == nucleotide_type<T>::zero) ? nucleotide_type<T>::one : nucleotide_type<T>::zero;
		};

		template<typename T>
		bool nucleotide_type<T>::operator==(const nucleotide_type<T> &other) const {
			return type_ == other.type_;
		};

		template<typename T>
		bool nucleotide_type<T>::operator!=(const nucleotide_type<T> &other)  const {
			return type_ == other.type_;
		};

		template<typename T>
		const nucleotide_type<T> nucleotide_type<T>::zero(nucleotide_type<T>::sc_zero_);

		template<typename T>
		const nucleotide_type<T> nucleotide_type<T>::one(nucleotide_type<T>::sc_one_);
	};
};