#include "form04.h"
#include "ui_form04.h"

Form04::Form04(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form04)
{
    ui->setupUi(this);
}

Form04::~Form04()
{
    delete ui;
}
