#pragma once

#include <memory>

#include <mtl/bits/mtl_traits.hpp>

#include "tensor_common.hpp"
#include "tensor_projection.hpp"
#include "tensor_iterator.hpp"

#ifndef MTL_TENSOR_BOUNDS_CHECK
#    define MTL_TENSOR_BOUNDS_CHECK true
#endif

namespace mtl {

template<
  typename Tp,
  typename Allocator = std::allocator<Tp>,
  typename Layout    = row_major>
struct tensor : private Layout
{
    using value_type       = Tp;
    using reference        = value_type&;
    using const_reference  = const value_type&;
    using layout_type      = Layout;
    using allocator_type   = Allocator;
    using allocator_traits = std::allocator_traits<allocator_type>;

    static_assert(
      std::is_same<value_type, typename allocator_traits::value_type>::value,
      "tensor's value_type and Allocator's value_type must match"
    );

    using size_type       = typename allocator_traits::size_type;
    using difference_type = typename allocator_traits::difference_type;
    using pointer         = typename allocator_traits::pointer;
    using const_pointer   = typename allocator_traits::const_pointer;

    //
    using iterator = tensor_iterator<
      value_type,
      layout_type,
      difference_type,
      pointer,
      reference>;

    //
    using const_iterator = tensor_iterator<
      const value_type,
      layout_type,
      difference_type,
      pointer,
      reference>;

  private:
    static constexpr bool bounds_check = MTL_TENSOR_BOUNDS_CHECK;

  public:
    // TODO
    template<typename S>
    auto cast() -> tensor<S, allocator_type, layout_type>;

    // TODO
    template<
      typename... N,
      std::enable_if_t<
        (sizeof...(N) > 0) && detail::all_integral<N...>::value,
        bool> = true>
    auto at(N... n) noexcept(!bounds_check) -> reference;

    // TODO
    template<
      typename... N,
      std::enable_if_t<
        (sizeof...(N) > 0) && detail::all_integral<N...>::value,
        bool> = true>
    auto at(N... n) noexcept(!bounds_check) -> const_reference;

    // TODO
    auto operator[](size_type n) noexcept -> tensor_projection<value_type>;

    // TODO
    auto operator[](size_type n) const noexcept
      -> tensor_projection<const value_type>;

    auto rank() const noexcept -> size_type;

    // TODO
    auto data() noexcept -> pointer;

    // TODO
    auto data() const noexcept -> const_pointer;

    // TODO
    auto begin() noexcept -> iterator;

    // TODO
    auto begin() const noexcept -> const_iterator;

    // TODO
    auto cbegin() const noexcept -> const_iterator;

    // TODO
    auto end() noexcept -> iterator;

    // TODO
    auto end() const noexcept -> const_iterator;

    // TODO
    auto cend() const noexcept -> const_iterator;

  private:
    size_type  rank_;
    size_type* dimensions_;
    pointer    data_;

    // TODO: empty base class optimization, compressed pair w/ data_?
    allocator_type alloc_;
};

} // namespace mtl
