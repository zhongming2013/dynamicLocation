#ifndef COMDIALOG_H
#define COMDIALOG_H

#include <QtGui/QDialog>

#include "win_qextserialport.h"

class QComboBox;

class ComDialog : public QDialog
{
    Q_OBJECT
public:
    ComDialog(QWidget* = 0);
    ~ComDialog();
    Win_QextSerialPort* getMyCom();
private slots:
    void openMyCom();
private:
    QComboBox *comComboBox;
    QComboBox *baudComboBox;
    QComboBox *dataComboBox;
    QComboBox *parityComboBox;
    QComboBox *stopComboBox;
    QPushButton *openPushButton;
    QPushButton *cancelPushButton;

    Win_QextSerialPort *myCom;
};

#endif // COMDIALOG_H
