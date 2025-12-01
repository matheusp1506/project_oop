#include "creditsmenu.h"
#include <QVBoxLayout>

CreditsMenu::CreditsMenu(QWidget *parent)
    : QWidget{parent}
{

    QVBoxLayout *boxLayout = new QVBoxLayout(this);

    dfn::TranslationObj translate;

    creditsText = new QLabel(tr("Jogo desenvolvido por:\n Matheus Pereira\nFeito para a disciplina de:\nProgramação Orientada a\n Objetos\nDisciplina dada por: \nHugo Marcondes\nIFSC\nArte disponível \ngratuitamente feita por: Kenney.nl\nFonte: Pixel Digivolve\n por Pixel Sagas\nPersonagem:\nAxulArt\nCenário:\nDungeon Scrawl e Mark Gosbell"));
    creditsText->setAlignment(Qt::AlignHCenter);
    translate.widget = creditsText;
    translate.text = "Jogo desenvolvido por:\n Matheus Pereira\nFeito para a disciplina de:\nProgramação Orientada a\n Objetos\nDisciplina dada por: \nHugo Marcondes\nIFSC\nArte disponível \ngratuitamente feita por: Kenney.nl\nFonte: Pixel Digivolve\n por Pixel Sagas\nPersonagem:\nAxulArt\nCenário:\nDungeon Scrawl e Mark Gosbell";
    translate.type = dfn::E_TextObjects::Label;
    objects.push_back(translate);

    backButton = new QPushButton(tr("Back to Menu"));
    translate.widget = backButton;
    translate.text = "Back to Menu";
    translate.type = dfn::E_TextObjects::Button;
    objects.push_back(translate);
    connect(backButton, &QPushButton::clicked, this, &CreditsMenu::onBackClicked);

    boxLayout->addWidget(creditsText);
    boxLayout->addWidget(backButton);
}

void CreditsMenu::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
    }
    QWidget::changeEvent(event);
}

void CreditsMenu::retranslateUi() {
    for(int i = objects.size()-1; i>=0; i--) {
        if(objects[i].type == dfn::E_TextObjects::Button) {
            ((QAbstractButton*)objects[i].widget)->setText(tr(objects[i].text.c_str()));
        }
    }
}

