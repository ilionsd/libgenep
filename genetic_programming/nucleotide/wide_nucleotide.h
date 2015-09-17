#pragma once

#include "nucleotide.h"
#include "nucleotide_type.h"

namespace genetic {
	namespace primitive {
		/// <summary>
		/// rapper class for widely stored genetic code
		/// </summary>
		/// <typeparam name="T">Container type</param>
		/// <param name="*p_value">Pointer to container variable</param>
		template<typename _Tcontainer>
		class wide_nucleotide : public nucleotide<_Tcontainer> {
		public:
			typedef typename nucleotide<_Tcontainer> base_t;

			wide_nucleotide(typename base_t::container_t &nucleotide)
			{
				p_value = &nucleotide;
				*p_value = base_t::nucleotide_type_t::cast(*p_value);
			};

			inline virtual typename base_t::nucleotide_type_t get() const override {
				return nucleotide_type<_Tcontainer>::cast(*p_value);
			};
			inline virtual void set(const typename base_t::nucleotide_type_t &type) override {
				*p_value = static_cast<typename base_t::container_t>(type);
			};

		private:
			typename base_t::container_t *p_value;
		};
	}; //-- namespace primitive --
}; //-- namespace genetic --