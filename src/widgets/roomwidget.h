#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QtCore>
#include <QtGui>

namespace ipn
{
    class ClickableWidget;

    class RoomWidget : public QWidget
    {
        Q_OBJECT

        public:
            explicit RoomWidget(QWidget *parent = 0);
            virtual void resize(int width, int height);
            virtual void mousePressEvent(QMouseEvent *event);
            virtual void mouseMoveEvent(QMouseEvent *event);
            virtual void mouseReleaseEvent(QMouseEvent *event);

        protected:

        private:
            ClickableWidget *m_overlay;
            QGraphicsView *m_graphicsView;
            QGraphicsScene *m_scene;
            QGraphicsPixmapItem *m_background;

            QPoint m_lastMousePos;
            QPoint m_scrollOffset;
            qreal m_currentScaleFactor;
            bool m_isPressed;

            QGraphicsItem *m_selectedItem;

        signals:

        public slots:
            void changePinchScaleFactor(qreal delta);
            void changePinchRotationAngle(qreal delta);


    };
}

#endif // ROOMWIDGET_H
