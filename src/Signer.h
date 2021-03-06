#ifndef __NODE_CADES_SIGNER_H
#define __NODE_CADES_SIGNER_H
#include "stdafx.h"
#include "CPPCadesCPSigner.h"
#include "Certificate.h"
#include "DateTime.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    class Signer: public Napi::ObjectWrap<Signer> {
     public:
        static void Init(Napi::Env env, Napi::Object exports);
        Signer(const Napi::CallbackInfo& info);
        static Napi::Object New(Napi::Env env, boost::shared_ptr<CPPCadesCPSignerObject>* cadesSigner);

        void setCertificate(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value getCertificate(const Napi::CallbackInfo& info);
        void setCheckCertificate(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value getCheckCertificate(const Napi::CallbackInfo& info);
        boost::shared_ptr<CPPCadesCPSignerObject> cadesSigner;
        Napi::Value getSigningTime(const Napi::CallbackInfo& info);
        Napi::Value getSignatureTimeStampTime(const Napi::CallbackInfo& info);
        void setOptions(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value getOptions(const Napi::CallbackInfo& info);

     private:
        static Napi::FunctionReference constructor;
    };
}

#endif