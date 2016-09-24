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
#include <iterator>
#include <sstream>

BOOST_AUTO_TEST_SUITE(calculate_raw_suite)

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename InputIterator,
//         typename Sentinel>
//     constexpr auto calculate_raw<Bits>(
//             T init,
//             InputIterator first,
//             Sentinel last,
//             T poly) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_iterator_signature_1)
{
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    
    auto const uc_init = static_cast<unsigned char>(0u);
    auto const uc_poly = static_cast<unsigned char>(9u);
	BOOST_CHECK((std::is_same<
		unsigned char,
		decltype(indi::crc::calculate_raw<7>(uc_init, ucptr, ucptr,
            uc_poly))>::value));
	
    auto const ull_init = std::uint_fast64_t{};
    auto const ull_poly = std::uint_fast64_t{};
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate_raw<64>(ull_init,
            std::istream_iterator<unsigned int>{iss},
            std::istream_iterator<unsigned int>{},
            ull_poly))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename InputIterator,
//         typename Sentinel, typename RandomAccessIterator>
//     constexpr auto calculate_raw<Bits>(
//             T init,
//             InputIterator first,
//             Sentinel last,
//             RandomAccessIterator table_first) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_iterator_signature_2)
{
    auto const u16_table = std::vector<std::uint_least16_t>{};
    
    auto u16fptr = static_cast<std::uint_fast16_t const*>(nullptr);
    BOOST_CHECK((std::is_same<
		std::uint_least16_t,
		decltype(indi::crc::calculate_raw<16>(
            std::uint_least16_t{},
            u16fptr,
            u16fptr,
            u16_table.begin()))>::value));
    
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		std::uint_fast32_t,
		decltype(indi::crc::calculate_raw<32>(
            std::uint_fast32_t{},
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{},
            u16_table.begin()))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename InputIterator,
//         typename Sentinel, typename Table>
//     constexpr auto calculate_raw<Bits>(
//             T init,
//             InputIterator first,
//             Sentinel last,
//             Table const& table) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_iterator_signature_3)
{
    auto u8lptr = static_cast<std::uint_least8_t const*>(nullptr);
    
    unsigned char const uc_table[312] = {};
    BOOST_CHECK((std::is_same<
		std::uint_fast16_t,
		decltype(indi::crc::calculate_raw<6>(
            std::uint_fast16_t{},
            u8lptr,
            u8lptr,
            uc_table))>::value));
    
    std::uint_least16_t const u16_table[256] = {};
    BOOST_CHECK((std::is_same<
		std::uint_least16_t,
		decltype(indi::crc::calculate_raw<14>(
            std::uint_least16_t{},
            u8lptr,
            u8lptr,
            u16_table))>::value));
    
    auto iss = std::istringstream{};
    auto const u64_table = std::vector<std::uint_least64_t>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate_raw<64>(
            std::uint_fast64_t{},
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{},
            u64_table))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename InputIterator,
//         typename Sentinel>
//     constexpr auto calculate_raw<16>(
//             T init,
//             InputIterator first,
//             Sentinel last) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_iterator_signature_4)
{
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_raw<16>(0u, ucptr, ucptr))>::
            value));
    
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		std::uint_fast16_t,
		decltype(indi::crc::calculate_raw<16>(
            std::uint_fast16_t{},
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{}))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename InputIterator,
//         typename Sentinel>
//     constexpr auto calculate_raw<32>(
//             T init,
//             InputIterator first,
//             Sentinel last) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_iterator_signature_5)
{
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_raw<32>(0u, ucptr, ucptr))>::
            value));
    
    auto iss = std::istringstream{};
    BOOST_CHECK((std::is_same<
		std::uint_fast32_t,
		decltype(indi::crc::calculate_raw<32>(
            std::uint_fast32_t{},
            std::istream_iterator<unsigned char>{iss},
            std::istream_iterator<unsigned char>{}))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename Range>
//     constexpr auto calculate_raw<Bits>(
//             T init,
//             Range const& range,
//             T poly) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_range_signature_1)
{
    unsigned char uc_carray[1] = {};
    
    auto const uc_init = static_cast<unsigned char>(0u);
    auto const uc_poly = static_cast<unsigned char>(9u);
	BOOST_CHECK((std::is_same<
		unsigned char,
		decltype(indi::crc::calculate_raw<7>(uc_init, uc_carray,
            uc_poly))>::value));
	
    auto const ull_init = std::uint_fast64_t{};
    auto const ull_poly = std::uint_fast64_t{};
    auto const fl = std::forward_list<unsigned char>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate_raw<64>(ull_init, fl,
            ull_poly))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename Range,
//         typename RandomAccessIterator>
//     constexpr auto calculate_raw<Bits>(
//             T init,
//             Range const& range,
//             RandomAccessIterator table_first) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_range_signature_2)
{
    unsigned char uc_carray[1] = {};
    
    auto const u16_table = std::vector<std::uint_least16_t>{};
    BOOST_CHECK((std::is_same<
		std::uint_least16_t,
		decltype(indi::crc::calculate_raw<16>(
            std::uint_least16_t{}, uc_carray,
            u16_table.begin()))>::value));
    
    auto const fl = std::forward_list<unsigned char>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast32_t,
		decltype(indi::crc::calculate_raw<32>(
            std::uint_fast32_t{}, fl, u16_table.begin()))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename Range,
//         typename Table>
//     constexpr auto calculate_raw<Bits>(
//             T init,
//             Range const& range,
//             Table const& table) noexcept ->
//         T
// with:
//     Bits: Constrained to be between 1 and 64 inclusive.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_range_signature_3)
{
    unsigned char uc_carray[1] = {};
    auto const uc_vector = std::vector<unsigned char>{};
    
    unsigned char const uc_table[312] = {};
    BOOST_CHECK((std::is_same<
		std::uint_fast16_t,
		decltype(indi::crc::calculate_raw<6>(
            std::uint_fast16_t{}, uc_carray, uc_table))>::value));
    
    std::uint_least16_t const u16_table[256] = {};
    BOOST_CHECK((std::is_same<
		std::uint_least16_t,
		decltype(indi::crc::calculate_raw<14>(
            std::uint_least16_t{}, uc_vector, u16_table))>::value));
    
    auto const fl = std::forward_list<unsigned char>{};
    auto const u64_table = std::vector<std::uint_least64_t>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast64_t,
		decltype(indi::crc::calculate_raw<64>(
            std::uint_fast64_t{}, fl, u64_table))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename Range>
//     constexpr auto calculate_raw<16>(
//             T init,
//             Range const& range) noexcept ->
//         T
// with:
//     Bits: Constrained to be 16.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_range_signature_4)
{
    unsigned char uc_carray[1] = {};
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    
    BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_raw<16>(0u, uc_carray))>::
            value));
    
    auto const fl = std::forward_list<unsigned char>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast16_t,
		decltype(indi::crc::calculate_raw<16>(
            std::uint_fast16_t{}, fl))>::value));
}

