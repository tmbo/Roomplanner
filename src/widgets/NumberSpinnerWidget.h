#ifndef NUMBERSPINNERWIDGET_H
#define NUMBERSPINNERWIDGET_H

#include "widgets/FlickArea.h"
namespace ipn
{
    class FlickArea;
    class TextWidget;

    class NumberSpinnerWidget : public FlickArea
    {
        Q_OBJECT

        public:
            NumberSpinnerWidget(int start, int end, int stepSize, QWidget *parent);

        private:
            int m_start;
            int m_end;
            int m_stepSize;
            void createNumber(int idx, int number);
    };
}

#endif // NUMBERSPINNERWIDGET_H
