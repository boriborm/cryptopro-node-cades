const Cades = require('../build/Release/NodeCades.node');
const testEncryptAndDecrypt = true,
      testCertificates = true,
      testSignCades=true,
      testSignHash=true,
      testCertificateThumbprint = "610A3B2E77EB6B49B6E083603517CFE67A7CB647",
      testText = "123 test Тест!!"
;

let e;
let certs;

const openStore = ()=>{
  const store = new Cades.Store();
  store.open(Cades.CADESCOM_CONTAINER_STORE, Cades.CAPICOM_MY_STORE, Cades.CAPICOM_STORE_OPEN_READ_ONLY);
  return store;
}

const getCerts = ()=>{
  const s = openStore();
  const certs = s.certificates;
  s.close();
  return certs;
}
const getTestCert = ()=>{
  const s = openStore();
  const certs = s.certificates;
  s.close();
  let cert;
  for (cert of certs){
    if (cert.thumbprint === testCertificateThumbprint) break;
  }
  return cert||certs[0];
}

function printCertificate(c){
  console.log('cert:', c);
  console.log('thumbprint:', c.thumbprint);
  console.log('serial:', c.serialNumber);
  console.log('subject:', c.subjectName);
  console.log('issuer:', c.issuerName);
}

if (testCertificates) {
  console.log("---- Get Certificates list ------------------------------------");
  certs = getCerts();
  for (const c of certs) {
    printCertificate(c);
  }
}

if (testEncryptAndDecrypt) {
    console.log("---- Test Encrypt and Decrypt------------------------------------");
    console.log("Text for encryption:", testText);
    certs = getCerts();
    e = new Cades.EnvelopedData();
    e.content = testText;
    e.recipients.add(getTestCert());
    // enc - Buffer
    let enc = e.encrypt(Cades.CAPICOM_ENCODE_BASE64);
    console.log("Encrypted:\n", enc.toString());
    console.log("Decrypted: ", e.decrypt(enc));
}

if (testSignCades) {
  console.log("---- Test SignCades  ------------------------------------");
  console.log("Text for sign:", testText);
  const cert = getTestCert();
  printCertificate(cert);
  const signer1 = new Cades.Signer()
  signer1.certificate = cert;
  signer1.checkCertificate = true;
  const signData = new Cades.SignedData();
  signData.content = testText;
  // sign - Buffer
  let sign = signData.signCades(signer1, Cades.CADESCOM_CADES_BES, false, Cades.CAPICOM_ENCODE_BASE64);
  console.log('signed data:');
  console.log(sign.toString());
  const signer2 = new Cades.SignedData();
  console.log("verify sign:", signer2.verifyCades(sign, Cades.CADESCOM_CADES_BES));
}

if (testSignHash) {
  console.log("---- Test SignHash  ------------------------------------");
  console.log("Text for sign:", testText);
  const cert = getTestCert();
  printCertificate(cert);

  const signer3 = new Cades.Signer()
  signer3.certificate = cert;
  signer3.checkCertificate = true;

  const hash = new Cades.HashedData();
  hash.algorithm = Cades.CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256;
  console.log("Hash algorithm:", hash.algorithm);
  hash.hash(testText);

  const signData = new Cades.SignedData();
  signData.content = testText;
  let sign = signData.signHash(hash, signer3, Cades.CADESCOM_CADES_BES, false, Cades.CAPICOM_ENCODE_BASE64);
  console.log('signed hash:');
  console.log(sign.toString());
  const signer4 = new Cades.SignedData();
  console.log("verify hash sign:", signer4.verifyHash(hash, sign, Cades.CADESCOM_CADES_BES));

}