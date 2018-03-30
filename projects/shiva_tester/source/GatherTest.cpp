
//          Copyright Tunc Bahcecioglu 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <array>
#include <algorithm>

#include <boost/test/unit_test.hpp>
#include "StaticEnvironment.h"

#include <shiva\collective.h>
#include <shiva\distribution.h>

BOOST_AUTO_TEST_SUITE(GatherTest)


BOOST_AUTO_TEST_CASE(Gather)
{
	shiva::environment& env = StaticEnvironment::mpi_environment;
	shiva::communicator comm;
	int mpi_size = comm.size();
	int mpi_rank = comm.rank();

    std::vector<double> send_vec(2);
    const double coeff = 23.5;
    std::generate(std::begin(send_vec), std::end(send_vec), [=]() {
        return coeff * mpi_rank;
    });
    
    if (mpi_rank == 0) {
        std::vector<double> recv_vec(send_vec.size() * mpi_size);
        shiva::gather(0, comm, shiva::make_message(send_vec), shiva::make_message(recv_vec));
        for (size_t i = 0; i < mpi_size; ++i) {
            for (size_t j = 0; j < 2; ++j) {
                BOOST_CHECK_EQUAL(coeff * i, recv_vec[i * 2 + j]);
            }
        }
    } else {
        shiva::gather(0, comm, shiva::make_message(send_vec));
    }
}

BOOST_AUTO_TEST_CASE(GatherV)
{
	shiva::environment& env = StaticEnvironment::mpi_environment;
	shiva::communicator comm;
	int mpi_size = comm.size();
	int mpi_rank = comm.rank();
	
    const int n = 14;
	auto dist = shiva::make_equal_distribution(comm, n);
	const int local_size = std::get<0>(dist)[mpi_rank];
	std::vector<int> send_vec(local_size);

    for (int i = 0; i < local_size; ++i) {
        send_vec[(size_t)i] = mpi_rank;
    }

    if (mpi_rank == 0) {
        std::vector<int> recv_vec(n);
        shiva::gatherv(0, comm, dist, shiva::make_message(send_vec), shiva::make_message(recv_vec));

        for (size_t i = 0; i < mpi_size; ++i) {
            size_t size  = std::get<0>(dist)[i];
            size_t start = std::get<1>(dist)[i];

            for (size_t j = 0; j < size; ++j) {
                BOOST_CHECK_EQUAL(recv_vec[start + j], i);
            }
        }

    } else {
        shiva::gatherv(0, comm, dist, shiva::make_message(send_vec));
    }
}

BOOST_AUTO_TEST_SUITE_END()