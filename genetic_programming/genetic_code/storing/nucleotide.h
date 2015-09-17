#pragma once

#ifndef _NUCLEOTIDE_
#define _NUCLEOTIDE_

#include <type_traits>

namespace genetic {
	namespace primitive {
			/// <summary>
			/// Represent nucleotides possibly values: 0 or 1
			/// </summary>
			template<typename _Tsource>
			class nucleotide {
				static_assert(std::is_integral<_Tsource>::value,
					"Template should be specialized by integral type");
				
			public:
				typedef typename _Tsource source_t;

				static const nucleotide<source_t> zero;
				static const nucleotide<source_t> one;

				nucleotide(const bool &type) {
					mType = (type) ? scOne : scZero;
				};
				nucleotide() :
					nucleotide(false)
				{};
				nucleotide(const source_t &type) :
					nucleotide(static_cast<bool>(type))
				{};

				~nucleotide() = default;
				
				operator bool() const {
					return static_cast<bool>(mType);
				};
				operator source_t() const {
					return static_cast<source_t>(mType);
				};
				
				inline nucleotide<source_t> &operator=(const nucleotide<source_t> &other) {
					mType = other.mType;
					return (*this);
				};
				inline nucleotide<source_t> operator!() const {
					return ((*this)) ? nucleotide<source_t>::zero : nucleotide<source_t>::one;
				}

				template<typename _otherTsource>
				inline bool operator==(const nucleotide<_otherTsource> &other) const {
					return mType == other.mType;
				};
				template<typename _otherTsource>
				inline bool operator!=(const nucleotide<_otherTsource> &other) const {
					return mType != other.mType;
				};

			private:
				static const char scZero = 0, scOne = 1;
				char mType;
			};

			template<typename T>
			const nucleotide<T> nucleotide<T>::zero(nucleotide<T>::scZero);

			template<typename T>
			const nucleotide<T> nucleotide<T>::one(nucleotide<T>::scOne);


	}; //-- namespace primitive --
}; //-- namespace genetic --

#endif //-- _NUCLEOTIDE_ --