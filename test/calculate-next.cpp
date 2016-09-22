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

#include <algorithm>
#include <array>
#include <deque>
#include <vector>

BOOST_AUTO_TEST_SUITE(calculate_next_suite)

// Testing for signature:
//     template <typename T, typename RandomAccessIterator>
//     constexpr auto indi::crc::calculate_next(
//         T last,
//         std::uint_fast8_t b,
//         RandomAccessIterator table_begin) noexcept ->
//             T
// with:
//     T: Constrained to be an unsigned integer type.
BOOST_AUTO_TEST_CASE(calculate_next_iterator_signature)
{
    constexpr auto uchar_ptr = static_cast<unsigned char const*>(nullptr);
    constexpr auto uint_ptr = static_cast<unsigned const*>(nullptr);
    constexpr auto ulint_ptr = static_cast<unsigned long const*>(nullptr);
    constexpr auto ullint_ptr = static_cast<unsigned long long const*>(nullptr);
    constexpr auto u8f_ptr = static_cast<std::uint_fast8_t*>(nullptr);
    constexpr auto u8l_ptr = static_cast<std::uint_least8_t*>(nullptr);
    constexpr auto u16f_ptr = static_cast<std::uint_fast16_t*>(nullptr);
    constexpr auto u16l_ptr = static_cast<std::uint_least16_t*>(nullptr);
    constexpr auto u32f_ptr = static_cast<std::uint_fast32_t*>(nullptr);
    constexpr auto u32l_ptr = static_cast<std::uint_least32_t*>(nullptr);
    constexpr auto u64f_ptr = static_cast<std::uint_fast64_t*>(nullptr);
    constexpr auto u64l_ptr = static_cast<std::uint_least64_t*>(nullptr);
    
    constexpr auto uchar_val = static_cast<unsigned char>(0u);
    constexpr auto u8f_val = std::uint_fast8_t{0u};
    constexpr auto u8l_val = std::uint_least8_t{0u};
    
    // Regular unsigned types.
	BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_next(0u, 0u, uint_ptr))>::value));
	BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_next(0u, 0uL, ulint_ptr))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_next(0u, uchar_val, ullint_ptr))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate_next(0uL, uchar_val, ullint_ptr))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate_next(0uLL, uchar_val, ullint_ptr))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned char,
		decltype(indi::crc::calculate_next(uchar_val, uchar_val, ullint_ptr))
        >::value));
    
    // 8-bit or less CRCs.
	BOOST_CHECK((std::is_same<
		std::uint_fast8_t,
		decltype(indi::crc::calculate_next(u8f_val, uchar_val, u8f_ptr))
        >::value));
	BOOST_CHECK((std::is_same<
		std::uint_fast8_t,
		decltype(indi::crc::calculate_next(u8f_val, uchar_val, u8l_ptr))
        >::value));
	BOOST_CHECK((std::is_same<
		std::uint_least8_t,
		decltype(indi::crc::calculate_next(u8l_val, uchar_val, u8f_ptr))
        >::value));
    
    // Non-pointer random access iterators.
    // std::vector
    auto const u16l_vtable = std::vector<std::uint_least16_t>{};
    auto const u64f_vtable = std::vector<std::uint_fast64_t>{};
    
    BOOST_CHECK((std::is_same<
        std::uint_fast16_t,
        decltype(indi::crc::calculate_next(std::uint_fast16_t{},
            uchar_val, u16l_vtable.begin()))
        >::value));
    BOOST_CHECK((std::is_same<
        std::uint_least64_t,
        decltype(indi::crc::calculate_next(std::uint_least64_t{},
            uchar_val, u64f_vtable.rbegin()))
        >::value));
    
    // std::deque
    auto const u16l_dtable = std::deque<std::uint_least16_t>{};
    auto const u64f_dtable = std::deque<std::uint_fast64_t>{};
    
    BOOST_CHECK((std::is_same<
        std::uint_fast16_t,
        decltype(indi::crc::calculate_next(std::uint_fast16_t{},
            uchar_val, u16l_dtable.begin()))
        >::value));
    BOOST_CHECK((std::is_same<
        std::uint_least64_t,
        decltype(indi::crc::calculate_next(std::uint_least64_t{},
            uchar_val, u64f_dtable.rbegin()))
        >::value));
}

