#ifndef FILEGESTION_H
#define FILEGESTION_H

#include <QWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QFile>

class FileGestion : public QTreeWidget
{
    Q_OBJECT
public:
    explicit FileGestion(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // FILEGESTION_H
