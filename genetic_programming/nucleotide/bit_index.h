#pragma once

#include <climits>
#include <type_traits>
#include <stdexcept>
#include <sstream>

namespace genetic {
	namespace primitive {
		/// <summary>
		/// Class for represent indices of bits in integer type variable
		/// </summary>
		/// <typeparam name="T">Integer type variable</typeparam>
		/// <param name="bit_size">Number of bits in &lt;T&gt;</param>
		/// <param name="index">Index of bit</param>
		/// <exception cref="std::out_of_range">Thrown then </exception>
		template<typename T>
		class bit_index {
			static_assert(std::is_integral<T>::value, 
				"Template should be specialized by unsigned integer type");
			static_assert(std::is_unsigned<T>::value, 
				"Template should be specialized by unsigned integer type");
			static_assert(!std::is_same<T, bool>::value, 
				"Template should be specialized by unsigned integer type");

		public:
			typedef size_t bitsize_t;

			static const bitsize_t bit_size;

			bit_index() :
				m_index(0)
			{};

			bit_index(const bitsize_t &index) {
				if (index < bit_size && index >= 0)
					m_index = index;
				else {
					std::ostringstream error_message;
					error_message << "value should be in [0; " << std::to_string(bit_size) << "], given " << std::to_string(index);
					throw std::out_of_range(error_message.str());
				}
			};

			operator bitsize_t() {
				return m_index;
			};

		private:
			bitsize_t m_index;
		};

		template<typename T>
		const typename bit_index<T>::bitsize_t bit_index<T>::bit_size = CHAR_BIT * sizeof(T);

	}; //-- namespace primitive --
}; //-- namespace genetic --