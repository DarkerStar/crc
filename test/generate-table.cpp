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

#include <array>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

// Helper function to load a CRC table from a datafile.
// 
// The datafile should be a plain text file with 256 hexadecimal values,
// one on each line, optionally prefixed with "0x" or "0X".
auto load_crc_table(std::string file)
{
	auto table = std::vector<unsigned long long>{};
	table.reserve(256);
	
	auto in = std::ifstream{"data/table-" + file};
	
	auto line = std::string{};
	while (std::getline(in, line))
		table.emplace_back(std::stoull(line, nullptr, 16));
	
	return table;
};

BOOST_AUTO_TEST_SUITE(generate_table_suite)

BOOST_AUTO_TEST_CASE(generate_table_return_types)
{
	BOOST_CHECK((std::is_same<
		std::array<unsigned int, 256>,
		decltype(indi::crc::generate_table<1, unsigned int>(
			0u))>::value));
	BOOST_CHECK((std::is_same<
		std::array<std::uint_fast8_t, 256>,
		decltype(indi::crc::generate_table<5, std::uint_fast8_t>(
			std::uint_fast8_t{}))>::value));
	BOOST_CHECK((std::is_same<
		std::array<std::uint_least32_t, 256>,
		decltype(indi::crc::generate_table<16, std::uint_least32_t>(
			std::uint_least32_t{}))>::value));
	BOOST_CHECK((std::is_same<
		std::array<std::uint_fast64_t, 256>,
		decltype(indi::crc::generate_table<64, std::uint_fast64_t>(
			std::uint_fast64_t{}))>::value));
	
	BOOST_CHECK((std::is_same<
		std::array<unsigned int, 256>,
		decltype(indi::crc::generate_table<5>(0u))>::value));
	BOOST_CHECK((std::is_same<
		std::array<std::uint_fast8_t, 256>,
		decltype(indi::crc::generate_table<8>(
			std::uint_fast8_t{}))>::value));
	BOOST_CHECK((std::is_same<
		std::array<std::uint_least16_t, 256>,
		decltype(indi::crc::generate_table<15>(
			std::uint_least16_t{}))>::value));
	BOOST_CHECK((std::is_same<
		std::array<std::uint_fast64_t, 256>,
		decltype(indi::crc::generate_table<64>(
			std::uint_fast64_t{}))>::value));
	
	// Check the versions with defaulted polynomials.
	BOOST_CHECK((std::is_same<
		std::array<std::uint_fast16_t, 256>,
		decltype(indi::crc::generate_table<16>())>::value));
	BOOST_CHECK((std::is_same<
		std::array<std::uint_fast32_t, 256>,
		decltype(indi::crc::generate_table<32>())>::value));
}

