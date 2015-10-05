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

#include "Common.h"
#include "DocEventSink.h"
#include <FindIndent.h>
#include <vector>

/// Called when the document closes
void DocEventSink::OnDocClosing()
{
	m_doc.reset();
}

/// Called when the scheme changes
void DocEventSink::OnSchemeChange(const char* scheme)
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
