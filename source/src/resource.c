#include "core.h"
#include "../d_resource.h"
#include "../d_memory.h"


Byte* Uncompress(Uint32 *bufId, Size *size) {
    Byte *buffer = (Byte*)MC_GETDPTR(*bufId);

#ifdef D_SKT
    Byte *src = buffer + 1;
    Bool compress = FALSE;

    D_CopyMemory(&compress, buffer, 1);

    if (compress) {
        Uint32 dataId = 0;
        Size dataSize = 0;
        Size srcSize = *size - 5;

        D_CopyMemory(&dataSize, src, 4);
        src += 4;

        dataId = MC_knlAlloc(dataSize);
        buffer = (Byte*)MC_GETDPTR(dataId);

        if (OEMC_utilUncompress("ZLIB", buffer, &dataSize, src, srcSize) != 0) {
            D_ASSERT(!"압축풀기 실패!");
            return NULL;
        }

        MC_knlFree(*bufId);

        *bufId = dataId;
        *size = dataSize;

        src = buffer;
    }
#else
    Byte *src = buffer;
#endif

    return src;
}

DResource* D_LoadResource(const Char *name) {
    Char resName[255] = {0};
    DResource *res = NULL;
    Uint32 resId = 0;
    Size size = 0;

    MC_knlSprintk(resName, "%s", name);

    resId = MC_knlGetResourceID(resName, (M_Int32*)&size);

    if (size > 0) {
        Uint32 bufId = MC_knlAlloc(size);
        Byte *data = NULL;

        MC_knlGetResource(resId, (void*)bufId, size);

        /*TODO: UnCompress
            1. read uncompressed size. (4bytes)
            2. allocate res->data (size).
            3. uncompress buffer data to res->data.
        */
        data = Uncompress(&bufId, &size);

        res = D_Alloc(sizeof(DResource));

        res->size = size;
        res->data = D_Alloc(size);
        res->offset = 0;

        D_CopyMemory(res->data, data, size);
        MC_knlFree(bufId);
    }

    return res;
}

void D_FreeResource(DResource *res) {
    if (res->data != NULL) {
        D_Free(res->data);
    }

    D_Free(res);
}

Bool D_ReadResource(void *buf, DResource *res, Size size) {
    Byte *data = res->data;

    if ((res->offset + size) <= res->size) {
        data += res->offset;
        res->offset += size;

        D_CopyMemory(buf, data, size);

        return TRUE;
    }

    return FALSE;
}
