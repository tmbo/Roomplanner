#include "FlickArea.h"
#include "helpers.h"
#include <QApplication>
#include <QMouseEvent>
#include <QTimer>
#include <qmath.h>
#include <QtAlgorithms>

QPoint multiplyPoint(QPoint p1, QPoint p2) {
    p1.setX(p1.x() * p2.x());
    p1.setY(p1.y() * p2.y());
    return p1;
}
#define MOVEMENT_LOCK_THRESHOLD 2
#define SNAPPING_DIRECTION_ASSIST 0.3

namespace ipn
{

    FlickArea::FlickArea(QWidget *parent) : ClickableWidget(parent)
    {
        m_active = true;
        m_scrollOffset = QPoint(0, 0);
        m_animating = false;

        // Create the animation timer:
        m_animationTimer = new QTimer(this);
        m_animationTimer->setSingleShot(false);
        connect(m_animationTimer, SIGNAL(timeout()), this, SLOT(proceedAnimation()));
        m_animationTimer->start(30);

        // Create an overlay to make sure the children do not catch any events we want to filter
        m_overlay = new PrettyClickableWidget(this);
        m_overlay->move(0, 0);
        m_overlay->resize(width(), height());

        m_currentChild = NULL;
        m_shadowsEnabled = false;
        m_shadowFadeInDistance = 24.0;
    }

    void FlickArea::resize(int width, int height)
    {
        ClickableWidget::resize(width, height);

        m_overlay->resize(width, height);
    }

    QPointF FlickArea::relativeScrollPosition()
    {
        float relativeX = -(float)childrenRect().x() / (childrenRect().width() - width());
        relativeX = helpers::maxf(0, helpers::minf(1, relativeX));

        float relativeY = -(float)childrenRect().y() / (childrenRect().height() - height());
        relativeY = helpers::maxf(0, helpers::minf(1, relativeY));

        return QPointF(relativeX, relativeY);
    }

    QPointF FlickArea::absoluteScrollPosition()
    {
        float absoluteX = -(float)childrenRect().x();
        float absoluteY = -(float)childrenRect().y();
        return QPointF(absoluteX, absoluteY);
    }

    float FlickArea::innerWidth()
    {
        return childrenRect().width();
    }

    void FlickArea::setMoveAfterRelease(bool value)
    {
        m_moveAfterRelease = value;
    }

    void FlickArea::setSnapEnabled(bool value)
    {
        m_snapping = value;
    }

    void FlickArea::setInactive()
    {
        m_active = false;
        update();
    }

    void FlickArea::setActive()
    {
        m_active = true;
        update();
    }

    void FlickArea::forwardMouseEvent(QMouseEvent *event, bool simulateMouseRelease)
    {
        if (m_active)
        {
            // make sure the child exists and that it is not the overlay, else this FlickArea would
            // handle and emit it infinitely
            if (!m_currentChild || m_currentChild == m_overlay)
                return;

            QPoint pos = event->pos() - m_currentChild->pos();
            QEvent::Type type = event->type();

            // simulate mouse release outside the widget by clicking at (-1, -1) which is always outside
            if (simulateMouseRelease)
            {
                pos = QPoint(-1, -1);
                type = QEvent::MouseButtonRelease;
            }

            QMouseEvent childEvent(type, pos, event->button(), event->buttons(), event->modifiers());

            m_currentChild->setAttribute(Qt::WA_NoMousePropagation);

            QApplication::sendEvent(m_currentChild, &childEvent);
        }
    }

    void FlickArea::mousePressEvent(QMouseEvent *event)
    {
        if (m_active)
        {
            m_mouseMovedSinceMousePress = false;

            // to determine the currently clicked child, it is necessary to hide the overlay, else
            // childAt would return us the overlay
            m_overlay->hide();
            m_currentChild = childAt(event->pos());
            forwardMouseEvent(event);
            m_overlay->show();

            m_lastMousePos = event->pos();
            m_mouseDownPos = event->pos();
            m_scrollOffset = QPoint(0, 0);
            m_movementLock = QPoint(1, 1);

            m_mouseDown = true;
        }
        ClickableWidget::mousePressEvent(event);
    }

