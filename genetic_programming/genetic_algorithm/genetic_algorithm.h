#pragma once

#include <functional>
#include <map>
#include <vector>

#include "context.h"


namespace genetic {
	namespace algorithm {
		template<typename _Tcoder>
		class genetic_algorithm {
		public:
			using coder_t = _Tcoder;
			using code_t = coder_t::storage_t;

			using individuals_t = std::vector<code_t>;
			using individuals_ref_t = std::vector<size_t>;

		private:
			context context;

			//-- Initialization --
			//	initial population count
			std::function< individuals_t( size_t ) > initializer;

			//-- Selection --
			//	Fitness function evaluations
			std::function< individuals_ref_t( std::vector<double> ) > selector;

			//-- Crossover --
			std::function< individuals_t( individuals_ref_t ) > crossover;

			//-- Mutation --
			std::function< individuals_t( individuals_ref_t ) > mutator;

			//-- Reduction --
			std::function< void( individuals_t ) > reductor;

			//-- Terminate condition --
			std::function< bool( void ) > terminator;



		};
	};
};
