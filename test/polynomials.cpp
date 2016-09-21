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

BOOST_AUTO_TEST_SUITE(polynomials_suite)

BOOST_AUTO_TEST_CASE(crc16_polynomial_values)
{
	namespace polynomials = indi::crc::polynomials;
	BOOST_CHECK_EQUAL(polynomials::crc16_ibm, 0x8005u);
	BOOST_CHECK_EQUAL(polynomials::crc16_ccitt, 0x1021u);
	BOOST_CHECK_EQUAL(polynomials::crc16_t10_dif, 0x8BB7u);
	BOOST_CHECK_EQUAL(polynomials::crc16_dnp, 0x3D65u);
	BOOST_CHECK_EQUAL(polynomials::crc16_dect, 0x0589u);
	BOOST_CHECK_EQUAL(polynomials::crc16_arinc, 0xA02Bu);
	BOOST_CHECK_EQUAL(polynomials::crc16_chakravarty, 0x2F15u);
	
	// "CRC16" by default is CRC16-IBM.
	BOOST_CHECK_EQUAL(polynomials::crc16, polynomials::crc16_ibm);
}

BOOST_AUTO_TEST_CASE(crc32_polynomial_values)
{
	namespace polynomials = indi::crc::polynomials;
	BOOST_CHECK_EQUAL(polynomials::crc32_ansi, 0x04C11DB7uL);
	BOOST_CHECK_EQUAL(polynomials::crc32_ieee, 0x04C11DB7uL);
	BOOST_CHECK_EQUAL(polynomials::crc32c, 0x1EDC6F41uL);
	BOOST_CHECK_EQUAL(polynomials::crc32k, 0x741B8CD7uL);
	BOOST_CHECK_EQUAL(polynomials::crc32q, 0x814141ABuL);
	
	// "CRC32" by default is CRC32-IEEE.
	BOOST_CHECK_EQUAL(polynomials::crc32, polynomials::crc32_ieee);
}

BOOST_AUTO_TEST_CASE(crc64_polynomial_values)
{
	namespace polynomials = indi::crc::polynomials;
	BOOST_CHECK_EQUAL(polynomials::crc64_iso, 0x000000000000001BuLL);
	BOOST_CHECK_EQUAL(polynomials::crc64_ecma, 0x42F0E1EBA9EA3693uLL);
}

BOOST_AUTO_TEST_CASE(polynomial_detail_ones)
{
	namespace detail = indi::crc::detail_;
	
	// Check the return type.
	BOOST_CHECK((
		std::is_same<
			std::uint_fast8_t,
			decltype(detail::ones<1, std::uint_fast8_t>())>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_least8_t,
			decltype(detail::ones<1, std::uint_least8_t>())>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_fast32_t,
			decltype(detail::ones<1, std::uint_fast32_t>())>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_least32_t,
			decltype(detail::ones<1, std::uint_least32_t>())>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_fast16_t,
			decltype(detail::ones<16, std::uint_fast16_t>())>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_fast64_t,
			decltype(detail::ones<24, std::uint_fast64_t>())>::value));
	BOOST_CHECK((
		std::is_same<
			std::size_t,
			decltype(detail::ones<15, std::size_t>())>::value));
	
	// Check return values.
	BOOST_CHECK_EQUAL((detail::ones<1, std::uint_fast8_t>()), 0b1u);
	BOOST_CHECK_EQUAL((detail::ones<2, std::uint_fast8_t>()), 0b11u);
	BOOST_CHECK_EQUAL((detail::ones<3, std::uint_fast8_t>()), 0b111u);
	BOOST_CHECK_EQUAL((detail::ones<7, std::uint_fast8_t>()), 0x7fu);
	BOOST_CHECK_EQUAL((detail::ones<8, std::uint_fast8_t>()), 0xffu);
	
	BOOST_CHECK_EQUAL((detail::ones<7, std::uint_fast16_t>()),
		0x7fu);
	BOOST_CHECK_EQUAL((detail::ones<9, std::uint_fast16_t>()),
		0x1ffu);
	BOOST_CHECK_EQUAL((detail::ones<14, std::uint_fast16_t>()),
		0x3fffu);
	BOOST_CHECK_EQUAL((detail::ones<16, std::uint_fast16_t>()),
		0xffffu);
	
	BOOST_CHECK_EQUAL((detail::ones<13, std::uint_fast32_t>()),
		0x1fffuL);
	BOOST_CHECK_EQUAL((detail::ones<22, std::uint_fast32_t>()),
		0x3fffffuL);
	BOOST_CHECK_EQUAL((detail::ones<32, std::uint_fast32_t>()),
		0xffffffffuL);
	
	BOOST_CHECK_EQUAL((detail::ones<37, std::uint_fast64_t>()),
		0x1fffffffffuLL);
	BOOST_CHECK_EQUAL((detail::ones<64, std::uint_fast64_t>()),
		0xffffffffffffffffuLL);
	
	// Verify constexpr.
	char dummy[detail::ones<3, std::size_t>()];
	BOOST_CHECK_MESSAGE(sizeof(dummy) == 0b111u, "not constexpr");
}

BOOST_AUTO_TEST_CASE(to_koopman_polynomial)
{
	namespace polynomials = indi::crc::polynomials;
}

BOOST_AUTO_TEST_CASE(from_koopman_polynomial)
{
	namespace polynomials = indi::crc::polynomials;
}

BOOST_AUTO_TEST_CASE(reverse_polynomial)
{
	namespace polynomials = indi::crc::polynomials;
}

BOOST_AUTO_TEST_SUITE_END()
