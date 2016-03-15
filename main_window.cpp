#include "main_window.h"


MainWindow::MainWindow(QString n) : nickname(n) {
    socket = new QUdpSocket(); //создание сокета
    connect(socket, SIGNAL(readyRead()), this, SLOT(getMessage())); //соединение сигнала сокета (готов к чтению) со слотом getMessage(принять сообщение)

    setWindowTitle("Mamonov_CHAT - [" + nickname + "]"); // задание названия формы
    setMinimumSize(400, 600); // задание размера формы

    QVBoxLayout *main_layout = new QVBoxLayout();  // вертикальный слой для отображения элементов управления
    QHBoxLayout *send_layout = new QHBoxLayout();   // горизонтальный слой для отображения элементов управления

    output_box = new QTextEdit(); // поле для отображения сообщений
    output_box->setReadOnly(true); // делаем текст в поле для отображения сообщений доступным ТОЛЬКО для чтения

    message_box = new QLineEdit();  //поле для ввода сообщений
    message_box->setMaxLength(128); //максимальная длина поля для ввода сообщений

    send_button = new QPushButton("Send"); //кнопка "Send"
    send_button->setFixedWidth(50); // размер кнопки
    connect(send_button, SIGNAL(clicked()), this, SLOT(sendDataMessage())); //соединение сигнала нажатия кнопки со слотом sendDataMessage(отправить сообщение)

    // добавление виджетов на слои
    main_layout->addWidget(output_box);
    send_layout->addWidget(message_box);
    send_layout->addWidget(send_button);
    main_layout->addLayout(send_layout);
    setLayout(main_layout); // установить слой для формы
    show();

    socket->bind(PORT); // установка сокета в режим прослушивания порта
    sendHelloMessage(); //вызов функции добавляющей сообщение о присоединении к чату
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(sendGoodbyeMessage())); //соединение сигнала выхода из приложения со слотом sendGoodbyeMessage(сообщение о выходе из чата)
}

void MainWindow::getMessage() //получить сообщение
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;   // байтовый массив куда записывается входящее сообщение (в виде байт)
        QString message;       // сюда сообщение переписывается в текстовом виде
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress address; // Адрес отправителя (от кого получили сообщение)
        quint16 port;         // Адрес отправителя (от кого получили сообщение)

        socket->readDatagram(datagram.data(), datagram.size(), &address, &port);  // считываем текущую датаграмму(сообщение)

        message = datagram.data(); // Возвращает указатель на данные сохраненные в массиве
        int type = message.at(0).digitValue(); // первый символ преобразуется в число
        message.remove(0, 1);  // удаляем первый символ из сообщения

        switch(type)
        {
        case Data :
        {
            for (int i = 0; i < adresses_list.size(); ++i)
            {
                if (adresses_list.at(i) == address) { // перебор адресов (если текущий адрес имеется в списке то сообщение выводится)
                    output_string += "<h6>[ " + QTime::currentTime().toString() + " ] <b>" + nicknames_list.at(i) + ":</b> " + message.toStdString().c_str() + "</h6>"; //вывод полученного сообщения с указанием даты и имени отправителя
                    output_box->setText(output_string);
                    break;
                }
            }
            break;
        }  
        case Hello :
        {
            addClient(address, message); // текущий отправитель добавляется в перечень клиентов
            newbie_address = address;
            output_string += "<h6>[ " + QTime::currentTime().toString() + " ] User <b>" + message + "</b> enters CHAT</h6>"; //оповещение о добавлениии нового пользователя в чат
            output_box->setText(output_string);
            sendAnswerMessage(); // // отправка ответа на приветственное сообщение
            break;
        }         
        case Goodbye :
        {
            deleteClient(address); // текущий отправитель удаляется из перечня клиентов
            output_string += "<h6>[ " + QTime::currentTime().toString() + " ] User <b>" + message + "</b> leaves CHAT</h6>";//оповещение о выходе пользователя из чата
            output_box->setText(output_string);
            break;
        }    
        case Answer :
        {
            addClient(address, message); // текущий отправитель добавляется в перечень клиентов
            break;
        }
        }
    }
}

void MainWindow::sendDataMessage()  // отправить сообщение
{
    int addresses_list_size = adresses_list.size(); // определение количества адресатов
    for(int i = 0; i < addresses_list_size; i++) {
        if(messageCorrectness(message_box->text())) // проверка  на  "не пустое" сообщение
        {
            QString message = QString::number(Data) + message_box->text(); // пометка сообщения как "Данные"
            socket->writeDatagram(QByteArray(message.toStdString().c_str()),adresses_list.at(i), PORT);// отправка сообщения
        }
    }
    message_box->clear();
}

void MainWindow::sendHelloMessage() // функция отправки сообщения о присоединении пользователя к чату
{
    QString message = QString::number(Hello) + nickname;// пометка сообщения как "приветственное сообщение"
    socket->writeDatagram(QByteArray(message.toStdString().c_str()),QHostAddress("192.168.255.255"), PORT); // отправка сообщения
}

void MainWindow::sendAnswerMessage() // отправка ответа на приветственное сообщение
{
    QString message = QString::number(Answer) + nickname; // пометка сообщения как "ответ на приветственное сообщение"
    socket->writeDatagram(QByteArray(message.toStdString().c_str()),newbie_address, PORT); // отправка
}

void MainWindow::sendGoodbyeMessage()  // функция отправки сообщения о выходе  пользователя из чата
{
    QString message = QString::number(Goodbye) + nickname; // пометка сообщения как "сообщение о выходе из чата"
    socket->writeDatagram(QByteArray(message.toStdString().c_str()),QHostAddress("192.168.255.255"), PORT);// отправка
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Return) || (event->key() == Qt::Key_Enter)) //если нажата клафиша Enter
    {
        sendDataMessage(); // отправить сообщение
    }
}

void MainWindow::addClient(QHostAddress address, QString nickname) // добавление пользователя
{
    bool match = false;
    int num;
    for (int i = 0; i < adresses_list.size(); ++i)
    {
        if (adresses_list.at(i) == address) {//если входящий адрес совпал с адресом в списке
            match = true;
            num = i;
            break;
        }
    }
    if (match) {
        nicknames_list.replace(num, nickname);//заменяем старый ник пользователя на новый
    } else {//иначе добавляем данные о новом пользователе
        adresses_list.append(address);
        nicknames_list.append(nickname);
    }
}

void MainWindow::deleteClient(QHostAddress address) // удаление пользователя
{
    for (int i = 0; i < adresses_list.size(); ++i)
    {
        if (adresses_list.at(i) == address)
        {
            adresses_list.removeAt(i);
            nicknames_list.removeAt(i);
            break;
        }
    }

}

bool MainWindow::messageCorrectness(QString message) // проверка  на  "не пустое" сообщение
{
    for (int i = 0; i < message.size(); ++i)
    {
        if (message.at(i) != ' ') {
            return true;
        }
    }
    return false;
}
