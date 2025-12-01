#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QSettings>
#include <QString>
#include <QSize>
#include <QApplication>
#include <qfont.h>

class ConfigManager {
public:
    static ConfigManager& instance();
    void setApp(QApplication *app) {
        qtApp = app;
    }

    void load();
    void save();

    int language() const { return m_language; }
    void setLanguage(const int& lang) { m_language = lang; }

    QSize windowSize() const { return m_windowSize; }
    void setWindowSize(const QSize& size);

private:
    ConfigManager() = default;
    int m_language = 0;
    QSize m_windowSize = QSize(320, 240);
    QApplication *qtApp = nullptr;
};

#endif // CONFIGMANAGER_H
