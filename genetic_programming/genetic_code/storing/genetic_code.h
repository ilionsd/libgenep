#pragma once

#ifndef _GENETIC_CODE_
#define _GENETIC_CODE_

#include <vector>
#include <memory>

#include "../../genetic_traits/genetic_traits.h"
#include "nucleotide.h"

namespace genetic {

	namespace primitive {
		/// <summary>
		/// Abstract prototype for nucleotide representation
		/// </summary>
		/// <typeparam name="T">Container type</param>
		template<typename _Tcontainer>
		class nucleotide_ref {
			static_assert(genetic::is_container<_Tcontainer>::value,
				"Template should be specialized by unsigned integer type");

		public:
			typedef typename _Tcontainer container_t;
			typedef typename nucleotide<container_t> nucleotide_t;

			nucleotide_ref() = default;
			~nucleotide_ref() = default;

			virtual nucleotide_t get() const = 0;
			virtual void set(const nucleotide_t &type) = 0;

			template<typename _Tcontainer_other>
			inline nucleotide_ref<container_t> &operator=(const nucleotide<_Tcontainer_other> &other) {
				set(other);
				return (*this);
			};
			template<typename _Tcontainer_other>
			inline nucleotide_ref<container_t> &operator=(const nucleotide_ref<_Tcontainer_other> &other) {
				set(other.get());
				return (*this);
			};

			inline bool operator==(const container_t &other) const {
				return get() == nucleotide_type_t(other);
			};
			inline bool operator!=(const container_t &other) const {
				return get() != nucleotide_type_t(other);
			};

		};
	}; //-- namespace privitive --


	template<typename _Tcontainer>
	class genetic_code {
		static_assert(is_container<_Tcontainer>::value, 
			"Template should be specialized by unsigned integer type");

	public:
		typedef typename _Tcontainer container_t;
		typedef typename size_t codesize_t;
		typedef typename primitive::nucleotide<container_t> nucleotide_t;

		genetic_code(const codesize_t &codeSize) :
			codeSize_(codeSize)
		{};

		virtual std::unique_ptr<nucleotide_t> at(const codesize_t &index) = 0;
		virtual std::unique_ptr<nucleotide_t> at(const codesize_t &index) const = 0;

		inline codesize_t codesize() {
			return codeSize_;
		};

	protected:
		

	private:
		codesize_t codeSize_;
	};
}; //-- namespace genetic --

#endif //-- _GENETIC_CODE_ --