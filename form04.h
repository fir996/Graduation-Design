#ifndef FORM04_H
#define FORM04_H

#include <QWidget>

namespace Ui {
class Form04;
}

class Form04 : public QWidget
{
    Q_OBJECT

public:
    explicit Form04(QWidget *parent = nullptr);
    ~Form04();

private:
    Ui::Form04 *ui;
};

#endif // FORM04_H
