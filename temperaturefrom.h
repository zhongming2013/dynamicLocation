#ifndef TEMPERATUREFROM_H
#define TEMPERATUREFROM_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QDialogButtonBox>

class TemperatureFrom : public QDialog
{
    Q_OBJECT
public:
    explicit TemperatureFrom(QWidget *parent = 0);

public slots:
    void find();

private:
    QSqlTableModel *model;
    QTableView *view;

    QLineEdit *floorEdit ;
    QLineEdit *numberEdit;
    QLineEdit *temperatureEdit;
};

#endif // TEMPERATUREFROM_H
