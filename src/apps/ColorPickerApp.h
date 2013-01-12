#ifndef COLORPICKERAPP_H
#define COLORPICKERAPP_H

#include <QtCore>
#include <QtGui>
#include "App.h"

namespace ipn
{
    class IPodFrameWidget;
    class BackgroundWidget;
    class TitleBarWidget;

    class ColorPickerApp : public App
    {
        Q_OBJECT

        public:
            explicit ColorPickerApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

        signals:
            void inputFinished(int color);

        private:
            BackgroundWidget *m_back;
            TitleBarWidget *m_titleBar;
            QGraphicsView *m_graphicsView;
            QGraphicsScene *m_scene;

        public slots:


        protected:
            IPodFrameWidget *m_frameWidget;

    };
}

#endif // COLORPICKERAPP_H
