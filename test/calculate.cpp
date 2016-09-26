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

#include <deque>
#include <forward_list>

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
BOOST_AUTO_TEST_CASE(calculate_range_signature_1)
{
    unsigned char const cdata[8] = {};
    auto const ddata = std::deque<unsigned char>{};
    
    auto const uc_poly = static_cast<unsigned char>(9u);
	BOOST_CHECK((std::is_same<
		unsigned char,
		decltype(indi::crc::calculate<7>(cdata, uc_poly))>::value));
	BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<7, unsigned char, sizeof(cdata),
			unsigned int, unsigned long>(cdata, 0u))>::value));
	BOOST_CHECK((std::is_same<
		unsigned char,
		decltype(indi::crc::calculate<7>(ddata, uc_poly))>::value));
	BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<7, std::deque<unsigned char>,
			unsigned int, unsigned long>(ddata, 0u))>::value));
	
    auto const ull_poly = std::uint_fast64_t{};
    auto const fldata = std::forward_list<unsigned char>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate<64>(fldata, ull_poly))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename Range,
//         typename RandomAccessIterator,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             Range const& range,
//             RandomAccessIterator table_begin) noexcept ->
//         T
//     template <std::size_t Bits, typename U, std::size_t N,
//         typename RandomAccessIterator,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             U const(&range)[N],
//             RandomAccessIterator table_begin) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_range_signature_2)
{
    auto const u16_table = std::vector<std::uint_least16_t>{};
    
    unsigned char const cdata[4] = {};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<16>(cdata,
            u16_table.begin()))>::value));
    BOOST_CHECK((std::is_same<
		unsigned short,
		decltype(indi::crc::calculate<16, decltype(cdata),
				decltype(u16_table.begin()), unsigned short>(
			cdata, u16_table.begin()))>::value));
    
    auto const ddata = std::deque<unsigned char>{};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<32>,
		decltype(indi::crc::calculate<32>(ddata,
            u16_table.begin()))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate<32,
				std::deque<unsigned char> const,
				decltype(u16_table.begin()),
				unsigned long long>(ddata,
            u16_table.begin()))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename Range, typename Table,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             Range const& range,
//             Table const& table) noexcept ->
//         T
//     template <std::size_t Bits, typename U, std::size_t N,
//         typename Table,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             U const(&range)[N],
//             Table const& table) noexcept ->
//         T
//     template <std::size_t Bits, typename Range,
//         typename V, std::size_t M,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             Range const& range,
//             V const(&table)[M]) noexcept ->
//         T
//     template <std::size_t Bits, typename U, std::size_t N,
//         typename V, std::size_t M,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<Bits>(
//             U const(&range)[N],
//             V const(&table)[M]) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_range_signature_3)
{
    unsigned char const cdata[8] = {};
    auto const ddata = std::deque<unsigned char>{};
    
    unsigned char const uc_table[312] = {};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<6>,
		decltype(indi::crc::calculate<6>(cdata, uc_table))>::
			value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<6, decltype(cdata),
				decltype(uc_table), unsigned long>(
			cdata, uc_table))>::value));
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<6>,
		decltype(indi::crc::calculate<6>(ddata, uc_table))>::
			value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<6, decltype(ddata),
				decltype(uc_table), unsigned long>(
			ddata, uc_table))>::value));
    
    std::uint_least16_t const u16_table[256] = {};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<14>(cdata, u16_table))>::
			value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<14, decltype(cdata),
				decltype(u16_table), unsigned long>(
			cdata, u16_table))>::value));
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<14>(ddata, u16_table))>::
			value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<14, decltype(ddata),
				decltype(u16_table), unsigned long>(
			ddata, u16_table))>::value));
    
    auto const fldata = std::forward_list<unsigned char>{};
    auto const u64_table = std::vector<std::uint_least64_t>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate<64>(fldata, u64_table))>::value));
}

// Testing for signature:
//     template <std::size_t Bits, typename Range,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<16>(Range const& range) noexcept -> T
//     template <std::size_t Bits, typename U, std::size_t N,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<16>(U const(&range)[N]) noexcept -> T
// with:
//     Bits: Constrained to be 16.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_range_signature_4)
{
    unsigned char const cdata[8] = {};
    auto const ddata = std::deque<unsigned char>{};
    
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<16>(cdata))>::value));
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<16>(ddata))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<16, decltype(cdata),
				unsigned long>(cdata))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<16, decltype(ddata),
				unsigned long>(ddata))>::value));
    
    auto const fldata = std::forward_list<unsigned char>{};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<16>,
		decltype(indi::crc::calculate<16>(fldata))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate<16,
				std::forward_list<unsigned char>,
				unsigned long long>(fldata))>::value));
}

// Testing for signature:
//     template <std::size_t Bits, typename Range,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<32>(Range const& range) noexcept -> T
//     template <std::size_t Bits, typename U, std::size_t N,
//         typename T = indi::crc_type_t<Bits>>
//     constexpr auto calculate<32>(U const(&range)[N]) noexcept -> T
// with:
//     Bits: Constrained to be 32.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_range_signature_5)
{
    unsigned char const cdata[8] = {};
    auto const ddata = std::deque<unsigned char>{};
    
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<32>,
		decltype(indi::crc::calculate<32>(cdata))>::value));
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<32>,
		decltype(indi::crc::calculate<32>(ddata))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<32, decltype(cdata),
				unsigned long>(cdata))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate<32, decltype(ddata),
				unsigned long>(ddata))>::value));
    
    auto const fldata = std::forward_list<unsigned char>{};
    BOOST_CHECK((std::is_same<
		indi::crc::crc_type_t<32>,
		decltype(indi::crc::calculate<32>(fldata))>::value));
    BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate<32,
				std::forward_list<unsigned char>,
				unsigned long long>(fldata))>::value));
}

BOOST_AUTO_TEST_SUITE_END()