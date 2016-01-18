#pragma once

#include <climits>
#include <type_traits>
#include <stdexcept>
#include <sstream>

#include "../../genetic_traits/genetic_traits.h"

namespace genetic {
	namespace primitive {
		/// <summary>
		/// Class for represent indices of bits in integer type variable
		/// </summary>
		/// <typeparam name="T">Integer type variable</typeparam>
		/// <param name="bit_size">Number of bits in &lt;T&gt;</param>
		/// <param name="index">Index of bit</param>
		/// <exception cref="std::out_of_range">Thrown then </exception>
		template<typename _Tcontainer>
		class bit_index {
			static_assert(is_container<_Tcontainer>::value,
				"Template should be specialized by unsigned integer type");

		public:
			bit_index(const size_t index) {
				if (index < container<_Tcontainer>::bit_size && index >= 0)
					index_ = index;
				else {
					std::ostringstream errorMessage;
					errorMessage << "value should be in [0; " << std::to_string(container<_Tcontainer>::bit_size) << "], given " << std::to_string(index);
					throw std::out_of_range(errorMessage.str());
				}
			};

			inline operator size_t() const {
				return index_;
			};

			inline bool operator==(const bit_index<_Tcontainer> &other) const {
				return m_index == other.m_index;
			};
			inline bool operator!=(const bit_index<_Tcontainer> &other) const {
				return m_index != other.m_index;
			};

		private:
			size_t index_;
		};

	}; //-- namespace primitive --
}; //-- namespace genetic --