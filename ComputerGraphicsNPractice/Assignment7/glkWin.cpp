#include <windows.h>

char *glkFileDlg(const char *filter) {
    const int MaxLen = 1024;
    static char fileName[MaxLen] = "";

    OPENFILENAME open_file;
    memset(&open_file, 0, sizeof(OPENFILENAME));
    open_file.lStructSize = sizeof(OPENFILENAME);
    open_file.hwndOwner = NULL;
    open_file.lpstrFilter = filter;
    open_file.nFilterIndex = 1;
    open_file.lpstrFile = fileName;
    open_file.nMaxFile = MaxLen;
    open_file.lpstrTitle = "Select a file";
//    open_file.lpstrDefExt = "bvh";
    open_file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    bool ret = GetOpenFileName(&open_file);
    return (ret) ? fileName : NULL;
}
