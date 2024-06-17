/**
    @file   d_file.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_FILE_H_
#define DOROTHY_FILE_H_

typedef enum D_FOPEN_TYPE {
    D_FOPEN_TYPE_TEXT = 0,
    D_FOPEN_TYPE_BINARY
} D_FOPEN_TYPE;

typedef enum D_FOPEN_MODE {
    D_FOPEN_MODE_READ = MC_FILE_OPEN_RDONLY,
    D_FOPEN_MODE_WRITE = MC_FILE_OPEN_WRTRUNC
} D_FOPEN_MODE;

typedef enum D_FILE_SEEK {
    D_FILE_SEEK_CUR = MC_FILE_SEEK_CUR,
    D_FILE_SEEK_SET = MC_FILE_SEEK_SET,
    D_FILE_SEEK_END = MC_FILE_SEEK_END
} D_FILE_SEEK;

typedef struct D_File {
    Int32 handle;
    Size size;
} DFile;

BEGIN_DOROTHY_API
    DFile*  D_OpenFile(Char *name, D_FOPEN_MODE mode, D_FOPEN_TYPE type);
    void    D_CloseFile(DFile *file);
    Int32   D_SeekFile(DFile *file, Uint32 pos, D_FILE_SEEK seek);
    Int32   D_TellFile(const DFile *file);
    Size    D_GetFileSize(Char *name);
    Bool    D_IsFileExist(Char *name);
END_DOROTHY_API

#endif
