#include <QCoreApplication>
#include "server.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Server s;
    if (s.open("9999")) {
        return a.exec();
    }
    
    return 1;
}
