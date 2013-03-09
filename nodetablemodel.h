#ifndef NODETABLEMODEL_H
#define NODETABLEMODEL_H

#include <QSqlTableModel>

class NodeTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    NodeTableModel(QObject *parent = 0);
    void refreshNodeTable(const QVector<int> referenceMsg);
};

#endif // NODETABLEMODEL_H
