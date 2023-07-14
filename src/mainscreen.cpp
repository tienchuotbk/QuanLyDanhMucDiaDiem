#include "mainscreen.h"
#include "ui_mainscreen.h"

mainscreen::mainscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainscreen)
{
    ui->setupUi(this);
}

mainscreen::~mainscreen()
{
    delete ui;
}
