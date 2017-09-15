#include "valueelement.h"

ValueElement::ValueElement(int number)
{
    p_layout = new QHBoxLayout;
    p_label = new QLabel;
    p_line_edit = new QLineEdit;

    p_label->setNum(number);

    setLayout(p_layout);
    setFixedHeight(50);

    p_layout->addWidget(p_label);
    p_layout->addWidget(p_line_edit);
}
