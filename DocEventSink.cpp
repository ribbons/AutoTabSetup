#include "stdafx.h"
#include "DocEventSink.h"
#include "FindIndent.h"
#include <vector>

/// Called when the document closes
void DocEventSink::OnDocClosing()
{
	m_doc.reset();
}

/// Called after a document is loaded
void DocEventSink::OnAfterLoad()
{
	int numLines = m_doc->SendEditorMessage(SCI_GETLINECOUNT, (WPARAM)0, (LPARAM)0);

	FindIndent finder;

	for(int lineNum = 0; lineNum < numLines; lineNum++)
	{
		int lineLength = m_doc->SendEditorMessage(SCI_LINELENGTH, lineNum, (LPARAM)0);

		if(lineLength > 0)
		{
			std::vector<char> line;
			line.resize(lineLength);

			m_doc->SendEditorMessage(SCI_GETLINE, lineNum, &line[0]);

			if(!finder.ProcessLine(&line[0], line.size()))
			{
				break;
			}
		}
	}

	switch(finder.getTabStyle())
	{
		case finder.tsTabs:
			m_doc->SendEditorMessage(SCI_SETUSETABS, true, (LPARAM)0);
			break;

		case finder.tsSpaces:
			m_doc->SendEditorMessage(SCI_SETUSETABS, false, (LPARAM)0);
			break;
	}

	int indentSize = finder.getIndentSize();

	if(indentSize != FindIndent::indUnknown)
	{
		m_doc->SendEditorMessage(SCI_SETTABWIDTH, indentSize, (LPARAM)0);
	}
}