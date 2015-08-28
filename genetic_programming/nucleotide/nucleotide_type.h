#pragma once

#include <type_traits>

namespace genetic {
	namespace primitive {
			/// <summary>
			/// Represent nucleotides possibly values: 0 or 1
			/// </summary>
			template<typename T>
			class nucleotide_type {
				static_assert(std::is_integral<T>::value,
					"Template should be specialized by unsigned integer type");
				static_assert(std::is_unsigned<T>::value,
					"Template should be specialized by unsigned integer type");
				static_assert(!std::is_same<T, bool>::value,
					"Template should be specialized by unsigned integer type");
			public:
				inline static nucleotide_type<T> cast(const T &value);

				static const nucleotide_type<T> zero;
				static const nucleotide_type<T> one;

				explicit operator T() {
					return static_cast<T>(type_);
				};

				inline nucleotide_type<T> &operator=(const nucleotide_type<T> &other);

				inline nucleotide_type<T> operator!() const;

				inline bool operator==(const nucleotide_type<T> &other) const;
				inline bool operator!=(const nucleotide_type<T> &other) const;

				

			private:
				nucleotide_type() :
					type_(c_zero_)
				{};
				nucleotide_type(const T &type) {
					type_ = (type == c_zero_) ? c_zero_ : c_one_;
				};

				static const char sc_zero_, sc_one_;

				char type_;
			};
	}; //-- namespace primitive --
}; //-- namespace genetic --