class DocEventSink : public extensions::IDocumentEventSink
{
public:
	DocEventSink(extensions::IDocumentPtr doc) : m_doc(doc){}

	virtual ~DocEventSink(){}

	/// Called when the scheme changes
	virtual void OnSchemeChange(const char* scheme){}
	
	/// Called when the document closes
	virtual void OnDocClosing();

	/// Called after a document is loaded
	virtual void OnAfterLoad();

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