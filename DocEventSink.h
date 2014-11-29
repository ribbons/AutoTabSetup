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

class DocEventSink : public extensions::IDocumentEventSink
{
public:
	DocEventSink(extensions::IDocumentPtr doc) : m_doc(doc){}

	virtual ~DocEventSink(){}

	/// Called when the scheme changes
	virtual void OnSchemeChange(const char* scheme);
	
	/// Called when the document closes
	virtual void OnDocClosing();

	/// Called after a document is loaded
	virtual void OnAfterLoad(){}

	/// Called before the document is saved
	virtual void OnBeforeSave(const wchar_t* filename){}

	/// Called after the document is saved
	virtual void OnAfterSave(){}

	/// Called when the document modified state changes
	virtual void OnModifiedChanged(bool modified){}

	/// Called when the document write protect state changes
	virtual void OnWriteProtectChanged(bool){}

private:
	extensions::IDocumentPtr m_doc;
};
