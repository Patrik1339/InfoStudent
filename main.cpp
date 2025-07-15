#include <QApplication>
#include "GUI/MainWindow.h"
#include "Repository/Repository.h"
#include "Service/Service.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repository repository;
    const Service service(repository);
    MainWindow m(service);
    m.show();

    return QApplication::exec();
}
