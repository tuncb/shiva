
//          Copyright Tunc Bahcecioglu 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <array>
#include <vector>


#include <boost/test/unit_test.hpp>
#include "StaticEnvironment.h"
#include <shiva\message.h>

template <typename T>
inline void run_fundemental_message_test(T t)
{
	T var = t;
	auto msg = shiva::make_message(var);
	BOOST_CHECK_EQUAL(msg.data, &var);
	BOOST_CHECK_EQUAL(msg.size, 1);
	BOOST_CHECK_EQUAL(msg.datatype, shiva::detail::mpi_datatype<T>::value);
}

BOOST_AUTO_TEST_SUITE(MakemessageTest)

BOOST_AUTO_TEST_CASE(MakemessageFundemental)
{
	run_fundemental_message_test<char>(5);
	run_fundemental_message_test<short>(5);
	run_fundemental_message_test<int>(5);
	run_fundemental_message_test<long>(5);
	run_fundemental_message_test<float>(5.0f);
	run_fundemental_message_test<double>(5.0);
	run_fundemental_message_test<__int64>(5);
}	

BOOST_AUTO_TEST_CASE(MakemessageStaticArray)
{
	float float_1d[5];
	auto msg_1d = shiva::make_message(float_1d,5);
	BOOST_CHECK_EQUAL(msg_1d.data, &float_1d[0]);
	BOOST_CHECK_EQUAL(msg_1d.size, 5);
	BOOST_CHECK_EQUAL(msg_1d.datatype, shiva::detail::mpi_datatype<float>::value);
}	

BOOST_AUTO_TEST_CASE(MakemessageStdArray)
{
	std::array<int,5> arr;
	auto msg = shiva::make_message(arr);
	BOOST_CHECK_EQUAL(msg.data, arr.data());
	BOOST_CHECK_EQUAL(msg.size, 5);
	BOOST_CHECK_EQUAL(msg.datatype, shiva::detail::mpi_datatype<int>::value);
}	

BOOST_AUTO_TEST_CASE(MakemessageStdVector)
{
	std::vector<int> arr(5);
	auto msg = shiva::make_message(arr);
	BOOST_CHECK_EQUAL(msg.data, arr.data());
	BOOST_CHECK_EQUAL(msg.size, 5);
	BOOST_CHECK_EQUAL(msg.datatype, shiva::detail::mpi_datatype<int>::value);
}

	
BOOST_AUTO_TEST_SUITE_END()