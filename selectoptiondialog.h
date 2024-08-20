#ifndef SELECTOPTIONDIALOG_H
#define SELECTOPTIONDIALOG_H

#include "practicedialog.h"
#include "referenceswindow.h"

#include <QDialog>

namespace Ui {
class SelectOptionDialog;
}

class SelectOptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectOptionDialog(QWidget *parent = nullptr, int lessonSelected = 1);
    ~SelectOptionDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SelectOptionDialog *ui;

    PracticeDialog *practiceDialog;
    ReferencesWindow *referencesWindow;

    int lesson;

    void startPractiseLesson();
    void showReferencesWindow();

    QString loadFileContent(const QString &fileName);
};

#endif // SELECTOPTIONDIALOG_H
