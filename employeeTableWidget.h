#ifndef EMPLOYEETABLEWIDGET_H
#define EMPLOYEETABLEWIDGET_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>

class EmployeeTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    EmployeeTableWidget();

public slots:
    void updateTable(const int fixId);

private:
    QStringList rowLabel;
    QStringList columnLabel;

    QTableWidgetItem *fixIdItem;
    QTableWidgetItem *nameItem;
    QTableWidgetItem *deptItem;
    QTableWidgetItem *extensionItem;
    QTableWidgetItem *emailItem;
    QTableWidgetItem *startDateItem;
};

#endif // EMPLOYEETABLEWIDGET_H
