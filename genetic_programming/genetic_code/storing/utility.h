#pragma once

#ifndef _REF_
#define _REF_

#include <type_traits>

namespace genetic {
	namespace utility {

		template<typename T>
		class reference_property
		{
		public:
			using value_type = T;
			virtual value_type get() const = 0;
			virtual void set(const value_type &value) = 0;
		};

		template<typename T>
		class equalable
		{
		public:
			using value_type = T;
			using value_type::get;
			
			inline bool operator==(const value_type &other) const {
				return this->get() == other.get();
			};
			inline bool operator!=(const value_type &other) const {
				return this->get() != other.get();
			};
		};


		template <typename _Tproperty>
		class const_reference : 
			public _Tproperty,
			public equalable<const_reference<_Tproperty>>
		{
		public:
			using property_t = _Tproperty;
			using ref_t = typename property_t::value_type;
			
			using property_t::property_t;

			using property_t::get;
			inline operator ref_t() const {
				return get();
			};

		};


		template<typename _Tproperty>
		class reference : 
			public const_reference<_Tproperty>
		{
		public:
			using const_reference<_Tproperty>::const_reference;

			using property_t::set;

			inline reference<property_t> &operator=(const const_reference<property_t> &other) {
				set(other.get());
				return *this;
			};
		};
	};
};

#endif
