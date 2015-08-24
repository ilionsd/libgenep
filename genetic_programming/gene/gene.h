#pragma once 

#include <vector>
#include <memory>


namespace genetic {
		

	template<gene_size _VSize>
		class gene {

		public:
			virtual point_number decode() const = 0;
			gene_size size();
			

			static std::vector<nucleotide> to_wide_bits()

		protected:

		private:
			static const gene_size s_size;

		};
}; //-- namespace genetic --