#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <vector>
#include "defines.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);

private:
    void changeEvent(QEvent *event) override;
    void retranslateUi();

signals:
    void onStartClicked();
    void onOptionsClicked();
    void onExitClicked();
    void onCreditsClicked();

private:
    QPushButton *startButton;
    QPushButton *loadButton;
    QPushButton *optionsButton;
    QPushButton *creditsButton;
    QPushButton *exitButton;
    std::vector<dfn::TranslationObj> objects;
};

#endif // MAINMENU_H
