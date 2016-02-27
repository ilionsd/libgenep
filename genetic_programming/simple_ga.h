#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <random>

#include "genetic_code\storing\genetic_code.h"
#include "genetic_algorithm\space.h"


namespace genetic {

		class simple {
		public:
			struct params {
				algotithm::space space;



				//-- algorithm params --
				size_t initialPopulationSize;
				size_t maxPopulationSize;

				std::function<double(std::vector<double>)> fitnessFunction;

			};

			static simple<code_t> init(params params) {
				simple ga(params);
				
				for (int k = 0; k < params.initialPopulationSize; ++k) {
					ga.individuals[k] = new code_t();
				}

			};

		protected:
			simple(params params) :
				individuals(params.maxPopulationSize), params(params)
			{};

			std::vector<double> gen_individual(space_params spaceParams, unsigned seed) {
				std::mt19937_64 gen(seed);
				std::uniform_int_distribution<> dist();

				std::vector<double> individual(size);
				for (size_t k = 0; k < individual.size(); ++k)
					individual[k] = dist
				return individual;
			}

			template<typename T1, typename T2>
			void do_ga(const storing::genetic_code<T1, T2> &initialPopulation) {

			}

		private:


			params params;

			std::vector<code_ptr> individuals;

		};	//-- class simple_ga --

};	//-- namespace genetic --