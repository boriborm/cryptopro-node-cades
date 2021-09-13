#include "stdafx.h"
#include "EnvelopedData.h"
#include "Certificate.h"
#include "Recipients.h"
#include "Store.h"
#include "Signer.h"
#include "HashedData.h"
#include "SignedData.h"


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

  NodeCades::EnvelopedData::Init(env, exports);
  NodeCades::Store::Init(env, exports);
  NodeCades::Certificate::Init(env, exports);
  NodeCades::Recipients::Init(env, exports);
  NodeCades::Signer::Init(env, exports);
  NodeCades::HashedData::Init(env, exports);
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

  //_CAPICOM_HASH_ALGORITHM
  exports.Set("CAPICOM_HASH_ALGORITHM_SHA1", Napi::Number::New(env, CAPICOM_HASH_ALGORITHM_SHA1));
  exports.Set("CAPICOM_HASH_ALGORITHM_MD2", Napi::Number::New(env, CAPICOM_HASH_ALGORITHM_MD2));
  exports.Set("CAPICOM_HASH_ALGORITHM_MD4", Napi::Number::New(env, CAPICOM_HASH_ALGORITHM_MD4));
  exports.Set("CAPICOM_HASH_ALGORITHM_MD5", Napi::Number::New(env, CAPICOM_HASH_ALGORITHM_MD5));
  exports.Set("CAPICOM_HASH_ALGORITHM_SHA_256", Napi::Number::New(env, CAPICOM_HASH_ALGORITHM_SHA_256));
  exports.Set("CAPICOM_HASH_ALGORITHM_SHA_384", Napi::Number::New(env, CAPICOM_HASH_ALGORITHM_SHA_384));
  exports.Set("CAPICOM_HASH_ALGORITHM_SHA_512", Napi::Number::New(env, CAPICOM_HASH_ALGORITHM_SHA_512));
  exports.Set("CADESCOM_HASH_ALGORITHM_CP_GOST_3411", Napi::Number::New(env, CADESCOM_HASH_ALGORITHM_CP_GOST_3411));
  exports.Set("CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256", Napi::Number::New(env, CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256));
  exports.Set("CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_512", Napi::Number::New(env, CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_512));
  exports.Set("CADESCOM_HASH_ALGORITHM_CP_GOST_3411_HMAC", Napi::Number::New(env, CADESCOM_HASH_ALGORITHM_CP_GOST_3411_HMAC));
  exports.Set("CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256_HMAC", Napi::Number::New(env, CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256_HMAC));
  exports.Set("CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_512_HMAC", Napi::Number::New(env, CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_512_HMAC));

  return exports;

}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)