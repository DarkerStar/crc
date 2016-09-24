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

#include <array>
#include <climits>
#include <cstdint>
#include <iterator>
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
//!           `Bits` bits in size.
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

template <typename T, typename = void>
struct is_input_iterator : std::false_type{};

template <typename T>
struct is_input_iterator<T,
        typename std::enable_if<
            std::is_base_of<
                std::input_iterator_tag,
                typename std::iterator_traits<T>::
                    iterator_category>::value
            >::type> :
    std::true_type{};

template <typename T, typename = void>
struct is_random_access_iterator : std::false_type{};

template <typename T>
struct is_random_access_iterator<T,
        typename std::enable_if<
            std::is_base_of<
                std::random_access_iterator_tag,
                typename std::iterator_traits<T>::
                    iterator_category>::value
            >::type> :
    std::true_type{};

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

//! Converts a polynomial to Koopman form.
//! 
//! A `N`-bit CRC polynomial always has at least two non-zero
//! coefficients: the coefficient of the constant term (that is, 1),
//! and the coefficient that defines its degree to `N`. So a 4-bit
//! CRC polynomial will always look like this:
//! 
//!     x^4 + (A * x^3) + (B * x^2) + (C * x) + 1
//! 
//! where `A`, `B`, and `C` are all either 0 or 1.
//! 
//! Normal encoding ignores the degree coefficient, but encodes all the
//! other coefficients in order. So the bits for the polynomial above
//! would be `0bABC1` (the least significant bit is always 1).
//! 
//! Koopman encoding, named after Philip Koopman, instead ignores the
//! constant term, and encodes the degree term coefficient. So the bits
//! for the Koopman rendering of the polynomial above would be
//! `0b1ABC`.
//! 
//! Koopman encoding has the benefit that the CRC's bit size is always
//! encoded - it is always identifiable by the most significant bit
//! set. For example, if you see `0b001?'????`, you know it's a 6-bit
//! CRC.
//! 
//! \requires `Bits` must be greater than zero. `T` must be at least
//!           `Bits` bits in size.
//! 
//! \tparam Bits  The CRC bit-size.
//! 
//! \tparam T The type of the encoded polynomial value.
//! 
//! \param polynomial  The encoded polynomial value.
//! 
//! No checking is done to ensure that it is a valid encoded `Bits`-bit
//! CRC polynomial. In particular, the least significant bit should be
//! set, but this is not checked.
//! 
//! Only the least significant `Bits` bits are used. Any higher bits
//! are discarded.
//! 
//! \returns The Koopman encoding of the supplied polynomial.
template <std::size_t Bits, typename T>
constexpr auto to_koopman(T polynomial) noexcept
{
	static_assert(std::is_integral<T>::value,
		"CRC type must be integer");
	static_assert(std::is_unsigned<T>::value,
		"CRC type must be unsigned");
	static_assert(Bits <= (sizeof(T) * CHAR_BIT), "T is too small");
	static_assert(Bits > 0, "0-bit CRCs make no sense");
	
	constexpr auto mask = detail_::ones<Bits, T>();
	
	return T(((polynomial >> 1) | (T(0x1u) << (Bits - 1))) & mask);
}

//! Converts a polynomial in Koopman form to standard form.
//! 
//! For an explanation of Koopman encoding, see the `to_koopman`
//! documentation.
//! 
//! \requires `Bits` must be greater than zero. `T` must be at least
//!           `Bits` bits in size.
//! 
//! \tparam Bits  The CRC bit-size.
//! 
//! \tparam T The type of the encoded polynomial value.
//! 
//! \param polynomial  The Koopman-encoded polynomial value.
//! 
//! No checking is done to ensure that it is a valid encoded `Bits`-bit
//! CRC polynomial. In particular, the bit at position (`Bits` - 1)
//! should be set, but this is not checked.
//! 
//! Only the least significant `Bits` bits are used. Any higher bits
//! are discarded.
//! 
//! \returns The given Koopman polynomial in standard form.
template <std::size_t Bits, typename T>
constexpr auto from_koopman(T polynomial) noexcept
{
	static_assert(std::is_integral<T>::value,
		"CRC type must be integer");
	static_assert(std::is_unsigned<T>::value,
		"CRC type must be unsigned");
	static_assert(Bits <= (sizeof(T) * CHAR_BIT), "T is too small");
	static_assert(Bits > 0, "0-bit CRCs make no sense");
	
	constexpr auto mask = detail_::ones<Bits, T>();
	
	return T(((polynomial << 1) | T(0x1u)) & mask);
}

