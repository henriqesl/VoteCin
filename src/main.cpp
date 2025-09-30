#include "mainwindow.h" // Funciona por causa do 'target_include_directories' no CMakeLists.txt
#include <QApplication>

int main(int argc, char *argv[])
{
    // Cria a aplicação
    QApplication a(argc, argv);

    // Cria a sua janela principal
    MainWindow w;

    // Mostra a janela
    w.show();

    // Inicia o loop de eventos da aplicação
    return a.exec();
}
