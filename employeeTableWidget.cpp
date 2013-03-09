#include "employeeTableWidget.h"
#include <QSqlQuery>

EmployeeTableWidget::EmployeeTableWidget()
{
    setRowCount(6);
    setColumnCount(1);
    rowLabel << "FixID" << "Name" << "Dept." << "Exten." << "Email" << "S.Date";
    columnLabel << "Value";
    setVerticalHeaderLabels(rowLabel);
    setHorizontalHeaderLabels(columnLabel);

    setEditTriggers(QAbstractItemView::DoubleClicked
                    | QAbstractItemView::SelectedClicked);

    fixIdItem = new QTableWidgetItem;
    nameItem = new QTableWidgetItem;
    deptItem = new QTableWidgetItem;
    extensionItem = new QTableWidgetItem;
    emailItem = new QTableWidgetItem;
    startDateItem = new QTableWidgetItem;

    setItem(0, 0, fixIdItem);
    setItem(1, 0, nameItem);
    setItem(2, 0, deptItem);
    setItem(3, 0, extensionItem);
    setItem(4, 0, emailItem);
    setItem(5, 0, startDateItem);
    setColumnWidth(0,180);
}

void EmployeeTableWidget::updateTable(const int fixId)
{
    if(fixId > 0)
    {
        QSqlQuery query;
        query.exec("SELECT name,department,extension,email,startDate "
                      "FROM employee WHERE fixId = " + QString::number(fixId));
        query.next();
        fixIdItem->setText(QString::number(fixId));
        nameItem->setText(query.value(0).toString());
        deptItem->setText(query.value(1).toString());
        extensionItem->setText(query.value(2).toString());
        emailItem->setText(query.value(3).toString());
        startDateItem->setText(query.value(4).toString());
    }
}