//! Converts a polynomial to reversed form.
//! 
//! The binary coefficients of a CRC polynomial (not including the
//! degree term) are usually encoded in integer form so that each
//! bit `B`, counting from zero as the least significant bit,
//! corresponds to the coefficient of the `x^B` term. This is
//! straightforward, but it means that you cannot tell the degree of
//! the CRC polynomial from the encoded integer.
//! 
//! Reversed form is exactly the same as normal form, except the bit
//! order is reversed. So a 4-bit CRC polynomial like this:
//! 
//!     x^4 + (A * x^3) + (B * x^2) + (C * x) + 1
//! 
//! (where `A`, `B`, and `C` are all either 0 or 1) will encode to
//! normal form as `0bABC1`, and to reversed form as `0b1CBA`. Because
//! bit `N-1` is always 1, you can tell from the reversed form that
//! this is a 4-bit CRC, because the highest set bit is 3 (which is
//! `4 - 1`).
//! 
//! Of course, the same transformation that converts a polynomial from
//! normal form to reversed can convert it back from reversed to
//! normal.
//! 
//! \requires `Bits` must be greater than zero. `T` must be at least
//!           `Bits` bits in size.
//! 
//! \tparam Bits  The CRC bit-size.
//! 
//! \tparam T The type of the encoded polynomial value.
//! 
//! \param polynomial  The encoded polynomial value.
//! 
//! Only the least significant `Bits` bits are used. Any higher bits
//! are discarded.
//! 
//! \returns The given polynomial with the bits reversed.
template <std::size_t Bits, typename T>
constexpr auto reversed(T polynomial) noexcept
{
	static_assert(std::is_integral<T>::value,
		"CRC type must be integer");
	static_assert(std::is_unsigned<T>::value,
		"CRC type must be unsigned");
	static_assert(Bits <= (sizeof(T) * CHAR_BIT), "T is too small");
	static_assert(Bits > 0, "0-bit CRCs make no sense");
	
	auto result = T{};
	
	for (auto bit = std::size_t{0}; bit < Bits; ++bit)
	{
		result <<= 1;
		result |= polynomial & 1u;
		
		polynomial >>= 1;
	}
	
	return result;
}

} // namespace polynomials

//! Generates a 256-element lookup table for CRC calculations.
//! 
//! The lookup table can be used in any of the CRC calculation
//! functions.
//! 
//! \requires `Bits` must be greater than zero. `T` must be at least
//!           `Bits` bits in size.
//! 
//! \tparam Bits  The CRC bit-size.
//! 
//! \tparam T The type of the encoded polynomial value.
//! 
//! \param polynomial  The encoded polynomial value.
//! 
//! \returns An std::array<T, 256> with the computed CRCs of every
//!          value from 0 to 255, using the given polynomial.
template <std::size_t Bits, typename T>
constexpr auto generate_table(T polynomial) noexcept
{
	static_assert(std::is_integral<T>::value,
		"CRC type must be integer");
	static_assert(std::is_unsigned<T>::value,
		"CRC type must be unsigned");
	static_assert(Bits <= (sizeof(T) * CHAR_BIT), "T is too small");
	static_assert(Bits > 0, "0-bit CRCs make no sense");
	
	auto const reversed_polynomial =
		polynomials::reversed<Bits>(polynomial);
	
	auto table = std::array<T, 256>{};
	
	for (auto n = std::size_t{0}; n < std::size_t{256}; ++n)
	{
		// Start with the value set as the index.
		table[n] = T(n);
		
		// For each bit...
		for (auto bit = 0; bit < 8; ++bit)
		{
			// ... if the bit is set, XOR the value with the reversed
			// polynomial.
			if (table[n] & 1)
			{
				table[n] >>= 1;
				table[n] ^= reversed_polynomial;
			}
			// ... if the bit is not set, do nothing.
			else
			{
				table[n] >>= 1;
			}
		}
	}
	
	return table;
}

