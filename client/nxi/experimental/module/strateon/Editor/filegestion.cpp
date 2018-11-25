#include "FileGestion.h"
#include <QTreeView>
#include <QTreeWidget>

FileGestion::FileGestion(QWidget *parent) : QTreeWidget(parent)
{
    setHeaderHidden(true);
    //header->setBackgroundColor(QPalette::Background, Qt::transparent);
    setStyleSheet("color: white; background: rgb(48,61,74); border: none;");
}


