#include <QtGui/QApplication>
#include "mainwindow.h"
#include "dbConnect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./");

    if(!createConnection())
        return 1;

//    QSqlQueryModel model;
//    model.setQuery("select * from node");
//    QTableView *view = new QTableView;
//    view->setModel(&model);
//    view->setColumnHidden(0, true);
//    view->resizeColumnsToContents();
//    view->show();

    MainWindow w;
    w.show();
    
    return a.exec();
}
