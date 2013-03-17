#ifndef REFERTABLEMODEL_H
#define REFERTABLEMODEL_H

#include <QSqlTableModel>

class ReferTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    ReferTableModel(QObject *parent = 0);
    void refreshReferTable(const QVector<int> referenceMsg);
};

#endif // REFERTABLEMODEL_H
