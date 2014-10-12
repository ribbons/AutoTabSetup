class FindIndent
{
private:
	int lines;
	int tabLines;
	int spaceLines;

public:
	typedef enum { tsUnknown, tsTabs, tsSpaces } TabStyle;

	FindIndent::FindIndent() : lines(0), tabLines(0), spaceLines(0) {}
	
	bool ProcessLine(const char* buffer, int length);
	
	TabStyle getTabStyle();
};
