
//          Copyright Tunc Bahcecioglu 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include "StaticEnvironment.h"
#include <vector>
#include <array>

#include <shiva\distribution.h>

BOOST_AUTO_TEST_SUITE(DistributionTest)

BOOST_AUTO_TEST_CASE(EqualDistribution)
{
	shiva::environment& env = StaticEnvironment::mpi_environment;
	shiva::communicator comm;
	const int n = 11;
	std::vector<int> data((size_t)n);

	auto dist = shiva::make_equal_distribution(comm, n);

	auto& sizes = std::get<0>(dist);
	auto& displacements = std::get<1>(dist);

	std::array<int, 3> sizes_correct = {4, 4, 3};
	std::array<int, 3> displacements_correct = {0, 4, 8};

	BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(sizes), std::end(sizes), std::begin(sizes_correct), std::end(sizes_correct));
	BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(displacements), std::end(displacements), std::begin(displacements_correct), std::end(displacements_correct));
}	
	
BOOST_AUTO_TEST_SUITE_END()