
//          Copyright Tunc Bahcecioglu 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include "StaticEnvironment.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(InitializationTests)

BOOST_AUTO_TEST_CASE(Initialization)
{
	shiva::environment& env = StaticEnvironment::mpi_environment;

    BOOST_REQUIRE(env.is_initialized() );
	std::cout << "Process name = " << env.get_processor_name() << std::endl;
}	
	
BOOST_AUTO_TEST_SUITE_END()