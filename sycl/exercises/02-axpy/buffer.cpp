#include <iostream>
#include <vector>
#include <algorithm> 
#include <sycl/sycl.hpp>
using namespace sycl;

int main() {
  // Set up queue on any available device
  squeue q{default_selector_v}; // TODO filled
  
  // Initialize input and output memory on the host
  constexpr size_t N = 25600;
  std::vector<int> x(N),y(N);
  int a=4;
  std::fill(x.begin(), x.end(), 1);
  std::fill(y.begin(), y.end(), 2);

  {
   // Create buffers for the host data or allocate memory usinggUSM
   // If USM + malloc_device() is used add the copy operations
   // TODO filled 
    buffer<int> x_buf(x.data(), range<1>(N));
    buffer<int> y_buf(y.data(), range<1>(N));

    // Submit the kernel to the queue
    q.submit([&](handler& h) {
      // Create accessors if necessary
      //TODO filled
      accessor x_acc(x_buf, h, read_only);
      accessor y_acc(y_buf, h, read_write);
      

      //The kernel as a lambda
      //TODO filled 
      h.parallel_for(range<1>(N), [=](id<1> i) {
              y_acc[i] = a * x_acc[i] + y_acc[i];
        });
    });

    //TODO after the submission works
    host_accessor y_host_acc(y_buf,read_only); // TODO filled  
    //Checking the result inside the scope of the buffers using host_accessors
    bool ok = std::all_of((const int*)y_host_acc.get_pointer(),
                            (const int*y)y_host_acc.get_pointer + N,
                            [a](int val){return val == a*1 + 2;});
    if(!ok){std::cerr << "buffer version: mismatch!\n";}
  }
  // If USM + malloc_device() is used add the copy operations 
  // TODO
  // Check that all outputs match expected value

  // If USM is used free the device memory
  // TODO
  // Check that all outputs match expected value
  bool passed = std::all_of(y.begin(), y.end(),
                            [a](int val) { return val == a * 1 + 2; });
  std::cout << ((passed) ? "SUCCESS" : "FAILURE")
            << std::endl;
  return (passed) ? 0 : 1;
}
