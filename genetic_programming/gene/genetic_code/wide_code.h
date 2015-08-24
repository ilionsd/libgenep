#pragma once 

#include <memory>
#include <vector>

#include "genetic.h"
#include "genetic_code.h"

namespace genetic {
	template<typename T>
	class wide_code : public genetic_code<T> {
	public:
		wide_code(const target_type &value) {

		};

		virtual nucleotide at(const point_number &point_number) override;

	protected:
		std::vector<nucleotide> m_code;
	};
};