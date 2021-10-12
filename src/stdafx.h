#ifndef __NODE_CADES_STDAFX_H
#define __NODE_CADES_STDAFX_H
#define CRYPT_SIGN_MESSAGE_PARA_HAS_CMS_FIELDS
#define CMSG_SIGNER_ENCODE_INFO_HAS_CMS_FIELDS
#define CMSG_SIGNED_ENCODE_INFO_HAS_CMS_FIELDS
#define CERT_PARA_HAS_EXTRA_FIELDS

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#ifdef _WIN32
#define RETURN_ATL_STRING RETURN_ATL_STRING_W
#define RETURN_ATL_STRINGL RETURN_ATL_STRINGL_W
#endif

#include <stdio.h>
#define SIZEOF_VOID_P (UINTPTR_MAX+0 > 0xffffffffUL ? 8 : 4)
#include <stdlib.h>
#include <iostream> //Без этого не собирается на старых версиях gcc (4.8.5 и выше). На gcc 9 можно не включать. Ошибки похожи как с <memory>
#include <memory> //Этот хедер тут нужен что бы компилить с новыми версиями libstdc++
                  //в них есть конфликт с __in и __out макросами которые определены в MS хедерах.
#ifdef UNIX
#include "CSP_WinDef.h"
#include "CSP_WinError.h"
#include <string>
#include <stdarg.h>
#include <atldef2.h>
#define CADES_CLASS
#define RETURN_ATL_STRING RETURN_ATL_STRING_A
#define RETURN_ATL_STRINGL RETURN_ATL_STRINGL_A
#endif //UNIX
#include <WinCryptEx.h>
#include <atlcrypt2.h>
#include <cades.h>

//#define _ATL_APARTMENT_THREADED
// some CString constructors will be explicit
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
// turns off ATL's hiding of some common and often safely ignored warning messages
//#define _ATL_ALL_WARNINGS

#include <napi.h>


#define HR_METHOD_ERRORCHECK_RETURN(env, errorMessage, result)   do   \
    {                                                                               \
        if (result != S_OK)                                                         \
        {                                                                           \
             char buff[100];                                                        \
             snprintf(buff, sizeof(buff), errorMessage, result);                    \
             std::string buffAsStdStr = buff;                                       \
             Napi::TypeError::New(env, buffAsStdStr).ThrowAsJavaScriptException();  \
             return env.Null();                                                     \
        }                                                                           \
    } while(0)

#define HR_METHOD_ERRORCHECK(env, errorMessage, result)   do   \
    {                                                                               \
        if (result != S_OK)                                                         \
        {                                                                           \
             char buff[100];                                                        \
             snprintf(buff, sizeof(buff), errorMessage, result);                    \
             std::string buffAsStdStr = buff;                                       \
             Napi::TypeError::New(env, buffAsStdStr).ThrowAsJavaScriptException();  \
        }                                                                           \
    } while(0)

#define COUNT_OF_ARGUMENTS_CHECK(info, env, cnt)                                    \
    do {                                                                            \
        if (info.Length() < cnt) {                                                  \
            Napi::TypeError::New(env, "Wrong number of arguments")                  \
                .ThrowAsJavaScriptException();                                      \
            return env.Null();                                                      \
        }                                                                           \
    }while (0)

#endif