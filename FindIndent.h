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

#include <string>
#include <vector>

class FindIndent
{
private:
	int minIndent, maxIndent, maxAnalyseLines;
	int lines, thresholdLines, tabLines, spaceLines;
	int prevLineInd;
	std::vector<int> diffCounts;

public:
	typedef enum { tsUnknown, tsTabs, tsSpaces } TabStyle;

	static const int indUnknown = 0;

	FindIndent::FindIndent() : minIndent(2), maxIndent(8), maxAnalyseLines(500),
		lines(0), thresholdLines(0), tabLines(0), spaceLines(0),
		prevLineInd(0),
		diffCounts(maxIndent - minIndent + 1) {}
	
	bool ProcessLine(const char* buffer, int length);

	bool ProcessLine(const std::string text)
	{
		return ProcessLine(text.c_str(), text.length());
	}

	int getMinIndent();

	void setMinIndent(int min);

	int getMaxIndent();

	void setMaxIndent(int max);

	int getMaxAnalyseLines();

	void setMaxAnalyseLines(int max);

	TabStyle getTabStyle();

	int getIndentSize();
};
