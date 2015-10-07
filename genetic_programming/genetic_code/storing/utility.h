#pragma once

#ifndef _REF_
#define _REF_

#include <type_traits>

namespace genetic {
	namespace utility {
		template<typename T>
		class accessor {
		public:
			typedef typename T value_type;
			virtual value_type get() const = 0;
		};

		template<typename T>
		class mutator {
		public:
			typedef typename T value_type;
			virtual void set(const value_type &value) = 0;
		};


		template <typename _Tref, typename _Taccessor>
		class const_reference :
			protected _Taccessor
		{
			static_assert(std::is_base_of<accessor<_Tref>, _Taccessor>::value,
				"");

			using _Taccessor::get;

		public:
			typedef typename _Tref ref_t;
			typedef typename _Taccessor accessor_t;

			const_reference() = default;
			~const_reference() = default;

			inline operator ref_t() const {
				return get();
			};

			inline bool operator==(const accessor_t &other) const {
				return this->get() == other.get();
			};
			inline bool operator!=(const accessor_t &other) const {
				return this->get() != other.get();
			};
		};


		template<typename _Tref, typename _Taccessor, typename _Tmutator>
		class reference : 
			public const_reference<_Tref, _Taccessor>,
			protected _Tmutator
		{
			static_assert(std::is_base_of<mutator<_Tref>, _Tmutator>::value,
				"");
			using _Tmutator::value_type;
			using _Tmutator::set;

		public:
			typedef typename _Tmutator mutator_t;

			reference() = default;
			~reference() = default;

			inline reference<ref_t, accessor_t, mutator_t> &operator=(const accessor_t &other) {
				set(other.get());
				return *this;
			};
		};
	};
};

#endif
