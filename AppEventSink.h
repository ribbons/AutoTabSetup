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