// Testing for signatures:
//     template <std::size_t Bits, typename T, typename Range>
//     constexpr auto calculate_raw<32>(
//             T init,
//             Range const& range) noexcept ->
//         T
// with:
//     Bits: Constrained to be 32.
//     T:    Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_raw_range_signature_5)
{
    unsigned char uc_carray[1] = {};
    auto ucptr = static_cast<unsigned char const*>(nullptr);
    
    BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_raw<32>(0u, uc_carray))>::
            value));
    
    auto const fl = std::forward_list<unsigned char>{};
    BOOST_CHECK((std::is_same<
		std::uint_fast32_t,
		decltype(indi::crc::calculate_raw<32>(
            std::uint_fast32_t{}, fl))>::value));
}

// Testing with polynomial argument.
BOOST_AUTO_TEST_CASE(calculate_raw_range_poly)
{
    using std::begin;
    using std::end;
    
    unsigned char cdata[] = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<5>(0u, begin(cdata),
        end(cdata), 0x09u), 0x02u);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<5>(0x12u,
        begin(cdata), end(cdata), 0x09u), 0x0Bu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<5>(0u, cdata, 0x09u),
        0x02u);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<5>(0x12u, cdata,
        0x09u), 0x0Bu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(0uLL, begin(cdata),
        end(cdata), 0x42F0E1EBA9EA3693uLL), 0xE51201F91A06376EuLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(
        0x1234567890ABCDEFuLL, begin(cdata), end(cdata),
        0x42F0E1EBA9EA3693uLL), 0x05D44A5662E09ED0uLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(0uLL, cdata,
        0x42F0E1EBA9EA3693uLL), 0xE51201F91A06376EuLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(
        0x1234567890ABCDEFuLL, cdata, 0x42F0E1EBA9EA3693uLL),
        0x05D44A5662E09ED0uLL);
    
    auto iss1 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0uL,
        std::istream_iterator<unsigned int>{iss1},
        std::istream_iterator<unsigned int>{},
        indi::crc::polynomials::crc32), 0xF93BA110uL);
    auto iss2 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0x12345678uL,
        std::istream_iterator<unsigned int>{iss2},
        std::istream_iterator<unsigned int>{},
        indi::crc::polynomials::crc32), 0x7712F9DEuL);
}

