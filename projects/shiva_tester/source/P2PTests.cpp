
//          Copyright Tunc Bahcecioglu 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>

#include <shiva/tagdispatcher.h>
#include <shiva\point2point.h>

BOOST_AUTO_TEST_SUITE(P2PTests)

BOOST_AUTO_TEST_CASE(StandardSRTest)
{
	shiva::communicator world;
	const int mpi_size = world.size();
	const int mpi_rank = world.rank();

	double msg_1 = 23.3;
	double msg_2 = 20.3;

	if (mpi_rank == 0) {
		shiva::send(world, shiva::make_message(msg_1), 1);
		shiva::send(world, shiva::make_message(msg_2), 2);
	} 

	if (mpi_rank == 1) {
		double rec;
		shiva::receive(world, shiva::make_message(rec));
		BOOST_CHECK_EQUAL(rec, msg_1);
	} else if (mpi_rank == 2) {
		double rec;
		shiva::receive(world, shiva::make_message(rec));
		BOOST_CHECK_EQUAL(rec, msg_2);
	}
}

BOOST_AUTO_TEST_CASE(StandardSRProtocolTest)
{
	shiva::communicator world;
	const int mpi_size = world.size();
	const int mpi_rank = world.rank();

	double msg_1 = 23.3;
	double msg_2 = 20.3;

	if (mpi_rank == 0) {
		shiva::send(world, shiva::make_message(msg_1), 1, shiva::protocol::synchronous);
		shiva::send(world, shiva::make_message(msg_2), 2, shiva::protocol::ready);
	} 

	if (mpi_rank == 1) {
		double rec;
		shiva::receive(world, shiva::make_message(rec));
		BOOST_CHECK_EQUAL(rec, msg_1);
	} else if (mpi_rank == 2) {
		double rec;
		shiva::receive(world, shiva::make_message(rec));
		BOOST_CHECK_EQUAL(rec, msg_2);
	}
}
	
BOOST_AUTO_TEST_SUITE_END()