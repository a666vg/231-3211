#include <QApplication>
#include "functions_for_client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FunctionsForClient window;

    return app.exec();
}
