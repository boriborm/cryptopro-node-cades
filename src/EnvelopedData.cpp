#include "EnvelopedData.h"

using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    Napi::FunctionReference EnvelopedData::constructor;

    void EnvelopedData::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);
        Napi::Function ctor = DefineClass(env, "EnvelopedData", {
            InstanceAccessor("recipients", &EnvelopedData::getRecipients, nullptr),
            InstanceMethod("decrypt", &EnvelopedData::Decrypt),
            InstanceMethod("encrypt", &EnvelopedData::Encrypt),
            InstanceAccessor("content", &EnvelopedData::getContent, &EnvelopedData::setContent),
        });
        exports.Set("EnvelopedData", ctor);
        constructor = Napi::Persistent(ctor);
        constructor.SuppressDestruct();
    }

    EnvelopedData::EnvelopedData(const Napi::CallbackInfo& info) : Napi::ObjectWrap<EnvelopedData>(info) {
      Napi::Env env = info.Env();
      Napi::HandleScope scope(env);
      boost::shared_ptr<CPPCadesCPEnvelopedDataObject> cadesEnvelopedData1 (new CPPCadesCPEnvelopedDataObject());
      cadesEnvelopedData = cadesEnvelopedData1;
    };

    Napi::Value EnvelopedData::Decrypt(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 1);

      if (!info[0].IsBuffer()) {
        Napi::TypeError::New(env, "EnvelopedData decrypt wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
      }

      Napi::Uint8Array arr = info[0].As<Napi::Uint8Array>();

      CryptoPro::CBlob blobData;
      blobData.assign((unsigned char *) arr.Data(), arr.ByteLength());

      HRESULT result = this->cadesEnvelopedData->Decrypt(blobData);
      HR_METHOD_ERRORCHECK_RETURN(env, "EnvelopedData decrypt error: 0x%08X", result);

      return this->getContent(info);
    }

    Napi::Value EnvelopedData::Encrypt(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();

      int iEncodingType = CAPICOM_ENCODE_BASE64;
      if (info[0].IsNumber()) {
        iEncodingType = (int) info[0].As<Napi::Number>().Uint32Value();
      }

      CAPICOM_ENCODING_TYPE encodingType = (CAPICOM_ENCODING_TYPE)iEncodingType;

      CryptoPro::CBlob blobData;
      HRESULT result = this->cadesEnvelopedData->Encrypt(encodingType, blobData);
      HR_METHOD_ERRORCHECK_RETURN(env, "EnvelopedData encrypt error: 0x%08X", result);

      return Napi::Buffer<char>::Copy(env, (const char *) blobData.pbData(), blobData.cbData());
    }

    Napi::Value EnvelopedData::getRecipients(const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();
        return Recipients::New(env, &cadesEnvelopedData);
    }

    void EnvelopedData::setContent(const Napi::CallbackInfo& info, const Napi::Value& value) {
        Napi::Env env = info.Env();

        if (!value.IsString()) {
            Napi::TypeError::New(env, "EnvelopedData content wrong value").ThrowAsJavaScriptException();
            return;
        }

        std::string szContent = value.As<Napi::String>().Utf8Value();
        CAtlString sContent = CAtlString(szContent.c_str());
        HRESULT result = this->cadesEnvelopedData->put_Content(sContent.GetString(), sContent.GetLength());
        HR_METHOD_ERRORCHECK(env, "EnvelopedData set content error: 0x%08X", result);
    }

    Napi::Value EnvelopedData::getContent(const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();
        CStringBlob blobContent;
        HRESULT result = this->cadesEnvelopedData->get_Content(blobContent);
        HR_METHOD_ERRORCHECK_RETURN(env, "EnvelopedData get content error: 0x%08X", result);
        return Napi::String::New(env, blobContent.GetString());
    }
}