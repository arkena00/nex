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

#include "SynColoHTML.h"

HtmlHighlighter::HtmlHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    normalFormat.setForeground(Qt::white);
    rule.pattern = QRegularExpression("[[:print:]]");
    rule.format = normalFormat;
    highlightingRules.append(rule);

    baliseFormat.setForeground(QColor(68,130,187));
    baliseFormat.setFontWeight(QFont::Bold);
    QStringList balisePatterns;
    balisePatterns << R"*(<[A-Za-z]+.+[A-Za-z]+\"+>)*" << R"*(<[A-Za-z]+.+[A-Za-z]+/+\"+>)*" << R"*(<[A-Za-z]+.+[A-Za-z]+\"+[A-Za-z]+>)*" << R"*(<[A-Za-z]+.+[A-Za-z]+/+\"+[A-Za-z]+>)*" << "<[A-Za-z]+>" << "<[A-Za-z]+.+[A-Za-z]+" << ">" << "/>" << "</[A-Za-z]+>";
    foreach (const QString &pattern, balisePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = baliseFormat;
        highlightingRules.append(rule);
    }

    equalityFormat.setForeground(QColor(192,100,108));
    rule.pattern = QRegularExpression("=");
    rule.format = equalityFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(QColor(134, 190, 122));
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    doctypeFormat.setForeground(QColor(192,100,108));
    doctypeFormat.setFontWeight(QFont::Bold);
    QStringList doctypePatterns;
    doctypePatterns << "<!DOCTYPE html>" << "<!doctype html>" ;
    foreach (const QString &pattern, doctypePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = doctypeFormat;
        highlightingRules.append(rule);
    }

    multiLineCommentFormat.setForeground(QColor(192,100,108));

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void HtmlHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
