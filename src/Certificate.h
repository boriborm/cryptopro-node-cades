#ifndef __NODE_CADES_CERTIFICATE_H
#define __NODE_CADES_CERTIFICATE_H
#include "stdafx.h"
#include "CPPCadesCPCertificate.h"
using namespace CryptoPro::PKI::CAdES;

namespace NodeCades {

    class Certificate : public Napi::ObjectWrap<Certificate> {
     public:
        static void Init(Napi::Env env, Napi::Object exports);
        Certificate(const Napi::CallbackInfo& info);
        static Napi::Object New(Napi::Env env, boost::shared_ptr<CPPCadesCPCertificateObject>* cadesCert);
        Napi::Value getThumbprint(const Napi::CallbackInfo& info);
        Napi::Value getSerialNumber(const Napi::CallbackInfo& info);
        Napi::Value getSubjectName(const Napi::CallbackInfo& info);
        Napi::Value getIssuerName(const Napi::CallbackInfo& info);

        //Используется в других классах напрямую вместо getter
        boost::shared_ptr<CPPCadesCPCertificateObject> cadesCert;
     //   void printData();
     private:
        static Napi::FunctionReference constructor;
    };
}

#endif