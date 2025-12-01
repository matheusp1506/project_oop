#ifndef CREDITSMENU_H
#define CREDITSMENU_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QPushButton>
#include <vector>
#include "defines.h"

class CreditsMenu: public QWidget
{
    Q_OBJECT
public:
    explicit CreditsMenu(QWidget *parent = nullptr);

private:
    void changeEvent(QEvent *event) override;
    void retranslateUi();

signals:
    void onBackClicked();

private:
    QPushButton *backButton;
    QLabel *creditsText;
    std::vector<dfn::TranslationObj> objects;
};

#endif // CREDITSMENU_H
