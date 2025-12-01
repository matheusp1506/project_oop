#include "mainmenu.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget *parent)
    : QWidget{parent}
{
    // Create layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    QVBoxLayout *buttonLayout = new QVBoxLayout;

    layout->setContentsMargins(10, 5, 30, 5);

    dfn::TranslationObj translate;

    // Buttons
    startButton = new QPushButton(tr("New Game"), this);
    translate.widget = startButton;
    translate.text = "New Game";
    translate.type = dfn::E_TextObjects::Button;
    objects.push_back(translate);
    loadButton = new QPushButton(tr("Load Game"), this);
    translate.widget = loadButton;
    translate.text = "Load Game";
    objects.push_back(translate);
    optionsButton = new QPushButton(tr("Options"), this);
    translate.widget = optionsButton;
    translate.text = "Options";
    objects.push_back(translate);
    creditsButton =  new QPushButton(tr("Credits"), this);
    translate.widget = creditsButton;
    translate.text = "Credits";
    objects.push_back(translate);
    exitButton = new QPushButton(tr("Exit"), this);
    translate.widget = exitButton;
    translate.text = "Exit";
    objects.push_back(translate);

    // Add buttons to layout
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(optionsButton);
    buttonLayout->addWidget(creditsButton);
    buttonLayout->addWidget(exitButton);

    layout->addStretch();
    layout->addLayout(buttonLayout);

    // Connect signals
    connect(startButton, &QPushButton::clicked, this, &MainMenu::onStartClicked);
    connect(optionsButton, &QPushButton::clicked, this, &MainMenu::onOptionsClicked);
    connect(creditsButton, &QPushButton::clicked, this, &MainMenu::onCreditsClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::onExitClicked);
}

void MainMenu::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
    }
    QWidget::changeEvent(event);
}

void MainMenu::retranslateUi() {
    for(int i = objects.size()-1; i>=0; i--) {
        if(objects[i].type == dfn::E_TextObjects::Button) {
            ((QAbstractButton*)objects[i].widget)->setText(tr(objects[i].text.c_str()));
        }
    }
}
