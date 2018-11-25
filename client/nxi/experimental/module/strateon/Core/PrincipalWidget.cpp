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

#include "PrincipalWidget.h"
#include "../Editor/Editor.h"
#include "../Editor/filegestion.h"
#include "MainWindow.h"
#include <QFileDialog>
#include <QTextStream>
#include "../SyntaxicColoration/SynColoCCpp.h"
#include "../SyntaxicColoration/SynColoHTML.h"
#include <QHBoxLayout>
#include <QFile>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <iostream>



PrincipalWidget::PrincipalWidget(QWidget *parent) : QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    editor = new Editor(this);
    m_manager = new FileGestion(this);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_manager, 20);
    m_layout->addWidget(editor, 80);
    setLayout(m_layout);
    connect(m_manager, &FileGestion::itemClicked, this, &PrincipalWidget::openFileFromTreeView);
}

/*void PrincipalWidget::saveFile(bool test)
{ if (test){}
    QString EditorContent = editor->toPlainText();
    QString FileName = QFileDialog::getSaveFileName(this, "Enregistrer...", "sansTitre.txt");
    QString Name = QFileInfo(FileName).fileName();
    QFile File(FileName);
    //items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(Name))));
    //fileView->insertTopLevelItems(0, items);
    if (File.open(QIODevice::WriteOnly))
    {
        QTextStream out(&File);
        out << EditorContent;
    }
}*/

void PrincipalWidget::openFile(bool test)
{ if (test){}
    QString FileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString());
    QString Name = QFileInfo(FileName).fileName();
    QFile File(FileName);
    //items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(Name))));
    //fileView->insertTopLevelItems(0, items);
    if (File.open(QIODevice::ReadOnly))
    {
        editor->document()->setPlainText(File.readAll());
    }
}



void PrincipalWidget::saveFile(bool test)
{ if (test){}
    QString EditorContent = editor->toPlainText();
    QString FileName = QFileDialog::getSaveFileName(this, "Enregistrer...", "sansTitre.txt");
    QString Name = QFileInfo(FileName).fileName();
    QFile File(FileName);
    if (File.open(QIODevice::WriteOnly))
    {
         QTextStream out(&File);
         out << EditorContent;
         QString row = QString::number(i);

         std::cout << i << std::endl;

         items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(row)));
         items.at(i)->setData(i, i, FileName);
         QString text = items.at(i)->data(i,i).toString();
         std::cout << i << std::endl;
         std::cout << text.toStdString() << std::endl;
         m_manager->insertTopLevelItems(i, items);
         i++;
    }
}

void PrincipalWidget::openFileFromTreeView(QTreeWidgetItem *treeItem, int row)
{
    std::cout << row << std::endl;
    std::cout << treeItem->text(row).toInt() << std::endl;
    QString text = treeItem->data(treeItem->text(row).toInt(), treeItem->text(row).toInt()).toString();
    QFile File(text);
    if (File.open(QIODevice::ReadOnly))
    {
        editor->document()->setPlainText(File.readAll());
    }
}





