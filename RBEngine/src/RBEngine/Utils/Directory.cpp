#include "rbpch.h"
#include "Directory.h"

#include <Windows.h>
#include <ShlObj.h>

namespace RB
{
	Directory::Directory(const FS::path& path)
		: m_Path(path)
	{
	}

	Directory::Directory(const std::string& path)
		: Directory(FS::path(path))
	{
	}

	Debug::Result Directory::Create() const
	{
		if (!Valid()) return Debug::ResultCode::Invalid;

		FS::create_directory(m_Path);
		if (Exists())
		{
			return Debug::ResultCode::Success;
		}

		return Debug::ResultCode::Error;
	}
	
	Directory Directory::GetDirectoryDialog()
	{
		FS::path path;
		HRESULT result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(result))
		{
			IFileOpenDialog* pFileOpen;
			result = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
			if (SUCCEEDED(result))
			{
				result = pFileOpen->SetOptions(FOS_PICKFOLDERS);
				if (SUCCEEDED(result))
				{
					result = pFileOpen->Show(NULL);

					if (SUCCEEDED(result))
					{
						IShellItem* pItem;
						result = pFileOpen->GetResult(&pItem);
						if (SUCCEEDED(result))
						{
							PWSTR pszFilePath;
							result = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
							if (SUCCEEDED(result))
							{
								path = pszFilePath;
								CoTaskMemFree(pszFilePath);
							}
							pItem->Release();
						}
						pFileOpen->Release();
					}
					CoUninitialize();
				}
			}
		}

		return Directory(path);
	}
}