// Testing with lookup table iterator argument.
BOOST_AUTO_TEST_CASE(calculate_raw_range_tableiter)
{
    using std::begin;
    using std::end;
    
    auto const atable = indi::crc::generate_table<16>(
        indi::crc::polynomials::crc16_ccitt);
    
    unsigned char cdata[] = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, begin(cdata),
        end(cdata), &atable[0]), 0xC54Fu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x1234u,
        begin(cdata), end(cdata), &atable[0]), 0xCB7Cu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, cdata,
        &atable[0]), 0xC54Fu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x1234u, cdata,
        &atable[0]), 0xCB7Cu);
    
    auto const crc64_table = indi::crc::generate_table<64>(
        indi::crc::polynomials::crc64_iso);
    auto const dtable = std::deque<std::uint_fast64_t>{
        begin(crc64_table), end(crc64_table)};
    
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(0uLL, begin(cdata),
        end(cdata), begin(dtable)), 0x06C2D361B0000000uLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(
        0x1234567890ABCDEFuLL, begin(cdata), end(cdata),
        begin(dtable)), 0xC5233D1A32345678uLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(0uLL, cdata,
        begin(dtable)), 0x06C2D361B0000000uLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(
        0x1234567890ABCDEFuLL, cdata, begin(dtable)),
        0xC5233D1A32345678uLL);
    
    auto iss1 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u,
        std::istream_iterator<unsigned int>{iss1},
        std::istream_iterator<unsigned int>{},
        &atable[0]), 0xFB56u);
    auto iss2 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x1234u,
        std::istream_iterator<unsigned int>{iss2},
        std::istream_iterator<unsigned int>{},
        &atable[0]), 0xF565u);
}

