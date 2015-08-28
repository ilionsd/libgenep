#pragma once 

#include <type_traits>

#include "nucleotide_type.h"

namespace genetic {
	namespace primitive {
		/// <summary>
		/// Abstract prototype for nucleotide representation
		/// </summary>
		/// <typeparam name="T">Container type</param>
		template<typename T>
		class nucleotide {
			static_assert(std::is_integral<T>::value, 
				"Template should be specialized by unsigned integer type");
			static_assert(std::is_unsigned<T>::value, 
				"Template should be specialized by unsigned integer type");
			static_assert(!std::is_same<T, bool>::value, 
				"Template should be specialized by unsigned integer type");

		public:
			typedef typename T target_type;

			nucleotide() = default;
			~nucleotide() = default;

			inline nucleotide<T> &operator=(const target_type &other);

			inline bool operator==(const target_type &other) const;
			inline bool operator!=(const target_type &other) const;

			virtual nucleotide_type<T> get() const = 0;
			virtual void set(const nucleotide_type<T> &type) = 0;
			
		};
	}; //-- namespace primitive --
}; //-- namespace genetic --