#include "locationRecordForm.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDate>

LocationRecordForm::LocationRecordForm(QWidget *parent)
    : QDialog(parent)
{
    locationRecordModel = new QSqlTableModel(this);
    locationRecordModel->setTable("location");
    locationRecordModel->setHeaderData(1, Qt::Horizontal, tr("NetID"));
    locationRecordModel->setHeaderData(2, Qt::Horizontal, tr("Room"));
    locationRecordModel->setHeaderData(3, Qt::Horizontal, tr("Help"));
    locationRecordModel->setHeaderData(4, Qt::Horizontal, tr("DateTime"));
    locationRecordModel->select();
    locationRecordView = new QTableView;
    locationRecordView->setModel(locationRecordModel);
    locationRecordView->setColumnHidden(0, true);
    locationRecordView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    nameLabel = new QLabel(tr("Name:"));
    roomLabel = new QLabel(tr("Room:"));
    helpLabel = new QLabel(tr("Help:"));
    dateLabel = new QLabel(tr("Date:"));
    nameEdit = new QLineEdit;
    roomEdit = new QLineEdit;
    helpEdit = new QComboBox;
    helpEdit->addItem(tr("Normal"));
    helpEdit->addItem(tr("Need Help"));
    dateEdit = new QDateEdit;
    nameLabel->setBuddy(nameEdit);
    roomLabel->setBuddy(roomEdit);
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
    firstHLayout->addWidget(roomLabel);
    firstHLayout->addWidget(roomEdit);
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
    QString netId = nameEdit->text();
    QString roomId = roomEdit->text();
    QString help = (helpEdit->currentText() == "Normal")?
                        QString::number(0):QString::number(1);
    QString date = dateEdit->date().toString("yyyy-MM-dd");

    QString condition = "help = " + help;
    if(!netId.isEmpty())
        condition.append(" and netId = " + netId);
    if(!roomId.isEmpty())
        condition.append(" and roomId = " + roomId);
    if(!date.isEmpty())
        condition.append(" and timeRecord like '" + date + "%'");
    locationRecordModel->setFilter(condition);
    locationRecordModel->select();
}
