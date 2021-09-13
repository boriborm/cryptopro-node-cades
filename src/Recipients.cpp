#include "Recipients.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    Napi::FunctionReference Recipients::constructor;

    void Recipients::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);
        Napi::Function ctor = DefineClass(env, "Recipients", {
            InstanceMethod("add", &Recipients::add),
            InstanceMethod("clear", &Recipients::clear),
            InstanceMethod("remove", &Recipients::remove),
            InstanceMethod("item", &Recipients::getItem),
            InstanceAccessor("count", &Recipients::getCount, nullptr),
        });
        exports.Set("Recipients", ctor);
        constructor = Napi::Persistent(ctor);
        constructor.SuppressDestruct();
    }

    Recipients::Recipients(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Recipients>(info) {

      Napi::Env env = info.Env();
      Napi::HandleScope scope(env);

      if (info.Length() < 1 || (info[0].Type() != napi_external)) {
          throw Napi::Error::New(env, "Recipients can only be constructed by native code");
      }
      boost::shared_ptr<CPPCadesCPEnvelopedDataObject> cadesEnvelopedData = *(info[0].As<Napi::External<boost::shared_ptr<CPPCadesCPEnvelopedDataObject>>>().Data());

      HRESULT result = cadesEnvelopedData->get_Recipients(cadesRecipients);
      HR_METHOD_ERRORCHECK(env, "Recipients constructor error: 0x%08X", result);

    };

    Napi::Object Recipients::New(Napi::Env env, boost::shared_ptr<CPPCadesCPEnvelopedDataObject>* cadesEnvelopedData) {
      return Recipients::constructor.Value().New({Napi::External<boost::shared_ptr<CPPCadesCPEnvelopedDataObject>>::New(env, cadesEnvelopedData)});
    }

    Napi::Value Recipients::add(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 1);

      if (!info[0].IsObject()) {
          Napi::TypeError::New(env, "Recipients add wrong arguments").ThrowAsJavaScriptException();
          return env.Null();
      }

      Napi::Object obj = info[0].ToObject();
      Certificate* cert = Certificate::Unwrap(obj);

      HRESULT result = this->cadesRecipients->Add(cert->cadesCert);
      HR_METHOD_ERRORCHECK_RETURN(env, "Recipients add error: 0x%08X", result);

      return env.Undefined();
    }

    Napi::Value Recipients::clear(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      HRESULT result = this->cadesRecipients->Clear();
      HR_METHOD_ERRORCHECK_RETURN(env, "Recipients clear error: 0x%08X", result);
      return env.Undefined();
    }

    Napi::Value Recipients::getCount(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      unsigned int cnt;
      HRESULT result = this->cadesRecipients->get_Count(&cnt);
      HR_METHOD_ERRORCHECK_RETURN(env, "Recipients get count error: 0x%08X", result);
      return Napi::Number::New(env, cnt);
    }

    Napi::Value Recipients::getItem(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 1);

      if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Recipients get item wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
      }
      long index = (long) info[0].As<Napi::Number>().Uint32Value();

      boost::shared_ptr<CPPCadesCPCertificateObject> cadesCert;
      HRESULT result = this->cadesRecipients->get_Item(index, cadesCert);
      HR_METHOD_ERRORCHECK_RETURN(env, "Recipients get item error: 0x%08X", result);

      return Certificate::New(env, &cadesCert);
    }

    Napi::Value Recipients::remove(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 1);

      if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Recipients remove wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
      }
      long index = (long) info[0].As<Napi::Number>().Uint32Value();

      HRESULT result = this->cadesRecipients->Remove(index);
      HR_METHOD_ERRORCHECK_RETURN(env, "Recipients remove error: 0x%08X", result);

      return env.Undefined();
    }
}