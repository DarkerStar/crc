/* This file is part of indi-crc.
 * 
 * indi-crc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * indi-crc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with indi-crc.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INDI_INC_CRC_IO_
#define INDI_INC_CRC_IO_

#include <locale>
#include <sstream>
#include <string>
#include <type_traits>

#include "indi/crc.hpp"

namespace indi {
namespace crc {

namespace polynomials {

//! Convert a CRC polynomial from normal encoded form to a string
//! representation.
//! 
//! CRC polynomials are normally encoded as an unsigned integer by
//! having the each bit represent the coefficient for the term whose
//! power is equal to the bit position. So if the value of bit `N` is
//! `b`, this represents the term in the polynomial `b * x^N`.
//! 
//! (The `^` character represents exponentiation operators. So `x^2` is
//! meant to be interpreted as "x squared", and `x^15` is "x raised to
//! the power of 15".)
//! 
//! In addition, for a `M`-bit CRC, the coefficient for `x^M` is not
//! encoded, and is implicitly 1.
//! 
//! So for  the 16-bit CRC polynomial `0x8005u`, bits 15, 2, and 0 are
//! set, so this function will convert it into the string:
//! 
//!     x^16 + x^15 + x^2 + 1
//! 
//! The `Bits` template parameter sets the CRC size. Only the least
//! significant `Bits` bits are considered - any higher bits are
//! ignored. So treating `0x50108005uL` as a 16-bit CRC polynomial will
//! give the same result as above. But treating it as a 32-bit
//! polynomial would result in:
//! 
//!     x^32 + x^30 + x^28 + x^15 + x^2 + 1
//! 
//! The format of the result string is guaranteed to be as follows:
//! 
//! 1.  For an `N`-bit CRC polynomial, the first term is always `x^N`.
//! 2.  For all bits that are set to 1 between bit `N` and bit 1
//!     (where bit 0 is the least significant bit), not inclusive,
//!     a term of the form ` + x^B` is appended, where `B` is the
//!     bit number.
//! 3.  If bit 1 is set, ` + x` is appended.
//! 4.  If bit 0 is set (which it always should be, for a CRC
//!     polynomial encoded in this form), ` + 1` is appended.
//! 
//! Note that numbers are always formatted according to the default "C"
//! locale, no matter what the current global locale is.
//! 
//! \tparam Bits  The CRC bit-size.
//! 
//! \tparam T The type of the encoded polynomial value.
//! 
//! No checking is done to ensure that `T` has at least `Bits` bits.
//! If `T` is too small to hold `Bits` bits, all bits missing are
//! presumed to be 0.
//! 
//! \param polynomial  The encoded polynomial value.
//! 
//! No checking is done to ensure that it is a valid encoded CRC
//! polynomial.
//! 
//! Only the least significant `Bits` bits are used.
//! 
//! \returns A string with the CRC polynomial encoded as described in
//!          the details.
//! 
template <std::size_t Bits, typename T>
auto to_string(T polynomial)
{
	static_assert(std::is_integral<T>::value,
        "CRC type must be integer");
	static_assert(std::is_unsigned<T>::value,
        "CRC type must be unsigned");
	static_assert(Bits > 0, "0-bit CRCs make no sense");
    
    // TODO: Handle the (rare) special case where Bits == 1.
    //       This would be a perfect job for constexpr if.
    
    auto oss = std::ostringstream{};
    
    // Explicitly imbue the "C" locale, just in case the global locale
    // has been set to something wacky.
    oss.imbue(std::locale::classic());
    
    // Handle the implicit order term.
    oss << "x^" << Bits;
    
    // Handle all exponents except 0 and 1.
    for (auto bit = Bits; bit > std::size_t{2}; --bit)
    {
        // IMPORTANT: The "1" must be cast to T before shifting.
        if (polynomial & (T(1u) << (bit - 1)))
            oss << " + x^" << (bit - 1);
    }
    
    // Handle "x" term.
    if (Bits > std::size_t{1} && (polynomial & 0x2u))
        oss << " + x";
    
    // Handle constant term.
    // Bits can never be 0, so there's no need to check. Technically
    // the constant term should always be 1 for a valid CRC polynomial,
    // so this if is really not necessary, but meh. It costs basically
    // nothing, and it makes the function slightly more generic.
    if (polynomial & 0x1u)
        oss << " + 1";
    
    return oss.str();
}

} // namespace polynomials

} // namespace crc
} // namespace indi

#endif // include guard
