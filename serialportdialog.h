#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>
#include <QComboBox>

class SerialPortDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SerialPortDialog(QWidget *parent = 0);
    QString getComName();
    int getBaud();
    int getData();
    QString getParity();
    int getStop();

signals:
    void okToOpen();

private:
    QComboBox *comComboBox;
    QComboBox *baudComboBox;
    QComboBox *dataComboBox;
    QComboBox *parityComboBox;
    QComboBox *stopComboBox;
};

#endif // SERIALPORTDIALOG_H
