#pragma once

#include <functional>
#include <map>
#include <vector>

#include "context.h"


namespace genetic {
	namespace algorithm {

		struct context {
			std::vector<double> fitness;
		};

		template<typename _Tcode>
		class genetic_algorithm {
		public:
			using code_t = _Tcode;

			template<typename _Context>
			using initializer_f = std::pair<std::vector<code_t>, _Context>(size_t, _Context&);

			template<typename _Context>
			using selector_f = std::vector<size_t>(std::vector<code_t>&, _Context&);

			


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


			std::vector<code_t> code_;
		};
	};
};
