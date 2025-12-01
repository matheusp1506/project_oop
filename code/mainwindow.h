#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QResizeEvent>
#include "mainmenu.h"
#include "optionsmenu.h"
#include "creditsmenu.h"
#include "gamewindow.h"
#include "gamemanager.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void changeStack(int);
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void changeToMainMenu() {changeStack(0);};
    void changeToOptionsMenu() {changeStack(1);};
    void changeToCreditsMenu() {changeStack(2);};
    void changeToGameScreen() {GameManager::instance().newGame(); changeStack(3);};

private:
    QStackedWidget *stackedWidget;

    MainMenu *mainMenuPage;
    OptionsMenu *optionsMenuPage;
    CreditsMenu *creditsMenuPage;
    GameWindow *gamePage;
};

#endif // MAINWINDOW_H
