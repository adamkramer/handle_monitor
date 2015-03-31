/*  This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Created by Adam Kramer [2015] - Email: adamkramer at hotmail dot com */

#include "stdafx.h"
#include "windows.h"


int _tmain(int argc, _TCHAR* argv[])
{

	/* Display intoduction */
	if (argc < 4)
	{
		printf("hm_test v1.0 - Adam Kramer\n"
			"Usage: hm_test.exe <path to directory> <command> <argument>\n\n");

		printf("Commands include:\n\n"
			"create - create a number of files in the specified directory\n"
			"Example: hm_test.exe c:\\directory create <number of files>\n\n"
			"encrypt - simulate encryption (read file, then write to file)\n"
			"Example: hm_test.exe c:\\directory encrypt <number of files>\n\n");

			return 1;
	}

	/* Check argument 1 is a path */
	int dwAttrib = GetFileAttributesW(argv[1]);

	if (!(dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)))
	{
		DWORD a = GetLastError();
		printf("Error: The first argument must be a directory\n");
		return 1;
	}

	/* Process command arguement */
	if (!wcscmp(argv[2], L"create") || !wcscmp(argv[2], L"encrypt"))
	{

		DWORD dNumberFiles = _wtoi(argv[3]);
		DWORD dSizeFiles = 1048576;

		WCHAR wFullPath[MAX_PATH];

		FILE* file;

		/* For as many files as have been requested... */
		for (DWORD i = 0; i < dNumberFiles; i++)
		{
			/* Generate specific path */
			WCHAR wFileNumber[MAX_PATH];
			_itow_s(i, wFileNumber, 10);

			wcscpy_s(wFullPath, MAX_PATH, argv[1]);
			wcscat_s(wFullPath, L"\\hm_testfile");
			wcscat_s(wFullPath, wFileNumber);

			/* Open file for writing */
			if (_wfopen_s(&file, wFullPath, L"w+"))
			{
				printf("Error: Cannot write to files\n");
				return 1;
			}

			wprintf(L"Writing file: %s\n", wFullPath);

			/* Write to file (0 for create mode, 1 for encrypt mode) */
			for (DWORD j = 0; j < dSizeFiles; j++)
				if (!wcscmp(argv[2], L"create"))
					putc(48, file);
				else
					putc(49, file);

			fclose(file);

		}

	}
	else 
	{
		printf("Error: Invalid command (use: create or encrypt)\n");
		return 1;
	}

	return 0;
}

