const Cades = require('../build/Release/NodeCades.node');
const testEncryptAndDecrypt = true,
      testCertificates = true,
      testSignCades=true,
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
    let enc = e.encrypt(Cades.CAPICOM_ENCODE_BASE64);
    console.log("Encrypted:\n", enc.toString());
    console.log("Decrypted: ", e.decrypt(enc));
}

if (testSignCades) {
  console.log("---- Test SignCades  ------------------------------------");
  console.log("Text for sign:", testText);
  const cert = getTestCert();
  printCertificate(cert);
  const signer = new Cades.Signer()
  signer.certificate = cert;
  signer.checkCertificate = true;
  const signData = new Cades.SignedData();
  signData.content = testText;
  const sign = signData.signCades(signer, Cades.CADESCOM_CADES_BES, false, Cades.CAPICOM_ENCODE_BASE64);
  console.log(sign.toString());
}