#include "stdafx.h"
#include "../FindIndent.h"

#define BOOST_TEST_MODULE FindIndent test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(default_values)
{
	FindIndent finder;
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
}

BOOST_AUTO_TEST_CASE(empty_string)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine(""), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
}

BOOST_AUTO_TEST_CASE(single_tab)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine("\t"), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsTabs);
}

BOOST_AUTO_TEST_CASE(single_space)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine(" "), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsSpaces);
}

BOOST_AUTO_TEST_CASE(tab_space)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine("\t "), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
}

BOOST_AUTO_TEST_CASE(space_tab)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine(" \t"), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
}