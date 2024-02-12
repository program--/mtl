#pragma once

#include <iterator>

namespace mtl {

// TODO
template<
  typename Tp,
  typename Layout,
  typename Difference,
  typename Pointer,
  typename Reference>
struct tensor_iterator
  : public std::iterator<
      std::random_access_iterator_tag,
      Tp,
      Difference,
      Pointer,
      Reference>
{};

} // namespace mtl
