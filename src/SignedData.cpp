#include "SignedData.h"


using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    Napi::FunctionReference SignedData::constructor;

    void SignedData::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);
        Napi::Function ctor = DefineClass(env, "SignedData", {
            InstanceMethod("signCades", &SignedData::signCades),
            InstanceMethod("verifyCades", &SignedData::verifyCades),
            InstanceAccessor("content", &SignedData::getContent, &SignedData::setContent),
        });
        exports.Set("SignedData", ctor);

        constructor = Napi::Persistent(ctor);
        constructor.SuppressDestruct();
    }

    SignedData::SignedData(const Napi::CallbackInfo& info) : Napi::ObjectWrap<SignedData>(info) {
      Napi::Env env = info.Env();
      Napi::HandleScope scope(env);
      cadesSignedData = new CPPCadesSignedDataObject();
    };

    Napi::Value SignedData::signCades(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 1);

      int iCadesType = CADESCOM_CADES_DEFAULT;
      int iEncodingType = CAPICOM_ENCODE_BASE64;
      BOOL bDetached = false;


      if (!info[0].IsObject()) {
        Napi::TypeError::New(env, "First parameter must be Signer").ThrowAsJavaScriptException();
        return env.Undefined();
      }
      Napi::Object obj = info[0].As<Napi::Object>();
      Signer* signer = Signer::Unwrap(obj);

      if (info[1].IsNumber()) {
        iCadesType = (int) info[1].As<Napi::Number>().Uint32Value();
      }
      CADESCOM_CADES_TYPE cadesType = (CADESCOM_CADES_TYPE)iCadesType;

      if (info[2].IsBoolean()) {
        BOOL bDetached = info[2].ToBoolean();
      }

      if (info[3].IsNumber()) {
        iEncodingType = (int) info[3].As<Napi::Number>().Uint32Value();
      }
      CAPICOM_ENCODING_TYPE encodingType = (CAPICOM_ENCODING_TYPE)iEncodingType;


      CryptoPro::CBlob blobSignedMessage;
      HRESULT result = this->cadesSignedData->SignCades(signer->cadesSigner, cadesType, bDetached, encodingType, &blobSignedMessage);
      HR_METHOD_ERRORCHECK_RETURN(env, "SignedData signCades error: 0x%08X", result);

      return Napi::Buffer<char>::Copy(env, (const char *) blobSignedMessage.pbData(), blobSignedMessage.cbData());

    }

    void SignedData::setContent(const Napi::CallbackInfo& info, const Napi::Value& value) {
        Napi::Env env = info.Env();

        if (!value.IsString()) {
            Napi::TypeError::New(env, "SignedData content wrong value").ThrowAsJavaScriptException();
            return;
        }

        std::string szContent = value.As<Napi::String>().Utf8Value();
        CAtlString sContent = CAtlString(szContent.c_str());
        HRESULT result = this->cadesSignedData->put_Content(sContent.GetString(), sContent.GetLength());
        HR_METHOD_ERRORCHECK(env, "SignedData set content error: 0x%08X", result);
    }

    Napi::Value SignedData::getContent(const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();
        CStringBlob blobContent;
        HRESULT result = this->cadesSignedData->get_Content(blobContent);
        HR_METHOD_ERRORCHECK_RETURN(env, "SignedData get content error: 0x%08X", result);
        return Napi::String::New(env, blobContent.GetString());
    }

    Napi::Value SignedData::verifyCades(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 1);

      if (!info[0].IsBuffer()) {
        Napi::TypeError::New(env, "SignedData verifyCades wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
      }

      Napi::Uint8Array arr = info[0].As<Napi::Uint8Array>();

      CryptoPro::CBlob blobData;
      blobData.assign((unsigned char *) arr.Data(), arr.ByteLength());

      int iCadesType = CADESCOM_CADES_DEFAULT;
      int iEncodingType = CAPICOM_ENCODE_BASE64;
      BOOL bDetached = false;

      if (info[1].IsNumber()) {
        iCadesType = (int) info[1].As<Napi::Number>().Uint32Value();
      }
      CADESCOM_CADES_TYPE cadesType = (CADESCOM_CADES_TYPE)iCadesType;

      if (info[2].IsBoolean()) {
        BOOL bDetached = info[2].ToBoolean();
      }

      HRESULT result = this->cadesSignedData->VerifyCades(blobData, cadesType, bDetached);
      if (result = CRYPT_E_SIGNER_NOT_FOUND) {
        return Napi::Boolean::New(env, false);
      }
      else HR_METHOD_ERRORCHECK_RETURN(env, "SignedData verifyCades error: 0x%08X", result);

      return Napi::Boolean::New(env, true);

    }
}