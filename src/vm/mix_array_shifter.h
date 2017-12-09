#ifndef MIX_ARRAY_SHIFTER_H
#define MIX_ARRAY_SHIFTER_H

#include "mix_byte.h"

#include <algorithm>
#include <array>

namespace mix {

template <typename T, unsigned long N> void rotate_left(std::array<T, N> *a, unsigned num_elements) {
  num_elements = num_elements % N;
  std::rotate(a->begin(), a->begin() + num_elements, a->end());
}

template <typename T, unsigned long N> void rotate_right(std::array<T, N> *a, unsigned num_elements) {
  num_elements = num_elements % N;
  std::rotate(a->rbegin(), a->rbegin() + num_elements, a->rend());
}

template <typename T, unsigned long N> void shift_left(std::array<T, N> *a, unsigned num_elements) {
  num_elements = std::min(num_elements, static_cast<unsigned>(N));
  rotate_left(a, num_elements);
  std::fill_n(a->rbegin(), num_elements, 0);
}

template <typename T, unsigned long N> void shift_right(std::array<T, N> *a, unsigned num_elements) {
  num_elements = std::min(num_elements, static_cast<unsigned>(N));
  rotate_right(a, num_elements);
  std::fill_n(a->begin(), num_elements, 0);
}

template <typename T, unsigned long N>
void double_rotate_left(std::array<T, N> *a, std::array<T, N> *b, unsigned num_elements) {
  num_elements = num_elements % (2 * N);

  rotate_left(a, num_elements);
  rotate_left(b, num_elements);

  std::swap_ranges(a->rbegin(), a->rbegin() + (num_elements % N), b->rbegin());

  if (num_elements >= N) {
    a->swap(*b);
  }
}

template <typename T, unsigned long N>
void double_rotate_right(std::array<T, N> *a, std::array<T, N> *b, unsigned num_elements) {
  num_elements = num_elements % (2 * N);

  rotate_right(a, num_elements);
  rotate_right(b, num_elements);

  std::swap_ranges(a->begin(), a->begin() + (num_elements % N), b->begin());

  if (num_elements >= N) {
    a->swap(*b);
  }
}

template <typename T, unsigned long N>
void double_shift_left(std::array<T, N> *a, std::array<T, N> *b, unsigned num_elements) {
  if (num_elements > 2 * N) {
    a->fill(0);
    b->fill(0);
  } else if (num_elements > N) {
    num_elements = num_elements % N;
    a->fill(0);
    a->swap(*b);
    shift_left(a, num_elements);
  } else {
    rotate_left(a, num_elements);
    rotate_left(b, num_elements);
    std::copy_n(b->rbegin(), num_elements, a->rbegin());
    std::fill_n(b->rbegin(), num_elements, 0);
  }
}

template <typename T, unsigned long N>
void double_shift_right(std::array<T, N> *a, std::array<T, N> *b, unsigned num_elements) {
  if (num_elements > 2 * N) {
    a->fill(0);
    b->fill(0);
  } else if (num_elements > N) {
    num_elements = num_elements % N;
    b->fill(0);
    b->swap(*a);
    shift_right(b, num_elements);
  } else {
    rotate_right(a, num_elements);
    rotate_right(b, num_elements);
    std::copy_n(a->begin(), num_elements, b->begin());
    std::fill_n(a->begin(), num_elements, 0);
  }
}

} // namespace mix

#endif // MIX_ARRAY_SHIFTER_H
