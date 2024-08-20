#include "practicedialog.h"
#include "ui_practicedialog.h"

PracticeDialog::PracticeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PracticeDialog)
{
    random = QRandomGenerator::global();
    timer = new QTimer(this);

    seconds = 0;
    minutes = 0;
    generatedIndex = 0;
    correctAnswersCounter = 0;
    incorrectAnswersCounter = 0;
    returnClickedTimes = 0;

    sentenceChecked = false;

    connect(timer, &QTimer::timeout, this, &PracticeDialog::timerSlot);

    timer->start(1000);

    ui->setupUi(this);

    setWindowTitle("Practice");
}

PracticeDialog::~PracticeDialog()
{
    delete ui;
}

void PracticeDialog::appendToUkrainian(const QString newUkrainianSentence)
{
    ukrainianSentences.append(newUkrainianSentence);
}

void PracticeDialog::appendToEnglish(const QString newEnglishSentence)
{
    englishSentences.append(newEnglishSentence);
}

void PracticeDialog::updateSentences()
{
    auto highest = ukrainianSentences.size();
    generatedIndex = random->bounded(highest);
    ui->sentence->setText(ukrainianSentences[generatedIndex]);
}

void PracticeDialog::nextWord()
{
    updateSentences();
    ui->lineEdit->clear();
    ui->messageToUser->clear();
}

void PracticeDialog::on_nextWordButton_clicked()
{
    nextWord();
}

void PracticeDialog::timerSlot()
{
    seconds++;

    if (seconds >= 60) {
        seconds = 0;
        minutes++;
    }

    ui->timer->setText(QString::asprintf("%02d:%02d", minutes, seconds));

}

void PracticeDialog::sendMessageToUser(QString color, QString text, int &answerVariable)
{
    ui->messageToUser->setStyleSheet("QLabel {color: " + color + "}");
    ui->messageToUser->setText(text);
    answerVariable++;
}

void PracticeDialog::refactorUserText(QString &userText)
{
    static const QMap<QString, QString> replacements = {
        {"n't", " not"}, {"n`t", " not"}, {"\'m", " am"}, {"`m", " am"},
        {"\'s", " is"}, {"\'re", " are"}, {"`re", " are"},
        {"gonna", "going to"}, {"\'ll", " will"}, {" the ", " this "},
    };

    for (auto it = replacements.constBegin(); it != replacements.constEnd(); ++it)
        userText.replace(it.key(), it.value());

    const QStringList symbolsToDelete = {"?", ",", ".", "!"};

    for (const QString &symbol : symbolsToDelete) {
        if (englishSentences[generatedIndex].contains(symbol) && !userText.contains(symbol))
            englishSentences[generatedIndex].remove(symbol);
    }
}

void PracticeDialog::updateAnswerCounters()
{
    ui->currectAnswers->setStyleSheet("QLabel {color: green}");
    ui->currectAnswers->setText(QString::number(correctAnswersCounter));

    ui->incurrectAnswers->setStyleSheet("QLabel {color: red}");
    ui->incurrectAnswers->setText(QString::number(incorrectAnswersCounter));
}

void PracticeDialog::checkSentence()
{
    QString userText = ui->lineEdit->text();
    QString tmpEnglishSentence = englishSentences[generatedIndex];

    refactorUserText(userText);

    if (englishSentences[generatedIndex].compare(userText, Qt::CaseInsensitive) == 0) {
        sendMessageToUser("green", "Correct!", correctAnswersCounter);
    }
    else {
        sendMessageToUser("red", tmpEnglishSentence, incorrectAnswersCounter);
        incorrectAnswersList.append(tmpEnglishSentence);
        userEnteredList.append(userText);
    }

    updateAnswerCounters();
    englishSentences[generatedIndex] = tmpEnglishSentence;
    sentenceChecked = true;
}

void PracticeDialog::on_lineEdit_returnPressed()
{
    if (++returnClickedTimes == 2) {
        sentenceChecked = false;
        returnClickedTimes = 0;
        nextWord();
    } else if (!sentenceChecked) {
        checkSentence();
    }
}


void PracticeDialog::on_endPracticeButton_clicked()
{
    timer->stop();
    QString timeSpend = QString("Затрачено часу: %1\n").arg(QString::asprintf("%02d:%02d", minutes, seconds));
    QString correctAnswersStats = QString("Правильних відповідей: %1\n").arg(correctAnswersCounter);
    QString incorrectAnswersInGeneral = QString("Неправильних відповідей: %1\n").arg(incorrectAnswersCounter);
    QString incorrectAnswers;

    for (int i = 0; i < incorrectAnswersList.size(); ++i)
        incorrectAnswers += QString("%1 | %2\n").arg(userEnteredList[i], incorrectAnswersList[i]);

    this->close();

    QMessageBox::information(this, "Статистика!", timeSpend + correctAnswersStats + incorrectAnswersInGeneral + incorrectAnswers);
}

