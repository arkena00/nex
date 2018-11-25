/*
    * MIT License
    *
    * Copyright (c) 2018 Theo Bessel
    *
    * Permission is hereby granted, free of charge, to any person obtaining a copy
    * of this software and associated documentation files (the "Software"), to deal
    * in the Software without restriction, including without limitation the rights
    * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    * copies of the Software, and to permit persons to whom the Software is
    * furnished to do so, subject to the following conditions:
    *
    * The above copyright notice and this permission notice shall be included in all
    * copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    * SOFTWARE.
*/

#ifndef PRINCIPALWIDGET_H
#define PRINCIPALWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QFileDialog>
#include "../Editor/Editor.h"

class FileGestion;
class QTreeView;
class QTreeWidgetItem;
class QTreeWidget;

class PrincipalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrincipalWidget(QWidget *parent = nullptr);
    QTreeWidget *fileView;
    QList<QTreeWidgetItem*> items;
    Editor *editor = nullptr;
    FileGestion *m_manager;
    void saveFile(bool test);
    void openFile(bool test);
    void setCurentFile(/*QTreeWidgetItem newTreeView, QTreeWidgetItem oldTreeView*/);
    void openFileFromTreeView(QTreeWidgetItem *treeItem, int row);
    int i{0};

private:
    QHBoxLayout *m_layout = nullptr;

};

#endif // PRINCIPALWIDGET_H
