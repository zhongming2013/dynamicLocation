#include "employeeform.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

EmployeeForm :: EmployeeForm(int id, QWidget *parent)
    : QDialog(parent)
{
    nameEdit = new QLineEdit;
    nameLabel = new QLabel(tr("Na&me:"));
    nameLabel->setBuddy(nameEdit);

    departmentEdit = new QLineEdit;
    departmentLabel = new QLabel(tr("Depar&tment:"));
    departmentLabel->setBuddy(departmentEdit);

    extensionEdit = new QLineEdit;
    extensionEdit->setValidator(new QIntValidator(0, 99999, this));
    extensionLabel = new QLabel(tr("E&xtension:"));
    extensionLabel->setBuddy(extensionEdit);

    emailEdit = new QLineEdit;
    emailLabel = new QLabel(tr("&Email:"));
    emailLabel->setBuddy(emailEdit);

    startDateEdit = new QDateEdit;
    startDateEdit->setCalendarPopup(true);
    QDate today = QDate::currentDate();
    startDateEdit->setDateRange(today.addDays(-90), today.addDays(90));
    startDateLabel = new QLabel(tr("&Start Date:"));
    startDateLabel->setBuddy(startDateEdit);

    firstButton = new QPushButton(tr("<< &First"));
    previousButton = new QPushButton(tr("< &Previous"));
    nextButton = new QPushButton(tr("&Next >"));
    lastButton = new QPushButton(tr("&Last >>"));
    addButton = new QPushButton(tr("&Add"));
    deleteButton = new QPushButton(tr("&Delete"));
    closeButton = new QPushButton(tr("&Close"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(deleteButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::AcceptRole);

    QHBoxLayout *topHLayout = new QHBoxLayout;
    topHLayout->addWidget(firstButton);
    topHLayout->addWidget(previousButton);
    topHLayout->addWidget(nextButton);
    topHLayout->addWidget(lastButton);
    QGridLayout *middleLayout = new QGridLayout;
    middleLayout->addWidget(nameLabel, 0, 0);
    middleLayout->addWidget(nameEdit, 0, 1);
    middleLayout->addWidget(departmentLabel, 1, 0);
    middleLayout->addWidget(departmentEdit, 1, 1);
    middleLayout->addWidget(extensionLabel, 2, 0);
    middleLayout->addWidget(extensionEdit, 2, 1);
    middleLayout->addWidget(emailLabel, 3, 0);
    middleLayout->addWidget(emailEdit, 3, 1);
    middleLayout->addWidget(startDateLabel, 4, 0);
    middleLayout->addWidget(startDateEdit);
    QHBoxLayout *bottomHLayout = new QHBoxLayout;
    bottomHLayout->addWidget(addButton);
    bottomHLayout->addWidget(deleteButton);
    bottomHLayout->addStretch();
    bottomHLayout->addWidget(closeButton);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topHLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomHLayout);

    tableModel = new QSqlTableModel(this);
    tableModel->setTable("employee");
//    tableModel->setRelation(Employee_DepartmentId,
//                            QSqlRelation("department", "id", "name"));
    tableModel->setSort(Employee_Name,Qt::AscendingOrder);
    tableModel->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(tableModel);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(nameEdit, Employee_Name);
    mapper->addMapping(departmentEdit, Employee_Department);
    mapper->addMapping(extensionEdit,Employee_Extension);
    mapper->addMapping(emailEdit, Employee_Email);
    mapper->addMapping(startDateEdit, Employee_StartDate);

    if(id != -1)
    {
        for(int row = 0; row < tableModel->rowCount(); row++)
        {
            QSqlRecord record = tableModel->record(row);
            if(record.value(Employee_Id).toInt() == id)
            {
                mapper->setCurrentIndex(row);
                break;
            }
        }
    }
    else
    {
        mapper->toFirst();
    }

    connect(firstButton, SIGNAL(clicked()), mapper, SLOT(toFirst()));
    connect(previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    connect(lastButton, SIGNAL(clicked()), mapper, SLOT(toLast()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addEmployee()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteEmployee()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(accept()));

    setLayout(mainLayout);
    setWindowTitle(tr("Employee Form"));
    setFixedHeight(sizeHint().height());

}

void EmployeeForm::done(int result)
{
    QDialog::done(result);
}

void EmployeeForm::addEmployee()
{
    int row = mapper->currentIndex();
    mapper->submit();
    tableModel->insertRow(row);
    mapper->setCurrentIndex(row);

    nameEdit->clear();
    extensionEdit->clear();
    startDateEdit->setDate(QDate::currentDate());
    nameEdit->setFocus();
}

void EmployeeForm::deleteEmployee()
{
    int row = mapper->currentIndex();
    tableModel->removeRow(row);
    mapper->submit();
    mapper->setCurrentIndex(qMin(row, tableModel->rowCount() - 1));
}
