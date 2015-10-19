#pragma once 

#include <memory>
#include <vector>
#include <utility>

#include "genetic_code.h"
#include "utility.h"

namespace genetic {
	namespace storing {
		template<typename _Tcontainer>
		class wide_code : 
			public genetic_code< wide_code< _Tcontainer > > 
		{
		public:
			using container_t = _Tcontainer;

			using base_t = genetic_code< wide_code< container_t > >;

			using codesize_t = base_t::codesize_t;
			using nucleotide_t = base_t::nucleotide_t;

			using nucleotide_cref = base_t::nucleotide_cref;
			using nucleotide_ref = base_t::nucleotide_ref;


			class wide_property;
			using refetence_property = wide_property;

			class wide_property :
				utility::reference_property<nucleotide_t>
			{
			public:
				wide_property(const container_t &container) :
					mContainerPtr(&container)
				{};

				virtual nucleotide_t get() const override {
					return static_cast<nucleotide_t>(*mContainerPtr);
				};
				virtual void set(const nucleotide_t &value) override {
					(*mContainerPtr) = static_cast<container_t>(value);
				};

			private:
				container_t *mContainerPtr;

			};



			wide_code(const codesize_t& codeSize) :
				genetic_code(codeSize), 
				mCode(codeSize)
			{};

			virtual nucleotide_cref at(const codesize_t &index) const override {
				nucleotide_cref cRef(mCode[index]);
				return cRef;
			};
			virtual nucleotide_ref at(const codesize_t &index) override {
				nucleotideRef ref(mCode[index]);
				return ref;
			};
			
		private:
			std::vector<container_t> mCode;
		};
	};
};