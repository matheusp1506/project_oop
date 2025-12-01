#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <vector>
#include "defines.h"

class OptionsMenu : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsMenu(QWidget *parent = nullptr);

private:
    void changeEvent(QEvent *event) override;
    void retranslateUi();

signals:
    void onBackClicked();
    void languageChanged();

private slots:
    void onResolutionChanged(const QString &resolution);

private:
    QPushButton *backButton;
    QComboBox *resolutionBox;
    QComboBox *languageBox;

    QLabel *resLabel;
    QLabel *langLabel;
    std::vector<dfn::TranslationObj> objects;
};

#endif // OPTIONSMENU_H
