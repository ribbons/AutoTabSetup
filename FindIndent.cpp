#include "stdafx.h"
#include "FindIndent.h"

bool FindIndent::ProcessLine(const char* buffer, int length)
{
	bool tabs = false;
	int spaces = 0;
	bool skip = false;

	for(int pos = 0; pos < length; pos++)
	{
		switch(buffer[pos])
		{
			case '\t':
				tabs = true;

				if(spaces > 0)
				{
					skip = true;
					goto EOL;
				}

				break;
			case ' ':
				spaces++;

				if(tabs)
				{
					skip = true;
					goto EOL;
				}

				break;
			case '*':
				skip = true;
				goto EOL;
			default:
				goto EOL;
		}
	}

EOL:

	if(!skip)
	{
		if(tabs)
		{
			tabLines++;
			indentLines++;
		}
		else if(spaces > 0)
		{
			spaceLines++;
			indentLines++;

			int difference = abs(spaces - prevLineInd);

			if(difference >= minIndent && difference <= maxIndent)
			{
				diffCounts[difference - minIndent]++;
			}
		}
	}

	return ++lines < maxAnalyseLines;
}

int FindIndent::getMinIndent()
{
	return minIndent;
}

void FindIndent::setMinIndent(int min)
{
	minIndent = min;
	diffCounts.resize(maxIndent - min + 1);
}

int FindIndent::getMaxIndent()
{
	return maxIndent;
}

void FindIndent::setMaxIndent(int max)
{
	maxIndent = max;
	diffCounts.resize(max - minIndent + 1);
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

	for(unsigned int i = 0; i < diffCounts.size(); i++)
	{
		if(diffCounts[i] > maxVal && diffCounts[i] > indentLines / 10)
		{
			maxPos = i + minIndent;
			maxVal = diffCounts[i];
		}
	}

	return maxPos;
}