BOOST_AUTO_TEST_CASE(generate_table_crc5_epc_values)
{
	constexpr auto expected = std::array<unsigned char, 256>{
		0x00u, 0x0Fu, 0x1Eu, 0x11u, 0x19u, 0x16u, 0x07u, 0x08u,
		0x17u, 0x18u, 0x09u, 0x06u, 0x0Eu, 0x01u, 0x10u, 0x1Fu,
		0x0Bu, 0x04u, 0x15u, 0x1Au, 0x12u, 0x1Du, 0x0Cu, 0x03u,
		0x1Cu, 0x13u, 0x02u, 0x0Du, 0x05u, 0x0Au, 0x1Bu, 0x14u,
		0x16u, 0x19u, 0x08u, 0x07u, 0x0Fu, 0x00u, 0x11u, 0x1Eu,
		0x01u, 0x0Eu, 0x1Fu, 0x10u, 0x18u, 0x17u, 0x06u, 0x09u,
		0x1Du, 0x12u, 0x03u, 0x0Cu, 0x04u, 0x0Bu, 0x1Au, 0x15u,
		0x0Au, 0x05u, 0x14u, 0x1Bu, 0x13u, 0x1Cu, 0x0Du, 0x02u,
		0x09u, 0x06u, 0x17u, 0x18u, 0x10u, 0x1Fu, 0x0Eu, 0x01u,
		0x1Eu, 0x11u, 0x00u, 0x0Fu, 0x07u, 0x08u, 0x19u, 0x16u,
		0x02u, 0x0Du, 0x1Cu, 0x13u, 0x1Bu, 0x14u, 0x05u, 0x0Au,
		0x15u, 0x1Au, 0x0Bu, 0x04u, 0x0Cu, 0x03u, 0x12u, 0x1Du,
		0x1Fu, 0x10u, 0x01u, 0x0Eu, 0x06u, 0x09u, 0x18u, 0x17u,
		0x08u, 0x07u, 0x16u, 0x19u, 0x11u, 0x1Eu, 0x0Fu, 0x00u,
		0x14u, 0x1Bu, 0x0Au, 0x05u, 0x0Du, 0x02u, 0x13u, 0x1Cu,
		0x03u, 0x0Cu, 0x1Du, 0x12u, 0x1Au, 0x15u, 0x04u, 0x0Bu,
		0x12u, 0x1Du, 0x0Cu, 0x03u, 0x0Bu, 0x04u, 0x15u, 0x1Au,
		0x05u, 0x0Au, 0x1Bu, 0x14u, 0x1Cu, 0x13u, 0x02u, 0x0Du,
		0x19u, 0x16u, 0x07u, 0x08u, 0x00u, 0x0Fu, 0x1Eu, 0x11u,
		0x0Eu, 0x01u, 0x10u, 0x1Fu, 0x17u, 0x18u, 0x09u, 0x06u,
		0x04u, 0x0Bu, 0x1Au, 0x15u, 0x1Du, 0x12u, 0x03u, 0x0Cu,
		0x13u, 0x1Cu, 0x0Du, 0x02u, 0x0Au, 0x05u, 0x14u, 0x1Bu,
		0x0Fu, 0x00u, 0x11u, 0x1Eu, 0x16u, 0x19u, 0x08u, 0x07u,
		0x18u, 0x17u, 0x06u, 0x09u, 0x01u, 0x0Eu, 0x1Fu, 0x10u,
		0x1Bu, 0x14u, 0x05u, 0x0Au, 0x02u, 0x0Du, 0x1Cu, 0x13u,
		0x0Cu, 0x03u, 0x12u, 0x1Du, 0x15u, 0x1Au, 0x0Bu, 0x04u,
		0x10u, 0x1Fu, 0x0Eu, 0x01u, 0x09u, 0x06u, 0x17u, 0x18u,
		0x07u, 0x08u, 0x19u, 0x16u, 0x1Eu, 0x11u, 0x00u, 0x0Fu,
		0x0Du, 0x02u, 0x13u, 0x1Cu, 0x14u, 0x1Bu, 0x0Au, 0x05u,
		0x1Au, 0x15u, 0x04u, 0x0Bu, 0x03u, 0x0Cu, 0x1Du, 0x12u,
		0x06u, 0x09u, 0x18u, 0x17u, 0x1Fu, 0x10u, 0x01u, 0x0Eu,
		0x11u, 0x1Eu, 0x0Fu, 0x00u, 0x08u, 0x07u, 0x16u, 0x19u
	};
	
	auto result = indi::crc::generate_table<5>(0x09u);
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_CASE(generate_table_crc16_values)
{
	auto const expected = load_crc_table("crc16");
	
	auto result = indi::crc::generate_table<16>(
		indi::crc::polynomials::crc16);
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_CASE(generate_table_crc16_ccitt_values)
{
	auto const expected = load_crc_table("crc16-ccitt");
	
	auto result = indi::crc::generate_table<16>(
		indi::crc::polynomials::crc16_ccitt);
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_CASE(generate_table_crc32_values)
{
	auto const expected = load_crc_table("crc32");
	
	auto result = indi::crc::generate_table<32>(
		indi::crc::polynomials::crc32);
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_CASE(generate_table_crc32c_values)
{
	auto const expected = load_crc_table("crc32c");
	
	auto result = indi::crc::generate_table<32>(
		indi::crc::polynomials::crc32c);
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_CASE(generate_table_crc64_ecma_values)
{
	auto const expected = load_crc_table("crc64-ecma");
	
	auto result = indi::crc::generate_table<64>(
		indi::crc::polynomials::crc64_ecma);
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_CASE(generate_table_crc16_default)
{
	auto const expected = indi::crc::generate_table<16>(
		indi::crc::polynomials::crc16);
	
	auto result = indi::crc::generate_table<16>();
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_CASE(generate_table_crc32_default)
{
	auto const expected = indi::crc::generate_table<32>(
		indi::crc::polynomials::crc32);
	
	auto result = indi::crc::generate_table<32>();
	
	using std::begin;
	using std::end;
	
	BOOST_CHECK_EQUAL_COLLECTIONS(
		begin(expected), end(expected),
		begin(result), end(result));
}

BOOST_AUTO_TEST_SUITE_END()
