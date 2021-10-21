#include "Certificate.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    Napi::FunctionReference Certificate::constructor;

    void Certificate::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);

        Napi::Function ctor = DefineClass(env, "Certificate", {
            InstanceAccessor("thumbprint", &Certificate::getThumbprint, nullptr),
            InstanceAccessor("serialNumber", &Certificate::getSerialNumber, nullptr),
            InstanceAccessor("subjectName", &Certificate::getSubjectName, nullptr),
            InstanceAccessor("issuerName", &Certificate::getIssuerName, nullptr),
        });
        exports.Set("Certificate", ctor);
        constructor = Napi::Persistent(ctor);
        constructor.SuppressDestruct();
    }

    Certificate::Certificate(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Certificate>(info) {
      Napi::Env env = info.Env();
      Napi::HandleScope scope(env);
      if (info.Length() < 1 || (info[0].Type() != napi_external)) {
          throw Napi::Error::New(env, "Certificates can only be constructed by native code");
      }
      cadesCert = *(info[0].As<Napi::External<boost::shared_ptr<CPPCadesCPCertificateObject>>>().Data());
    };

    Napi::Object Certificate::New(Napi::Env env, boost::shared_ptr<CPPCadesCPCertificateObject>* cadesCert) {
      return Certificate::constructor.Value().New({Napi::External<boost::shared_ptr<CPPCadesCPCertificateObject>>::New(env, cadesCert)});
    }

    Napi::Value Certificate::getThumbprint(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      CAtlString sName;
      HRESULT result = this->cadesCert->get_Thumbprint(sName);
      HR_METHOD_ERRORCHECK_RETURN(env, "Certificate getThumbprint error: 0x%08X", result);
      return Napi::String::New(env, sName.GetString());
    }

    Napi::Value Certificate::getSerialNumber(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      CAtlString sName;
      HRESULT result = this->cadesCert->get_SerialNumber(sName);
      HR_METHOD_ERRORCHECK_RETURN(env, "Certificate getSerialNumber error: 0x%08X", result);
      return Napi::String::New(env, sName.GetString());
    }

    Napi::Value Certificate::getSubjectName(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      CAtlString sName;
      HRESULT result = this->cadesCert->get_SubjectName(sName);
      HR_METHOD_ERRORCHECK_RETURN(env, "Certificate getSubjectName error: 0x%08X", result);
      return Napi::String::New(env, sName.GetString());
    }

    Napi::Value Certificate::getIssuerName(const Napi::CallbackInfo& info) {
      Napi::Env env = info.Env();
      CAtlString sName;
      HRESULT result = this->cadesCert->get_IssuerName(sName);
      HR_METHOD_ERRORCHECK_RETURN(env, "Certificate getIssuerName error: 0x%08X", result);
      return Napi::String::New(env, sName.GetString());
    }
}