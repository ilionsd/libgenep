#pragma once

#include "nucleotide.h"
#include "nucleotide_type.h"
#include "../genetic_code/genetic_code.h"

namespace genetic {
	namespace primitive {
		template<typename T>
		class wide_nucleotide : public nucleotide<T> {
			friend class genetic_code<T>;
		public:
			virtual nucleotide_type<T> get() const override;
			virtual void set(const nucleotide_type<T> &type) override;

		private:
			wide_nucleotide(const target_type &nucleotide) :
				p_value(&nucleotide)
			{
				*p_value = nucleotide_type<T>::cast(*p_value);
			};

			target_type *p_value;
		};
	}; //-- namespace primitive --
}; //-- namespace genetic --