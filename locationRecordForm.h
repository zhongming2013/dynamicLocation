#ifndef LOCATIONFORM_H
#define LOCATIONFORM_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <QDialogButtonBox>

class LocationRecordForm : public QDialog
{
    Q_OBJECT

public:
    LocationRecordForm(QWidget *parent = 0);
    ~LocationRecordForm();

private slots:
    void find();

private:
    QSqlTableModel *locationRecordModel;
    QTableView *locationRecordView;

    QLabel *nameLabel;
    QLabel *floorLabel;
    QLabel *numberLabel;
    QLabel *helpLabel;
    QLabel *dateLabel;
    QLineEdit *nameEdit;
    QLineEdit *floorEdit;
    QLineEdit *numberEdit;
    QComboBox *helpEdit;
    QDateEdit *dateEdit;
    QGroupBox *conditionGroup;
    QPushButton *findButton;
    QPushButton *closeButton;
    QDialogButtonBox *buttonBox;
};


#endif // LOCATIONFORM_H
