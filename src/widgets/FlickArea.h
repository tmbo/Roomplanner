#ifndef IPN_FLICKAREA_H
#define IPN_FLICKAREA_H

#include "PrettyClickableWidget.h"

namespace ipn
{
    class FlickArea : public ClickableWidget
    {
        Q_OBJECT

        public:
            FlickArea(QWidget *parent = 0);

            virtual void resize(int width, int height);

            QPointF relativeScrollPosition();
            QPointF absoluteScrollPosition();

            float innerWidth();

            void setSnapEnabled(bool value);
            void setMovementLockEnabled(bool value);

            bool shadowsEnabled() { return m_shadowsEnabled; };
            void setShadowsEnabled(bool value);

            void setMoveAfterRelease(bool value);

            inline float shadowFadeInDistance() { return m_shadowFadeInDistance; };
            inline void setShadowFadeInDistance(float value) { m_shadowFadeInDistance = value; };

            inline void setShadowGray(unsigned char value) { m_overlay->setGradientGray(value); }
            inline void setShadowWidth(int value) { m_overlay->setGradientWidth(value); };

            void setActive();
            void setInactive();

        public slots:
            void forwardMouseEvent(QMouseEvent *event, bool simulateMouseRelease = false);

        signals:
            void moved(int);
            void released();
            void ready();

        protected:
            void mousePressEvent(QMouseEvent *event);
            void mouseMoveEvent(QMouseEvent *event);
            void mouseReleaseEvent(QMouseEvent *event);
            void paintEvent(QPaintEvent *event);

        private:
            PrettyClickableWidget *m_overlay;

            QTimer *m_animationTimer;
            QPoint m_lastMousePos;
            QPoint m_mouseDownPos;
            QPoint m_scrollOffset;
            QPoint m_movementLock;
            bool m_mouseMovedSinceMousePress;
            bool m_shadowsEnabled;
            float m_shadowFadeInDistance;
            QWidget *m_currentChild;

            bool m_moveAfterRelease;
            bool m_mouseDown;
            bool m_animating;
            bool m_active;
            bool m_snapping;
            bool m_movementLockEnabled;

            float calculateFlickDistance(float realDistance);
            void flick(QPoint offset);
            inline void scrollOutToShadowAlpha(PrettyClickableWidget::GradientPosition pos, qreal value);

        private slots:
            void proceedAnimation();
    };

} // namespace ipn

#endif // IPN_FLICKAREA_H

