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

#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>

class HtmlHighlighter;
class CppHighlighter;
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
//class std::map;

class LineNumberClass;

/* Editor Class (with Line number updating and Save/Open File functions)*/

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int LineNumberWidth();
    QSet<int> pressedKeys;
    void setTabSize(int tabSize);
    void createSnippets();

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    /*Line number updating*/
    void UpdateLineNumberWidth(int newBlockCount);
    void HighlightCurrentLine();
    void UpdateLineNumber(const QRect &, int);


private:
    QWidget *LineNumber = nullptr;
    CppHighlighter *highlighter = nullptr;
    HtmlHighlighter *htmlHighlighter = nullptr;
    std::map<std::string, QString> m_snippets;

};

/* Line number Class */

class LineNumberClass : public QWidget
{
public:
    LineNumberClass(Editor *editor) : QWidget(editor) {
        Editor = editor;
    }

    QSize sizeHint() const override {
        return QSize(Editor->LineNumberWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Editor->lineNumberAreaPaintEvent(event);
    }

private:
    Editor *Editor;
};


#endif
