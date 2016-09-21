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
	BOOST_CHECK_EQUAL(polynomials::crc16_chakravarty,
		0x2F15u);
	
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

BOOST_AUTO_TEST_SUITE_END()
