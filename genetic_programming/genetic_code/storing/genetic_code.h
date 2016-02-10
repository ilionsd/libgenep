#pragma once

#ifndef _GENETIC_STORING_GENETIC_CODE_
#define _GENETIC_STORING_GENETIC_CODE_

#include <vector>
#include <functional>

#include "../../utility/reference.h"
#include "../../utility/bitset.h"


namespace genetic {
	namespace storing {

		template<typename T> class genetic_code;

		template<typename T>
		using integer_code_t = genetic_code<std::vector<T>>;

		using bit_code = genetic_code<utility::bitset>;
		using integer_code = integer_code_t<unsigned int>;

		using numeric_code = genetic_code<std::vector<double>>;



		template<typename T>
		class genetic_code {
		public:
			using container_t = T;
			using const_reference = container_t::const_reference;
			using reference = container_t::reference;

			inline genetic_code(const size_t size) :
				container_(size)
			{};

			inline size_t size() {
				return container_.size();
			};

			inline void resize(const size_t newSize) {
				container_.resize(newSize);
			};

			inline const_reference operator[] (const size_t index) const {
				return container_[index];
			};

			inline reference operator[] (const size_t index) {
				return container_[index];
			};

			inline const_reference at(const size_t index) const {
				return container_.at(index);
			};

			inline reference at(const size_t index) {
				return container_.at(index);
			};

			template<typename T2>
			genetic_code<T>& operator=(const genetic_code<T2> &other) {
				if (size() != other.size())
					resize(other.size());
				for (int k = 0; k < size(); ++k)
					operator[](k) = other[k];
			};

		private:
			container_t container_;

		};	//-- genetic_code<T> --
	};	//-- namespace storing --
};	//-- namespace genetic --


#endif //-- _GENETIC_STORING_GENETIC_CODE_ --
