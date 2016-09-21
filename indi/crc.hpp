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

#ifndef INDI_INC_CRC_
#define INDI_INC_CRC_

#include <climits>
#include <cstdint>
#include <type_traits>

namespace indi {
namespace crc {

namespace detail_ {

//! CRC type guesser.
//! 
//! This type is intended to simplify the CRC interface by automatically
//! selecting an appropriate type for a given bit size. For example, if
//! `Bits` is 32, the `type` member is `std::uint_fast32_t`.
//! 
//! Note that the type selected is always of the `fast` family.
//! 
//! Currently only 8, 16, 32, and 64 bit sizes are possible, but in
//! future any bit size up to and including 64 bits will be valid.
template <std::size_t Bits>
struct crc_type
{
	static_assert(Bits == 8 || Bits == 16 || Bits == 32 || Bits == 64,
		"only 8, 16, 32, or 64-bit CRCs supported by default");
	
	using type = std::conditional_t<Bits == 8,
		std::uint_fast8_t,
		std::conditional_t<Bits == 16,
			std::uint_fast16_t,
			std::conditional_t<Bits == 32,
				std::uint_fast32_t,
				std::uint_fast64_t>
			>
		>;
};

template <std::size_t Bits>
using crc_type_t = typename crc_type<Bits>::type;

//! Create a value with a given number of set bits.
//! 
//! This produces a value of type `T` with the `Bits` least significant
//! bits all set to 1. This is handy for producing masks for `Bits`
//! bits.
//! 
//! Examples:
//! 
//!     ones<3, uint_16>;  // produces uint_16(0b111u)
//!     ones<6, uint_8>;   // produces uint_8(0b11'1111u)
//!     ones<25, uint_32>; // produces uint_32(0x1ff'ffffuL)
//!     ones<18, uint_64>; // produces uint_64(0x3'ffffuLL)
//! 
//! \requires `Bits` must be greater than zero. `T` must be at least
//!           `Bits` bits.
//! 
//! \tparam Bits  The number of set bits to produce.
//! \tparam T     The type to produce.
//! 
//! \returns  A value of type `T` with the least significant `Bits`
//!           bits all set to 1.
template <std::size_t Bits, typename T>
constexpr auto ones() noexcept
{
	static_assert(std::is_integral<T>::value,
        "CRC type must be integer");
	static_assert(std::is_unsigned<T>::value,
        "CRC type must be unsigned");
	static_assert(Bits <= (sizeof(T) * CHAR_BIT), "T is too small");
	static_assert(Bits > 0, "0-bit CRCs make no sense");
    
    auto val = T{};
    
    // IMPORTANT: The "1" must be cast to T before shifting.
    for (auto bit = std::size_t{0}; bit < Bits; ++bit)
        val |= (T(0x1u) << bit);
    
    return val;
}

} // namespace detail_

namespace polynomials {

// Common 16-bit CRC polynomials.
constexpr auto crc16_ibm         = std::uint_fast16_t(0x8005u);
constexpr auto crc16_ccitt       = std::uint_fast16_t(0x1021u);
constexpr auto crc16_t10_dif     = std::uint_fast16_t(0x8BB7u);
constexpr auto crc16_dnp         = std::uint_fast16_t(0x3D65u);
constexpr auto crc16_dect        = std::uint_fast16_t(0x0589u);
constexpr auto crc16_arinc       = std::uint_fast16_t(0xA02Bu);
constexpr auto crc16_chakravarty = std::uint_fast16_t(0x2F15u);
// "CRC16" usually means the IBM polynomial.
constexpr auto crc16 = crc16_ibm;

// Common 32-bit crc polynomials.
constexpr auto crc32_ansi = std::uint_fast32_t(0x04C11DB7uL);
constexpr auto crc32_ieee = std::uint_fast32_t(0x04C11DB7uL);
constexpr auto crc32c     = std::uint_fast32_t(0x1EDC6F41uL);
constexpr auto crc32k     = std::uint_fast32_t(0x741B8CD7uL);
constexpr auto crc32q     = std::uint_fast32_t(0x814141ABuL);
// "CRC32" almost always means CRC32-IEEE.
constexpr auto crc32 = crc32_ieee;

// Common 32-bit crc polynomials.
constexpr auto crc64_iso  = std::uint_fast64_t(0x000000000000001BuLL);
constexpr auto crc64_ecma = std::uint_fast64_t(0x42F0E1EBA9EA3693uLL);
// Not sure which polynomial should be considered "CRC64".

} // namespace polynomials

} // namespace crc
} // namespace indi

#endif // include guard
