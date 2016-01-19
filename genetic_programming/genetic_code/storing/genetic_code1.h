#pragma once

#ifndef _GENETIC_STORING_GENETIC_CODE_
#define _GENETIC_STORING_GENETIC_CODE_

#include <functional>
#include <vector>

#include "../../utility/reference.h"
#include "../../utility/bitset.h"


namespace genetic {
	namespace storing {
		template<typename T>
		class genetic_code {
		public:
			using container_t = T;

			template<typename T>
			using cref = utility::cref<T>;

			template<typename T>
			using ref = utility::ref<T>;

			inline genetic_code(const size_t size) :
				container_(size)
			{};

			inline size_t size() {
				return container_.size();
			};

			inline void resize(const size_t newSize) {
				container_.resize(newSize);
			};

			template<typename T2>
			inline cref<T2> operator[] (const size_t index) const {
				utility::get<T2> get = [&container_, index]() -> {static_cast<T2>(container_[index])};
				return cref<T2>(get);
			};

			template<typename T2>
			inline ref<T2> operator[] (const size_t index) {
				utility::get<T2> get = [&container_, index]() -> T2 {static_cast<T2>(container_[index])};
				utility::set<T2> set = [&container_, index](T2 value) -> void {container_[index] = value};
				return ref<T2>(get, set);
			};

			template<typename T2>
			inline cref<T2> at(const size_t index) const {
				utility::get<T2> get = [&container_, index]() -> {static_cast<T2>(container_.at(index))};
				return cref<T2>(get);
			};

			template<typename T2>
			inline ref<T2> at(const size_t index) {
				utility::get<T2> get = [&container_, index]() -> T2 {static_cast<T2>(container_.at(index))};
				utility::set<T2> set = [&container_, index](T2 value) -> void {container_.at(index) = value};
				return ref<T2>(get, set);
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



		using bit_code = genetic_code<utility::bitset>;

		template<typename T>
		using numeric_code = genetic_code<std::vector<T>>;

	};	//-- namespace storing --
};	//-- namespace genetic --


#endif
