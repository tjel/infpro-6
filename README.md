
Ten program jest program przeznaczony do komunikacji między ludzkiej przy użyciu wspaniałego sprzętu jakim jest komputer. Jest on prosty w użyciu dla osób w (PRAWIE) każdym wieku i stanie fizycznym (nie wliczając osób niewidomych i ślepych).

W programie znajdują się:

Klasy MainWindow i ChatWidget udostępniające publicznie swoje obiekty ui logice komunikatora.

Każdy ChatWindow obsługuje komunikację z jednym adresem IP. Posiada wskaźnik na widżet, w którym się ona odbywa oraz adres IP odbiorcy i QtcpSockety do wysyłania i odbierania wiadomości. Obiekt może zostać zainicjowany na dwa sposoby: przez użytkownika nawiązującego połączenie lub po zaakceptowaniu sygnalizowanego przez QtcpServer połączenia przychodzącego.

Klasa Chat uruchamia serwer odbierający nowe połączenia. Tworzy nowe instancje ChatWindow wraz z przypisanymi im zakładkami interfejsu graficznego, przekazując im również socket do odczytu wiadomości.

Wszystkie wiadomości dostarczane jaki i odpierane są szyfrowane skomplikowanym systemem zaimplementowanym w programie. Przechowywane są one również w archiwum.

By uruchomić program należy do folderu, w którym znajduje się GUI.exe dodać pliki .dll dla systemu 32 bitowego:
1. Qt5Cored.dll
2. icudt51.dll
3. icuin51.dll
4. icuuc51.dll
5. msvcp110d.dll
6. msvcr110d.dll
