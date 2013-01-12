#include "RoomWidget.h"
#include "helpers.h"
#include "widgets/ClickableWidget.h"
#include "widgets/ButtonWidget.h"
#include "apps/MapApp.h"

namespace ipn
{

    RoomWidget::RoomWidget(MapApp *parent) : QWidget(parent)
    {
        m_parent = parent;
        m_graphicsView = new QGraphicsView(this);
        m_scene = new QGraphicsScene(m_graphicsView);

        m_graphicsView->setBackgroundBrush(QBrush(QColor(230, 230, 230)));
        m_graphicsView->setScene(m_scene);
        m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->setSceneRect(0, 0, 240, 240);
        m_graphicsView->move(0, 0);

        m_sceneRoot = m_scene->createItemGroup(QList<QGraphicsItem*>());

        m_background = m_scene->addPixmap(QPixmap(":/assets/images/room.png"));
        m_background->setTransformationMode(Qt::SmoothTransformation);
        m_sceneRoot->addToGroup(m_background);

        m_selectedItem = 0;
        m_currentScaleFactor = 1.0;
        m_isPressed = false;

        connect(parent, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
        connect(parent, SIGNAL(pinchRotationAngleChanged(qreal)), this, SLOT(changePinchRotationAngle(qreal)));

        m_overlay = new ClickableWidget(this);
        m_overlay->move(0,0);
        m_overlay->resize(width(), height());

        m_tapTimer = new QTimer(this);
        m_tapTimer->setSingleShot(true);

        changePinchScaleFactor(.5);
    }

    void RoomWidget::resize(int width, int height)
    {
        QWidget::resize(width, height);
        m_graphicsView->resize(width, height);
        m_overlay->resize(width, height);
    }

    void RoomWidget::changePinchScaleFactor(qreal delta)
    {
        if (m_selectedItem == 0) {

            m_isPressed = false;

            qreal newScaleFactor = helpers::maxf(helpers::minf(m_currentScaleFactor * delta, 1.0), .3);
            qreal scaleDelta = newScaleFactor / m_currentScaleFactor;
            m_currentScaleFactor = newScaleFactor;

            QPointF translation = m_sceneRoot->mapFromScene(QPoint(width() / 2, height() / 2));

            m_sceneRoot->setTransform(
                QTransform()
                    .translate(translation.x(), translation.y())
                    .scale(scaleDelta, scaleDelta)
                    .translate(-translation.x(), -translation.y()),
                true
            );

            update();
        }
    }

    void RoomWidget::changePinchRotationAngle(qreal delta)
    {
        if (m_selectedItem) {

            m_isPressed = false;
            QPointF halfSize = m_selectedItem->boundingRect().center();
            m_selectedItem->transform().m13();

            QPointF ee = m_selectedItem->mapToScene(
                halfSize
            );
            m_selectedItem->setTransform(
                QTransform()
                    .translate(halfSize.x(), halfSize.y())
                    .rotate(delta)
                    .translate(-halfSize.x(), -halfSize.y()),
                true
            );

            update();
        }
    }

    void RoomWidget::mousePressEvent(QMouseEvent *event)
    {
        m_isPressed = true;

        m_lastMousePos = event->pos();
        m_scrollOffset = QPoint(0, 0);

        m_tapTimer->start(1000);
    }

    void RoomWidget::mouseMoveEvent(QMouseEvent *event)
    {
        if (m_isPressed) {
            QPoint moveDifference = event->pos() - m_lastMousePos;
            m_lastMousePos = event->pos();
            m_scrollOffset += moveDifference;

            QTransform transform = m_sceneRoot->transform();
            foreach(QGraphicsItem *item, m_scene->items()) {
                if (item == m_selectedItem || item == m_sceneRoot) continue;
                item->setTransform(
                    item->transform() *
                    QTransform().translate(
                        moveDifference.x() / transform.m11(),
                        moveDifference.y() / transform.m22())
                );

            }
        }
    }

    void RoomWidget::mouseReleaseEvent(QMouseEvent *event){

        m_isPressed = false;

        if (m_tapTimer->isActive() && abs(m_scrollOffset.x()) < 3 && abs(m_scrollOffset.y()) < 3) {
            QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress, m_lastMousePos, Qt::LeftButton, Qt::LeftButton, 0);
            mouseTapEvent(e);
            m_tapTimer->stop();
        }
    }

    void RoomWidget::mouseTapEvent(QMouseEvent *event){

        if (m_selectedItem != m_background && m_selectedItem != 0)
        {
            unselectFurniture();
        }

        QGraphicsItem *item = m_graphicsView->itemAt(event->pos() - this->pos());


        if (item != m_background && item != m_sceneRoot && item != 0)
        {
            selectFurniture(item);
            QPointF moveDifference =
                m_graphicsView->mapToScene(size().width() / 2, size().height() / 2) -
                m_selectedItem->mapToScene(m_selectedItem->boundingRect().center());

            QTransform transform = m_sceneRoot->transform();
            foreach(QGraphicsItem *item, m_scene->items()) {
                if (item == m_sceneRoot) continue;
                item->setTransform(
                    item->transform() *
                    QTransform().translate(
                        moveDifference.x() / transform.m11(),
                        moveDifference.y() / transform.m22())
                );
            }
        }
    }

    void RoomWidget::addFurniture(int idx, int size, int color)
    {
        QString tempUrl = QString(":/assets/images/furniture/couch_%1_%2_%3.png").arg(
            QString::number(idx),
            QString::number(size),
            QString::number(color)
        );
        QGraphicsPixmapItem *item = m_scene->addPixmap(QPixmap(tempUrl));
        item->setTransformationMode(Qt::SmoothTransformation);
        item->translate(width() / 2, height() / 2);
        item->scale(m_sceneRoot->transform().m11(), m_sceneRoot->transform().m22());
        item->translate(-item->pixmap().width() / 2, -item->pixmap().height() / 2);
        m_sceneRoot->addToGroup(item);
        selectFurniture(item);
    }

    void RoomWidget::deleteFurniture()
    {
        if (m_selectedItem != m_background && m_selectedItem != 0)
        {
            m_sceneRoot->removeFromGroup(m_selectedItem);
            m_scene->removeItem(m_selectedItem);
            m_selectedItem = 0;
        }
    }

    void RoomWidget::unselectFurniture()
    {
        if (m_selectedItem == 0)
            return;

        m_selectedItem->setGraphicsEffect(0);
        m_selectedItem = 0;
        m_parent->m_deleteButton->setHidden(true);
    }

    void RoomWidget::selectFurniture(QGraphicsItem *item)
    {
        // set dropShadow
        m_selectedItem = item;
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(20);
        effect->setColor(QColor(Qt::blue));
        effect->setOffset(0, 0);
        m_selectedItem->setGraphicsEffect(effect);
        m_parent->m_deleteButton->setHidden(false);

    }


}
