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

#include <QtWidgets>

#include "Editor/Editor.h"
#include "../Core/MainWindow.h"
#include "../SyntaxicColoration/SynColoCCpp.h"
#include "../SyntaxicColoration/SynColoHTML.h"

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    LineNumber = new LineNumberClass(this);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(UpdateLineNumberWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(UpdateLineNumber(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(HighlightCurrentLine()));

    UpdateLineNumberWidth(0);
    HighlightCurrentLine();
    this->setStyleSheet("background: rgb(48,61,74); border: none;");

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalScrollBar()->hide();
    verticalScrollBar()->resize(0, 0);
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    horizontalScrollBar()->hide();
    horizontalScrollBar()->resize(0, 0);
    installEventFilter(this);

    createSnippets();
    setTabSize(4);
}

void Editor::setTabSize(int tabSize) {
    QFont font;
    QFontMetrics metrics(font);
    setTabStopWidth(tabSize * metrics.width(' '));
}

void Editor::createSnippets() {

    //html
    QString html5 = "<!doctype html>\n\n<html lang=\"fr\">\n\t<head>\n\t\t <meta charset=\"utf-8\">\n\t\t <title>Titre</title>\n\t\t </head>\n\t\t<body>\n\n\t\t</body>\n</html>";
    QString input = "<input type=\"text\" name=\"\" />";
    QString strong = "<strong></strong>";
    QString ul = "<ul>\n\t<li></li>\n</ul>";
    QString img = "<img src=\"\" alt=\"\" />";
    QString link = "<a href=\"\"></a>";
    QString italic = "<em></em>";
    QString css = "<link rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\" />";
    QString js = "<script type=\"text/javascript\" src=\"js/main.js\"></script>";
    QString textarea = "<textarea name=\"\" cols=\"30\" rows=\"10\"></textarea>";
    QString select = "<select>\n\t<option value=\"\"></option>\n</select>";
    QString form = "<form action=\"#\" method=\"post\"></form>";
    m_snippets["html"] = html5;
    m_snippets["input"] = input;
    m_snippets["strong"] = strong;
    m_snippets["ul"] = ul;
    m_snippets["img"] = img;
    m_snippets["a"] = link;
    m_snippets["em"] = italic;
    m_snippets["css"] = css;
    m_snippets["js"] = js;
    m_snippets["texta"] = textarea;
    m_snippets["select"] = select;
    m_snippets["form"] = form;

    //cpp

    QString cpp = "int main()  //main function\n {\n\t\t return 0;\n}";
    m_snippets["cpp"] = cpp;

}


bool Editor::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        pressedKeys += ((QKeyEvent*)event)->key();
        QTextCursor cursor = textCursor();
        cursor.select(QTextCursor::WordUnderCursor);
        QString word = cursor.selectedText();

        if (pressedKeys.contains(Qt::Key_QuoteDbl)) {
            textCursor().insertText(R"*(" ")*");
            return true;
        }
        if (pressedKeys.contains(Qt::Key_ParenLeft) && !pressedKeys.contains(Qt::Key_Alt)) {
            textCursor().insertText(R"*(( ))*");
            return true;
        }
        if (pressedKeys.contains(Qt::Key_Alt) && pressedKeys.contains(Qt::Key_ParenLeft)) {
            textCursor().insertText(R"*({)*");
            textCursor().insertText("\n");
            textCursor().insertText("\n");
            textCursor().insertText(R"*(})*");
            return true;
        }

        if(pressedKeys.contains(Qt::Key_Tab)) {
            if(word.toStdString() == "cpp"){
                highlighter = new CppHighlighter(this->document());
                delete htmlHighlighter;
            }
            if(word.toStdString() == "html"){
                htmlHighlighter = new HtmlHighlighter(this->document());
                delete highlighter;
            }
            if(m_snippets.find(word.toStdString()) != m_snippets.end()) {
                cursor.removeSelectedText();
                cursor.insertText(m_snippets.find(word.toStdString())->second);
            }

        }

    }

    if (event->type() == QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }

    return QObject::eventFilter(obj, event);
}

int Editor::LineNumberWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void Editor::UpdateLineNumberWidth(int /* newBlockCount */)
{
    setViewportMargins(LineNumberWidth(), 0, 0, 0);
}

void Editor::UpdateLineNumber(const QRect &rect, int dy)
{
    if (dy)
        LineNumber->scroll(0, dy);
    else
        LineNumber->update(0, rect.y(), LineNumber->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        UpdateLineNumberWidth(0);
}

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    LineNumber->setGeometry(QRect(cr.left(), cr.top(), LineNumberWidth(), cr.height()));
}

void Editor::HighlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(24,30,37).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(LineNumber);
    painter.fillRect(event->rect(), QColor(48,61,74));


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::white);
            painter.drawText(0, top, LineNumber->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

