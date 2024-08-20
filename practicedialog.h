#ifndef PRACTICEDIALOG_H
#define PRACTICEDIALOG_H

#include <QDialog>
#include <QList>
#include <QRandomGenerator>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>

namespace Ui {
class PracticeDialog;
}

class PracticeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PracticeDialog(QWidget *parent = nullptr);
    ~PracticeDialog();

    QMap<QString, QString> getSentencesContainer() const;

    void appendToUkrainian(const QString newUkrainianSentence);
    void appendToEnglish(const QString newEnglishSentence);
    void updateSentences();

private slots:
    void on_nextWordButton_clicked();

    void timerSlot();

    void on_lineEdit_returnPressed();

    void on_endPracticeButton_clicked();

private:
    Ui::PracticeDialog *ui;

    QRandomGenerator *random;

    QList<QString> ukrainianSentences;
    QList<QString> englishSentences;
    QList<QString> incorrectAnswersList;
    QList<QString> userEnteredList;



    QTimer *timer;

    int seconds;
    int minutes;
    int generatedIndex;
    int correctAnswersCounter;
    int incorrectAnswersCounter;
    int returnClickedTimes;

    bool sentenceChecked;

    void checkSentence();
    void nextWord();

    void checkExceptions(QString userText);
    void sendMessageToUser(QString color, QString text, int &answerVariable);
    void refactorUserText(QString &userText);
    void updateAnswerCounters();
};

#endif // PRACTICEDIALOG_H
