#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QTableView>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DynamicLocation.db");

    if (!db.open())
    {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit.", QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // DBCONNECT_H
