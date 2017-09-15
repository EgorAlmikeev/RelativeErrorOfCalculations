#ifndef VALUEELEMENT_H
#define VALUEELEMENT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

class ValueElement : public QWidget
{
    Q_OBJECT

public:

    QHBoxLayout *p_layout;
    QLabel *p_label;
    QLineEdit *p_line_edit;

    ValueElement(int);
};

#endif // VALUEELEMENT_H
