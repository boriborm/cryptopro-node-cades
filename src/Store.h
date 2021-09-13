#ifndef __NODE_CADES_STORE_H
#define __NODE_CADES_STORE_H
#include "stdafx.h"
#include "CPPCadesCPStore.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    class Store: public Napi::ObjectWrap<Store> {
     public:
        static void Init(Napi::Env env, Napi::Object exports);
        Store(const Napi::CallbackInfo& info);
        Napi::Value Open(const Napi::CallbackInfo& info);
        Napi::Value Close(const Napi::CallbackInfo& info);
        Napi::Value getCertificates(const Napi::CallbackInfo& info);
        Napi::Value getName(const Napi::CallbackInfo& info);
        Napi::Value getLocation(const Napi::CallbackInfo& info);
     private:
        boost::shared_ptr<CPPCadesCPStoreObject> cadesStore;
        static Napi::FunctionReference constructor;
    };
}

#endif