    void FlickArea::mouseMoveEvent(QMouseEvent *event)
    {
        if (m_active)
        {
            m_mouseMovedSinceMousePress = true;

            // since the mouse was moved, simulate a mouse release event on the child
            forwardMouseEvent(event, true);

            QPoint moveDifference = event->pos() - m_lastMousePos;
            m_lastMousePos = event->pos();

            if (m_movementLock.x() == 1 && m_movementLock.y() == 1) {
                QPoint movement = m_lastMousePos - m_mouseDownPos;
                if (abs(movement.x()) > MOVEMENT_LOCK_THRESHOLD || abs(movement.y()) > MOVEMENT_LOCK_THRESHOLD) {

                    if (abs(movement.x()) > abs(movement.y()))
                        m_movementLock = QPoint(1, 0);
                    else
                        m_movementLock = QPoint(0, 1);

                    qDebug("%i %i\n", m_movementLock.x() ? 0 : movement.x(), m_movementLock.y() ? 0 : movement.y());

//                    foreach (QObject *childObject, children())
//                    {
//                        // Don't move our event-catching overlay
//                        if (childObject == m_overlay)
//                            continue;

//                        QWidget *childWidget = qobject_cast<QWidget*>(childObject);

//                        if (childWidget)
//                            childWidget->move(
//                                childWidget->pos() +
//                                QPoint(
//                                    m_movementLock.x() ? 0 : movement.x(),
//                                    m_movementLock.y() ? 0 : movement.y()));
//                    }

                    m_scrollOffset = multiplyPoint(m_scrollOffset, m_movementLock);
                    moveDifference = multiplyPoint(moveDifference, m_movementLock);

                }
            } else {
                moveDifference = multiplyPoint(moveDifference, m_movementLock);
            }

            flick(moveDifference);
        }
    }

    void FlickArea::mouseReleaseEvent(QMouseEvent *event)
    {
        if (m_active)
        {
            // if the area was not flicked, forward the event normally,
            // else simulate releasing the mouse outside the widget to prevent it from being clicked
            if (!m_mouseMovedSinceMousePress)
                forwardMouseEvent(event);
            else
                forwardMouseEvent(event, true);

            m_lastMousePos = event->pos();
            m_lastMousePos = QPoint(m_lastMousePos.x()+absoluteScrollPosition().x(),
                                    m_lastMousePos.y()+absoluteScrollPosition().y());

            m_currentChild = NULL;
            released();
            if (!m_animating)
            {
                emit ready();
            }
            m_mouseDown = false;
        }
        ClickableWidget::mouseReleaseEvent(event);
    }

    void FlickArea::paintEvent(QPaintEvent*)
    {
        // Make sure the overlay is on top of all other children before drawing the FlickArea
        m_overlay->raise();

        if (!m_shadowsEnabled)
            return;

        QPointF absPos = absoluteScrollPosition();
        QRect cRect = childrenRect();

        scrollOutToShadowAlpha(PrettyClickableWidget::TOP_GRADIENT, absPos.y());
        scrollOutToShadowAlpha(PrettyClickableWidget::BOTTOM_GRADIENT, cRect.height() - absPos.y() - height());
        scrollOutToShadowAlpha(PrettyClickableWidget::LEFT_GRADIENT, absPos.x());
        scrollOutToShadowAlpha(PrettyClickableWidget::RIGHT_GRADIENT, cRect.width() - absPos.x() - width());
    }

