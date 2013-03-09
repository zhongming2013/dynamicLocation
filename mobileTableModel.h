#ifndef MOBILETABLEMODEL_H
#define MOBILETABLEMODEL_H

#include <QSqlTableModel>

class MobileTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    MobileTableModel(QObject *parent = 0);
    void refreshMobileTable(const QVector<int> mobileMsg);
};

#endif // MOBILETABLEMODEL_H
