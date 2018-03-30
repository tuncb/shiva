
//          Copyright Tunc Bahcecioglu 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include "StaticEnvironment.h"
#include <iostream>
#include <array>

#include <shiva\collective.h>

BOOST_AUTO_TEST_SUITE(BroadcastTest)

BOOST_AUTO_TEST_CASE(Broadcast)
{
	shiva::environment& env = StaticEnvironment::mpi_environment;
	shiva::communicator comm;

	int mpi_size = comm.size();
	int mpi_rank = comm.rank();
	
	std::array<float, 5> arr_correct = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

	std::array<float, 5> arr;
	if (mpi_rank == 0) {
		arr[0] = 1.0f;
		arr[1] = 2.0f;
		arr[2] = 3.0f;
		arr[3] = 4.0f;
		arr[4] = 5.0f;

		shiva::broadcast(0, comm, shiva::make_message(arr) );
	} else {
		shiva::broadcast(0, comm, shiva::make_message(arr) );
	}
	
	BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(arr), std::end(arr), std::begin(arr_correct), std::end(arr_correct) );
}	
	
BOOST_AUTO_TEST_SUITE_END()