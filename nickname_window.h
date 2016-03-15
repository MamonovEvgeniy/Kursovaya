#ifndef NICKNAME_WINDOW_H
#define NICKNAME_WINDOW_H

#include <QtWidgets>
#include "main_window.h"

class NicknameWindow : public QWidget
{
    Q_OBJECT
public:
    NicknameWindow();

private:
    QLineEdit *nickname_box; // поле для ввода
    QPushButton *confirm_button; // кнопка
    QPushButton *discard_button; // кнопка
    QFile *file; // обьект типа File

private slots:
    void confirm(); // слот для кнопки "ОК"
    void discard(); // слот для кнопки "Exit"
};

#endif // NICKNAME_WINDOW_H
