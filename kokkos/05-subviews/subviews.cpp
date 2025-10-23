#include <Kokkos_Core.hpp>
#include <iostream>

int main(int argc, char* argv[]) {

  // Initialize Kokkos
  Kokkos::initialize(argc, argv);

  {
    int n = 20;
    int m = 20;

    Kokkos::View<int**> a("a", n, m); 

    // Subviews of boundaries
    auto TOP = Kokkos::subview(a, 0, Kokkos::ALL());
    auto BOTTOM = Kokkos::subview(a, n-1, Kokkos::ALL());
    auto LEFT = Kokkos::subview(a, Kokkos::ALL(), 0);
    auto RIGHT = Kokkos::subview(a, Kokkos::ALL(), m-1); 

    // Initialize boundaries in parallel
    Kokkos::parallel_for(m, KOKKOS_LAMBDA(const int i) {
      TOP(i) = -1;
      BOTTOM(i) = -1;
    }); 

    Kokkos::parallel_for(n, KOKKOS_LAMBDA(const int i) {
      LEFT(i) = -2;
      RIGHT(i) = -2;
    });
    Kokkos::fence();

    // For copying to host, we need contiguous buffers in device
    Kokkos::View<int*> top("top", TOP.extent(0));  
    Kokkos::deep_copy(top, TOP);
    Kokkos::View<int*> bottom("bottom", BOTTOM.extent(0));
    Kokkos::deep_copy(bottom, BOTTOM);
    Kokkos::View<int*> left("left", LEFT.extent(0));
    Kokkos::deep_copy(left, LEFT);
    Kokkos::View<int*> right("right", RIGHT.extent(0));
    Kokkos::deep_copy(right, RIGHT);


    // Create mirror views
    auto h_top = Kokkos::create_mirror(top);
    auto h_bottom = Kokkos::create_mirror(bottom);
    auto h_left = Kokkos::create_mirror(left);
    auto h_right = Kokkos::create_mirror(right);

    // Copy to host
    Kokkos::deep_copy(h_top, top);
    Kokkos::deep_copy(h_bottom, bottom);
    Kokkos::deep_copy(h_left, left);
    Kokkos::deep_copy(h_right, right);

    Kokkos::fence();

  }
  Kokkos::finalize();
  return 0;
}
