#pragma once 

#include <memory>
#include <vector>
#include <utility>

#include "nucleotide.h"
#include "genetic_code.h"
#include "utility.h"

namespace genetic {
	namespace storing {
		///<summary>
		///Class for wide property
		///</summary>
		template<typename _Tcontainer>
		class wide_property :
			public utility::reference_property< nucleotide<_Tcontainer> >
		{
		public:
			using container_t = _Tcontainer;
			using nucleotide_t = nucleotide<container_t>;

			/*
			Keyword explicit is nesessary because with operator= integer can be cast to wide_property instead of nucleotide<T>
			*/
			explicit wide_property(const container_t &container) :
				mContainerPtr(const_cast<container_t*>(&container))
			{};

			virtual nucleotide_t get() const override {
				return static_cast<nucleotide_t>(*mContainerPtr);
			};

			virtual void set(const nucleotide_t &value) override {
				(*mContainerPtr) = static_cast<container_t>(value);
			};

		private:
			container_t *mContainerPtr;

		}; //-- class wide_property<T> --



		template<typename _Tcontainer>
		class wide_code : 
			public genetic_code < _Tcontainer, wide_property<_Tcontainer> >
		{
		public:
			using container_t = _Tcontainer;
			using reference_property = wide_property<container_t>;
			using base_t = genetic_code< container_t, reference_property >;

			using codesize_t = typename base_t::codesize_t;
			using nucleotide_t = typename reference_property::nucleotide_t;

			using nucleotide_cref = typename base_t::nucleotide_cref;
			using nucleotide_ref = typename base_t::nucleotide_ref;


			wide_code(const codesize_t &codeSize) :
				genetic_code(codeSize), 
				mCode(codeSize)
			{};

			template<typename T1, typename T2>
			wide_code(const genetic_code<T1, T2> &other) :
				genetic_code(other),
				mCode(bit_code<container_t>::element_size(other.size()))
			{
				for (codesize_t k = 0; k < size(); ++k)
					operator[](k) = other[k];
			};

			nucleotide_cref operator[] (const codesize_t &index) const override {
				nucleotide_cref cRef(mCode[index]);
				return cRef;
			};
			nucleotide_ref operator[] (const codesize_t &index) override {
				nucleotide_ref ref(mCode[index]);
				return ref;
			};

		protected:
			inline virtual void resize(const codesize_t &codeSize) {
				base_t::resize(codeSize);
				mCode.resize(codeSize);
			};
			
		private:
			std::vector<container_t> mCode;

		}; //-- class wide_code<T> --
	}; //-- namespace storing --
}; //-- namespace genetic --