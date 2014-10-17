#include "stdafx.h"
#include "FindIndent.h"

bool FindIndent::ProcessLine(const char* buffer, int length)
{
	bool tabs = false;
	int spaces = 0;
	bool finished = false;

	for(int pos = 0; pos < length; pos++)
	{
		switch(buffer[pos])
		{
			case '\t':
				tabs = true;

				if(spaces > 0)
				{
					finished = true;
				}

				break;
			case ' ':
				spaces++;

				if(tabs)
				{
					finished = true;
				}

				break;
			default:
				finished = true;
		}

		if(finished)
		{
			break;
		}
	}

	if(tabs && spaces == 0)
	{
		tabLines++;
	}
	else if(spaces > 0 && !tabs)
	{
		spaceLines++;

		int difference = abs(spaces - prevLineInd);

		if(difference <= maxIndent)
		{
			diffCounts[difference - 1]++;
		}
	}

	return ++lines < maxAnalyseLines;
}

int FindIndent::getMaxIndent()
{
	return maxIndent;
}

void FindIndent::setMaxIndent(int max)
{
	maxIndent = max;
	diffCounts.resize(max);
}

int FindIndent::getMaxAnalyseLines()
{
	return maxAnalyseLines;
}

void FindIndent::setMaxAnalyseLines(int max)
{
	maxAnalyseLines = max;
}

FindIndent::TabStyle FindIndent::getTabStyle()
{
	if(tabLines > spaceLines)
	{
		return tsTabs;
	}
	else if(spaceLines > tabLines)
	{
		return tsSpaces;
	}

	return tsUnknown;
}

int FindIndent::getIndentSize()
{
	int maxPos = indUnknown;
	int maxVal = 0;

	for(int i = 0; i < maxIndent; i++)
	{
		if(diffCounts[i] > maxVal)
		{
			maxPos = i + 1;
			maxVal = diffCounts[i];
		}
	}

	return maxPos;
}