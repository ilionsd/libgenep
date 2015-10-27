#pragma once

#ifndef _REF_
#define _REF_

#include <type_traits>
#include <iostream>

namespace genetic {
	namespace utility {

		template<typename T>
		class reference_property
		{
		public:
			using value_type = T;
			virtual value_type get() const = 0;
			virtual void set(const value_type &value) = 0;

			friend std::ostream& operator << (std::ostream& os, const reference_property<value_type> &referenceProperty) {
				return os << referenceProperty.get();
			};
		};


		template <typename _Tproperty>
		class const_reference : 
			public _Tproperty
		{
		public:
			using property_t = _Tproperty;
			using ref_t = typename property_t::value_type;
			
			using property_t::property_t;

			using property_t::get;
			inline operator ref_t() const {
				return get();
			};

			inline bool operator==(const const_reference<property_t> &other) const {
				return this->get() == other.get();
			};
			inline bool operator!=(const const_reference<property_t> &other) const {
				return this->get() != other.get();
			};
			inline bool operator==(const property_t &other) const {
				return this->get() == other.get();
			};
			inline bool operator!=(const property_t &other) const {
				return this->get() != other.get();
			};
			inline bool operator==(const ref_t &other) const {
				return this->get() == other;
			};
			inline bool operator!=(const ref_t &other) const {
				return this->get() != other;
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
			inline reference<property_t> &operator=(const property_t &other) {
				set(other.get());
				return *this;
			};
			inline reference<property_t> &operator=(const ref_t &other) {
				set(other);
				return *this;
			};
		};
	};
};

#endif
