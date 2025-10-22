#include <iostream>
#include <vector>
#include <algorithm>
#include <sycl/sycl.hpp>
using namespace sycl;

int main() {
  // Set up queue on any available device
  queue q{default_selector_v};  // TODO filled

  // Initialize input and output memory on the host
  constexpr size_t N = 25600;
  std::vector<int> x(N), y(N);
  int a = 4;
  std::fill(x.begin(), x.end(), 1);
  std::fill(y.begin(), y.end(), 2);

  // USM device allocations
  int* dx = malloc_device<int>(N, q);   // TODO filled
  int* dy = malloc_device<int>(N, q);   // TODO filled

  // Copies H2D
  q.memcpy(dx, x.data(), N * sizeof(int));  // TODO filled
  q.memcpy(dy, y.data(), N * sizeof(int));  // TODO filled

  // Submit the kernel: raw pointer access
  q.submit([&](handler& h) {

    h.parallel_for(range<1>(N), [=](id<1> idx) {  // TODO filled
        dy[idx] = a * dx[idx] + dy[idx];
    });
  }).wait();

  // Copy D2H and wait
  q.memcpy(y.data(), dy, N * sizeof(int)).wait();  // TODO filled

  // Free USM
  free(dx, q);  // TODO filled
  free(dy, q);  // TODO filled

  // Check that all outputs match expected value
  bool passed = std::all_of(y.begin(), y.end(),
                            [a](int val) { return val == a * 1 + 2; });
  std::cout << (passed ? "SUCCESS" : "FAILURE") << std::endl;
  return passed ? 0 : 1;
}

