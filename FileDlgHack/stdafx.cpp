// stdafx.cpp : 標準インクルード FileDlgHack.pch のみを
// 含むソース ファイルは、プリコンパイル済みヘッダーになります。
// stdafx.obj にはプリコンパイル済み型情報が含まれます。

#include "stdafx.h"

// TODO: このファイルではなく、STDAFX.H で必要な
// 追加ヘッダーを参照してください。

/*	// デバッグウィンドウに出力するver
void DebugTrace(const char *format, ...)
{
	char buf[1024];
	va_list list;
	va_start(list, format);

	wvsprintf( buf,format, list);

	OutputDebugString(buf);
	va_end(list);
}

void DebugTrace(const char *str)
{
	OutputDebugString(str);
}
*/

#include "FileDlgHack.h"
#include "Config.h"

void LogFilePath(TCHAR* path)
{
	static TCHAR LogPath[MAX_PATH] = L"";
	if (LogPath[0] == L'\0') {
		int len = GetModuleFileName(g_Inst, LogPath, MAX_PATH);
	 	LogPath[len - 3] = L'l';
	 	LogPath[len - 2] = L'o';
		LogPath[len - 1] = L'g';
	}
	lstrcpy(path, LogPath); 
}

void DebugTrace(const char *format, ...)
{
	char str[1024];
	va_list list;
	va_start(list, format);

	wvsprintfA(str, format, list);
	va_end(list);

	FILE *fp = nullptr;
	TCHAR LogPath[MAX_PATH];
	LogFilePath(LogPath);
	if (::strcmp(str, "open") == 0) {	// 空のファイルを作成する
		fp = _wfopen(LogPath, L"w");
		fclose(fp);
		return ;
	}
	fp = _wfopen(LogPath, L"a");

	fputs(str, fp);				// ファイルに書き込み

	fclose(fp);
}

#if 0
void DebugTrace(const char *str)
{
	FILE *fp;
	char LogPath[MAX_PATH];
	LogFilePath(LogPath);

	fp = fopen(LogPath, "a");

	fputs(str, fp);				// ファイルに書き込み

	fclose(fp);
}
#endif
