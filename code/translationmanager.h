#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QTranslator>
#include <QLocale>
#include <QVector>
#include <QString>

class TranslationManager {
public:
    static TranslationManager& instance();
    void loadTranslations(const QString &path);
    QStringList availableLanguages() const;
    void setLanguage(int index);
    QString languageCode(int index) const;

private:
    TranslationManager() = default;
    QVector<QTranslator*> translators;
    QStringList langCodes;
    QStringList langNames;
    int activeIndex = -1;
};

#endif // TRANSLATIONMANAGER_H
