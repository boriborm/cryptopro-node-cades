# cryptopro-node-cades

Модуль Node.js, используемый для работы с КриптоПро библиотекой.
Данный модуль на текущий момент был протестирован только на Node.Js версии 14.17 и на операционной системе Ubuntu 20.04. Версия Node.Js должна поддерживать [Node-API](https://nodejs.org/api/n-api.html#n_api_node_api). 

## Установка

1. Установить КриптоПро CSP (тестировалось на версии 5.0).
Для установи использовать `install_gui.sh`
При установке КриптоПро выбирать пункты:
    - Криптопровайдер КС1;
    - Библиотека PKCS #11;
    - cptools, многоцелевое графическое приложение; (опционально)

2. Скачать [КриптоПро SDK](https://cryptopro.ru/products/cades/downloads) и установить `cprocsp-pki-cades`
3. Установить пакет `lsb-cprocsp-devel` из дистрибутива CryptoPro
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
Для его корректной работы необходимо прописать отпечаток сертификата в переменной `testCertificateThumbprint`

Для использования модуля в других проектах достаточно скопировать файл `NodeCades.node` в нужный проект и подключить его директивой `require('./NodeCades.node');`
Для его работы необходимо сделать установку КриптоПро CSP и КриптоПро SDK согласно пунктам 1 и 2
