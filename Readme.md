# cryptopro-node-cades

Модуль Node.js, используемый для работы с КриптоПро библиотекой.
Данный модуль на текущий момент был протестирован только на Node.Js версии 14.17 и на операционной системе Ubuntu 20.04. Версия Node.Js должна поддерживать [Node-API](https://nodejs.org/api/n-api.html#n_api_node_api). 

## Установка

1. Скачать КриптоПро CSP (тестировалось на версии 5.0).
2. Установить пакеты:
   - `lsb-cprocsp-base`;
   - `lsb-cprocsp-rdr-64`;
   - `lsb-cprocsp-kc1-64`;
   - `lsb-cprocsp-pkcs11-64`;
   - `lsb-cprocsp-capilite-64`;
   - `lsb-cprocsp-devel` - требуется только для сборки node модуля из исходников;
   - `lsb-cprocsp-ca-certs` - корневые сертификаты и сертификаты промежуточных УЦ. Требуются для теста;    
3. Скачать [КриптоПро SDK](https://cryptopro.ru/products/cades/downloads) и установить `cprocsp-pki-cades-64`
4. В стандартных пакетах отсутствуют некоторые файлы, которые нужно взять из архива pycades по [ссылке](https://cryptopro.ru/sites/default/files/products/cades/pycades/pycades.zip).
Инструкия по установке pycades со всеми необходимым ссылками, указанными выше, находится по [ссылке](https://docs.cryptopro.ru/cades/pycades/pycades-build).
Саму pycades собирать не нужно!
   
5. В проект `cryptopro-node-cades` в папку `src` скопировать из архива `pycades`:
    - файл `cpstldll.h`;
    - каталог `cplib`;
    
6. В каталог `/opt/cprocsp/include/pki/atl` скопировать папку `/opt/cprocsp/include/reader`  

## Сборка

В каталоге проекта выполнить `npm install`
В случае успешной сборки появится файл `build/Release/NodeCades.node`

## Использование модуля
Пример использования модуля находится в файле `test/index.js`.
Для его корректной работы необходимо прописать отпечаток предварительно установенного сертификата в переменной `testCertificateThumbprint`

Для использования модуля в других проектах достаточно скопировать файл `NodeCades.node` в нужный проект и подключить его директивой `require('./NodeCades.node');`
