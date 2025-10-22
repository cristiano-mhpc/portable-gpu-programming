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

  {
    // Create buffers for the host data
    buffer<int> bx(x.data(), range<1>(N));  // TODO filled
    buffer<int> by(y.data(), range<1>(N));  // TODO filled

    // Submit the kernel to the queue
    q.submit([&](handler& h) {
      // Create accessors
      accessor ax(bx, h, read_only);        // TODO filled
      accessor ay(by, h, read_write);       // TODO filled

      h.parallel_for(range<1>(N), [=](id<1> i) {   // TODO filled
        ay[i] = a * ax[i] + ay[i];
      });
    });

    // Checking the result inside the scope of the buffers using host accessors
    host_accessor hy(by, read_only);  // forces completion & host visibility  // TODO filled
    bool ok = std::all_of((const int*)hy.get_pointer(),
                          (const int*)hy.get_pointer() + N,
                          [a](int val){ return val == a*1 + 2; });
    if(!ok) { std::cerr << "Buffer version: mismatch!\n"; }
  } // buffers go out of scope; data is back in y

  // Final check on y (redundant but fine)
  bool passed = std::all_of(y.begin(), y.end(),
                            [a](int val) { return val == a * 1 + 2; });
  std::cout << (passed ? "SUCCESS" : "FAILURE") << std::endl;
  return passed ? 0 : 1;
}

