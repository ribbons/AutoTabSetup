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

class AppEventSink : public extensions::IAppEventSink
{
public:
	virtual ~AppEventSink(){}
	
	/// Called when a new document is opened/created
	virtual void OnNewDocument(extensions::IDocumentPtr& doc);
	
	/// Called when PN is closing (you are about to be unloaded!)
	virtual void OnAppClose(){}
	
	/// Called when the user switches to a different document
	virtual void OnDocSelected(extensions::IDocumentPtr& doc){}
	
	/// Called when the very first Scintilla window is created, used for loading external lexers
	virtual void OnFirstEditorCreated(HWND hWndScintilla){}
};
