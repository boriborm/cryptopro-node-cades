#ifndef __NODE_CADES_SIGNEDDATA_H
#define __NODE_CADES_SIGNEDDATA_H
#include "stdafx.h"
#include "CPPCadesCPSignedData.h"
#include "Signer.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    class SignedData : public Napi::ObjectWrap<SignedData> {
     public:
        static void Init(Napi::Env env, Napi::Object exports);
        SignedData(const Napi::CallbackInfo& info);
        Napi::Value signCades(const Napi::CallbackInfo& info);
        void setContent(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value getContent(const Napi::CallbackInfo& info);
     private:
        CPPCadesSignedDataObject* cadesSignedData;
        static Napi::FunctionReference constructor;
    };
}

#endif