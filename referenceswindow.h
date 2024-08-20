#ifndef REFERENCESWINDOW_H
#define REFERENCESWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <cmark.h>

namespace Ui {
class ReferencesWindow;
}

class ReferencesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReferencesWindow(QWidget *parent = nullptr);
    ~ReferencesWindow();

    QString loadMarkdownFromFile(const QString& filePath);

    void setMarkdown(const QString& markdown);

private slots:
    void on_actionPrint_triggered();

    void on_actionSave_triggered();

private:
    Ui::ReferencesWindow *ui;

    void printDocument(QTextDocument *doc, QPrinter::OutputFormat outputFormat, const QString &fileName);
};

#endif // REFERENCESWINDOW_H
