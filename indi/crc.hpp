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

#include <cstdint>

namespace indi {
namespace crc {

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
