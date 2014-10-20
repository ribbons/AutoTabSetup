#include <string>
#include <vector>

class FindIndent
{
private:
	int minIndent, maxIndent, maxAnalyseLines;
	int lines, indentLines, tabLines, spaceLines;
	int prevLineInd;
	std::vector<int> diffCounts;

public:
	typedef enum { tsUnknown, tsTabs, tsSpaces } TabStyle;

	static const int indUnknown = 0;

	FindIndent::FindIndent() : minIndent(2), maxIndent(8), maxAnalyseLines(100),
		lines(0), indentLines(0), tabLines(0), spaceLines(0),
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
