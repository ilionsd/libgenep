#pragma once 

#include <type_traits>

#include "nucleotide_type.h"

namespace genetic {
	namespace primitive {
		/// <summary>
		/// Abstract prototype for nucleotide representation
		/// </summary>
		/// <typeparam name="T">Container type</param>
		template<typename _Tcontainer>
		class nucleotide {
			static_assert(std::is_integral<_Tcontainer>::value,
				"Template should be specialized by unsigned integer type");
			static_assert(std::is_unsigned<_Tcontainer>::value,
				"Template should be specialized by unsigned integer type");
			static_assert(!std::is_same<_Tcontainer, bool>::value,
				"Template should be specialized by unsigned integer type");

		public:
			typedef typename _Tcontainer container_t;
			typedef typename nucleotide_type<container_t> nucleotide_type_t;

			nucleotide() = default;
			~nucleotide() = default;

			inline nucleotide<container_t> &operator=(const container_t &other);

			inline bool operator==(const container_t &other) const;
			inline bool operator!=(const container_t &other) const;

			virtual nucleotide_type_t get() const = 0;
			virtual void set(const nucleotide_type_t &type) = 0;
			
		};
	}; //-- namespace primitive --
}; //-- namespace genetic --