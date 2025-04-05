

// SPDX-License-Identifier: MIT

#pragma once

import std;

namespace la {

template <class ElementType, std::size_t kNumRows, std::size_t kNumCols>
class Matrix final {
 public:
  using MdSpanType =
      std::mdspan<ElementType, std::extents<std::size_t, kNumRows, kNumCols>>;
  using ConstMdSpanType =
      std::mdspan<ElementType const,
                  std::extents<std::size_t, kNumRows, kNumCols>>;

  constexpr Matrix() { std::ranges::fill(m_data, 0); }

  auto constexpr GetData() { return MdSpanType{m_data.data()}; }

  auto constexpr GetConstData() const { return ConstMdSpanType{m_data.data()}; }

  auto constexpr Print() const {
    for (auto row : std::views::iota(0, static_cast<int>(kNumRows))) {
      std::println("{}",
                   std::span{std::ranges::next(std::ranges::cbegin(m_data),
                                               row * kNumCols),
                             kNumCols});
    }
    std::println("---");
  }

 private:
  std::array<ElementType, kNumRows * kNumCols> m_data;
};

template <class ElementType, std::size_t kNumRows1, std::size_t kNumCols1,
          std::size_t kNumRows2, std::size_t kNumCols2>
auto constexpr MatrixProduct(
    Matrix<ElementType, kNumRows1, kNumCols1> const& matrix_a,
    Matrix<ElementType, kNumRows2, kNumCols2> const& matrix_b)
    -> Matrix<ElementType, kNumRows1, kNumCols2> {
  Matrix<ElementType, kNumRows1, kNumCols2> result{};

  for (auto r : std::views::iota(0, static_cast<int>(kNumRows1))) {
    for (auto const vec1{std::span<ElementType const, kNumCols1>{
             std::ranges::next(matrix_a.GetConstData().data_handle(),
                               r * kNumCols1),
             kNumCols1}};
         auto c : std::views::iota(0, static_cast<int>(kNumCols2))) {
      auto vec2{std::views::iota(0, static_cast<int>(kNumRows2)) |
                std::views::transform([c, &matrix_b](auto ridx) -> ElementType {
                  return matrix_b.GetConstData()[ridx, c];
                })};
      result.GetData()[r, c] =
          std::inner_product(std::ranges::cbegin(vec1), std::ranges::cend(vec1),
                             std::ranges::cbegin(vec2), 0);
    }
  }

  return result;
}

}  // namespace la
