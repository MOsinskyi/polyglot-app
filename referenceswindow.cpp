#include "referenceswindow.h"
#include "ui_referenceswindow.h"

ReferencesWindow::ReferencesWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReferencesWindow)
{
    ui->setupUi(this);

    setWindowTitle("References");
}

ReferencesWindow::~ReferencesWindow()
{
    delete ui;
}

QString ReferencesWindow::loadMarkdownFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }

    return QTextStream(&file).readAll();
}

void ReferencesWindow::setMarkdown(const QString &text)
{
    ui->textEdit->setMarkdown(text);
}

void ReferencesWindow::on_actionPrint_triggered()
{
    printDocument(ui->textEdit->document(), QPrinter::NativeFormat, QString());
}


void ReferencesWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save reference", "", "PDF Files (*.pdf);;All Files (*)");

    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    printDocument(ui->textEdit->document(), QPrinter::PdfFormat, fileName);
}

void ReferencesWindow::printDocument(QTextDocument *doc, QPrinter::OutputFormat outputFormat, const QString &fileName)
{
    QPrinter printer;
    printer.setOutputFormat(outputFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setFullPage(true);

    if (outputFormat == QPrinter::PdfFormat) {
        printer.setOutputFileName(fileName);
    }

    QPrintDialog printDialog(&printer, this);
    if (outputFormat == QPrinter::PdfFormat || printDialog.exec() == QDialog::Accepted) {
        doc->print(&printer);
    }
}

