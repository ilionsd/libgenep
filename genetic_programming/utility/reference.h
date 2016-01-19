#pragma once

#ifndef _GENETIC_UTILITY_REFERENCE_
#define _GENETIC_UTILITY_REFERENCE_

#include <functional>

namespace genetic {
	namespace utility {

		template<typename T>
		using get = std::function<T(void)>;

		template<typename T>
		using set = std::function<void(T)>;

		template<typename T>
		class cref {
		public:
			cref(const std::function<T(void)> &get) :
				get_(get)
			{};

			inline operator T() const {
				return get_();
			};

			bool operator==(const cref<T> &other) const {
				return get_() == other.get_();
			};
			bool operator!=(const cref<T> &other) const {
				return get_() != other.get_();
			};
			bool operator==(const T &other) const {
				return get_() == other;
			};
			bool operator!=(const T &other) const {
				return get_() != other;
			};

		protected:
			get get_;
		};


		template<typename T>
		class ref : public cref<T> {
		public:
			ref(const std::function<T(void)> &get, const std::function<void(T)> &set) :
				cref(get),
				set_(set)
			{};

			ref<T>& operator=(const cref<T> &other) const {
				set_(other.get_());
				return (*this);
			};
			ref<T>& operator=(const T &other) const {
				set_(other);
				return (*this);
			};

		protected:
			set set_;
		};
	};
};

#endif
