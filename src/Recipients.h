#ifndef __NODE_CADES_RECIPIENTS_H
#define __NODE_CADES_RECIPIENTS_H
#include "stdafx.h"
#include "CPPCadesCPEnvelopedData.h"
#include "Certificate.h"

using namespace CryptoPro::PKI::CAdES;

namespace NodeCades {

    class Recipients : public Napi::ObjectWrap<Recipients> {
     public:
        static void Init(Napi::Env env, Napi::Object exports);
        Recipients(const Napi::CallbackInfo& info);
        static Napi::Object New(Napi::Env env, boost::shared_ptr<CPPCadesCPEnvelopedDataObject>* cadesEnvelopedData);
        Napi::Value add(const Napi::CallbackInfo& info);
        Napi::Value clear(const Napi::CallbackInfo& info);
        Napi::Value getCount(const Napi::CallbackInfo& info);
        Napi::Value getItem(const Napi::CallbackInfo& info);
        Napi::Value remove(const Napi::CallbackInfo& info);
     private:
        boost::shared_ptr<CPPCadesCPRecipientsObject> cadesRecipients;
        static Napi::FunctionReference constructor;
    };
}

#endif