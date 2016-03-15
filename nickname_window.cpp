#include "nickname_window.h"

NicknameWindow::NicknameWindow()
{
    setWindowTitle("Mamonov_Chat"); // задание названия формы
    setFixedSize(300, 100);    // задание размера формы

    QVBoxLayout *main_layout = new QVBoxLayout();  // вертикальный слой для отображения элементов управления
    QHBoxLayout *send_layout = new QHBoxLayout();  // горизонтальный слой для отображения элементов управления

    nickname_box = new QLineEdit(); //поле для ввода имени пользователя
    nickname_box->setMaxLength(24); // задание максимальной длинны имени пользователя

    confirm_button = new QPushButton("Ok");  // создание кнопки "ОК"
    discard_button = new QPushButton("Exit"); // создание кнопки "Exit"

    main_layout->addWidget(new QLabel("Name:")); // добавление надписи Name на вертикальный слой
    main_layout->addWidget(nickname_box); // добавление поля для ввода текста на вертикальный слой
    send_layout->addWidget(confirm_button); // добавление кнопки "ОК" на горизонтальный слой
    send_layout->addWidget(discard_button); // добавление кнопки "Exit" на горизонтальный слой
    main_layout->addLayout(send_layout); // добавление горизонтального слоя на вертикальный
    setLayout(main_layout); // установка слоя для формы

    connect(confirm_button, SIGNAL(clicked()), this, SLOT(confirm())); //соединение сигнала нажатия кнопки "ОК" с соотвествующим слотом (confirm())
    connect(discard_button, SIGNAL(clicked()), this, SLOT(discard()));//соединение сигнала нажатия кнопки "Exit" с соотвествующим слотом (discard())

    file = new QFile("nickname.ini");  // файл в котором хранится имя пользователя
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {} // если чтение из файла невозможно, ничего не делать
    else
        //иначе считываем текст из файла
        {
        QTextStream in(file); // создаем обьект для считывания, записываем в него содержимое файла
        

	while (!in.atEnd())
            {
            nickname_box->setText(in.readLine().toStdString().c_str()); // записываем содержимое файла в поле для ввода (приводя его в нужный формат)
            }
        file->close();//закрытие файла
        }
    show();
}

void NicknameWindow::confirm()  // Кнопка "OK"
{
    if(MainWindow::messageCorrectness(nickname_box->text())) {   //если -----
        close();  // закрыть текущее окно

        // запись имени пользователя в файл
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){ }
        else
        {
            QTextStream out(file);
            out << nickname_box->text();
            file->close();
        }

        MainWindow *window = new MainWindow(nickname_box->text()); // создание нового окна
    }
}

void NicknameWindow::discard() // Кнопка "Exit"
{
    qApp->exit(); // Выход
}
