/*
 *  prjpeppercorn -- GateMate FPGAs Bitstream Documentation and Tools
 *
 *  Copyright (C) 2024  The Project Peppercorn Authors.
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef LIBGATEMATE_CHIP_HPP
#define LIBGATEMATE_CHIP_HPP

#include <string>
#include <vector>
#include "Die.hpp"

namespace GateMate {

class Chip
{
  public:
    explicit Chip(std::string name);
    explicit Chip(int num);

    int get_max_die() const;
    std::string get_name() const;
    const Die &get_die(int num) const { return dies.at(num); }
    Die &get_die(int num) { return dies.at(num); }

  private:
    int die_num;
    std::vector<Die> dies;
};

} // namespace GateMate

#endif // LIBGATEMATE_CHIP_HPP
