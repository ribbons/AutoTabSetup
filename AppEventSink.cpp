#include "stdafx.h"
#include "AppEventSink.h"
#include "DocEventSink.h"

/// Called when a new document is opened/created
void AppEventSink::OnNewDocument(extensions::IDocumentPtr& doc)
{
	extensions::IDocumentEventSinkPtr docEvents(new DocEventSink(doc));
	doc->AddEventSink(docEvents);
}
