#include "stdafx.h"
#include "FindIndent.h"

const int MAX_ANALYSE_LINES = 100;

bool FindIndent::ProcessLine(const char* buffer, int length)
{
	bool tabs = false;
	bool spaces = false;
	bool finished = false;

	for(int pos = 0; pos < length; pos++)
	{
		switch(buffer[pos])
		{
			case '\t':
				tabs = true;

				if(spaces)
				{
					finished = true;
				}

				break;
			case ' ':
				spaces = true;

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

	if(tabs && !spaces)
	{
		tabLines++;
	}
	else if(spaces && !tabs)
	{
		spaceLines++;
	}

	return ++lines < MAX_ANALYSE_LINES;
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