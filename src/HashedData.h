#ifndef __NODE_CADES_HASHEDDATA_H
#define __NODE_CADES_HASHEDDATA_H
#include "stdafx.h"
#include "CPPCadesCPHashedData.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    class HashedData : public Napi::ObjectWrap<HashedData> {
     public:
        static void Init(Napi::Env env, Napi::Object exports);
        HashedData(const Napi::CallbackInfo& info);
        void setAlgorithm(const Napi::CallbackInfo& info, const Napi::Value& value);
        Napi::Value getAlgorithm(const Napi::CallbackInfo& info);
        Napi::Value Hash(const Napi::CallbackInfo& info);

        boost::shared_ptr<CPPCadesCPHashedDataObject> cadesHashedData;
     private:
        static Napi::FunctionReference constructor;
    };
}

#endif