#include "configmanager.h"

ConfigManager& ConfigManager::instance() {
    static ConfigManager inst;
    return inst;
}

void ConfigManager::load() {
    QSettings settings("config.ini", QSettings::IniFormat);

    m_language = settings.value("language", "en_US").toInt();
    int w = settings.value("window/width", 320).toInt();
    int h = settings.value("window/height", 240).toInt();
    m_windowSize = QSize(w, h);
}

void ConfigManager::save() {
    QSettings settings("config.ini", QSettings::IniFormat);

    settings.setValue("language", m_language);
    settings.setValue("window/width", m_windowSize.width());
    settings.setValue("window/height", m_windowSize.height());
}

void ConfigManager::setWindowSize(const QSize &size) {
    m_windowSize = size;
    /*int w = size.width();
    int h = size.height();
    int targetHeight = w * 3 / 4;
    if (targetHeight > h) {
        w = h * 4 / 3;
    }
    QFont f = qtApp->font();
    f.setPixelSize(16*w/320);*/

    //qtApp->setFont(f);
}
