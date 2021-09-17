#include "HashedData.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

   Napi::FunctionReference HashedData::constructor;

    void HashedData::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);
        Napi::Function ctor = DefineClass(env, "HashedData", {
            InstanceAccessor("algorithm", &HashedData::getAlgorithm, &HashedData::setAlgorithm),
            InstanceAccessor("value", &HashedData::getValue, nullptr),
            InstanceMethod("hash", &HashedData::Hash)
        });
        exports.Set("HashedData", ctor);

        constructor = Napi::Persistent(ctor);
        constructor.SuppressDestruct();
    }

    HashedData::HashedData(const Napi::CallbackInfo& info) : Napi::ObjectWrap<HashedData>(info) {
      Napi::Env env = info.Env();
      Napi::HandleScope scope(env);
      boost::shared_ptr<CPPCadesCPHashedDataObject> cadesHashedData1 (new CPPCadesCPHashedDataObject());
      cadesHashedData = cadesHashedData1;
    };

    void HashedData::setAlgorithm(const Napi::CallbackInfo& info, const Napi::Value& value) {
      Napi::Env env = info.Env();

      int iAlgorithm = 0;

      if (value.IsNumber()) {
        iAlgorithm = (int) value.As<Napi::Number>().Uint32Value();
      }
      CAPICOM_HASH_ALGORITHM algorithm = (CAPICOM_HASH_ALGORITHM)iAlgorithm;

      HRESULT result = this->cadesHashedData->put_Algorithm(algorithm);
      HR_METHOD_ERRORCHECK(env, "HashedData set algorithm error: 0x%08X", result);

    }

    Napi::Value HashedData::getAlgorithm(const Napi::CallbackInfo& info){
        Napi::Env env = info.Env();

        CAPICOM_HASH_ALGORITHM algorithm;

        HRESULT result = this->cadesHashedData->get_Algorithm(&algorithm);
        HR_METHOD_ERRORCHECK_RETURN(env, "HashedData get algorithm error: 0x%08X", result);
        return Napi::Number::New(env, algorithm);
    }

    Napi::Value HashedData::Hash(const Napi::CallbackInfo& info){

        Napi::Env env = info.Env();
        COUNT_OF_ARGUMENTS_CHECK(info, env, 1);

        if (!info[0].IsString()) {
          Napi::TypeError::New(env, "HashedData hash wrong value").ThrowAsJavaScriptException();
          return env.Null();
        }
        std::string szContent = info[0].As<Napi::String>().Utf8Value();
        CAtlString sValue = CAtlString(szContent.c_str());
        HRESULT result = this->cadesHashedData->put_Hash(sValue.GetString(), sValue.GetLength());
        HR_METHOD_ERRORCHECK_RETURN(env, "HashedData hash error: 0x%08X", result);
        return env.Undefined();
    }

    Napi::Value HashedData::getValue(const Napi::CallbackInfo& info){
        Napi::Env env = info.Env();
        CAtlString sValue;
        HRESULT result = this->cadesHashedData->get_Value(sValue);
        HR_METHOD_ERRORCHECK_RETURN(env, "HashedData get value error: 0x%08X", result);
        return Napi::String::New(env, sValue.GetString());
    }

}