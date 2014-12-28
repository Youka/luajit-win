#include "win_io.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wchar.h>

static wchar_t* utf8_to_ucs2(const char* str){
	int wlen;
	wchar_t* wstr;
	if(!(wlen = MultiByteToWideChar(CP_UTF8, 0x0, str, -1, NULL, 0)) || !(wstr = malloc(wlen << 1)))
		return NULL;
	if(!MultiByteToWideChar(CP_UTF8, 0x0, str, -1, wstr, wlen)){
		free(wstr);
		return NULL;
	}
	return wstr;
}

FILE* _ufopen(const char* filename, const char* mode){
	wchar_t* wfilename, *wmode;
	FILE* file;
	if(!(wfilename = utf8_to_ucs2(filename)))
		return NULL;
	if(!(wmode = utf8_to_ucs2(mode))){
		free(wfilename);
		return NULL;
	}
	file = _wfopen(wfilename, wmode);
	free(wfilename);
	free(wmode);
	return file;
}

FILE* _ufreopen (const char* filename, const char* mode, FILE* stream){
	wchar_t* wfilename, *wmode;
	if(!(wfilename = utf8_to_ucs2(filename)))
		return NULL;
	if(!(wmode = utf8_to_ucs2(mode))){
		free(wfilename);
		return NULL;
	}
	stream = _wfreopen(wfilename, wmode, stream);
	free(wfilename);
	free(wmode);
	return stream;
}

FILE* _upopen(const char* command, const char* mode){
	wchar_t* wcommand, *wmode;
	FILE* stream;
	if(!(wcommand = utf8_to_ucs2(command)))
		return NULL;
	if(!(wmode = utf8_to_ucs2(mode))){
		free(wcommand);
		return NULL;
	}
	stream = _wfopen(wcommand, wmode);
	free(wcommand);
	free(wmode);
	return stream;
}

int _uremove(const char* filename){
	wchar_t* wfilename;
	int status;
	if(!(wfilename = utf8_to_ucs2(filename)))
		return 1;
	status = _wremove(wfilename);
	free(wfilename);
	return status;
}

int _urename(const char* oldname, const char* newname){
	wchar_t* woldname, *wnewname;
	int status;
	if(!(woldname = utf8_to_ucs2(oldname)))
		return 1;
	if(!(wnewname = utf8_to_ucs2(newname))){
		free(woldname);
		return 1;
	}
	status = _wrename(woldname, wnewname);
	free(woldname);
	free(wnewname);
	return status;
}

int _usystem(const char* command){
	wchar_t* wcommand;
	int status;
	if(!(wcommand = utf8_to_ucs2(command)))
		return -1;
	status = _wsystem(wcommand);
	free(wcommand);
	return status;
}