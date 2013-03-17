#include "locationRecordForm.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDate>

LocationRecordForm::LocationRecordForm(QWidget *parent)
    : QDialog(parent)
{
    locationRecordModel = new QSqlTableModel(this);
    locationRecordModel->setTable("location");
    locationRecordModel->setHeaderData(1, Qt::Horizontal, tr("FixID"));
    locationRecordModel->setHeaderData(2, Qt::Horizontal, tr("NetID"));
    locationRecordModel->setHeaderData(3, Qt::Horizontal, tr("Floor"));
    locationRecordModel->setHeaderData(4, Qt::Horizontal, tr("Number"));
    locationRecordModel->setHeaderData(5, Qt::Horizontal, tr("Help"));
    locationRecordModel->setHeaderData(6, Qt::Horizontal, tr("DateTime"));
    locationRecordModel->select();
    locationRecordView = new QTableView;
    locationRecordView->setModel(locationRecordModel);
    locationRecordView->setColumnHidden(0, true);
    locationRecordView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    nameLabel = new QLabel(tr("FixId:"));
    floorLabel = new QLabel(tr("Floor:"));
    numberLabel = new QLabel(tr("Number:"));
    helpLabel = new QLabel(tr("Help:"));
    dateLabel = new QLabel(tr("Date:"));
    nameEdit = new QLineEdit;
    floorEdit = new QLineEdit;
    numberEdit = new QLineEdit;
    helpEdit = new QComboBox;
    helpEdit->addItem(tr("Normal"));
    helpEdit->addItem(tr("Need Help"));
    dateEdit = new QDateEdit;
    nameLabel->setBuddy(nameEdit);
    floorLabel->setBuddy(floorEdit);
    numberLabel->setBuddy(numberEdit);
    helpLabel->setBuddy(helpEdit);
    dateLabel->setBuddy(dateEdit);
    dateEdit->setCalendarPopup(true);
    QDate today = QDate::currentDate();
    dateEdit->setDate(today);
    dateEdit->setDateRange(today.addDays(-90), today.addDays(90));
    conditionGroup = new QGroupBox(tr("Search Conditions"));
    findButton = new QPushButton(tr("Find"));
    connect(findButton, SIGNAL(clicked()), this, SLOT(find()));
    closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(findButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::AcceptRole);

    QHBoxLayout *firstHLayout = new QHBoxLayout;
    firstHLayout->addWidget(nameLabel);
    firstHLayout->addWidget(nameEdit);
    firstHLayout->addWidget(floorLabel);
    firstHLayout->addWidget(floorEdit);
    firstHLayout->addWidget(numberLabel);
    firstHLayout->addWidget(numberEdit);
    QHBoxLayout *secondHLayout = new QHBoxLayout;
    secondHLayout->addWidget(helpLabel);
    secondHLayout->addWidget(helpEdit);
    secondHLayout->addWidget(dateLabel);
    secondHLayout->addWidget(dateEdit);
    QHBoxLayout *thirdHLayout = new QHBoxLayout;
    thirdHLayout->addStretch();
    thirdHLayout->addWidget(buttonBox);
    QVBoxLayout *conditionLayout = new QVBoxLayout;
    conditionLayout->addLayout(firstHLayout);
    conditionLayout->addLayout(secondHLayout);
    conditionLayout->addLayout(thirdHLayout);

    conditionGroup->setLayout(conditionLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(locationRecordView);
    mainLayout->addWidget(conditionGroup);

    setLayout(mainLayout);
    setWindowTitle("Location Records");
    resize(500, 500);
}

LocationRecordForm::~LocationRecordForm()
{
}

void LocationRecordForm::find()
{
    QString fixId = nameEdit->text();
    QString floor = floorEdit->text();
    QString number = numberEdit->text();
    QString help = (helpEdit->currentText() == "Normal")?
                        QString::number(0):QString::number(1);
    QString date = dateEdit->date().toString("yyyy-MM-dd");

    QString condition = "help = " + help;
    if(!fixId.isEmpty())
        condition.append(" and fixId = " + fixId);
    if(!floor.isEmpty())
        condition.append(" and floor = " + floor);
    if(!number.isEmpty())
        condition.append("and number = " + number);
    if(!date.isEmpty())
        condition.append(" and time like '" + date + "%'");
    locationRecordModel->setFilter(condition);
    locationRecordModel->select();
}
