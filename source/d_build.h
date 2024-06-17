/**
    @file   d_build.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_BUILD_H_
#define DOROTHY_BUILD_H_

#if defined(_DEBUG)
#   define D_DEBUG
#else
#   define D_RELEASE
#endif

#if defined(_WEPI_WIN32)
#   define D_WEPI
#else
#   ifdef _SKT_DLL
#       define D_SKT_EMUL
#   endif
#   define D_SKT
#endif

#endif
