//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <cmath>
#include <cstddef>
#include <cassert>

void zeroize(Vector& x) {
  // WRITE ME
  for (size_t i = 0; i < x.num_rows(); ++i) {
    x(i) = 0;
    // x.at(i) = 0;
  }
}

double one_norm(const Vector& x) {
  // WRITE ME
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += std::abs(x(i));  
  }
  return sum;
}

double two_norm(const Vector& x) {
  // WRITE ME
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i)*x(i);
  }
  double norm = std::sqrt(sum);
  return norm;
}

double inf_norm(const Vector& x) {
  double result = 0.0;
  // WRITE ME
  for (size_t i = 0; i < x.num_rows(); ++i) {
    if (x(i) > result){
      result = x(i);
    }
  }
  return result;
}


double dot(const Vector& x, const Vector& y) {
  assert(x.num_rows() == y.num_rows() && "Vectors not the same size");  
  // WRITE ME
  double result = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    result += x(i)*y(i);
  }
  return result;
}

double two_norm_d(const Vector& x) { 
  // WRITE ME / FIX ME -- can you make the function only one line long including return?
  return 0.0;  
}

double one_norm(const Matrix& A) {
  double sum = 0.0;
  for (size_t j = 0; j < A.num_cols(); ++j) {    // for each column
    double tmp = 0.0;
    for (size_t i = 0; i < A.num_rows(); ++i) {    // compute column sum
      tmp += std::abs(A(i, j));
    }
    sum = std::max(sum, tmp);
  }
  return sum;
}


double inf_norm(const Matrix& A) {
  double sum = 0.0;
  for (size_t j = 0; j < A.num_rows(); ++j) {    // for each column
    double tmp = 0.0;
    for (size_t i = 0; i < A.num_rows(); ++i) {    // compute column sum
      tmp += std::abs(A(j, i));
    }
    sum = std::max(sum, tmp);
  }
  return sum;
}



// WRITE ME f_norm()
double f_norm(const Matrix& A){
  double sum = 0.0;
  double result = 0.0;
  for (size_t j = 0; j < A.num_rows(); ++j) {    // for each column
    for (size_t i = 0; i < A.num_rows(); ++i) {    // compute column sum
      sum += A(i,j)*A(i,j);
    }
    result = std::sqrt(sum);
  }
  return result;
}
