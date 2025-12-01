#include <QApplication>
#include <QFontDatabase>
#include <QLocale>
#include "translationmanager.h"
#include "configmanager.h"
#include "mainwindow.h"
#include "defines.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/assets/fonts/Pixel Digivolve.otf");
    if (id < 0) {
        qWarning("Failed to load font!");
    }


    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont f = QFont(family);

    ConfigManager::instance().load();

    ConfigManager::instance().setApp(&app);

    // Apply language from config
    int lang = ConfigManager::instance().language();
    TranslationManager::instance().loadTranslations(":/translations");
    TranslationManager::instance().setLanguage(lang);

    QSize siz = ConfigManager::instance().windowSize();

    /*int w = siz.width();
    int h = siz.height();
    int targetHeight = w * 3 / 4;
    if (targetHeight > h) {
        w = h * 4 / 3;
    }*/

    f.setPixelSize(/*14*w/320*/16);

    app.setFont(f);

    MainWindow window;

    window.setFixedSize(siz);
    window.show();

    return app.exec();
}
