#pragma once

#ifndef _GENETIC_CODE_
#define _GENETIC_CODE_


#include <vector>

#include "utility.h"

namespace genetic {

	namespace storing {
		template<typename _Tcontainer, typename _Treference_property>
		class genetic_code 
		{
			/*static_assert(std::is_base_of<genetic_code<_Tderived_code>, _Tderived_code>::value,
				"");*/
		public:
			using container_t = _Tcontainer;
			using reference_property = _Treference_property;

			using codesize_t = size_t;

			using nucleotide_cref = utility::const_reference<reference_property>;
			using nucleotide_ref = utility::reference<reference_property>;

			explicit genetic_code(const codesize_t &codeSize) :
				mCodeSize(codeSize)
			{};

			virtual nucleotide_cref operator[] (const codesize_t &index) const = 0;
			virtual nucleotide_ref operator[] (const codesize_t &index) = 0;

			inline nucleotide_cref at(const codesize_t &index) const {
				if (index >= size())
					throw std::out_of_range("Invalid index");
				return this->operator[](index);
			};
			inline nucleotide_ref at(const codesize_t &index) {
				if (index >= size())
					throw std::out_of_range("Invalid index");
				return this->operator[](index);
			};

			inline codesize_t size() {
				return mCodeSize;
			};
			
		private:
			codesize_t mCodeSize;
		};
	}; //-- namespace privitive --
}; //-- namespace genetic --

#endif //-- _GENETIC_CODE_ --