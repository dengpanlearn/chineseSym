#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_symbolTrainWindow.h"

class CSymbolTrainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CSymbolTrainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::CSymbolTrainWindowClass ui;
};
