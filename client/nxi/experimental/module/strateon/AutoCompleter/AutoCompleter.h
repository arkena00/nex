#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <QCompleter>

class AutoCompleter : QCompleter
{
public:
    AutoCompleter();
};

#endif // AUTOCOMPLETER_H

/*#include "qtexteditsnippet.h"
#include <QKeyEvent>
#include <QFont>
#include <QFontMetrics>
QTextEditSnippet::QTextEditSnippet(QWidget *parent) : QTextEdit(parent) {
createSnippets();
setTabSize(4);
}
void QTextEditSnippet::setTabSize(int tabSize) {
QFont font;
QFontMetrics metrics(font);
setTabStopWidth(tabSize * metrics.width(' '));
}
*/
