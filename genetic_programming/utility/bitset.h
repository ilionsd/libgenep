#pragma once

/*
	Dynamic size bitset
*/

#ifndef _GENETIC_UTILITY_BITSET_
#define _GENETIC_UTILITY_BITSET_


#include <algorithm>
#include <stdexcept>
#include <string>

#include "type_traits.h"
#include "reference.h"

namespace genetic {
	namespace utility {

		template<typename T>
		struct enable_if_integral {
			typedef typename std::enable_if<std::is_integral<T>::value, T>::type type;
		};


		class bit {
		public:
			const static bit one;
			const static bit zero;

			template<typename T, typename = enable_if_integral<T>::type>
			bit(T value) :
				value_(convert(value))
			{};

			template<typename T>
			operator enable_if_integral<T>::type() const {
				return static_cast<T>(value_);
			};

			bit& operator=(const bit &other) {
				value_ = other.value_;
				return (*this);
			};
		private:
			template<typename T>
			inline static unsigned __int8 convert(T value) {
				return (value) ? one_ : zero_;
			};
			unsigned __int8 value_;

			const static unsigned __int8 zero_	= 0;
			const static unsigned __int8 one_	= 1;
		};	//-- class bit --

		const bit bit::zero(bit::zero_);
		const bit bit::one(bit::one_);



		template <typename _Tcontainer>
		class bitset_t {
			static_assert(is_container<_Tcontainer>::value, 
				"bitset<T> should be specialized by unsigned integer type");

		public:
			using container_t = _Tcontainer;

			bitset_t(const size_t size) :
				size_(size)
			{
				container_ptr_ = new container_t[memory_size(size)];
			};

			~bitset_t() {
				delete[]container_ptr_;
			};


			class reference {
				friend class bitset_t<container_t>;
			public:
				inline reference& operator=(const bit &bit) {
					bitset_ptr_->set(index_, bit);
					return (*this);
				};
				inline reference& operator=(const reference &bitRef) {
					bitset_ptr_->set(index_, bitRef);
					return (*this);
				};

				inline operator bit() const {
					return bitset_ptr_->get(index_);
				};

			private:
				explicit reference(bitset_t<container_t> &bitset, const size_t index) :
					bitset_ptr_(&bitset),
					index_(index)
				{};

				bitset_t<container_t> *bitset_ptr_;
				size_t index_;
			};



			size_t size() {
				return size_;
			};

			void resize(const size_t newSize) {
				size_t newMemorySize = memory_size(newSize);
				size_t memorySize = memory_size(size());
				container_t *tempPtr = new container_t[memory_size];
				size_t minMemorySize = std::min(memorySize, newMemorySize);
				for (int k = 0; k < minMemorySize; ++k)
					tempPtr[k] = container_ptr_[k];
				container_t* oldContainerPtr = container_ptr_;
				container_ptr_ = tempPtr;
				size_ = newSize;
				delete []oldContainerPtr;
			};

			inline bit operator[] (const size_t index) const {
				return get(index);
			};

			inline ref<bit> operator[] (const size_t index) {
				utility::set<bit> set = [index](bit value) -> void {set(index, value)};
				return ref<bit>(set);
			};

			inline bit at(const size_t index) const {
				if (index >= size())
					throw std::out_of_range(std::to_string(index) + " out of range [0; " + std::to_string(size()) + "]");
				return operator[](index);
			};

			inline ref<bit> at(const size_t index) {
				if (index >= size())
					throw std::out_of_range(std::to_string(index) + " out of range [0; " + std::to_string(size()) + "]");
				return operator[](index);
			};

			template<typename T>
			bitset_t<container_t>& operator=(const bitset_t<T> &other) {
				if (size() != other.size()) {
					size_ = 0;
					delete[]container_ptr_;
					container_ptr_ = new container_t[other.size()];
					size_ = other.size();
				}
				for (int k = 0; k < size(); ++k)
					operator[](other[k]);
				return (*this);
			};


		private:
			static size_t memory_size(size_t elementsCount) {
				double memory_size = static_cast<double>(elementsCount) / container<container_t>::bit_size;
				return static_cast<size_t>(std::ceil(memory_size));
			};

			bit get(const size_t index) const {
				size_t base = index / container<container_t>::bit_size;
				size_t offset = index % container<container_t>::bit_size;
				bit b = (container_ptr_[base] & (0x1 << offset)) >> offset;
				return b;
			};

			void set(const size_t index, const bit &value) {
				size_t base = index / container<container_t>::bit_size;
				size_t offset = index % container<container_t>::bit_size;
				container_t m = static_cast<container_t>(value) << offset;
				container_ptr_[base] = (container_ptr_[base] & ~m) | (-static_cast<container_t>(value) & m);
			};

			container_t *container_ptr_;
			size_t size_;

		};	//-- class bitset_t --


		using bitset = bitset_t<char>;
	};	//-- namespace containers --
};	//-- namespace utility --

#endif
