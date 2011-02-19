#ifndef MORSEMODE_H
#define MORSEMODE_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTime>
#include <QtCore/QSignalMapper>
#include <QtCore/QSettings>
#include <qaudio.h>

// #include "Morse.h"
#include "ui_MainWindow.h"
#include "MorseStat.h"

#if (defined(Q_WS_MAEMO_5) || defined(MAEMO_CHANGES))
#define SMALL_DEVICE 1
#endif

#ifdef Q_OS_WIN32
// cross compiling pulls in the wrong stdlib.h for some reason
#undef RAND_MAX
#define RAND_MAX 0x7FFF
#endif

class Morse;

class MorseMode : public QObject
{
public:
    Q_OBJECT

public:
    enum RunningMode { RUNNING = 0, PAUSED = 1 };

    MorseMode(Morse *morse, Ui::MainWindow *ui);
    Morse *morseParent();
    MorseStat *getStat(const QChar &key);

    int msToWPM(float ms);
    int msToPauseWPM(float ms);
    float msToPauseWPMF(float ms);

    void hideWidgets();
    void setupKeyWidgets(const QString &sequence, QBoxLayout *inside = 0);
    void setupWPMWidgets(QBoxLayout *to = 0);
    void createGlobalActions();
    void createMenuStructures();
    virtual void modeMenus();
    virtual void setupSequenceLayout(QVBoxLayout *parentLayout = 0,
                                      QWidget *theMainThing = 0);
    virtual void setupLastWPMLayout(QVBoxLayout *parentLayout = 0,
                                      QWidget *theMainThing = 0);
    virtual void setupAveWPMLayout(QVBoxLayout *parentLayout = 0,
                                      QWidget *theMainThing = 0);
    virtual void setupSequenceLayouts(QVBoxLayout *parentLayout = 0,
                                      QWidget *theMainThing = 0);

    RunningMode runningMode();
    void setRunningMode(RunningMode newMode);

    void clearLayout(QLayout *layout);

    virtual QString name() = 0;
    virtual QString helpText() = 0;

public slots:
    virtual void handleKeyPress(QChar letterPressed); // by default does nothing
    virtual void handleKeyPress(const QString &letterPressed);  // by default calls the QChar version
    virtual void switchToMode() = 0;
    virtual void switchFromMode();
    virtual void switchToYou();
    virtual void switchFromYou();

    virtual void playButton();
    virtual bool enterPressed();

    virtual void play();
    virtual void pause();
    virtual void stop();

    virtual void clear();
    virtual void clearModeLayout();

    virtual void help();

    virtual void audioFinished(QAudio::State state);
    virtual void audioStopped();

    virtual void changeWPM(int wpm);
    virtual void changeSpaceWPM(int wpm);
    virtual void changeLetterSpaceWPM(int wpm);

    virtual void loadSettings(QSettings &settings);
    virtual void saveSettings(QSettings &settings);

protected:
    Morse                          *m_morse;
    Ui::MainWindow                 *m_ui;
    int                             m_badCount, m_goodCount;
    int                             m_countWeight;
    int                             m_WPM, m_spaceWPM, m_letterSpaceWPM;
    QIcon                           m_playIcon, m_pauseIcon;
    RunningMode                     m_runningMode;
    QSignalMapper                  *m_mapper;
    QGridLayout                    *m_buttons;
#ifdef SMALL_DEVICE
    QMenuBar                       *m_helpMenu;
    QMenuBar                       *m_optionsMenu;
    QMenuBar                       *m_cuteCWMenu;
#else
    QMenu                          *m_helpMenu;
    QMenu                          *m_optionsMenu;
    QMenu                          *m_modeMenu;
    QMenu                          *m_cuteCWMenu;
#endif

    QHBoxLayout                    *m_sequenceLayout;
    QHBoxLayout                    *m_lastWPMLayout;
    QHBoxLayout                    *m_aveWPMLayout;

    QLabel                         *m_avewpmLabel;
    QLabel                         *m_lastwpmLabel;
    QLabel                         *m_sequenceLabel;
};

#endif // MORSEMODE_H
