#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QtCore>
#include <QtGui>

namespace ipn
{
    class ClickableWidget;
    class ButtonWidget;
    class MapApp;

    class RoomWidget : public QWidget
    {
        Q_OBJECT

        public:
            explicit RoomWidget(MapApp *parent = 0);
            void addFurniture(int idx, int size = 0, int color = 0);
            void deleteFurniture();
            void unselectFurniture();
            void selectFurniture(QGraphicsItem *item);
            virtual void resize(int width, int height);
            virtual void mousePressEvent(QMouseEvent *event);
            virtual void mouseMoveEvent(QMouseEvent *event);
            virtual void mouseReleaseEvent(QMouseEvent *event);
            virtual void mouseTapEvent(QMouseEvent *event);


        protected:

        private:
            MapApp *m_parent;
            ClickableWidget *m_overlay;
            QGraphicsView *m_graphicsView;
            QGraphicsScene *m_scene;
            QGraphicsItemGroup *m_sceneRoot;
            QGraphicsPixmapItem *m_background;

            QPoint m_lastMousePos;
            QPoint m_scrollOffset;
            qreal m_currentScaleFactor;
            bool m_isPressed;
            bool m_isRotating;

            QTimer* m_tapTimer;
            QGraphicsItem *m_selectedItem;
            QPixmap *m_tempPixmap;
            QString *m_tempUrl;

        signals:

        public slots:
            void changePinchScaleFactor(qreal delta);
            void changePinchRotationAngle(qreal delta);

    };
}

#endif // ROOMWIDGET_H