    void FlickArea::proceedAnimation()
    {
        if(m_moveAfterRelease || m_mouseDown) {
            // Move each child widget by m_scrollOffset

            m_animating = true;

            if (m_snapping && !m_mouseDown &&
                (((abs(m_scrollOffset.x()) < 5) && (qAbs(m_scrollOffset.x() * 0.2) > 0)) || ((abs(m_scrollOffset.y()) < 5) && (qAbs(m_scrollOffset.y() * 0.2) > 0)))) {
                QRect cRect = QRect();
                QPoint cCount = QPoint(3,1);
                QList<QPoint> childPositions = QList<QPoint>();
                QPoint cActualSize = QPoint(0,0);

                foreach (QObject *childObject, children())
                {
                    // Don't move our event-catching overlay
                    if (childObject == m_overlay)
                        continue;

                    QWidget *childWidget = qobject_cast<QWidget*>(childObject);

                    if (childWidget) {
                        QRect childRect = childWidget->rect();
                        childRect.moveTo(childWidget->pos());
                        cRect = cRect.united(childRect);
                        cActualSize.setX(cActualSize.x() + childRect.size().width());
                        cActualSize.setY(cActualSize.y() + childRect.size().height());
                        childPositions.push_back(childRect.topLeft());
                    }
                }
                for(int i = 0; i < childPositions.length(); i++) {
                    childPositions.replace(i, childPositions.at(i) - cRect.topLeft());
                }

                QPoint direction = multiplyPoint(QPoint(
                    m_scrollOffset.x() < 0 ? -1 : 1,
                    m_scrollOffset.y() < 0 ? -1 : 1), m_movementLock);
                QPoint snapIndex = QPoint(
                    - round((float)cCount.x() * cRect.left() / cRect.width()),
                    - round((float)cCount.y() * cRect.top() / cRect.height())
                    ) + direction * SNAPPING_DIRECTION_ASSIST;

                QPoint delta = - cRect.topLeft() - childPositions.at(snapIndex.x() * cCount.y() + snapIndex.y());

                foreach (QObject *childObject, children())
                {
                    // Don't move our event-catching overlay
                    if (childObject == m_overlay)
                        continue;

                    QWidget *childWidget = qobject_cast<QWidget*>(childObject);

                    if (childWidget)
                        childWidget->move(childWidget->pos() + delta);
                }

                // stop animation
                m_scrollOffset = QPoint(0,0);
                moved(snapIndex.x());
            }

            foreach (QObject *childObject, children())
            {
                // Don't move our event-catching overlay
                if (childObject == m_overlay)
                    continue;

                QWidget *childWidget = qobject_cast<QWidget*>(childObject);

                if (childWidget)
                    childWidget->move(childWidget->pos() + (m_scrollOffset * 0.2));
            }

            // If the widgets were moved by at least one pixel, announce the changement
            if (!(((int)qAbs(m_scrollOffset.x() * 0.2)) > 0 || ((int)qAbs(m_scrollOffset.y() * 0.2)) > 0))
                m_scrollOffset = QPoint(0, 0);

            m_scrollOffset *= (1 - 0.2);
        }

        m_animating = false;

        if ( (abs(m_scrollOffset.y()) < 5) && (abs(m_scrollOffset.x()) < 5))
        {
            emit ready();
        }
    }

    float FlickArea::calculateFlickDistance(float realDistance)
    {
        int signum = (realDistance < 0.0) ? -1 : 1;
        float acceleratedChangement = signum * qPow(realDistance / 8.0, 2) * 8.0;

        return qAbs(realDistance) > qAbs(acceleratedChangement)
            ? realDistance
            : acceleratedChangement;
    }

    void FlickArea::flick(QPoint offset)
    {
        // Add the current offset to the sum of offsets:
        m_scrollOffset += multiplyPoint(QPoint(calculateFlickDistance(offset.x()),
            calculateFlickDistance(offset.y())), m_movementLock);

        // Calculate how much place the children take:
        QRect cRect = childrenRect();

        // Make sure the children will stay inside the borders of this widget:
        if (cRect.right() + m_scrollOffset.x() > helpers::max(cRect.width(), width()))
            m_scrollOffset.setX(helpers::max(cRect.width(), width()) - cRect.right());

        if (cRect.left() + m_scrollOffset.x() < helpers::min(width() - cRect.width(), 0))
            m_scrollOffset.setX(-cRect.left() + helpers::min(width() - cRect.width(), 0));

        if (cRect.bottom() + m_scrollOffset.y() > helpers::max(cRect.height(), height()))
            m_scrollOffset.setY(helpers::max(cRect.height(), height()) - cRect.bottom());

        if (cRect.top() + m_scrollOffset.y() < helpers::min(height() - cRect.height(), 0))
            m_scrollOffset.setY(-cRect.top() + helpers::min(height() - cRect.height(), 0));
    }


    void FlickArea::setShadowsEnabled(bool value)
    {
        m_shadowsEnabled = value;
        m_overlay->setAllGradientsEnabled(value);
    }

    inline void FlickArea::scrollOutToShadowAlpha(PrettyClickableWidget::GradientPosition pos, qreal value)
    {
         m_overlay->setGradientAlpha(pos, (int) (255.0 * helpers::minf(1.0, value / m_shadowFadeInDistance)));
    }

} // namespace ipn

