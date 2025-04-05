
#include "la.hpp"

import std;

auto main() -> int {
  la::Matrix<int, 4, 3> matrix_a{};
  for (auto matrix_a_mdspan{matrix_a.GetData()};
       auto row : std::views::iota(0, 4)) {
    std::iota(std::ranges::next(matrix_a_mdspan.data_handle(), row * 3),
              std::ranges::next(matrix_a_mdspan.data_handle(), (row + 1) * 3),
              row * 3);
  }
  matrix_a.Print();

  la::Matrix<int, 3, 4> matrix_b{};
  std::iota(std::ranges::next(matrix_b.GetData().data_handle(), 0),
            std::ranges::next(matrix_b.GetData().data_handle(), 12), 0);
  matrix_b.Print();

  auto const result{la::MatrixProduct(matrix_a, matrix_b)};
  result.Print();

  return 0;
}
