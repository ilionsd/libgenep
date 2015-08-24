#pragma once

#include <vector>

#include "genetic.h"
#include "gene.h"

namespace genetic {
	
	template<gene_size _VSize>
	class wide_gene : public gene<_VSize> {

	public:
		wide_gene(const point_number &) :
			code(_VSize)
		{
			

		};

		virtual point_number decode() const override;
		virtual nucleotide &at(const point_number &point_number) const override;

	protected:
		std::vector<nucleotide> m_code;

	private:
		static void to_genome()
	};
};