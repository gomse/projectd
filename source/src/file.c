#include "core.h"
#include "../d_file.h"

/**
    파일을 연다.
    @param  name    파일명.
    @param  mode    열기 모드.
    @param  type    여는 파일의 속성.
*/
DFile* D_OpenFile(Char *name, D_FOPEN_MODE mode, D_FOPEN_TYPE type) {
    M_Int32 fd = 0, size = 0;
    DFile *file = NULL;

    //type은 무조껀 PRIVATE으로 고정시켜둠.
    type = MC_DIR_PRIVATE_ACCESS;

    fd = MC_fsOpen(name, mode, type);
    if (fd < 0) {
        return NULL;
    }

    MC_fsSeek(fd, 0, MC_FILE_SEEK_END);
    size = MC_fsTell(fd);
    MC_fsSeek(fd, 0, MC_FILE_SEEK_SET);

    file = D_Alloc(sizeof(DFile));

    file->handle = (Int32)fd;
    file->size = (Size)size;

    return file;
}

/**
    열었던 파일을 닫는다.
*/
void D_CloseFile(DFile *file) {
    D_ASSERT(file != NULL);

    MC_fsClose(file->handle);
/*
    file->handle = 0;
    file->size = 0;
*/
    D_Free(file);
}

/**
    파일의 크기를 얻는다.
*/
Size D_GetFileSize(Char *name) {
    M_Int32 fd = 0;
    M_Int32 size = 0;

    fd = MC_fsOpen(name, MC_FILE_OPEN_RDONLY, MC_FILE_OPEN_WRTRUNC);
    if (fd < 0) {
        return 0;
    }

    MC_fsSeek(fd, 0, MC_FILE_SEEK_SET);
    size = MC_fsTell(fd);
    MC_fsClose(fd);

    return (Size)size;
}

/**
    파일이 존재하는지 체크한다.
*/
Bool D_IsFileExist(Char *name) {
    if (MC_fsIsExist(name, MC_DIR_PRIVATE_ACCESS) == M_E_SUCCESS) {
        return TRUE;
    }
    return FALSE;
}

Int32 D_SeekFile(DFile *file, Uint32 pos, D_FILE_SEEK seek) {
    return MC_fsSeek(file->handle, pos, seek);
}

Int32 D_TellFile(const DFile *file) {
    return MC_fsTell(file->handle);
}
