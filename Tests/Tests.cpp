#include "stdafx.h"
#include "../FindIndent.h"

#define BOOST_TEST_MODULE FindIndent test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(default_values)
{
	FindIndent finder;
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
}

BOOST_AUTO_TEST_CASE(blank_line)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine("", 0), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
}
