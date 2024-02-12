#pragma once

namespace mtl {

struct row_major
{};

struct column_major
{};

using c_layout       = row_major;
using fortran_layout = column_major;

} // namespace mtl
