#pragma once

#include "gene.h"

namespace genetic {
	template<gene_size _VSize>
	const gene_size gene<_VSize>::s_size = _VSize;

	template<gene_size _VSize>
	gene_size gene<_VSize>::size() {
		return gene<_VSize>::s_size;
	};
};