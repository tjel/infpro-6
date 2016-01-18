# Wersja okienkowa:

Klasy **MainWindow**i **ChatWidget** udostêpniaj¹ publicznie swoje obiekty *ui* logice komunikatora.

Ka¿dy **ChatWindow** obs³uguje komunikacjê z jednym adresem IP. Posiada wskaŸnik na wid¿et, w którym siê ona odbywa oraz adres IP odbiorcy i *TcpSockety* do wysy³ania i odbierania wiadomoœci. Obiekt mo¿e zostaæ zainicjowany na dwa sposoby: przez u¿ytkownika nawi¹zuj¹cego po³¹czenie lub po zaakceptowaniu sygnalizowanego przez *QTcpServer* po³¹czenia przychodz¹cego.

Klasa **Chat** uruchamia serwer odbieraj¹cy nowe po³¹czenia. Tworzy nowe instancjê *Chat Window* wraz z przypisanymi im zak³adkami interfejsu graficznego, przekazuj¹c im równie¿ socket do odczytu wiadomoœci. Posiada wskaŸnik na *MainWindow::ui*.