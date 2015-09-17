#pragma once

#ifndef _REF_
#define _REF_

namespace genetic {
	namespace utility {

		template <typename _Tref>
		class const_reference {
		public:
			typedef typename _Tref ref_t;

			const_reference() = default;
			~const_reference() = default;

			inline operator ref_t() const {
				return get();
			};

			inline bool operator==(const abstract_reference<ref_t> &other) const {
				return this->get() == other.get();
			};
			inline bool operator!=(const abstract_reference<ref_t> &other) const {
				return this->get() != other.get();
			};

		protected:
			inline virtual ref_t get() const = 0;
		};


		template<typename _Tref>
		class reference : 
			public const_reference<_Tref> {
		public:

			reference() = default;
			~reference() = default;

			inline reference<ref_t> &operator=(const abstract_reference<ref_t> &other) {
				set(other.get());
				return *this;
			};

		protected:
			inline virtual void set(const ref_t& value) = 0;
		};
	};
};

#endif
