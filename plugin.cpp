// plugin.cpp : Defines the entry point for the Programmer's Notepad Plugin
//

#include "stdafx.h"
#include "AppEventSink.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

bool __stdcall pn_init_extension(int iface_version, extensions::IPN* pn)
{
	if(iface_version != PN_EXT_IFACE_VERSION)
	{
		return false;
	}
	
	// Store a global reference to the IPN instance
	g_pn = pn;

	pn->GetGlobalOutputWindow()->AddToolOutput(L"Auto Tab Setup loaded");
	
	extensions::IAppEventSinkPtr appSink(new AppEventSink());
	pn->AddEventSink(appSink);

	return true;
}

void __declspec(dllexport) __stdcall pn_get_extension_info(PN::BaseString& name, PN::BaseString& version)
{
	name = "Auto Tab Setup";
	version = "0.1";
}

void __declspec(dllexport) __stdcall pn_exit_extension()
{

}
