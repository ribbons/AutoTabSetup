#include "stdafx.h"
#include "../FindIndent.h"

#define BOOST_TEST_MODULE FindIndent test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(default_values)
{
	FindIndent finder;
	BOOST_CHECK_EQUAL(finder.getMaxIndent(), 8);
	BOOST_CHECK_EQUAL(finder.getMaxAnalyseLines(), 100);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
	BOOST_CHECK_EQUAL(finder.getIndentSize(), FindIndent::indUnknown);
}

BOOST_AUTO_TEST_CASE(accessors)
{
	FindIndent finder;

	const int testMaxIndent = 25;
	const int testMaxAnalyse = 1000;

	finder.setMaxIndent(testMaxIndent);
	BOOST_CHECK_NO_THROW(finder.getIndentSize());
	BOOST_CHECK_EQUAL(finder.getMaxIndent(), testMaxIndent);

	finder.setMaxAnalyseLines(testMaxAnalyse);
	BOOST_CHECK_EQUAL(finder.getMaxAnalyseLines(), testMaxAnalyse);
}

BOOST_AUTO_TEST_CASE(empty_string)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine(""), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsUnknown);
	BOOST_CHECK_EQUAL(finder.getIndentSize(), FindIndent::indUnknown);
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

BOOST_AUTO_TEST_CASE(two_spaces)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine("  "), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsSpaces);
	BOOST_CHECK_EQUAL(finder.getIndentSize(), 2);
}

BOOST_AUTO_TEST_CASE(four_spaces)
{
	FindIndent finder;
	
	BOOST_CHECK_EQUAL(finder.ProcessLine("    "), true);
	BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsSpaces);
	BOOST_CHECK_EQUAL(finder.getIndentSize(), 4);
}
