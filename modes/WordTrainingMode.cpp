#include <qdebug.h>
#include <QtGui/QMenu>

#include "WordTrainingMode.h"

WordTrainingMode::WordTrainingMode(Morse *parent, Ui::MainWindow *ui)
    : MorseMode(parent, ui)
{
    setupWords();
}


void WordTrainingMode::setupWords() {
#include "words/100words.h"
#include "words/200words.h"
#include "words/300words.h"
#include "words/400words.h"
#include "words/500words.h"
}

void WordTrainingMode::setupWordsMenu() {

    m_wordsNumber = N100;

    m_wordSignalMapper = new QSignalMapper();
    QMenu *modeMenu = new QMenu(m_ui->changeWords);
    m_ui->changeWords->setMenu(modeMenu);

    QAction *action = modeMenu->addAction("Words 1-100");
    connect(action, SIGNAL(triggered()), m_wordSignalMapper, SLOT(map()));
    m_wordSignalMapper->setMapping(action, (int) N100);

    action = modeMenu->addAction("Words 101-200");
    connect(action, SIGNAL(triggered()), m_wordSignalMapper, SLOT(map()));
    m_wordSignalMapper->setMapping(action, (int) N200);

    action = modeMenu->addAction("Words 201-300");
    connect(action, SIGNAL(triggered()), m_wordSignalMapper, SLOT(map()));
    m_wordSignalMapper->setMapping(action, (int) N300);

    action = modeMenu->addAction("Words 301-400");
    connect(action, SIGNAL(triggered()), m_wordSignalMapper, SLOT(map()));
    m_wordSignalMapper->setMapping(action, (int) N400);

    action = modeMenu->addAction("Words 401-500");
    connect(action, SIGNAL(triggered()), m_wordSignalMapper, SLOT(map()));
    m_wordSignalMapper->setMapping(action, (int) N500);

    connect(m_wordSignalMapper, SIGNAL(mapped(int)), this, SLOT(switchWords(int)));
}

void WordTrainingMode::switchToMode() {
    m_goodCount = 0;
    m_badCount = 0;
    m_ui->wordbox->clear();
    m_ui->letter->show();
    m_ui->modeMenu->setText("Word Training");
    m_ui->changeWords->show();
    m_ui->helpBar->setText("<font color=\"green\">Enter the word you hear and hit enter.</font>");
    m_ui->play->show();
    m_ui->WPM->show();
    clear();

    setupWordsMenu();
    setupKeyWidgets("abcdefghijklmnopqrstuvwxyz");
    m_maxWord = 2;

    enterPressed();
}

void WordTrainingMode::switchWords(int sequence) {
    m_wordsNumber = (wordNums) sequence;
    qDebug() << "switching to: " << m_wordsNumber;
}

void WordTrainingMode::play() {
    enterPressed();
}

bool WordTrainingMode::enterPressed() {
    m_wordnumber = qrand()%(m_maxWord);
    m_morse->add((*(words[m_wordsNumber]))[m_wordnumber]);
    m_morse->maybePlaySequence();
    m_enteredWord = "";
    m_ui->letter->setText("");
    m_morse->m_sequenceLabel->setText(QString("%1/%2").arg(m_maxWord).arg(words[m_wordsNumber]->length()));
    m_wordWasGood = true;
    return true;
}

void WordTrainingMode::handleKeyPress(QChar letter) {
    if (runningMode() != RUNNING)
        return;
    if (letter == '\r') {
        enterPressed();
        return;
    }
    if ((*(words[m_wordsNumber]))[m_wordnumber][m_enteredWord.length()] == letter) {
        m_ui->letter->setText(m_ui->letter->text() + "<font color=\"green\">" + letter + "<font>");
    } else {
        m_ui->letter->setText(m_ui->letter->text() + "<font color=\"red\">" + letter + "<font>");
        m_wordWasGood = false;
    }
    m_enteredWord.append(letter);
    if ((*(words[m_wordsNumber]))[m_wordnumber].length() == m_enteredWord.length()) {
        if (m_wordWasGood) {
            m_ui->letter->setText(m_ui->letter->text() + " - <font color=\"green\">GOOD</font>");
            if (m_maxWord < 10)
                m_maxWord += 2;
            else
                m_maxWord += 1;
            if (m_maxWord > (*(words[m_wordsNumber])).count())
                m_maxWord = (*(words[m_wordsNumber])).count();
        } else {
            m_ui->letter->setText(m_ui->letter->text() + " - <font color=\"red\">FAIL (" + (*(words[m_wordsNumber]))[m_wordnumber] + ")</font>");
            if (m_maxWord > 1)
                m_maxWord--;
        }
    }
}

