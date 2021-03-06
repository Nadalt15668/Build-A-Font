#include "FileDialog.h"

HRESULT _WriteDataToFile(HANDLE hFile, PCWSTR pszDataIn)
{
    // First figure out our required buffer size.
    DWORD cbData = WideCharToMultiByte(CP_ACP, 0, pszDataIn, -1, NULL, 0, NULL, NULL);
    HRESULT hr = (cbData == 0) ? HRESULT_FROM_WIN32(GetLastError()) : S_OK;
    if (SUCCEEDED(hr))
    {
        // Now allocate a buffer of the required size, and call WideCharToMultiByte again to do the actual conversion.
        char* pszData = new (std::nothrow) CHAR[cbData];
        hr = pszData ? S_OK : E_OUTOFMEMORY;
        if (SUCCEEDED(hr))
        {
            hr = WideCharToMultiByte(CP_ACP, 0, pszDataIn, -1, pszData, cbData, NULL, NULL)
                ? S_OK
                : HRESULT_FROM_WIN32(GetLastError());
            if (SUCCEEDED(hr))
            {
                DWORD dwBytesWritten = 0;
                hr = WriteFile(hFile, pszData, cbData - 1, &dwBytesWritten, NULL)
                    ? S_OK
                    : HRESULT_FROM_WIN32(GetLastError());
            }
            delete[] pszData;
        }
    }
    return hr;
}

HRESULT _WriteDataToCustomFile(PCWSTR pszFileName, PCWSTR pszFileData)
{
    HANDLE hFile = CreateFileW(pszFileName,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,  // Let's always create this file.
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    HRESULT hr = (hFile == INVALID_HANDLE_VALUE) ? HRESULT_FROM_WIN32(GetLastError()) : S_OK;
    if (SUCCEEDED(hr))
    {
        hr = _WriteDataToFile(hFile, pszFileData);
        CloseHandle(hFile);
    }
    return hr;
}

IFACEMETHODIMP CDialogEventHandler::QueryInterface(REFIID riid, void** ppv)
{
    static const QITAB qit[] = {
        QITABENT(CDialogEventHandler, IFileDialogEvents),
        QITABENT(CDialogEventHandler, IFileDialogControlEvents),
        { 0 },
#pragma warning(suppress:4838)
    };
    return QISearch(this, qit, riid, ppv);
}

ULONG __stdcall CDialogEventHandler::AddRef()
{
    return InterlockedIncrement(&_cRef);
}

ULONG __stdcall CDialogEventHandler::Release()
{
    long cRef = InterlockedDecrement(&_cRef);
    if (!cRef)
        delete this;
    return cRef;
}

IFACEMETHODIMP CDialogEventHandler::OnFileOk(IFileDialog*)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnFolderChange(IFileDialog*)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnFolderChanging(IFileDialog*, IShellItem*)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnHelp(IFileDialog*)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnSelectionChange(IFileDialog*)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnTypeChange(IFileDialog* pfd)

{
    IFileSaveDialog* pfsd;
    HRESULT hr = pfd->QueryInterface(&pfsd);
    if (SUCCEEDED(hr))
    {
        UINT uIndex;
        hr = pfsd->GetFileTypeIndex(&uIndex);   // index of current file-type
        if (SUCCEEDED(hr))
        {
            IPropertyDescriptionList* pdl = NULL;

            switch (uIndex)
            {
            case INDEX_WORDDOC:
                // When .doc is selected, let's ask for some arbitrary property, say Title.
                hr = PSGetPropertyDescriptionListFromString(L"prop:System.Title", IID_PPV_ARGS(&pdl));
                if (SUCCEEDED(hr))
                {
                    // FALSE as second param == do not show default properties.
                    hr = pfsd->SetCollectedProperties(pdl, FALSE);
                    pdl->Release();
                }
                break;

            case INDEX_WEBPAGE:
                // When .html is selected, let's ask for some other arbitrary property, say Keywords.
                hr = PSGetPropertyDescriptionListFromString(L"prop:System.Keywords", IID_PPV_ARGS(&pdl));
                if (SUCCEEDED(hr))
                {
                    // FALSE as second param == do not show default properties.
                    hr = pfsd->SetCollectedProperties(pdl, FALSE);
                    pdl->Release();
                }
                break;

            case INDEX_TEXTDOC:
                // When .txt is selected, let's ask for some other arbitrary property, say Author.
                hr = PSGetPropertyDescriptionListFromString(L"prop:System.Author", IID_PPV_ARGS(&pdl));
                if (SUCCEEDED(hr))
                {
                    // TRUE as second param == show default properties as well, but show Author property first in list.
                    hr = pfsd->SetCollectedProperties(pdl, TRUE);
                    pdl->Release();
                }
                break;
            }
        }
        pfsd->Release();
    }
    return hr;
}

IFACEMETHODIMP CDialogEventHandler::OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem)

