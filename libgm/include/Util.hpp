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

#ifndef LIBGATEMATE_UTIL_HPP
#define LIBGATEMATE_UTIL_HPP

#include <boost/range/adaptor/reversed.hpp>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace GateMate {
enum class VerbosityLevel
{
    ERROR,
    NOTE,
    DEBUG,
};
extern VerbosityLevel verbosity;

inline std::string uint32_to_hexstr(uint32_t val)
{
    std::ostringstream os;
    os << "0x" << std::hex << std::setw(8) << std::setfill('0') << val;
    return os.str();
}

// Hex is not allowed in JSON, to avoid an ugly decimal integer use a string
// instead But we need to parse this back to a uint32_t
inline uint32_t parse_uint32(std::string str) { return uint32_t(strtoul(str.c_str(), nullptr, 0)); }

inline std::string to_string(const std::vector<bool> &bv)
{
    std::ostringstream os;
    for (auto bit : boost::adaptors::reverse(bv))
        os << (bit ? '1' : '0');
    return os.str();
}

inline std::istream &operator>>(std::istream &in, std::vector<bool> &bv)
{
    bv.clear();
    std::string s;
    in >> s;
    for (auto c : boost::adaptors::reverse(s)) {
        assert((c == '0') || (c == '1'));
        bv.push_back((c == '1'));
    }
    return in;
}

// Skip whitespace, optionally including newlines
inline void skip_blank(std::istream &in, bool nl = false)
{
    int c = in.peek();
    while (in && (((c == ' ') || (c == '\t')) || (nl && ((c == '\n') || (c == '\r'))))) {
        in.get();
        c = in.peek();
    }
}
// Return true if end of line (or file)
inline bool skip_check_eol(std::istream &in)
{
    skip_blank(in, false);
    if (!in)
        return false;
    int c = in.peek();
    // Comments count as end of line
    if (c == '#') {
        in.get();
        c = in.peek();
        while (in && c != EOF && c != '\n') {
            in.get();
            c = in.peek();
        }
        return true;
    }
    return (c == EOF || c == '\n');
}

// Skip past blank lines and comments
inline void skip(std::istream &in)
{
    skip_blank(in, true);
    while (in && (in.peek() == '#')) {
        // Skip comment line
        skip_check_eol(in);
        skip_blank(in, true);
    }
}

// Return true if at the end of a record (or file)
inline bool skip_check_eor(std::istream &in)
{
    skip(in);
    int c = in.peek();
    return (c == EOF || c == '.');
}

// Return true if at the end of file
inline bool skip_check_eof(std::istream &in)
{
    skip(in);
    int c = in.peek();
    return (c == EOF);
}

std::string stringf(const char *fmt, ...);
std::string vstringf(const char *fmt, va_list ap);

} // namespace GateMate
#define fmt(x) (static_cast<const std::ostringstream &>(std::ostringstream() << x).str())

#define UNUSED(x) (void)(x)

#endif // LIBGATEMATE_UTIL_HPP
