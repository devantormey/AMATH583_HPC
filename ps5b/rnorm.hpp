//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_RNORM_HPP
#define AMATH583_RNORM_HPP

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

// Useful utility function for computing sum_of_squares over a range of a vector
double sum_of_squares(const Vector& x, size_t begin, size_t end) {
  double sum = 0.0;
  for (size_t i = begin; i < end; ++i) {
    sum += x(i) * x(i);
  }
  return sum;
}

// Write me
double recursive_worker_a(const Vector& x, size_t begin, size_t end, size_t level) { 
	if (level == 0) {
	    double sum = 0;
	    sum = sum_of_squares(x,begin,end);
	    // code that computes the sum of squares of x from begin to end into sum
	    return sum;
  	} else {
    return recursive_worker_a(x, begin, begin+(end-begin)/2, level-1)
         + recursive_worker_a(x, begin+(end-begin)/2, end , level-1);
  }
}

// Dispatch to the actual recursive function -- start with 0 and num_rows() as begin and end
double recursive_two_norm_a(const Vector& x, size_t levels) {

  double sum = 0.0;

  // also from lecture
  size_t blocksize = x.num_rows() / levels;

  std::vector<std::future<double>> partial_sums;
  

  for (size_t i = 0; i < levels; ++i) {
      partial_sums.push_back(std::async(std::launch::async, recursive_worker_a, std::cref(x), i * blocksize, (i + 1) * blocksize,i));
  }

  for (unsigned long k = 0; k < levels; ++k){
    sum += partial_sums[k].get();
  }
  return std::sqrt(sum);

}

// Write me
double recursive_worker_b(const Vector& x, size_t begin, size_t end, size_t level) {	
	if (level == 0) {
	    double sum = 0;
	    sum = sum_of_squares(x,begin,end);
	    // code that computes the sum of squares of x from begin to end into sum
	    return sum;
  	} else {
    return recursive_worker_a(x, begin, begin+(end-begin)/2, level-1)
         + recursive_worker_a(x, begin+(end-begin)/2, end , level-1);
  }
}

// Dispatch to the actual recursive function -- start with 0 and num_rows() as begin and end
double recursive_two_norm_b(const Vector& x, size_t levels) {
  
  double sum = 0.0;

  // also from lecture
  size_t blocksize = x.num_rows() / levels;

  std::vector<std::future<double>> partial_sums;
  

  for (size_t i = 0; i < levels; ++i) {
      partial_sums.push_back(std::async(std::launch::deferred, recursive_worker_a, std::cref(x), i * blocksize, (i + 1) * blocksize,i));
  }

  for (unsigned long k = 0; k < levels; ++k){
    sum += partial_sums[k].get();
  }
  return std::sqrt(sum);
}

#endif    // AMATH583_RNORM_HPP
