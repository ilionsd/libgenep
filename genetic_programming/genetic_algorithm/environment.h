#pragma once

#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#include <map>
#include <vector>

namespace genetic {
	namespace algorithm {
		template<typename _Tcoder>
		class environment {
		public:
			using coder_t = _Tcoder;
			using code_t = coder_t::storage_t;

		

		private:
			//-- Initialization --
			//	initial population count

			//-- Selection --
			//	population

			//-- Crossover --

			//-- Mutation --

			//-- Reduction --

			//-- Terminate condition --


			unsigned int initialPopulationSize;

			

			std::vector<code_t> population;
		};
	}; //-- namespace algorithm --
}; //-- namespace genetic --

#endif //-- _ENVIRONMENT_ --
