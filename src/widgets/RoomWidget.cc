#include "RoomWidget.h"
#include "helpers.h"
#include "widgets/ClickableWidget.h"

namespace ipn
{

    RoomWidget::RoomWidget(QWidget *parent) : QWidget(parent)
    {
        m_graphicsView = new QGraphicsView(this);
        m_scene = new QGraphicsScene(m_graphicsView);

        m_graphicsView->setScene(m_scene);
        m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        m_graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        m_graphicsView->move(0, 0);

        m_background = m_scene->addPixmap(QPixmap(":/img/backgrounds/map.png"));
        m_background->setTransformationMode(Qt::SmoothTransformation);

        m_selectedItem = 0;
        m_currentScaleFactor = 1.0;
        m_isPressed = false;

        connect(parent, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
        connect(parent, SIGNAL(pinchRotationAngleChanged(qreal)), this, SLOT(changePinchRotationAngle(qreal)));

        m_overlay = new ClickableWidget(this);
        m_overlay->move(0,0);
        m_overlay->resize(width(), height());
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
            m_graphicsView->scale(scaleDelta, scaleDelta);
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
        m_selectedItem = m_graphicsView->itemAt(event->pos() - this->pos());

        if (m_selectedItem == m_background)
            m_selectedItem = 0;

        m_lastMousePos = event->pos();
        m_scrollOffset = QPoint(0, 0);
    }

    void RoomWidget::mouseMoveEvent(QMouseEvent *event)
    {
        if (m_isPressed) {
            QPoint moveDifference = event->pos() - m_lastMousePos;
            m_lastMousePos = event->pos();

            QTransform transform = m_graphicsView->transform();
            m_background->translate(moveDifference.x() / transform.m11(), moveDifference.y() / transform.m11());
        }
    }

    void RoomWidget::mouseReleaseEvent(QMouseEvent *event){
        m_isPressed = false;
    }

    void RoomWidget::addFurniture(int idx)
    {
        QString m_tempUrl = QString(":/assets/images/furniture2d_%1.png").arg(QString::number(idx));
        m_tempPixmap = new QPixmap();
        m_tempPixmap->load(m_tempUrl);
        m_scene->addPixmap(*m_tempPixmap);
    }

}