{
    IFileDialog* pfd = NULL;
    HRESULT hr = pfdc->QueryInterface(&pfd);
    if (SUCCEEDED(hr))
    {
        if (dwIDCtl == CONTROL_RADIOBUTTONLIST)
        {
            switch (dwIDItem)
            {
            case CONTROL_RADIOBUTTON1:
                hr = pfd->SetTitle(L"Longhorn Dialog");
                break;

            case CONTROL_RADIOBUTTON2:
                hr = pfd->SetTitle(L"Vista Dialog");
                break;
            }
        }
        pfd->Release();
    }
    return hr;
}

IFACEMETHODIMP CDialogEventHandler::OnButtonClicked(IFileDialogCustomize*, DWORD)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnCheckButtonToggled(IFileDialogCustomize*, DWORD, BOOL)
{
    return S_OK;
}

IFACEMETHODIMP CDialogEventHandler::OnControlActivating(IFileDialogCustomize*, DWORD)
{
    return S_OK;
}

HRESULT CDialogEventHandler::CDialogEventHandler_CreateInstance(REFIID riid, void** ppv)

{
    *ppv = NULL;
    CDialogEventHandler* pDialogEventHandler = new (std::nothrow) CDialogEventHandler();
    HRESULT hr = pDialogEventHandler ? S_OK : E_OUTOFMEMORY;
    if (SUCCEEDED(hr))
    {
        hr = pDialogEventHandler->QueryInterface(riid, ppv);
        pDialogEventHandler->Release();
    }
    return hr;
}

std::string CDialogEventHandler::ChooseFile(IShellItem** loadedProject)

{
    // CoCreate the File Open Dialog object.
    char* path = new char[MAX_PATH];
    IFileDialog* pfd = NULL;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    if (SUCCEEDED(hr))
    {
        // Create an event handling object, and hook it up to the dialog.
        IFileDialogEvents* pfde = NULL;
        hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
        if (SUCCEEDED(hr))
        {
            // Hook up the event handler.
            DWORD dwCookie;
            hr = pfd->Advise(pfde, &dwCookie);
            if (SUCCEEDED(hr))
            {
                // Set the options on the dialog.
                DWORD dwFlags;

                // Before setting, always get the options first in order not to override existing options.
                hr = pfd->GetOptions(&dwFlags);
                if (SUCCEEDED(hr))
                {
                    // In this case, get shell items only for file system items.
                    hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
                    if (SUCCEEDED(hr))
                    {
                        // Set the file types to display only. Notice that, this is a 1-based array.
                        hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
                        if (SUCCEEDED(hr))
                        {
                            // Show the dialog
                            hr = pfd->Show(NULL);
                            if (SUCCEEDED(hr))
                            {
                                // Obtain the result, once the user clicks the 'Open' button.
                                // The result is an IShellItem object.
                                hr = pfd->GetResult(loadedProject);
                                if (SUCCEEDED(hr))
                                {
                                    // We are just going to print out the name of the file for sample sake.
                                    PWSTR pszFilePath = NULL;
                                    hr = (*loadedProject)->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                                    if (SUCCEEDED(hr))
                                    {
                                        wcstombs(path, pszFilePath, MAX_PATH);
                                        CoTaskMemFree(pszFilePath);
                                    }
                                }
                            }
                        }
                    }
                }
                // Unhook the event handler.
                pfd->Unadvise(dwCookie);
            }
            pfde->Release();
        }
        pfd->Release();
    } 
    std::string strPath(path);
    delete[] path;
    return strPath.substr(strPath.find_last_of('\\') + 1);
}