// Testing with lookup table range argument.
BOOST_AUTO_TEST_CASE(calculate_raw_range_table)
{
    using std::begin;
    using std::end;
    
    auto const atable = indi::crc::generate_table<16>(
        indi::crc::polynomials::crc16_ccitt);
    
    unsigned char cdata[] = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, begin(cdata),
        end(cdata), atable), 0xC54Fu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x12u,
        begin(cdata), end(cdata), atable), 0xCB7Cu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, cdata,
        atable), 0xC54Fu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x12u, cdata,
        atable), 0xCB7Cu);
    
    auto const crc64_table = indi::crc::generate_table<64>(
        indi::crc::polynomials::crc64_iso);
    auto const dtable = std::deque<std::uint_fast64_t>{
        begin(crc64_table), end(crc64_table)};
    
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(0uLL, begin(cdata),
        end(cdata), dtable), 0x06C2D361B0000000uLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(
        0x1234567890ABCDEFuLL, begin(cdata), end(cdata),
        dtable), 0xC5233D1A32345678uLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(0uLL, cdata,
        dtable), 0x06C2D361B0000000uLL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<64>(
        0x1234567890ABCDEFuLL, cdata, dtable), 0xC5233D1A32345678uLL);
    
    auto iss1 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0uL,
        std::istream_iterator<unsigned int>{iss1},
        std::istream_iterator<unsigned int>{},
        atable), 0xFB56u);
    auto iss2 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x12345678uL,
        std::istream_iterator<unsigned int>{iss2},
        std::istream_iterator<unsigned int>{},
        atable), 0xF565u);
    
    auto const crc32_table = indi::crc::generate_table<32>();
    unsigned long ctable[256];
    std::copy_n(crc32_table.begin(), 256, ctable);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0uL, begin(cdata),
        end(cdata), ctable), 0x977824D1uL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x12345678uL,
        begin(cdata), end(cdata), ctable), 0x19517C1FuL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0uL, cdata,
        ctable), 0x977824D1uL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x12345678uL, cdata,
        ctable), 0x19517C1FuL);
}

// Testing CRC16.
BOOST_AUTO_TEST_CASE(calculate_raw_16)
{
    using std::begin;
    using std::end;
    
    unsigned char cdata[] = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, begin(cdata),
        end(cdata)), 0x0FA1u);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x1234u,
        begin(cdata), end(cdata)), 0x3A0Fu);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, cdata),
        0x0FA1u);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x1234u, cdata),
        0x3A0Fu);
    
    auto const fldata = std::forward_list<unsigned char>{5, 6, 7, 8};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, begin(fldata),
        end(fldata)), 0x3BE3u);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0xBEEFu,
        begin(fldata), end(fldata)), 0xCBB7u);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u, fldata),
        0x3BE3u);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0xBEEFu,
        fldata), 0xCBB7u);
    
    auto iss1 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0u,
        std::istream_iterator<unsigned int>{iss1},
        std::istream_iterator<unsigned int>{}), 0xF82Eu);
    auto iss2 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<16>(0x1234u,
        std::istream_iterator<unsigned int>{iss2},
        std::istream_iterator<unsigned int>{}), 0xCD80u);
}

// Testing CRC32.
BOOST_AUTO_TEST_CASE(calculate_raw_32)
{
    using std::begin;
    using std::end;
    
    unsigned char cdata[] = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0uL, begin(cdata),
        end(cdata)), 0x977824D1uL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0x12345678uL,
        begin(cdata), end(cdata)), 0x19517C1FuL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0uL, cdata),
        0x977824D1uL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0x12345678uL, cdata),
        0x19517C1FuL);
    
    auto const fldata = std::forward_list<unsigned char>{5, 6, 7, 8};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0uL, begin(fldata),
        end(fldata)), 0x72C99275uL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0xDEADBEEFuL,
        begin(fldata), end(fldata)), 0x49D72D76uL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0uL, fldata),
        0x72C99275uL);
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0xDEADBEEFuL,
        fldata), 0x49D72D76uL);
    
    auto iss1 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0uL,
        std::istream_iterator<unsigned long>{iss1},
        std::istream_iterator<unsigned long>{}), 0xF93BA110uL);
    auto iss2 = std::istringstream{"116 101 115 116"};
    BOOST_CHECK_EQUAL(indi::crc::calculate_raw<32>(0x12345678uL,
        std::istream_iterator<unsigned long>{iss2},
        std::istream_iterator<unsigned long>{}), 0x7712F9DEuL);
}

BOOST_AUTO_TEST_SUITE_END()