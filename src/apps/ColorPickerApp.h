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
            void setColors(int furnitureIndex);
            QColor colorValue(int, int);
            virtual void mousePressEvent(QMouseEvent *event);

        signals:
            void inputFinished(int furnitureIndex, QColor color);

        private:
            BackgroundWidget *m_back;
            TitleBarWidget *m_titleBar;
            QGraphicsView *m_graphicsView;
            QGraphicsScene *m_scene;
            QGraphicsEllipseItem *m_color0;
            QGraphicsEllipseItem *m_color1;
            QGraphicsEllipseItem *m_color2;
            int m_furnitureIndex;

        public slots:


        protected:
            IPodFrameWidget *m_frameWidget;


        protected slots:

    };
}

#endif // COLORPICKERAPP_H