// Testing for signature:
//     template <typename T, typename Table>
//     constexpr auto indi::crc::calculate_next(
//         T last,
//         std::uint_fast8_t b,
//         Table const& table) noexcept ->
//             T
// with:
//     T: Constrained to be an unsigned integer type.
//     Table: Constrained to be *not* a random-access iterator.
//         Must also have operator[](X) where X is an unsigned
//         integer type of at least 8 bits.
BOOST_AUTO_TEST_CASE(calculate_next_range_signature)
{
    constexpr auto uchar_val = static_cast<unsigned char>(0u);
    constexpr auto u8f_val = std::uint_fast8_t{0u};
    constexpr auto u8l_val = std::uint_least8_t{0u};
    
    unsigned char uc_ctable[256];
    unsigned int ui_ctable[300];
    
    auto const u16l_atable =
        std::array<std::uint_least16_t, 512>{};
    auto const u32f_atable =
        std::array<std::uint_fast32_t, 260>{};
    auto const u64f_atable =
        std::array<std::uint_fast64_t, 256>{};
    
    // Regular unsigned types.
	BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_next(0u, 0u, ui_ctable))>::value));
	BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_next(0u, 0uL, ui_ctable))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned int,
		decltype(indi::crc::calculate_next(0u, uchar_val, ui_ctable))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned long,
		decltype(indi::crc::calculate_next(0uL, uchar_val, u32f_atable))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned long long,
		decltype(indi::crc::calculate_next(0uLL, uchar_val, u64f_atable))
        >::value));
	BOOST_CHECK((std::is_same<
		unsigned char,
		decltype(indi::crc::calculate_next(uchar_val, uchar_val, uc_ctable))
        >::value));
    
    // Vectors.
    auto const u16l_vtable = std::vector<std::uint_least16_t>{};
    auto const u32f_vtable = std::vector<std::uint_fast32_t>{};
    auto const u64f_vtable = std::vector<std::uint_fast64_t>{};
    
    BOOST_CHECK((std::is_same<
        std::uint_fast16_t,
        decltype(indi::crc::calculate_next(std::uint_fast16_t{},
            uchar_val, u16l_vtable.begin()))
        >::value));
    BOOST_CHECK((std::is_same<
        std::uint_fast32_t,
        decltype(indi::crc::calculate_next(std::uint_fast32_t{},
            uchar_val, u32f_vtable.begin()))
        >::value));
    BOOST_CHECK((std::is_same<
        std::uint_least64_t,
        decltype(indi::crc::calculate_next(std::uint_least64_t{},
            uchar_val, u64f_vtable.rbegin()))
        >::value));
    
    // Deques are also random-access ranges!
    auto const u16l_dtable = std::deque<std::uint_least16_t>{};
    auto const u32f_dtable = std::deque<std::uint_fast32_t>{};
    auto const u64f_dtable = std::deque<std::uint_fast64_t>{};
    
    BOOST_CHECK((std::is_same<
        std::uint_fast16_t,
        decltype(indi::crc::calculate_next(std::uint_fast16_t{},
            uchar_val, u16l_dtable.begin()))
        >::value));
    BOOST_CHECK((std::is_same<
        std::uint_fast32_t,
        decltype(indi::crc::calculate_next(std::uint_fast32_t{},
            uchar_val, u32f_dtable.begin()))
        >::value));
    BOOST_CHECK((std::is_same<
        std::uint_least64_t,
        decltype(indi::crc::calculate_next(std::uint_least64_t{},
            uchar_val, u64f_dtable.rbegin()))
        >::value));
}

BOOST_AUTO_TEST_CASE(calculate_next_crc16)
{
    auto const table = indi::crc::generate_table<16>();
    unsigned int ctable[256];
    std::copy_n(table.begin(), 256, ctable);
    
    auto prev = 0u;
    auto next = indi::crc::calculate_next(prev, 't', table.begin());
    BOOST_CHECK_EQUAL(next, 0x2700u);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 'e', table);
    BOOST_CHECK_EQUAL(next, 0x2be7u);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 's', ctable);
    BOOST_CHECK_EQUAL(next, 0xaf2au);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 't', table.begin());
    BOOST_CHECK_EQUAL(next, 0xf82eu);
}

BOOST_AUTO_TEST_CASE(calculate_next_crc32)
{
    auto const table = indi::crc::generate_table<32>();
    unsigned long ctable[256];
    std::copy_n(table.begin(), 256, ctable);
    
    auto prev = 0uL;
    auto next = indi::crc::calculate_next(prev, 't', table.begin());
    BOOST_CHECK_EQUAL(next, 0x5768b525uL);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 'e', table);
    BOOST_CHECK_EQUAL(next, 0x768b2925uL);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 's', ctable);
    BOOST_CHECK_EQUAL(next, 0x827e7fe8uL);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 't', table.begin());
    BOOST_CHECK_EQUAL(next, 0xf93ba110uL);
}

BOOST_AUTO_TEST_CASE(calculate_next_crc64_ecma)
{
    auto const table = indi::crc::generate_table<64>(
        indi::crc::polynomials::crc64_ecma);
    unsigned long long ctable[256];
    std::copy_n(table.begin(), 256, ctable);
    
    auto prev = 0uLL;
    auto next = indi::crc::calculate_next(prev, 't', table.begin());
    BOOST_CHECK_EQUAL(next, 0x99ca0b06e7197349uLL);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 'e', table);
    BOOST_CHECK_EQUAL(next, 0x77dfccf6a41037b4uLL);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 's', ctable);
    BOOST_CHECK_EQUAL(next, 0x91d71afe9e8839d3uLL);
    
    prev = next;
    next = indi::crc::calculate_next(prev, 't', table.begin());
    BOOST_CHECK_EQUAL(next, 0x0eb07b92df17eaeeuLL);
}

BOOST_AUTO_TEST_SUITE_END()
