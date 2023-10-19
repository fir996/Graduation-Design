#include "form03.h"
#include "ui_form03.h"

Form03::Form03(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form03)
{
    ui->setupUi(this);
}

Form03::~Form03()
{
    delete ui;
}
