#include "selectoptiondialog.h"
#include "ui_selectoptiondialog.h"

SelectOptionDialog::SelectOptionDialog(QWidget *parent, int lessonSelected)
    : QDialog(parent), ui(new Ui::SelectOptionDialog)
{
    ui->setupUi(this);
    lesson = lessonSelected;

    setWindowTitle("Chose option");
}

SelectOptionDialog::~SelectOptionDialog() { delete ui; }

void SelectOptionDialog::startPractiseLesson()
{
    const QString &fileName =
        ":/textData/SentencesForPractice/translations" + QString::number(lesson) + ".txt";

    QString fileContent = loadFileContent(fileName);
    if (fileContent.isEmpty()) return;

    practiceDialog = new PracticeDialog;

    QStringList lines = fileContent.split("\n");
    for (const QString &line : lines) {
        QStringList parts = line.split("|");

        if (parts.size() == 2) {
            practiceDialog->appendToUkrainian(parts[0].trimmed());
            practiceDialog->appendToEnglish(parts[1].trimmed());
        }
    }

    practiceDialog->show();
    practiceDialog->updateSentences();
}

void SelectOptionDialog::showReferencesWindow()
{
    const QString &filePath =
        ":/markdownData/ReferenсesFromLessons/lesson" + QString::number(lesson) + ".md";

    referencesWindow = new ReferencesWindow;

    QString markdown = loadFileContent(filePath);
    if (markdown.isEmpty()) return;

    referencesWindow->setMarkdown(markdown);
    referencesWindow->show();
}

QString SelectOptionDialog::loadFileContent(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Критична помилка",
                              "Не вдалось відкрити файл: " + fileName + "\n" +
                                  file.errorString());
        return QString();
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    return content;
}

void SelectOptionDialog::on_pushButton_clicked()
{
    showReferencesWindow();
    this->close();
}

void SelectOptionDialog::on_pushButton_2_clicked()
{
    startPractiseLesson();
    this->close();
}

