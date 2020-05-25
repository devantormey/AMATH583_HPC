//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_FNORM_HPP
#define AMATH583_FNORM_HPP

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "norm_utils.hpp"

#include <cassert>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

// Write us
double worker_a(const Vector& x, size_t begin, size_t end) {
	double sum_of_squares = 0.0;

	for (size_t i = begin; i < end; ++i) {
		sum_of_squares += x(i) * x(i);
	}

    return sum_of_squares;
}

// Write us
double partitioned_two_norm_a(const Vector& x, size_t partitions) {
	// Copied from lecture
	unsigned long intervals = 1024 * 1024;
	unsigned long num_blocks = 1;
	// We don't use h for this
	// double h = 1.0 / (double)intervals;

	// from skeleton
	double sum = 0.0;

	// also from lecture
	size_t blocksize = x.num_rows() / partitions;
	std::vector<std::future<double>> partial_sums;
	

	for (size_t i = 0; i < partitions; ++i) {
		
			partial_sums.push_back(std::async(std::launch::async, worker_a, std::cref(x), i * blocksize, (i + 1) * blocksize));
	}

	for (unsigned long k = 0; k < num_blocks; ++k){
		sum += partial_sums[k].get();
	}

  	return std::sqrt(sum);
}

// Write us
double partitioned_two_norm_b(const Vector& x, size_t partitions) {
  // Copied from lecture
	unsigned long intervals = 1024 * 1024;
	unsigned long num_blocks = 1;
	// We don't use h for this
	// double h = 1.0 / (double)intervals;

	// from skeleton
	double sum = 0.0;

	// also from lecture
	size_t blocksize = x.num_rows() / partitions;
	std::vector<std::future<double>> partial_sums;
	

	for (size_t i = 0; i < partitions; ++i) {
			partial_sums.push_back(std::async(std::launch::deferred, worker_a, std::cref(x), i * blocksize, (i + 1) * blocksize));
	}

	for (unsigned long k = 0; k < num_blocks; ++k){
		sum += partial_sums[k].get();
	}

  	return std::sqrt(sum);
}

#endif    // AMATH_583_FNORM_HPP
