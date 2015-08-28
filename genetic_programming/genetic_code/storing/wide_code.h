#pragma once 

#include <memory>
#include <vector>

#include "genetic_code.h"
#include "../nucleotide/wide_nucleotide.h"

namespace genetic {
	template<typename T>
	class wide_code : public genetic_code<T> {
	public:
		wide_code(const target_type &value) {

		};

		virtual std::unique_ptr< primitive::nucleotide<T> > at(const point_number &point_number) override;

	protected:
		std::vector<nucleotide> m_code;
	};
};