//! Generates a 256-element lookup table for CRC16 calculations.
//! 
//! This is a convenience method which just calls:
//! 
//!     generate_table<16>(polynomials::crc16)
//! 
//! \requires `Bits` is 16.
//! 
//! \tparam Bits  The CRC bit-size (must be 16).
//! 
//! \param polynomial  The encoded polynomial value.
//! 
//! \returns An std::array<std::uint_fast16_t, 256> with the computed
//!          CRC16s of every value from 0 to 255.
template <std::size_t Bits>
constexpr auto generate_table() noexcept ->
	std::enable_if_t<Bits == 16, std::array<std::uint_fast16_t, 256>>
{
	return generate_table<Bits>(polynomials::crc16);
}

//! Generates a 256-element lookup table for CRC32 calculations.
//! 
//! This is a convenience method which just calls:
//! 
//!     generate_table<16>(polynomials::crc32)
//! 
//! \requires `Bits` is 32.
//! 
//! \tparam Bits  The CRC bit-size (must be 32).
//! 
//! \param polynomial  The encoded polynomial value.
//! 
//! \returns An std::array<std::uint_fast32_t, 256> with the computed
//!          CRC32s of every value from 0 to 255.
template <std::size_t Bits>
constexpr auto generate_table() noexcept ->
	std::enable_if_t<Bits == 32, std::array<std::uint_fast32_t, 256>>
{
	return generate_table<Bits>(polynomials::crc32);
}

//! Calculates the CRC of an 8-bit value given a previous CRC and a
//! lookup table.
//! 
//! \requires `T` is an unsigned integral type.
//! \requires `RandomAccessIterator` is a random access iterator to
//!     a sequence of values convertible to `T` that is at least 256
//!     items in size.
//! 
//! \tparam T  The CRC type.
//! \tparam RandomAccessIterator  An iterator to the beginning of a
//!     lookup table of precomputed CRC values for 0 to 255.
//! 
//! \param current  The CRC of the preceding input sequence.
//! \param b  The next 8-bit value in the input sequence.
//! \param table_begin  An iterator to a sequence of precomputed CRCs.
//! 
//! \returns The computed CRC.
template <typename T, typename RandomAccessIterator>
constexpr auto calculate_next(T current, std::uint_fast8_t b,
		RandomAccessIterator table_begin) noexcept ->
	std::enable_if_t<
		detail_::is_input_iterator<RandomAccessIterator>::value &&
			detail_::is_random_access_iterator<
				RandomAccessIterator>::value,
		T>
{
	static_assert(std::is_integral<T>::value,
		"CRC type must be integer");
	static_assert(std::is_unsigned<T>::value,
		"CRC type must be unsigned");
	
	return T(table_begin[(current ^ b) & 0xffu] ^ (current >> 8));
}

// This overload only exists to produce a better error message
// if someone attempts to use a non-random-access iterator as the
// table iterator. It will never actually return anything.
template <typename T, typename InputIterator>
auto calculate_next(T, std::uint_fast8_t, InputIterator) ->
	std::enable_if_t<
		detail_::is_input_iterator<InputIterator>::value &&
			!detail_::is_random_access_iterator<InputIterator>::
			value,
		T>
{
	static_assert(detail_::is_random_access_iterator<InputIterator>::
			value,
		"iterator argument is not a random access iterator");
	
	return T{};
}

