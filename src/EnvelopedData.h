#ifndef __NODE_CADES_ENVELOPEDDATA_H
#define __NODE_CADES_ENVELOPEDDATA_H
#include "stdafx.h"
#include "CPPCadesCPEnvelopedData.h"
#include "Recipients.h"

using namespace CryptoPro::PKI::CAdES;

namespace NodeCades {

    class EnvelopedData : public Napi::ObjectWrap<EnvelopedData>{
     public:
        static void Init(Napi::Env env, Napi::Object exports);
        EnvelopedData(const Napi::CallbackInfo& info);
        Napi::Value Decrypt(const Napi::CallbackInfo& info);
        Napi::Value Encrypt(const Napi::CallbackInfo& info);
        Napi::Value getRecipients(const Napi::CallbackInfo& info);
        void setContent(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value getContent(const Napi::CallbackInfo& info);
     private:

        boost::shared_ptr<CPPCadesCPEnvelopedDataObject> cadesEnvelopedData;
        static Napi::FunctionReference constructor;
        Napi::String sContent;
    };
}

#endif