//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//

#include <iostream>
#include <vector>
#include "Timer.hpp"
#include <cstdlib>


int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " size" << std::endl;
    return -1;
  }
  size_t dim = std::stol(argv[1]);
  Timer t;    

  t.start();
  std::vector<double> dx(dim, 3.14);
  std::vector<double> dy(dim, 27.0);
  std::vector<double> dz(dim, 0.0);
  t.stop();
  std::cout << "Construction time for double: " << t.elapsed() << std::endl;

  t.start();
  for (size_t i = 0; i < dim; ++i) {
    dz[i] = dx[i] * dy[i];
  }
  t.stop();
  std::cout << "Multiplication time for double: " << t.elapsed() << std::endl;


  t.start();
  std::vector<float> fx(dim, 3.14);
  std::vector<float> fy(dim, 27.0);
  std::vector<float> fz(dim, 0.0);
  t.stop();
  std::cout << "Construction time for float: " << t.elapsed() << std::endl;

  t.start();
  for (size_t i = 0; i < dim; ++i) {
    fz[i] = fx[i] * fy[i];
  }
  t.stop();
  std::cout << "Multiplication time for float: " << t.elapsed() << std::endl;

//Calculate some FLOPS (do the LINPACK thing)
  double FLOPS = 0;
  double time_elapsed = t.elapsed();
  FLOPS = dim/time_elapsed;
  if (FLOPS >= 100000){
    std::cout << "CPU Speed: " << FLOPS/1000000 << " MFLOPS" << std::endl;
  } else {
    std::cout << "CPU Speed: " << FLOPS << " FLOPS" << std::endl;
  }
  



  return 0;
}
