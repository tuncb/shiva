
//          Copyright Tunc Bahcecioglu 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <array>

#include <boost/test/unit_test.hpp>
#include "StaticEnvironment.h"

#include <shiva\collective.h>
#include <shiva\distribution.h>

BOOST_AUTO_TEST_SUITE(ScatterTest)

BOOST_AUTO_TEST_CASE(Scatter)
{
	shiva::environment& env = StaticEnvironment::mpi_environment;
	shiva::communicator comm;
	int mpi_size = comm.size();
	int mpi_rank = comm.rank();

	std::vector<double> recv_data(2);

	if (mpi_rank == 0) {
		std::vector<double> send_data(mpi_size * 2);
		for (int i = 0; i < mpi_size; ++i) {
			send_data[i*2]     = (double) (i * 2);
			send_data[i*2 + 1] = (double) (i * 2 + 1);
		}
		shiva::scatter(0, comm, shiva::make_message(send_data), shiva::make_message(recv_data) );
	} else {
		shiva::scatter(0, comm, shiva::make_message(recv_data) );
	}
	
	BOOST_CHECK_EQUAL(recv_data[0], (double)(mpi_rank * 2));
	BOOST_CHECK_EQUAL(recv_data[1], (double)(mpi_rank * 2 + 1));
}	

BOOST_AUTO_TEST_CASE(Scatterv)
{
	shiva::environment& env = StaticEnvironment::mpi_environment;
	shiva::communicator comm;

	int mpi_size = comm.size();
	int mpi_rank = comm.rank();
	
	const int n = 14;
	auto dist = shiva::make_equal_distribution(comm, n);
	const int local_size = std::get<0>(dist)[mpi_rank];
	std::vector<int> recv_data(local_size);

	if (mpi_rank == 0) {
		std::vector<int> send_data((size_t)n);
		for (int i = 0; i < n; ++i) {
			send_data[(size_t)i] = i;
		}
		shiva::scatterv(0, comm, shiva::make_message(send_data), dist, shiva::make_message(recv_data) );
	} else {
		shiva::scatterv(0, comm, dist, shiva::make_message(recv_data.data(), local_size) );
	}

	const int local_disp = std::get<1>(dist)[mpi_rank];
	for (int i = 0; i < local_size; ++i) {
		BOOST_CHECK_EQUAL(recv_data[i], local_disp + i);
	}
}	
	
BOOST_AUTO_TEST_SUITE_END()