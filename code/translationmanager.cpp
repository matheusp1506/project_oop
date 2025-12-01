#include "translationmanager.h"
#include <QApplication>
#include <QDir>
#include <QDebug>

TranslationManager& TranslationManager::instance() {
    static TranslationManager inst;
    return inst;
}

void TranslationManager::loadTranslations(const QString &path) {
    QDir dir(path);
    QStringList files = dir.entryList(QStringList() << "*.qm", QDir::Files);
    for (const QString &file : files) {

        auto *translator = new QTranslator;
        if (translator->load(path + "/" + file)) {
            translators.push_back(translator);
            QString temp = file.split(".").first();
            temp = temp.split("_").mid(1).first() + "_" + temp.split("_").last();
            langCodes.push_back(temp);
            QLocale locale(temp);
            langNames.push_back(locale.nativeLanguageName());
            qApp->installTranslator(translator); // install all at once
        }
    }
}

void TranslationManager::setLanguage(int index) {
    if (index < 0 || index >= translators.size() || index == activeIndex)
        return;

    // Remove the old translator
    if (activeIndex >= 0)
        qApp->removeTranslator(translators[activeIndex]);

    // Install the new one
    qApp->installTranslator(translators[index]);
    activeIndex = index;

    // Broadcast event to update UI
    QEvent event(QEvent::LanguageChange);
    qApp->sendEvent(qApp, &event);
}

QStringList TranslationManager::availableLanguages() const {
    return langNames;
}

QString TranslationManager::languageCode(int index) const {
    return langCodes[index];
}
