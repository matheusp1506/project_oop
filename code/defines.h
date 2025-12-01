#ifndef DEFINES_H
#define DEFINES_H

#include <QWidget>
#include <string>

namespace dfn {
    enum class E_TextObjects{
        Button,
        Label
    };

    enum class E_Interaction {
        Dialog,
        Item,
        Room
    };

    typedef struct  {
        QWidget *widget;
        std::string text;
        E_TextObjects type;
    } TranslationObj;

    typedef struct {
        float x;
        float y;
    } Point2D;

    enum class E_Collision {
        Rectangle = 0,
        Cirle = 1
    };

    typedef union {
        char keys;
        struct {
            char forward : 1;
            char back : 1;
            char left : 1;
            char right : 1;
            char interact : 1;
            char update : 1;
            char unused : 2;
        } data;
    } COMMANDS;

    typedef struct {
        QString text;
        QString speaker;
    } DialogStruct;

    const float SPEED = 0.05;
}

#endif // DEFINES_H
