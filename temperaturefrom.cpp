#include "temperaturefrom.h"
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>

TemperatureFrom::TemperatureFrom(QWidget *parent) :
    QDialog(parent)
{
    model = new QSqlTableModel(this);
    model->setTable("temperature");
    model->setHeaderData(1, Qt::Horizontal, tr("Floor"));
    model->setHeaderData(2, Qt::Horizontal, tr("Number"));
    model->setHeaderData(3, Qt::Horizontal, tr("Temperature(`C)"));
    model->setHeaderData(4, Qt::Horizontal, tr("Time"));
    model->select();
    view = new QTableView;
    view->setModel(model);
    view->setColumnHidden(0, true);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QLabel *floorLabel = new QLabel(tr("Floor:"));
    QLabel *numberLabel = new QLabel(tr("Number:"));
    QLabel *temperatureLabel = new QLabel("Temperature:");
    floorEdit = new QLineEdit;
    numberEdit = new QLineEdit;
    temperatureEdit = new QLineEdit;

    QPushButton *findButton = new QPushButton(tr("Find"));
    connect(findButton, SIGNAL(clicked()), this, SLOT(find()));
    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(findButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::AcceptRole);

    QHBoxLayout *conditionLayout = new QHBoxLayout;
    conditionLayout->addWidget(floorLabel);
    conditionLayout->addWidget(floorEdit);
    conditionLayout->addWidget(numberLabel);
    conditionLayout->addWidget(numberEdit);
    conditionLayout->addWidget(temperatureLabel);
    conditionLayout->addWidget(temperatureEdit);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addLayout(conditionLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Temperature History");
    resize(500, 500);
}

void TemperatureFrom::find()
{
    QString floor = floorEdit->text();
    QString number = numberEdit->text();
    QString temperature = temperatureEdit->text();

    QString condition = "1 ";
    if(!floor.isEmpty())
        condition.append("AND floor = " + floor);
    if(!number.isEmpty())
        condition.append(" and number = " + number);
    if(!temperature.isEmpty())
        condition.append(" and temperature = " + temperature);
    model->setFilter(condition);
    model->select();
}
