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

BOOST_AUTO_TEST_CASE(polynomial_detail_crc_type)
{
	namespace detail = indi::crc::detail_;
	
	BOOST_CHECK((std::is_same<typename detail::crc_type<8>::type,
		std::uint_fast8_t>::value));
	BOOST_CHECK((std::is_same<typename detail::crc_type<16>::type,
		std::uint_fast16_t>::value));
	BOOST_CHECK((std::is_same<typename detail::crc_type<32>::type,
		std::uint_fast32_t>::value));
	BOOST_CHECK((std::is_same<typename detail::crc_type<64>::type,
		std::uint_fast64_t>::value));
	
	BOOST_CHECK((std::is_same<detail::crc_type_t<8>,
		std::uint_fast8_t>::value));
	BOOST_CHECK((std::is_same<detail::crc_type_t<16>,
		std::uint_fast16_t>::value));
	BOOST_CHECK((std::is_same<detail::crc_type_t<32>,
		std::uint_fast32_t>::value));
	BOOST_CHECK((std::is_same<detail::crc_type_t<64>,
		std::uint_fast64_t>::value));
}

BOOST_AUTO_TEST_CASE(to_koopman_polynomial)
{
	namespace polynomials = indi::crc::polynomials;
	
	// Check the return type.
	BOOST_CHECK((
		std::is_same<
			std::uint_fast8_t,
			decltype(polynomials::to_koopman<4, std::uint_fast8_t>(
				0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_least32_t,
			decltype(polynomials::to_koopman<32, std::uint_least32_t>(
				0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			unsigned,
			decltype(polynomials::to_koopman<8>(0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_fast64_t,
			decltype(polynomials::to_koopman<1>(
				std::uint_fast64_t{0x1u}))>::value));
	
	// Check return values.
	BOOST_CHECK_EQUAL(polynomials::to_koopman<1>(0b1u), 0b1u);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<2>(0b1u), 0b10u);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<4>(0b1u), 0b1000u);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<16>(0x8005u), 0xC002u);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<16>(0x1021u), 0x8810u);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<32>(0x04C11DB7uL),
		0x82608EDBuL);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<32>(0x1EDC6F41uL),
		0x8F6E37A0uL);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<64>(
		0x42F0E1EBA9EA3693uLL), 0xA17870F5D4F51B49uLL);
	BOOST_CHECK_EQUAL(polynomials::to_koopman<64>(
		0x000000000000001BuLL), 0x800000000000000DuLL);
	
	// Verify constexpr.
	constexpr auto p = polynomials::to_koopman<32>(0x741B8CD7uL);
	BOOST_CHECK_EQUAL(p, 0xBA0DC66BuL);
}

BOOST_AUTO_TEST_CASE(from_koopman_polynomial)
{
	namespace polynomials = indi::crc::polynomials;
	
	// Check the return type.
	BOOST_CHECK((
		std::is_same<
			std::uint_fast8_t,
			decltype(polynomials::from_koopman<4, std::uint_fast8_t>(
				0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_least32_t,
			decltype(polynomials::from_koopman<32, std::uint_least32_t>(
				0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			unsigned,
			decltype(polynomials::from_koopman<8>(0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_fast64_t,
			decltype(polynomials::from_koopman<1>(
				std::uint_fast64_t{0x1u}))>::value));
	
	// Check return values.
	BOOST_CHECK_EQUAL(polynomials::from_koopman<1>(0b1u), 0b1u);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<2>(0b10u), 0b1u);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<4>(0b1000u), 0b1u);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<16>(0xC002u), 0x8005u);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<16>(0x8810u), 0x1021u);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<32>(0x82608EDBuL),
		0x04C11DB7uL);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<32>(0x8F6E37A0uL),
		0x1EDC6F41uL);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<64>(
		0xA17870F5D4F51B49uLL), 0x42F0E1EBA9EA3693uLL);
	BOOST_CHECK_EQUAL(polynomials::from_koopman<64>(
		0x800000000000000DuLL), 0x000000000000001BuLL);
	
	// Verify constexpr.
	constexpr auto p = polynomials::from_koopman<32>(0xBA0DC66BuL);
	BOOST_CHECK_EQUAL(p, 0x741B8CD7uL);
}

BOOST_AUTO_TEST_CASE(reverse_polynomial)
{
	namespace polynomials = indi::crc::polynomials;
	namespace polynomials = indi::crc::polynomials;
	
	// Check the return type.
	BOOST_CHECK((
		std::is_same<
			std::uint_fast8_t,
			decltype(polynomials::reversed<4, std::uint_fast8_t>(
				0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_least32_t,
			decltype(polynomials::reversed<32, std::uint_least32_t>(
				0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			unsigned,
			decltype(polynomials::reversed<8>(0x1u))>::value));
	BOOST_CHECK((
		std::is_same<
			std::uint_fast64_t,
			decltype(polynomials::reversed<1>(
				std::uint_fast64_t{0x1u}))>::value));
	
	// Check return values.
	BOOST_CHECK_EQUAL(polynomials::reversed<1>(0b1u), 0b1u);;
	BOOST_CHECK_EQUAL(polynomials::reversed<2>(0b10u), 0b1u);
	BOOST_CHECK_EQUAL(polynomials::reversed<2>(0b1u), 0b10u);
	BOOST_CHECK_EQUAL(polynomials::reversed<4>(0b1u), 0b1000u);
	BOOST_CHECK_EQUAL(polynomials::reversed<4>(0b1000u), 0b1u);
	BOOST_CHECK_EQUAL(polynomials::reversed<16>(0x8005u), 0xA001u);
	BOOST_CHECK_EQUAL(polynomials::reversed<16>(0x1021u), 0x8408u);
	BOOST_CHECK_EQUAL(polynomials::reversed<32>(0x04C11DB7uL),
		0xEDB88320uL);
	BOOST_CHECK_EQUAL(polynomials::reversed<32>(0x1EDC6F41uL),
		0x82F63B78uL);
	BOOST_CHECK_EQUAL(polynomials::reversed<64>(
		0x42F0E1EBA9EA3693uLL), 0xC96C5795D7870F42uLL);
	BOOST_CHECK_EQUAL(polynomials::reversed<64>(
		0x000000000000001BuLL), 0xD800000000000000uLL);
	
	// Verify constexpr.
	constexpr auto p = polynomials::reversed<32>(0x741B8CD7uL);
	BOOST_CHECK_EQUAL(p, 0xEB31D82EuL);
}

BOOST_AUTO_TEST_SUITE_END()
