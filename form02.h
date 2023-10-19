#ifndef FORM02_H
#define FORM02_H

#include <QWidget>

namespace Ui {
class Form02;
}

class Form02 : public QWidget
{
    Q_OBJECT

public:
    explicit Form02(QWidget *parent = nullptr);
    ~Form02();

private:
    Ui::Form02 *ui;
};

#endif // FORM02_H
