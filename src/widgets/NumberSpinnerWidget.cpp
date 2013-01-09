#include "NumberSpinnerWidget.h"

#include "helpers.h"
#include <QApplication>
#include <QMouseEvent>
#include <QTimer>
#include <math.h>
#include "widgets/TextWidget.h"
#include "widgets/ImageWidget.h"
#include <sstream>

namespace ipn
{

    NumberSpinnerWidget::NumberSpinnerWidget(int start, int end, int stepSize, QWidget *parent) : FlickArea(parent)
    {
        this->resize(64, 128);
        m_start = start;
        m_end = end;
        m_stepSize = stepSize;

        for(int number = start, idx=0; number <= end; number += stepSize, idx++)
            createNumber(idx, number);
    }

    void NumberSpinnerWidget::createNumber(int idx, int number){
        TextWidget* tw = new TextWidget(this);
        //tw->setColor(Qt::white);

        char buffer [33];
        //itoa (number,buffer,10);

        tw->setText("12");
        tw->move(0, 20 * idx);
        //printf("called!");
    }

}
