{
  "targets": [
    {
      "target_name": "NodeCades",
      "cflags_cc": [ "-std=c++11"],
      "cflags!": [ "-Wall","-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions","-std=gnu++1y" ],
      "sources": [
        "./src/addon.cpp",
        "./src/EnvelopedData.cpp",
        "./src/Certificate.cpp",
        "./src/Recipients.cpp",
        "./src/Store.cpp",
        "./src/Signer.cpp",
        "./src/HashedData.cpp",
        "./src/SignedData.cpp",

      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "conditions": [
        [ "OS==\"linux\"", {
          "defines": [
            "UNIX"
          ],
          "cflags": [
            "-Wno-write-strings",
            "-Wno-deprecated-declarations",
            "-Wno-narrowing"
          ],
          "include_dirs": [
            "src/",
            "src/cplib",
            "/opt/cprocsp/include",
            "/opt/cprocsp/include/cpcsp",
            "/opt/cprocsp/include/pki/atl",
            "/opt/cprocsp/include/pki/cppcades",
            "/opt/cprocsp/include/pki"
          ],
          "link_settings": {
            "library_dirs": ["/opt/cprocsp/lib/amd64/"],
          },
          "libraries":[
            "/opt/cprocsp/lib/amd64/libcppcades.so"
          ]
        }],
        [ "OS==\"win\"", {
          "defines": [
            "WINDOWS_SPECIFIC_DEFINE"
          ]
        }]
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
    }
  ]
}
