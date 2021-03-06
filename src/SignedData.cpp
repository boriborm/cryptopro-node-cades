#include "SignedData.h"


using namespace CryptoPro::PKI::CAdES;
namespace NodeCades {

    Napi::FunctionReference SignedData::constructor;

    void SignedData::Init(Napi::Env env, Napi::Object exports){
        Napi::HandleScope scope(env);
        Napi::Function ctor = DefineClass(env, "SignedData", {
            InstanceMethod("signCades", &SignedData::SignCades),
            InstanceMethod("signHash", &SignedData::SignHash),
            InstanceMethod("verifyCades", &SignedData::VerifyCades),
            InstanceMethod("verifyHash", &SignedData::VerifyHash),
            InstanceMethod("EnhanceCades", &SignedData::EnhanceCades),
            InstanceAccessor("content", &SignedData::getContent, &SignedData::setContent),
            InstanceAccessor("signers", &SignedData::getSigners, nullptr),
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

    Napi::Value SignedData::SignCades(const Napi::CallbackInfo& info) {

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

    Napi::Value SignedData::VerifyCades(const Napi::CallbackInfo& info) {

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
      BOOL bDetached = false;

      if (info[1].IsNumber()) {
        iCadesType = (int) info[1].As<Napi::Number>().Uint32Value();
      }
      CADESCOM_CADES_TYPE cadesType = (CADESCOM_CADES_TYPE)iCadesType;

      if (info[2].IsBoolean()) {
        BOOL bDetached = info[2].ToBoolean();
      }

      HRESULT result = this->cadesSignedData->VerifyCades(blobData, cadesType, bDetached);
      if (result == CRYPT_E_SIGNER_NOT_FOUND) {
        return Napi::Boolean::New(env, false);
      }
      else HR_METHOD_ERRORCHECK_RETURN(env, "SignedData verifyCades error: 0x%08X", result);

      return Napi::Boolean::New(env, true);

    }

    Napi::Value SignedData::SignHash(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 2);

      int iCadesType = CADESCOM_CADES_DEFAULT;
      int iEncodingType = CAPICOM_ENCODE_BASE64;

      if (!info[0].IsObject()) {
        Napi::TypeError::New(env, "First parameter must be HashedData").ThrowAsJavaScriptException();
        return env.Undefined();
      }
      HashedData* hashedData = HashedData::Unwrap(info[0].As<Napi::Object>());

      if (!info[1].IsObject()) {
        Napi::TypeError::New(env, "Second parameter must be Signer").ThrowAsJavaScriptException();
        return env.Undefined();
      }
      Signer* signer = Signer::Unwrap(info[1].As<Napi::Object>());

      if (info[2].IsNumber()) {
        iCadesType = (int) info[2].As<Napi::Number>().Uint32Value();
      }
      CADESCOM_CADES_TYPE cadesType = (CADESCOM_CADES_TYPE)iCadesType;

      if (info[3].IsNumber()) {
        iEncodingType = (int) info[3].As<Napi::Number>().Uint32Value();
      }
      CAPICOM_ENCODING_TYPE encodingType = (CAPICOM_ENCODING_TYPE)iEncodingType;

      CryptoPro::CBlob blobSignedMessage;
      HRESULT result = this->cadesSignedData->SignHash(signer->cadesSigner, hashedData->cadesHashedData, cadesType, encodingType, &blobSignedMessage);
      HR_METHOD_ERRORCHECK_RETURN(env, "SignedData signHash error: 0x%08X", result);

      return Napi::Buffer<char>::Copy(env, (const char *) blobSignedMessage.pbData(), blobSignedMessage.cbData());

    }

    Napi::Value SignedData::VerifyHash(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 2);

      if (!info[0].IsObject()) {
        Napi::TypeError::New(env, "SignedData verifyHash wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
      }

      if (!info[1].IsBuffer()) {
        Napi::TypeError::New(env, "SignedData verifyHash wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
      }
      HashedData* hashedData = HashedData::Unwrap(info[0].As<Napi::Object>());
      Napi::Uint8Array arr = info[1].As<Napi::Uint8Array>();

      int iCadesType = CADESCOM_CADES_DEFAULT;

      if (info[2].IsNumber()) {
        iCadesType = (int) info[2].As<Napi::Number>().Uint32Value();
      }
      CADESCOM_CADES_TYPE cadesType = (CADESCOM_CADES_TYPE)iCadesType;

      CryptoPro::CBlob blobData;
      blobData.assign((unsigned char *) arr.Data(), arr.ByteLength());

      HRESULT result = this->cadesSignedData->VerifyHash(hashedData->cadesHashedData, blobData, cadesType);
      if (result == CRYPT_E_SIGNER_NOT_FOUND) {
        return Napi::Boolean::New(env, false);
      }
      else HR_METHOD_ERRORCHECK_RETURN(env, "SignedData verifyHash error: 0x%08X", result);

      return Napi::Boolean::New(env, true);

    }

    Napi::Value SignedData::getSigners(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();

      boost::shared_ptr<CPPCadesCPSignersObject> cadesSigners;
      HRESULT result = this->cadesSignedData->get_Signers(cadesSigners);
      HR_METHOD_ERRORCHECK_RETURN(env, "SignedData getSigners error: 0x%08X", result);

      unsigned int signersCount;
      result = cadesSigners->get_Count(&signersCount);
      HR_METHOD_ERRORCHECK_RETURN(env, "SignedData getSigners getCount error: 0x%08X", result);

      Napi::Array signers = Napi::Array::New(env, signersCount);

      boost::shared_ptr<CPPCadesCPSignerObject> cadesSigner;

      for (unsigned int i = 0; i < signersCount; i++) {

        result = cadesSigners->get_Item(i+1, cadesSigner);
        HR_METHOD_ERRORCHECK_RETURN(env, "SignedData getSigners getItem() error: 0x%08X", result);
        signers[i] = Signer::New(env, &cadesSigner);
      }

      return signers;
    }

    Napi::Value SignedData::EnhanceCades(const Napi::CallbackInfo& info) {

      Napi::Env env = info.Env();
      COUNT_OF_ARGUMENTS_CHECK(info, env, 3);

      int iCadesType = CADESCOM_CADES_DEFAULT;

      if (info[0].IsNumber()) {
          iCadesType = (int) info[2].As<Napi::Number>().Uint32Value();
      }
      CADESCOM_CADES_TYPE cadesType = (CADESCOM_CADES_TYPE)iCadesType;

      std::string szTSAAddress = "";
      if (info[1].IsString()) {
        szTSAAddress = info[1].As<Napi::String>().Utf8Value();
      }

      long lEncodingType = CAPICOM_ENCODE_BASE64;
      if (info[2].IsNumber()) {
        lEncodingType = (int) info[2].As<Napi::Number>().Uint32Value();
      }
      CAPICOM_ENCODING_TYPE encodingType = (CAPICOM_ENCODING_TYPE)lEncodingType;

      CryptoPro::CBlob blobData;

      HRESULT result = this->cadesSignedData->EnhanceCades(cadesType, CAtlString(szTSAAddress.c_str()), encodingType, &blobData);
      HR_METHOD_ERRORCHECK_RETURN(env, "SignedData EnhanceCades error: 0x%08X", result);



      if (encodingType == CAPICOM_ENCODE_BINARY){
        return Napi::Buffer<char>::Copy(env, (const char *) blobData.pbData(), blobData.cbData());
      }

      CAtlString sValue = CAtlString((const char *)blobData.pbData(), blobData.cbData());

      return Napi::String::New(env, sValue.GetString());

    }
}