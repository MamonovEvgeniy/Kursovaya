#ifndef MESSAGE_MONITOR_H
#define MESSAGE_MONITOR_H

#include <QtNetwork>
#include <QtWidgets>
#define PORT 5432

enum MessageType  // перечисление используемых типов сообщения
{
    Data = 1,
    Hello = 2,
    Answer = 3,
    Goodbye = 4
};

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QString n);
    static bool messageCorrectness(QString message); // функция проверки

    private:
    QUdpSocket *socket; //

    QTextEdit* output_box; // поле для отображения сообщений
    QString output_string; // строковая переменная
    QString nickname;      // строковая переменная

    QLineEdit* message_box; // поле для ввода сообщений
    QPushButton *send_button; // кнопка для отправки сообщений

    QList<QHostAddress> adresses_list; // список в котором будут хранится адреса пользователей
    QList<QString> nicknames_list; // список в котором будут хранится имена пользователей
    QHostAddress newbie_address;

    void addClient(QHostAddress address, QString nickname); // функция добавления клиента
    void deleteClient(QHostAddress address); // функция удаления клиента

public slots:
    void keyPressEvent(QKeyEvent *event); // обработка события нажатия клавиш

private slots:
    void getMessage(); // функция получения сообщения
    void sendDataMessage(); // функция отправки сообщения
    void sendHelloMessage(); // функция отправки сообщения о присоединении пользователя к чату
    void sendAnswerMessage();
    void sendGoodbyeMessage();// функция отправки сообщения о выходе  пользователя из чата

};

#endif // MESSAGE_MONITOR_H