//! Calculates the CRC of an 8-bit value given a previous CRC and a
//! lookup table.
//! 
//! This is a convenience method which just calls:
//! 
//!     using std::begin;
//!     calculate_next(current, b, begin(table));
//! 
//! \requires `T` is an unsigned integral type.
//! \requires `RandomAccessIterator` is a random access iterator to
//!     a sequence of values convertible to `T` that is at least 256
//!     items in size.
//! 
//! \tparam T  The CRC type.
//! \tparam RandomAccessIterator  An iterator to the beginning of a
//!     lookup table of precomputed CRC values for 0 to 255.
//! 
//! \param current  The CRC of the preceding input sequence.
//! \param b  The next 8-bit value in the input sequence.
//! \param table_begin  An iterator to a sequence of precomputed CRCs.
//! 
//! \returns The computed CRC.
template <typename T, typename Table>
constexpr auto calculate_next(T current, std::uint_fast8_t b,
		Table const& table) noexcept ->
	std::enable_if_t<!detail_::is_input_iterator<Table>::value, T>
{
	using std::begin;
	
	return calculate_next(current, b, begin(table));
}

//! Calculates the CRC of an 8-bit value given a previous CRC and a
//! lookup table.
//! 
//! This is a convenience method which just calls:
//! 
//!     calculate_next(current, b, table + 0)
//! 
//! \requires `T` is an unsigned integral type.
//! \requires `RandomAccessIterator` is a random access iterator to
//!     a sequence of values convertible to `T` that is at least 256
//!     items in size.
//! 
//! \tparam T  The CRC type.
//! \tparam RandomAccessIterator  An iterator to the beginning of a
//!     lookup table of precomputed CRC values for 0 to 255.
//! 
//! \param current  The CRC of the preceding input sequence.
//! \param b  The next 8-bit value in the input sequence.
//! \param table_begin  An iterator to a sequence of precomputed CRCs.
//! 
//! \returns The computed CRC.
template <typename T, typename U, std::size_t N>
constexpr auto calculate_next(T current, std::uint_fast8_t b,
		const U(&table)[N]) noexcept
{
	static_assert(N >= 256,
		"CRC lookup table must have at least 256 items");
	
	return calculate_next(current, b, table + 0);
}

// calculate_raw ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <std::size_t Bits, typename T, typename InputIterator,
	typename Sentinel>
constexpr auto calculate_raw(T init, InputIterator first, Sentinel last,
		T poly) noexcept ->
	std::enable_if_t<
		detail_::is_input_iterator<InputIterator>::value &&
			std::is_integral<T>::value,
		T>
{
	return init;
}

template <std::size_t Bits, typename T, typename InputIterator,
	typename Sentinel, typename RandomAccessIterator>
constexpr auto calculate_raw(T init, InputIterator first, Sentinel last,
		RandomAccessIterator table_begin) noexcept ->
	std::enable_if_t<
		detail_::is_input_iterator<InputIterator>::value &&
			!std::is_integral<RandomAccessIterator>::value &&
			detail_::is_random_access_iterator<RandomAccessIterator>::
				value,
		T>
{
	return init;
}

template <std::size_t Bits, typename T, typename InputIterator,
	typename Sentinel, typename Table>
constexpr auto calculate_raw(T init, InputIterator first, Sentinel last,
		Table const& table) noexcept ->
	std::enable_if_t<
		detail_::is_input_iterator<InputIterator>::value &&
			!std::is_integral<Table>::value &&
			!detail_::is_random_access_iterator<Table>::value,
		T>
{
	return init;
}

template <std::size_t Bits, typename T, typename InputIterator,
	typename Sentinel, typename U, std::size_t N>
constexpr auto calculate_raw(T init, InputIterator first, Sentinel last,
		const U(&table)[N]) noexcept
{
	return init;
}

template <std::size_t Bits, typename T, typename InputIterator,
	typename Sentinel>
constexpr auto calculate_raw(T init, InputIterator first, Sentinel last)
		noexcept ->
	std::enable_if_t<Bits == 16, T>
{
	return init;
}

template <std::size_t Bits, typename T, typename InputIterator,
	typename Sentinel>
constexpr auto calculate_raw(T init, InputIterator first, Sentinel last)
		noexcept ->
	std::enable_if_t<Bits == 32, T>
{
	return init;
}

} // namespace crc
} // namespace indi

#endif // include guard
