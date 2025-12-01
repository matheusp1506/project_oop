#include "optionsmenu.h"
#include "translationmanager.h"
#include "configmanager.h"
#include <QVBoxLayout>
#include <QEvent>

OptionsMenu::OptionsMenu(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    dfn::TranslationObj translate;

    // --- Resolution Selector ---
    resLabel = new QLabel(tr("Resolution"), this);
    translate.widget = resLabel;
    translate.text = "Resolution";
    translate.type = dfn::E_TextObjects::Label;
    objects.push_back(translate);
    resolutionBox = new QComboBox(this);
    resolutionBox->addItems({"320x240", "400x200", "640x480", "800x600", "1024x768", "1280x960", "1440x900", "1600x900", "1280x1024", "1366x768", "1920x1080"}); // 4:3

    QSize tmp = ConfigManager::instance().windowSize();
    resolutionBox->setCurrentText(QString::number(tmp.width()) + "x" + QString::number(tmp.height()));

    connect(resolutionBox, &QComboBox::currentTextChanged, this, [=](QString text) {
        QStringList parts = text.split("x");
        int w = 320, h = 240;
        if(parts.size() == 2) {
            w = parts[0].toInt();
            h = parts[1].toInt();
        }
        ConfigManager::instance().setWindowSize(QSize(w, h));
        emit onResolutionChanged(text);
    });

    // --- Language Selector ---
    langLabel = new QLabel(tr("Language"), this);
    translate.widget = langLabel;
    translate.text = "Language";
    objects.push_back(translate);
    languageBox = new QComboBox(this);
    auto langs = TranslationManager::instance().availableLanguages();
    for (auto &l : langs) languageBox->addItem(l);

    languageBox->setCurrentIndex(ConfigManager::instance().language());

    connect(languageBox, &QComboBox::currentIndexChanged, this, [=](int index){
        TranslationManager::instance().setLanguage(index);
        ConfigManager::instance().setLanguage(index);
        emit languageChanged();
    });

    backButton = new QPushButton(tr("Back to Menu"));
    translate.widget = backButton;
    translate.text = "Back to Menu";
    translate.type = dfn::E_TextObjects::Button;
    objects.push_back(translate);
    connect(backButton, &QPushButton::clicked, this, [=]{
        ConfigManager::instance().save();
        emit onBackClicked();
    });

    // --- Layout ---
    layout->addWidget(resLabel);
    layout->addWidget(resolutionBox);
    layout->addSpacing(10);
    layout->addWidget(langLabel);
    layout->addWidget(languageBox);
    layout->addStretch();
    layout->addWidget(backButton);
}

void OptionsMenu::onResolutionChanged(const QString &res) {
    // Get parent window and resize it
    QWidget *window = this->window();
    QStringList parts = res.split("x");
    if (parts.size() == 2) {
        int w = parts[0].toInt();
        int h = parts[1].toInt();
        window->setFixedSize(w, h);
        window->update();
    }
}

void OptionsMenu::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
    }
    QWidget::changeEvent(event);
}

void OptionsMenu::retranslateUi() {
    /*resLabel->setText(tr("Resolution"));
    langLabel->setText(tr("Language"));
    backButton->setText(tr("Back to Menu"));*/
    for(int i = objects.size()-1; i>=0; i--) {
        if(objects[i].type == dfn::E_TextObjects::Button) {
            ((QAbstractButton*)objects[i].widget)->setText(tr(objects[i].text.c_str()));
        } else if(objects[i].type == dfn::E_TextObjects::Label) {
            ((QLabel*)objects[i].widget)->setText(tr(objects[i].text.c_str()));
        }
    }
}
