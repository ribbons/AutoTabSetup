/* 
 * This file is part of Auto Tab Setup.
 * Copyright © 2014 by the authors - see the AUTHORS file for details.
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"
#include "FindIndent.h"

bool FindIndent::ProcessLine(const char* buffer, int length)
{
	bool tabs = false;
	int spaces = 0;
	bool skip = false;

	while(length > 0)
	{
		switch(buffer[length - 1])
		{
			case '\r':
			case '\n':
				length--;
				break;

			default:
				goto ENDTRIM;
		}
	}

ENDTRIM:

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
			thresholdLines++;
		}
		else 
		{
			if(spaces > 0)
			{
				spaceLines++;
			}

			if(length > 0)
			{
				int difference = abs(spaces - prevLineInd);
				prevLineInd = spaces;

				if(difference >= minIndent && difference <= maxIndent)
				{
					diffCounts[difference - minIndent]++;
					thresholdLines++;
				}
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
		if(diffCounts[i] > maxVal && diffCounts[i] > thresholdLines / 10)
		{
			maxPos = i + minIndent;
			maxVal = diffCounts[i];
		}
	}

	return maxPos;
}
