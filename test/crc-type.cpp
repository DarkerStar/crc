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

#include <cstdint>
#include <type_traits>

BOOST_AUTO_TEST_SUITE(crc_type_suite)

BOOST_AUTO_TEST_CASE(crc_types)
{
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<1>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<2>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<3>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<4>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<5>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<6>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<7>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        typename indi::crc::crc_type<8>::type>::value));
    
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<9>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<10>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<11>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<12>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<13>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<14>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<15>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        typename indi::crc::crc_type<16>::type>::value));
    
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<17>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<18>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<19>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<20>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<21>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<22>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<23>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<24>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<25>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<26>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<27>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<28>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<29>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<30>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<31>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        typename indi::crc::crc_type<32>::type>::value));
    
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<33>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<34>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<35>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<36>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<37>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<38>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<39>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<40>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<41>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<42>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<43>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<44>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<45>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<46>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<47>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<48>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<49>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<50>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<51>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<52>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<53>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<54>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<55>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<56>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<57>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<58>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<59>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<60>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<61>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<62>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<63>::type>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        typename indi::crc::crc_type<64>::type>::value));
}

BOOST_AUTO_TEST_CASE(crc_type_ts)
{
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<1>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<2>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<3>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<4>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<5>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<6>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<7>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast8_t,
        indi::crc::crc_type_t<8>>::value));
    
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<9>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<10>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<11>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<12>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<13>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<14>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<15>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast16_t,
        indi::crc::crc_type_t<16>>::value));
    
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<17>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<18>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<19>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<20>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<21>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<22>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<23>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<24>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<25>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<26>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<27>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<28>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<29>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<30>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<31>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast32_t,
        indi::crc::crc_type_t<32>>::value));
    
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<33>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<34>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<35>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<36>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<37>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<38>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<39>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<40>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<41>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<42>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<43>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<44>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<45>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<46>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<47>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<48>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<49>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<50>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<51>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<52>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<53>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<54>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<55>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<56>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<57>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<58>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<59>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<60>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<61>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<62>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<63>>::value));
    BOOST_CHECK((std::is_same<std::uint_fast64_t,
        indi::crc::crc_type_t<64>>::value));
}

BOOST_AUTO_TEST_SUITE_END()