#include "stdafx.h"
#include "EnvelopedData.h"
#include "Certificate.h"
#include "Recipients.h"
#include "Store.h"
#include "Signer.h"
#include "SignedData.h"


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

  NodeCades::EnvelopedData::Init(env, exports);
  NodeCades::Store::Init(env, exports);
  NodeCades::Certificate::Init(env, exports);
  NodeCades::Recipients::Init(env, exports);
  NodeCades::Signer::Init(env, exports);
  NodeCades::SignedData::Init(env, exports);

  //_CADESCOM_STORE_LOCATION
  exports.Set("CADESCOM_MEMORY_STORE", Napi::Number::New(env, CADESCOM_MEMORY_STORE));
  exports.Set("CADESCOM_LOCAL_MACHINE_STORE", Napi::Number::New(env, CADESCOM_LOCAL_MACHINE_STORE));
  exports.Set("CADESCOM_CURRENT_USER_STORE", Napi::Number::New(env, CADESCOM_CURRENT_USER_STORE));
  exports.Set("CADESCOM_CONTAINER_STORE", Napi::Number::New(env, CADESCOM_CONTAINER_STORE));
  exports.Set("CADESCOM_ACTIVE_DIRECTORY_USER_STORE", Napi::Number::New(env, CADESCOM_ACTIVE_DIRECTORY_USER_STORE));
  exports.Set("CADESCOM_SMART_CARD_USER_STORE", Napi::Number::New(env, CADESCOM_SMART_CARD_USER_STORE));

  // STORE_TYPES
  exports.Set("CAPICOM_MY_STORE", Napi::String::New(env, "My"));
  exports.Set("CAPICOM_CA_STORE", Napi::String::New(env, "CA"));
  exports.Set("CAPICOM_ROOT_STORE", Napi::String::New(env, "ROOT"));

  //_CAPICOM_STORE_OPEN_MODE
  exports.Set("CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED", Napi::Number::New(env, CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED));
  exports.Set("CAPICOM_STORE_OPEN_READ_ONLY", Napi::Number::New(env, CAPICOM_STORE_OPEN_READ_ONLY));
  exports.Set("CAPICOM_STORE_OPEN_READ_WRITE", Napi::Number::New(env, CAPICOM_STORE_OPEN_READ_WRITE));
  exports.Set("CAPICOM_STORE_OPEN_EXISTING_ONLY", Napi::Number::New(env, CAPICOM_STORE_OPEN_EXISTING_ONLY));
  exports.Set("CAPICOM_STORE_OPEN_INCLUDE_ARCHIVED", Napi::Number::New(env, CAPICOM_STORE_OPEN_INCLUDE_ARCHIVED));

  //_CAPICOM_ENCODING_TYPE
  exports.Set("CAPICOM_ENCODE_BASE64", Napi::Number::New(env, CAPICOM_ENCODE_BASE64));
  exports.Set("CAPICOM_ENCODE_BINARY", Napi::Number::New(env, CAPICOM_ENCODE_BINARY));

  // _CADESCOM_CADES_TYPE
  exports.Set("CADESCOM_CADES_BES", Napi::Number::New(env, CADESCOM_CADES_BES));
  exports.Set("CADESCOM_CADES_DEFAULT", Napi::Number::New(env, CADESCOM_CADES_DEFAULT));
  exports.Set("CADESCOM_PKCS7_TYPE", Napi::Number::New(env, CADESCOM_PKCS7_TYPE));

  return exports;

}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)