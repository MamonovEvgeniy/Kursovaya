#include <QApplication>
#include "nickname_window.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    NicknameWindow *window = new NicknameWindow();
    return app.exec(); //запуск приложения
}