char* CDialogEventHandler::ReadFromFile(IShellItem** loadedProject)
{
    HRESULT hr;
    if ((*loadedProject) != nullptr)
    {
        IPropertyStore* ps;
        if (SUCCEEDED((*loadedProject)->BindToHandler(NULL, BHID_PropertyStore, IID_PPV_ARGS(&ps))))
        {
            PROPVARIANT pv;
            PropVariantInit(&pv);
            if (SUCCEEDED(ps->GetValue(PKEY_Size, &pv)))  // include propkey.h
            {
                ULONGLONG size;
                DWORD dwBytesRead = 0;
                char* fileData;
                if (SUCCEEDED(PropVariantToUInt64(pv, &size))) // include propvarutil.h
                {
                    fileData = new char[size];
                    PWSTR pszFilePath = NULL;
                    hr = (*loadedProject)->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    if (SUCCEEDED(hr))
                    {
                        OVERLAPPED ol = { 0 };
                        HANDLE hFile = CreateFileW(pszFilePath,
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_ALWAYS,  // Let's always create this file.
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
                        hr = ReadFile(hFile, fileData, size, &dwBytesRead, NULL);
                        if (SUCCEEDED(hr))
                        {
                            CloseHandle(hFile);
                            return fileData;
                        }
                    }
                }
                PropVariantClear(&pv);
            }
            ps->Release();
        }
    }
    else
        return nullptr;
}

HRESULT CDialogEventHandler::SaveFileAs(PWSTR fileData, IShellItem** loadedProject)
{
    // CoCreate the File Open Dialog object.
    IFileSaveDialog* pfsd;
    HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfsd));
    if (SUCCEEDED(hr))
    {
        // Set the file types to display.
        hr = pfsd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
        if (SUCCEEDED(hr))
        {
            hr = pfsd->SetFileTypeIndex(0);
            if (SUCCEEDED(hr))
            {
                // Set default file extension.
                hr = pfsd->SetDefaultExtension(L"baf");
                if (SUCCEEDED(hr))
                {
                    // Ensure the dialog only returns items that can be represented by file system paths.
                    DWORD dwFlags;
                    hr = pfsd->GetOptions(&dwFlags);
                    if (SUCCEEDED(hr))
                    {
                        hr = pfsd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
                    }
                }
            }
        }
    }

    if (SUCCEEDED(hr))
    {
        if (*loadedProject != nullptr)
            hr = pfsd->SetSaveAsItem(*loadedProject);
        if (SUCCEEDED(hr))
        {
            // Now show the dialog.
            hr = pfsd->Show(NULL);
            if (SUCCEEDED(hr))
            {
                hr = pfsd->GetResult(loadedProject);
                if (SUCCEEDED(hr))
                {
                    // Get the path to the file.
                    PWSTR pszNewFileName;
                    hr = (*loadedProject)->GetDisplayName(SIGDN_FILESYSPATH, &pszNewFileName);
                    if (SUCCEEDED(hr))
                    {
                        // Write data to the file.
                        hr = _WriteDataToCustomFile(pszNewFileName, fileData);
                        CoTaskMemFree(pszNewFileName);
                    }
                }
            }
        }
        
    }
    pfsd->Release();
    return hr;
}
HRESULT CDialogEventHandler::SaveChanges(PWSTR fileData, IShellItem** loadedProject)
{
    HRESULT hr;
    if (*loadedProject != nullptr)
    {
        PWSTR pszNewFileName;
        hr = (*loadedProject)->GetDisplayName(SIGDN_FILESYSPATH, &pszNewFileName);
        if (SUCCEEDED(hr))
        {
            // Write data to the file.
            hr = _WriteDataToCustomFile(pszNewFileName, fileData);
             CoTaskMemFree(pszNewFileName);
        }
    }
    else
        hr = SaveFileAs(fileData, loadedProject);
    return hr;
}
PWSTR CDialogEventHandler::StrToPWSTR(std::string fileData)
{
    size_t newsize =fileData.length() + 1;
    PWSTR returnedData = new wchar_t[newsize];
    mbstowcs(returnedData, fileData.c_str(), newsize);
    return returnedData;
}
std::string CDialogEventHandler::ChooseFolder(IShellItem** chosenPathItem)
{
    IFileDialog* pfd;
    char* path = new char[MAX_PATH];
    if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
    {
        DWORD dwOptions;
        if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
        {
            pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
        }
        if (SUCCEEDED(pfd->SetDefaultFolder(*chosenPathItem)))
        {
            if (SUCCEEDED(pfd->Show(NULL)))
            {
                if (SUCCEEDED(pfd->GetResult(chosenPathItem)))
                {
                    LPWSTR chosenPath;
                    if (SUCCEEDED((*chosenPathItem)->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &chosenPath)))
                    {
                        wcstombs(path, chosenPath, MAX_PATH);
                    }
                    // If there are releasing problems
                    //(*chosenPathItem)->Release();
                }
            }
        }
        pfd->Release();
    }
    std::string strPath(path);
    delete[] path;
    return strPath;
}