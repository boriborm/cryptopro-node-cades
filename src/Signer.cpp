#include "Signer.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

   Napi::FunctionReference Signer::constructor;

    void Signer::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);
        Napi::Function ctor = DefineClass(env, "Signer", {
            InstanceAccessor("certificate", &Signer::getCertificate, &Signer::setCertificate),
            InstanceAccessor("checkCertificate", &Signer::getCheckCertificate, &Signer::setCheckCertificate),
        });
        exports.Set("Signer", ctor);

        constructor = Napi::Persistent(ctor);
        constructor.SuppressDestruct();
    }

    Signer::Signer(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Signer>(info) {
      Napi::Env env = info.Env();
      Napi::HandleScope scope(env);
      boost::shared_ptr<CPPCadesCPSignerObject> cadesSigner1 (new CPPCadesCPSignerObject());
      cadesSigner = cadesSigner1;
      //CPPCadesCPSignerObject* cadesSigner1 = new CPPCadesCPSignerObject();
      cadesSigner = cadesSigner1;
    };

    void Signer::setCertificate(const Napi::CallbackInfo& info, const Napi::Value& value) {
      Napi::Env env = info.Env();
      Napi::Object obj = value.As<Napi::Object>();
      Certificate* cert = Certificate::Unwrap(obj);

      CCertContext certContext;
      HRESULT result = cert->cadesCert->get_CertContext(certContext);
      HR_METHOD_ERRORCHECK(env, "Signer set certificate get context error: 0x%08X", result);
      boost::shared_ptr<CPPCadesCPCertificateObject> cadesCert(new CPPCadesCPCertificateObject());
      cadesCert->put_CertContext(certContext);

      result = this->cadesSigner->put_Certificate(cadesCert);
      HR_METHOD_ERRORCHECK(env, "Signer set certificate error: 0x%08X", result);

    }

    Napi::Value Signer::getCertificate(const Napi::CallbackInfo& info){
        Napi::Env env = info.Env();
        boost::shared_ptr<CPPCadesCPCertificateObject> cadesCert;
        HRESULT result = this->cadesSigner->get_Certificate(cadesCert);
        HR_METHOD_ERRORCHECK_RETURN(env, "Signer get certificate error: 0x%08X", result);
        return Certificate::New(env, &cadesCert);
    }

    void Signer::setCheckCertificate(const Napi::CallbackInfo& info, const Napi::Value& value) {
      Napi::Env env = info.Env();
      BOOL bValue = value.ToBoolean();
      HRESULT result = this->cadesSigner->put_CheckCertificate(bValue);
      HR_METHOD_ERRORCHECK(env, "Signer set check certificate error: 0x%08X", result);
    }

    Napi::Value Signer::getCheckCertificate(const Napi::CallbackInfo& info){
        Napi::Env env = info.Env();
        BOOL bValue = 0;
        HRESULT result = this->cadesSigner->get_CheckCertificate(bValue);
        HR_METHOD_ERRORCHECK_RETURN(env, "Signer get check certificate error: 0x%08X", result);
        return Napi::Boolean::New(env, bValue);
    }

}