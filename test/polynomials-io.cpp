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

#include "indi/crc-io.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(polynomials_io_suite)

BOOST_AUTO_TEST_CASE(polynomial_to_string)
{
	// Check that the max ordinal is correct.
	BOOST_CHECK_EQUAL(indi::crc::polynomials::to_string<3>(0u), "x^3");
	BOOST_CHECK_EQUAL(indi::crc::polynomials::to_string<16>(0u),
        "x^16");
	
	// Check the constant term.
	BOOST_CHECK_EQUAL(indi::crc::polynomials::to_string<5>(1u),
		"x^5 + 1");
	BOOST_CHECK_EQUAL(indi::crc::polynomials::to_string<8>(1u),
		"x^8 + 1");
	
	// Check the "x" term.
	BOOST_CHECK_EQUAL(indi::crc::polynomials::to_string<5>(2u),
		"x^5 + x");
	BOOST_CHECK_EQUAL(indi::crc::polynomials::to_string<12>(2u),
		"x^12 + x");
	
	// Check the general result.
	namespace polys = indi::crc::polynomials;
	BOOST_CHECK_EQUAL(polys::to_string<16>(polys::crc16),
		"x^16 + x^15 + x^2 + 1");
	BOOST_CHECK_EQUAL(polys::to_string<32>(polys::crc32),
		"x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + "
			"x^8 + x^7 + x^5 + x^4 + x^2 + x + 1");
	BOOST_CHECK_EQUAL(polys::to_string<64>(polys::crc64_iso),
		"x^64 + x^4 + x^3 + x + 1");
	BOOST_CHECK_EQUAL(polys::to_string<64>(polys::crc64_ecma),
		"x^64 + x^62 + x^57 + x^55 + x^54 + x^53 + x^52 + x^47 + "
			"x^46 + x^45 + x^40 + x^39 + x^38 + x^37 + x^35 + "
			"x^33 + x^32 + x^31 + x^29 + x^27 + x^24 + x^23 + "
			"x^22 + x^21 + x^19 + x^17 + x^13 + x^12 + x^10 + "
			"x^9 + x^7 + x^4 + x + 1");
}

/* Not yet implemented, but will be.
BOOST_AUTO_TEST_CASE(polynomial_1_to_string)
{
	namespace polynomials = indi::crc::polynomials;
	BOOST_CHECK_EQUAL(polynomials::to_string<1>(0u), "x");
	BOOST_CHECK_EQUAL(polynomials::to_string<1>(1u), "x + 1");
}
*/

BOOST_AUTO_TEST_SUITE_END()
