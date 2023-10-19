#ifndef FORM03_H
#define FORM03_H

#include <QWidget>

namespace Ui {
class Form03;
}

class Form03 : public QWidget
{
    Q_OBJECT

public:
    explicit Form03(QWidget *parent = nullptr);
    ~Form03();

private:
    Ui::Form03 *ui;
};

#endif // FORM03_H
