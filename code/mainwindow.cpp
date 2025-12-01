#include "mainwindow.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("Tape/Kill");
    setFixedSize(320,240);

    GameManager::instance().setSize(320, 240);

    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    stackedWidget = new QStackedWidget(this);

    mainMenuPage = new MainMenu(this);

    optionsMenuPage = new OptionsMenu(this);

    creditsMenuPage = new CreditsMenu(this);

    gamePage = new GameWindow(this);

    GameManager::instance().setGameWidget(gamePage);

    stackedWidget->addWidget(mainMenuPage);
    stackedWidget->addWidget(optionsMenuPage);
    stackedWidget->addWidget(creditsMenuPage);
    stackedWidget->addWidget(gamePage);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    connect(mainMenuPage, &MainMenu::onStartClicked, this, &MainWindow::changeToGameScreen);
    connect(mainMenuPage, &MainMenu::onOptionsClicked, this, &MainWindow::changeToOptionsMenu);
    connect(mainMenuPage, &MainMenu::onCreditsClicked, this, &MainWindow::changeToCreditsMenu);
    connect(mainMenuPage, &MainMenu::onExitClicked, this, &QWidget::close);
    connect(optionsMenuPage, &OptionsMenu::onBackClicked, this, &MainWindow::changeToMainMenu);
    connect(creditsMenuPage, &CreditsMenu::onBackClicked, this, &MainWindow::changeToMainMenu);
}

MainWindow::~MainWindow() {

}

void MainWindow::changeStack(int index) {
    stackedWidget->setCurrentIndex(index);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();

    GameManager::instance().setSize(w, h);

    resize(w, h);
}
