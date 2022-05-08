#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define STRICT_TYPED_ITEMIDS
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <sstream>
#include <propkey.h>
#include <propvarutil.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Propsys.lib")

using namespace std;

#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
// Added for changing the entry point
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

const COMDLG_FILTERSPEC c_rgSaveTypes[] =
{
    {L"Build-A-Font Document (*.baf)", L"*.baf"}
};

// Indices of file types
#define INDEX_WORDDOC 1
#define INDEX_PRPNTPR 2
#define INDEX_WEBPAGE 3
#define INDEX_TEXTDOC 4

// Controls
#define CONTROL_GROUP           2000
#define CONTROL_RADIOBUTTONLIST 2
#define CONTROL_RADIOBUTTON1    1
#define CONTROL_RADIOBUTTON2    2       // It is OK for this to have the same ID as CONTROL_RADIOBUTTONLIST,
                                        // because it is a child control under CONTROL_RADIOBUTTONLIST

// IDs for the Task Dialog Buttons
#define IDC_BASICFILEOPEN                       100

/* File Dialog Event Handler *****************************************************************************************************/

class CDialogEventHandler : public IFileDialogEvents,
    public IFileDialogControlEvents
{
public:
    // IUnknown methods
    IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv);
    IFACEMETHODIMP_(ULONG) AddRef();
    IFACEMETHODIMP_(ULONG) Release();
    // IFileDialogEvents methods
    IFACEMETHODIMP OnFileOk(IFileDialog*);
    IFACEMETHODIMP OnFolderChange(IFileDialog*);
    IFACEMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*);
    IFACEMETHODIMP OnHelp(IFileDialog*);
    IFACEMETHODIMP OnSelectionChange(IFileDialog*);
    IFACEMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*);
    IFACEMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*);
    // This method gets called when the file-type is changed (combo-box selection changes).
    // For sample sake, let's react to this event by changing the properties show.
    IFACEMETHODIMP OnTypeChange(IFileDialog* pfd);
    // IFileDialogControlEvents methods

    // This method gets called when an dialog control item selection happens (radio-button selection. etc).
    // For sample sake, let's react to this event by changing the dialog title.
    IFACEMETHODIMP OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem);
    IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize*, DWORD);
    IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize*, DWORD, BOOL);
    IFACEMETHODIMP OnControlActivating(IFileDialogCustomize*, DWORD);
    static HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv);
    static string ChooseFile(IShellItem** loadedProject);
    static char* ReadFromFile(IShellItem** loadedProject);
    static HRESULT SaveFileAs(PWSTR fileData, IShellItem** loadedProject);
    static HRESULT SaveChanges(PWSTR fileData, IShellItem** loadedProject);
    static PWSTR StrToPWSTR(string fileData);
    static string ChooseFolder(IShellItem** chosenPath);

    CDialogEventHandler() : _cRef(1) { };
private:
    ~CDialogEventHandler() { };
    long _cRef;
};
