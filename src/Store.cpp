#include "Store.h"
#include "Certificate.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

   Napi::FunctionReference Store::constructor;

    void Store::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);
        Napi::Function ctor = DefineClass(env, "Store", {
            InstanceMethod("open", &Store::Open),
            InstanceMethod("close", &Store::Close),
            InstanceAccessor("certificates", &Store::getCertificates, nullptr),
            InstanceAccessor("name", &Store::getName, nullptr),
            InstanceAccessor("location", &Store::getLocation, nullptr),
        });
        exports.Set("Store", ctor);

        constructor = Napi::Persistent(ctor);
        constructor.SuppressDestruct();
    }

    Store::Store(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Store>(info) {
      Napi::Env env = info.Env();
      Napi::HandleScope scope(env);
      //cadesStore = new CPPCadesCPStoreObject();
      boost::shared_ptr<CPPCadesCPStoreObject> cadesStore1 (new CPPCadesCPStoreObject());
      cadesStore = cadesStore1;
    };

    Napi::Value Store::Open(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 3);

      std::string sName = "My";

      int lLocation = CADESCOM_CURRENT_USER_STORE;
      long lMode = CAPICOM_STORE_OPEN_READ_ONLY;

      if (info[0].IsNumber()) {
        lLocation = (int) info[0].As<Napi::Number>().Uint32Value();
      }

      if (info[1].IsString()) {
        sName = info[1].As<Napi::String>().Utf8Value();
      }

      if (info[2].IsNumber()) {
          lMode = (int) info[2].As<Napi::Number>().Uint32Value();
      }

      CADESCOM_STORE_LOCATION Location = (CADESCOM_STORE_LOCATION)lLocation;
      CAPICOM_STORE_OPEN_MODE Mode = (CAPICOM_STORE_OPEN_MODE)lMode;
      CAtlStringW swName = CAtlStringW(sName.c_str());

      HRESULT result = this->cadesStore->Open(Location, swName.GetString(), Mode);
      HR_METHOD_ERRORCHECK_RETURN(env, "Open store error: 0x%08X", result);

      return env.Null();
    }

    Napi::Value Store::Close(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();

      HRESULT result = this->cadesStore->Close();
      HR_METHOD_ERRORCHECK_RETURN(env, "Close store error: 0x%08X", result);

      return env.Null();
    }

    Napi::Value Store::getName(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      CAtlString sName;
      HRESULT result = this->cadesStore->get_Name(sName);
      HR_METHOD_ERRORCHECK_RETURN(env, "Store getName error: 0x%08X", result);
      return Napi::String::New(env, sName.GetString());
    }

    Napi::Value Store::getLocation(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      CADESCOM_STORE_LOCATION location;
      HRESULT result = this->cadesStore->get_Location(&location);
      HR_METHOD_ERRORCHECK_RETURN(env, "Store getLocation error: 0x%08X", result);
      return Napi::Number::New(env, location);
    }

    Napi::Value Store::getCertificates(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();

      boost::shared_ptr<CPPCadesCPCertificatesObject> cadesCertificates;
      HRESULT result = this->cadesStore->get_Certificates(cadesCertificates);
      HR_METHOD_ERRORCHECK_RETURN(env, "Store getCertificates error: 0x%08X", result);

      unsigned int certCount;
      result = cadesCertificates->Count(&certCount);
      HR_METHOD_ERRORCHECK_RETURN(env, "Store getCertificates getCount error: 0x%08X", result);

      Napi::Array certificates = Napi::Array::New(env, certCount);

      boost::shared_ptr<CPPCadesCPCertificateObject> cadesCert;

      for (unsigned int i = 0; i < certCount; i++) {

        result = cadesCertificates->Item(i+1, cadesCert);
        HR_METHOD_ERRORCHECK_RETURN(env, "Store getCertificates getItem() error: 0x%08X", result);

        certificates[i] = Certificate::New(env, &cadesCert);

        //Napi::Object obj = Napi::Object::New(env);
        //obj.Set("value", i);

      }

      return certificates;
    }
}