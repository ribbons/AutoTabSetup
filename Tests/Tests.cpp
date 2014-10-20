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

	const int testMinIndent = 1;
	const int testMaxIndent = 25;
	const int testMaxAnalyse = 1000;

	finder.setMinIndent(testMinIndent);
	finder.setMaxIndent(testMaxIndent);
	BOOST_CHECK_NO_THROW(finder.getIndentSize());
	BOOST_CHECK_EQUAL(finder.getMinIndent(), testMinIndent);
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

BOOST_AUTO_TEST_CASE(indent_lengths)
{
	for(int count = 1; count <= 10; count++)
	{
		FindIndent finder;
		std::string spaces(count, ' ');

		BOOST_CHECK_EQUAL(finder.ProcessLine(spaces), true);
		BOOST_CHECK_EQUAL(finder.getTabStyle(), FindIndent::tsSpaces);

		if(count >= finder.getMinIndent() && count <= finder.getMaxIndent())
		{
			BOOST_CHECK_EQUAL(finder.getIndentSize(), count);
		}
		else
		{
			BOOST_CHECK_EQUAL(finder.getIndentSize(), FindIndent::indUnknown);
		}
	}
}

BOOST_AUTO_TEST_CASE(c_style_comments)
{
	FindIndent findTabs, findIndent;

	BOOST_CHECK_EQUAL(findTabs.ProcessLine(" *"), true);
	BOOST_CHECK_EQUAL(findTabs.ProcessLine(" *"), true);
	BOOST_CHECK_EQUAL(findTabs.ProcessLine("\t"), true);
	BOOST_CHECK_EQUAL(findTabs.getTabStyle(), FindIndent::tsTabs);

	BOOST_CHECK_EQUAL(findTabs.ProcessLine("  /*"), true);
	BOOST_CHECK_EQUAL(findTabs.ProcessLine("   *"), true);
	BOOST_CHECK_EQUAL(findTabs.ProcessLine("   *"), true);
	BOOST_CHECK_EQUAL(findTabs.getIndentSize(), 2);
}

BOOST_AUTO_TEST_CASE(blank_lines)
{
	FindIndent finder;

	BOOST_CHECK_EQUAL(finder.ProcessLine("    "), true);

	for(int count = 0; count < 9; count++)
	{
		BOOST_CHECK_EQUAL(finder.ProcessLine("\n"), true);
	}

	BOOST_CHECK_EQUAL(finder.getIndentSize(), 4);
}

BOOST_AUTO_TEST_CASE(line_continuation)
{
	FindIndent finder;

	BOOST_CHECK_EQUAL(finder.ProcessLine("unlink 'file1',"), true);
	BOOST_CHECK_EQUAL(finder.ProcessLine("       'file2';"), true);

	for(int count = 0; count < 9; count++)
	{
		BOOST_CHECK_EQUAL(finder.ProcessLine("\t"), true);
	}

	BOOST_CHECK_EQUAL(finder.getIndentSize(), FindIndent::indUnknown);
}
