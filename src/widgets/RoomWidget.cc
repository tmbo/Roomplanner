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

        m_graphicsView->setScene(m_scene);
        m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->setSceneRect(0, 0, 240, 240);
        m_graphicsView->move(0, 0);


        m_sceneRoot = m_scene->createItemGroup(QList<QGraphicsItem*>());

        m_background = m_scene->addPixmap(QPixmap(":/img/backgrounds/map.png"));
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

            qreal newScaleFactor = helpers::maxf(helpers::minf(m_currentScaleFactor * delta, 10.0), .1);
            qreal scaleDelta = newScaleFactor / m_currentScaleFactor;
            m_currentScaleFactor = newScaleFactor;

            QPoint mid = QPoint(width() / 2, height() / 2);
            QPointF translation = m_sceneRoot->mapFromScene(m_graphicsView->mapToScene(mid));

            QTransform transform = m_sceneRoot->transform();
            transform.translate(-translation.x(), -translation.y());
            transform.scale(scaleDelta, scaleDelta);
            transform.translate(translation.x(), translation.y());

            m_sceneRoot->setTransform(transform);

            QTransform m = m_sceneRoot->transform();
            printf("%f, %f, %f; %f, %f, %f\n",
                   m.m11(),m.m12(),m.m31(),
                   m.m21(),m.m22(),m.m32());
            m = m_background->transform();
            printf("%f, %f, %f; %f, %f, %f\n",
                   m.m11(),m.m12(),m.m31(),
                   m.m21(),m.m22(),m.m32());
            update();
        }
    }

    void RoomWidget::changePinchRotationAngle(qreal delta)
    {
        if (m_selectedItem) {
            m_selectedItem->rotate(delta);
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
                item->translate(moveDifference.x() / transform.m11(), moveDifference.y() / transform.m11());
            }
        }
    }

    void RoomWidget::mouseReleaseEvent(QMouseEvent *event){
        m_isPressed = false;

        if (m_tapTimer->isActive() && abs(m_scrollOffset.x()) < 3 && abs(m_scrollOffset.y()) < 3) {
            QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, m_lastMousePos, Qt::LeftButton, Qt::LeftButton, 0);
            mouseTapEvent(event);
            m_tapTimer->stop();
        }
    }

    void RoomWidget::mouseTapEvent(QMouseEvent *event){

        if (m_selectedItem != m_background && m_selectedItem != 0)
        {
            unselectFurniture();
        }

        QGraphicsItem *item = m_graphicsView->itemAt(event->pos() - this->pos());

        if (item != m_background)
        {
            selectFurniture(item);
            QPoint moveDifference = QPoint(width()/2, height() / 2) - event->pos();
            m_scrollOffset += moveDifference;

            QTransform transform = m_sceneRoot->transform();
            foreach(QGraphicsItem *item, m_scene->items()) {
                if (item == m_sceneRoot) continue;
                item->translate(moveDifference.x() / transform.m11(), moveDifference.y() / transform.m11());
            }
        }
    }

    void RoomWidget::addFurniture(int idx)
    {
        QString tempUrl = QString(":/assets/images/furniture2d_%1.png").arg(QString::number(idx));
        QGraphicsPixmapItem *item = m_scene->addPixmap(QPixmap(tempUrl));
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
        effect->setBlurRadius(8);
        m_selectedItem->setGraphicsEffect(effect);
        m_parent->m_deleteButton->setHidden(false);

    }


}
