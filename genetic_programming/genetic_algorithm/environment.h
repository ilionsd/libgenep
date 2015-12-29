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

			using individuals_t = std::vector<code_t>;
			using individuals_ref_t = std::vector<size_t>;

			using fitness = double;
			using fitnesses = std::vector<fitness>;

			static environment initialization() {
				return environment();
			};

			environment& selection() {
				return *this;
			};

			environment& crossover() {
				return *this;
			};

			environment& mutation() {
				return *this;
			};

			environment& reduction() {
				return *this;
			};




		

		private:
			//-- Initialization --
			//	initial population size

			//-- Selection --
			//	population

			//-- Crossover --

			//-- Mutation --

			//-- Reduction --

			//-- Terminate condition --


			size_t initialPopulationSize;

			
			std::vector<double> fitness;
			std::vector<code_t> population;
		}; //-- class environment --
	}; //-- namespace algorithm --
}; //-- namespace genetic --

#endif //-- _ENVIRONMENT_ --
