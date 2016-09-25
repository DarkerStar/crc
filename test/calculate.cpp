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

#include "indi/crc.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(calculate_suite)

// Testing for signature:
//     template <std::size_t Bits, typename InputIterator,
//         typename Sentinel, typename T>
//     constexpr auto calculate<Bits>(
//             InputIterator first,
//             Sentinel last,
//             T poly) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_iterator_signature_1)
{
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    
    auto const uc_poly = static_cast<unsigned char>(9u);
	BOOST_CHECK((std::is_same<
		unsigned char,
		decltype(indi::crc::calculate<7>(ucptr, ucptr, uc_poly))>::
			value));
	
    auto const ull_poly = std::uint_fast64_t{};
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate<64>(
            std::istream_iterator<unsigned int>{iss},
            std::istream_iterator<unsigned int>{},
            ull_poly))>::value));
}

// Testing for signature:
//     template <std::size_t Bits, typename InputIterator,
//         typename Sentinel, typename RandomAccessIterator,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             InputIterator first,
//             Sentinel last,
//             RandomAccessIterator table_begin) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_iterator_signature_2)
{
    auto const u16_table = std::vector<std::uint_least16_t>{};
    
    auto u16fptr = static_cast<std::uint_fast16_t const*>(nullptr);
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<16>(u16fptr, u16fptr,
            u16_table.begin()))>::value));
    BOOST_CHECK((std::is_same<
		unsigned short,
		decltype(indi::crc::calculate<16, decltype(u16fptr),
				decltype(u16fptr), decltype(u16_table.begin()),
				unsigned short>(
			u16fptr, u16fptr,
            u16_table.begin()))>::value));
    
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<32>,
		decltype(indi::crc::calculate<32>(
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{},
            u16_table.begin()))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate<32,
				std::istream_iterator<unsigned char>,
				std::istream_iterator<unsigned char>,
				decltype(u16_table.begin()),
				unsigned long long>(
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{},
            u16_table.begin()))>::value));
}

// Testing for signature:
//     template <std::size_t Bits, typename InputIterator,
//         typename Sentinel, typename Table,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             InputIterator first,
//             Sentinel last,
//             Table const& table) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_iterator_signature_3)
{
    auto u8lptr = static_cast<std::uint_least8_t const*>(nullptr);
    
    unsigned char const uc_table[312] = {};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<6>,
		decltype(indi::crc::calculate<6>(u8lptr, u8lptr, uc_table))>::
			value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<6, decltype(u8lptr),
				decltype(u8lptr), decltype(uc_table), unsigned long>(
			u8lptr, u8lptr, uc_table))>::value));
    
    std::uint_least16_t const u16_table[256] = {};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<14>(u8lptr, u8lptr, u16_table))>::
			value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<14, decltype(u8lptr),
				decltype(u8lptr), decltype(u16_table), unsigned long>(
			u8lptr, u8lptr, u16_table))>::value));
    
    auto iss = std::istringstream{};
    auto const u64_table = std::vector<std::uint_least64_t>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate<64>(
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{},
            u64_table))>::value));
}

// Testing for signature:
//     template <std::size_t Bits, typename InputIterator,
//         typename Sentinel, typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<16>(
//             InputIterator first,
//             Sentinel last) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_iterator_signature_4)
{
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<16>(ucptr, ucptr))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<16, decltype(ucptr),
				decltype(ucptr), unsigned long>(ucptr, ucptr))>::
					value));
    
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<16>(
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{}))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate<16,
				std::istream_iterator<unsigned char>,
				std::istream_iterator<unsigned char>,
				unsigned long long>(
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{}))>::value));
}

// Testing for signature:
//     template <std::size_t Bits, typename InputIterator,
//         typename Sentinel, typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<32>(
//             InputIterator first,
//             Sentinel last) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_iterator_signature_5)
{
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<32>,
		decltype(indi::crc::calculate<32>(ucptr, ucptr))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<32, decltype(ucptr),
				decltype(ucptr), unsigned long>(ucptr, ucptr))>::
					value));
    
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<32>,
		decltype(indi::crc::calculate<32>(
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{}))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate<32,
				std::istream_iterator<unsigned char>,
				std::istream_iterator<unsigned char>,
				unsigned long long>(
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{}))>::value));
}

BOOST_AUTO_TEST_SUITE_END()