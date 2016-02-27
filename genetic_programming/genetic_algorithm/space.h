#pragma once

#ifndef _GENETIC_ALGORITHM_SPACE_
#define _GENETIC_ALGORITHM_SPACE_

#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <ctime>

#include "../typedefs.h"

namespace genetic {
	namespace algotithm {

		class dimension {
		public:

			class splitting {
			public:
				inline splitting(const double dimensionSize, const number pointsNumber) :
					points_number_(pointsNumber)
				{
					interval_size_ = dimensionSize / (pointsNumber - 1);
				};

				inline splitting(const splitting &other) :
					points_number_(other.points_number()),
					interval_size_(other.interval_size())
				{};

				inline number points_number() const {
					return points_number_;
				};
				inline number interval_number() const {
					return points_number() - 1;
				};
				inline double interval_size() const {
					return interval_size_;
				};

				inline splitting& operator= (const splitting &other) {
					points_number_ = other.points_number();
					interval_size_ = other.interval_size();
					return (*this);
				};

			private:
				number points_number_;
				double interval_size_;

			};	//-- class splitting --

			using splitting_t = splitting;

			dimension() :
				dimension(0, 0, 0)
			{};

			dimension(const double leftBound, const double rightBound, const number pointsNumber) :
				left_bound_(std::min(leftBound, rightBound)),
				right_bound_(std::max(leftBound, rightBound)),
				splitting_(right_bound() - left_bound(), pointsNumber)
			{};

			dimension(const dimension &other) :
				left_bound_(other.left_bound()),
				right_bound_(other.right_bound()),
				splitting_(other.splitting())
			{};

			inline double left_bound() const {
				return left_bound_;
			};
			inline double right_bound() const {
				return right_bound_;
			};

			inline const splitting_t& splitting() const {
				return splitting_;
			};

			inline double dimension_size() const {
				return right_bound() - left_bound();
			};

			inline dimension& operator=(const dimension &other) {
				left_bound_ = other.left_bound();
				right_bound_ = other.right_bound();
				splitting_ = other.splitting();
				return (*this);
			};

			void bounds(const double leftBound, const double rightBound) {
				left_bound_ = std::min(leftBound, rightBound);
				right_bound_ = std::max(leftBound, rightBound);
			};

		private:
			double left_bound_;
			double right_bound_;
			splitting_t splitting_;

		};	//-- class dimension --

		

		class space {
		public:
			space(const size_t size) :
				dimentions_(size)
			{};

			space(const std::vector<dimension> &dimensions) :
				dimentions_(dimensions)
			{};

			inline operator std::vector<dimension>() const {
				return dimentions_;
			};

			inline size_t size() const {
				return dimentions_.size();
			};

			inline dimension operator[] (const size_t index) const {
				return dimentions_[index];
			};
			inline dimension& operator[] (const size_t index) {
				return dimentions_[index];
			};
			inline dimension at (const size_t index) const {
				return dimentions_.at(index);
			};
			inline dimension& at (const size_t index) {
				return dimentions_.at(index);
			};

		private:
			std::vector<dimension> dimentions_;

		};	//-- class space --


		template<typename T>
		class generator {
		public:
			generator(const space &space) :
				generator(space, time( NULL ))
			{};
			generator(const space &space, const unsigned seed) :
				distributions_(space.size()),
				engine_(seed)
			{
				for (size_t k = 0; k < space.size(); ++k)
					distributions_[k] = std::uniform_real_distribution(space[k].left_bound(), space[k].right_bound());
			};

			std::vector<double> point() const {
				size_t size = distributions_.size();
				std::vector<double> point(size);
				for (size_t k = 0; k < size; ++k)
					point[k] = distributions_[k](engine_);
				return point;
			};

		private:
			std::vector<std::uniform_real_distribution> distributions_;
			T engine_;

		};	//-- class generator --


	};	//-- namespace algorithm --
};	//-- namespace genetic --

#endif