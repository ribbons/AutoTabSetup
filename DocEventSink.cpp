#include "stdafx.h"
#include "DocEventSink.h"
#include <vector>

const int MAX_ANALYSE_LINES = 100;

/// Called when the document closes
void DocEventSink::OnDocClosing()
{
	m_doc.reset();
}

/// Called after a document is loaded
void DocEventSink::OnAfterLoad()
{
	int numLines = m_doc->SendEditorMessage(SCI_GETLINECOUNT, (WPARAM)0, (LPARAM)0);
	
	if(numLines < MAX_ANALYSE_LINES)
	{
		numLines = MAX_ANALYSE_LINES;
	}
	
	int tabLines = 0;
	int spaceLines = 0;

	for(int lineNum = 0; lineNum < numLines; lineNum++)
	{
		int lineLength = m_doc->SendEditorMessage(SCI_LINELENGTH, lineNum, (LPARAM)0);

		if(lineLength > 0)
		{
			std::vector<char> line;

			line.resize(lineLength);
			m_doc->SendEditorMessage(SCI_GETLINE, lineNum, &line[0]);

			bool tabs = false;
			bool spaces = false;
			bool finished = false;

			for(int pos = 0; pos < lineLength; pos++)
			{
				switch(line[pos])
				{
					case '\t':
						if(spaces)
						{
							finished = true;
						}
						else
						{
							tabs = true;
						}

						break;
					case ' ':
						if(tabs)
						{
							finished = true;
						}
						else
						{
							spaces = true;
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
		}
	}

	if(tabLines > spaceLines)
	{
		m_doc->SendEditorMessage(SCI_SETUSETABS, true, (LPARAM)0);
	}
	else if(spaceLines > tabLines)
	{
		m_doc->SendEditorMessage(SCI_SETUSETABS, false, (LPARAM)0);
	}
}