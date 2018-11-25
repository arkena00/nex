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

#include "SynColoCCpp.h"

CppHighlighter::CppHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    normalFormat.setForeground(Qt::white);
    rule.pattern = QRegularExpression(".");
    rule.format = normalFormat;
    highlightingRules.append(rule);

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(QColor(186,127,184));

    QStringList classPattern;
    classPattern << "\\bQ[A-Za-z]+\\b" << "[A-Za-z]+::" << "class +[A-Za-z]+" << "[A-Za-z]+ \\*";
    foreach (const QString &pattern, classPattern) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = classFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setForeground(QColor(68,130,187));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b"
                    << "cout" << "std" << "endl" << "new" << "nullptr";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }



    objectFormat.setFontWeight(QFont::Bold);
    objectFormat.setForeground(QColor(206,134,150));

    QStringList objectPattern;
    objectPattern << "\\*+[A-Za-z]+" << " \\*+[A-Za-z]" << " \\*+>+[A-Za-z]+" << " \\*+>+ [A-Za-z]+" << " \\*+[A-Za-z]+_+[A-Za-z]+";
    foreach (const QString &pattern, objectPattern) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = objectFormat;
        highlightingRules.append(rule);
    }

    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(QColor(134, 190, 122));
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    includeFormat.setFontWeight(QFont::Bold);
    includeFormat.setForeground(QColor(192,100,108));
    QStringList includePattern;
    includePattern << "#include<[A-Za-z]+>" << "#include <[A-Za-z]+>" << R"*(#include "[A-Za-z]+.+[A-Za-z]")*" << R"*(#include"[A-Za-z]+.+[A-Za-z]")*" << "#define +[A-Za-z]+_+[A-Za-z]+"
                   << "#ifndef +[A-Za-z]+_+[A-Za-z]+" << "#endif"  << R"*(#include "..+/+[A-Za-z]+.+[A-Za-z]")*" << R"*(#include"..+/+[A-Za-z]+.+[A-Za-z]")*" << "Q_OBJECT";
    foreach (const QString &pattern, includePattern) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = includeFormat;
        highlightingRules.append(rule);
    }


    singleLineCommentFormat.setForeground(QColor(192,100,108));
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(QColor(192,100,108));


    functionFormat.setFontWeight(QFont::Bold);
    functionFormat.setForeground(QColor(73,166,165));
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void CppHighlighter::highlightBlock(const QString &text)
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
