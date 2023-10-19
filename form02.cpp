#include "form02.h"
#include "ui_form02.h"

Form02::Form02(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form02)
{
    ui->setupUi(this);
}

Form02::~Form02()
{
    delete ui;
}
