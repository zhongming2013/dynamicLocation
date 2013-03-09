#ifndef EMPLOYEEFORM_H
#define EMPLOYEEFORM_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QDialogButtonBox>

class EmployeeForm : public QDialog
{
    Q_OBJECT

public:
    EmployeeForm(int id, QWidget *parent = 0);
    void done(int result);

private slots:
    void addEmployee();
    void deleteEmployee();

private:
    enum
    {
        Employee_Id = 0,
        Employee_NetId,
        Employee_Name,
        Employee_Department,
        Employee_Extension,//分机号
        Employee_Email,
        Employee_StartDate//进入公司的日期
    };
    QSqlTableModel *tableModel;
    QDataWidgetMapper *mapper;

    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *departmentLabel;
    QLineEdit *departmentEdit;
    QLabel *extensionLabel;
    QLineEdit *extensionEdit;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QLabel *startDateLabel;
    QDateEdit *startDateEdit;

    QPushButton *firstButton;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *lastButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *closeButton;
    QDialogButtonBox *buttonBox;
};

#endif // EMPLOYEEFORM_H
