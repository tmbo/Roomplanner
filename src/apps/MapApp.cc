#include "MapApp.h"
#include "helpers.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/FlickArea.h"
#include <stdio.h>
#include "widgets/ButtonWidget.h"
#include "widgets/ImageWidget.h"

namespace ipn
{

	MapApp::MapApp(QWidget *parent) : App(parent)
	{
        /*m_titleBar = new TitleBarWidget(this);
		m_titleBar->setTitle("MapApp");
		m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);*/

          m_addButton = new ButtonWidget(this);
          m_addButton->setInactiveImages(":/assets/images/add.png");
          m_addButton->move(200,5);

        m_flickArea = new FlickArea(this);
        m_flickArea->resize(240, 192);
        m_flickArea->move(0, 48);

        graphicsView = new QGraphicsView(m_flickArea);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

        m_currentScaleFactor = 1.0;
        m_currentRotationAngle = 0;

        scene = new QGraphicsScene(graphicsView);
        graphicsView->setScene(scene);

        backgroundPixmap = new QPixmap(":/img/backgrounds/map.png");
        background = scene->addPixmap(*backgroundPixmap);

        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
        connect(this, SIGNAL(pinchRotationAngleChanged(qreal)), this, SLOT(changePinchRotationAngle(qreal)));

        m_clickable0 = new ClickableWidget(m_flickArea);
        m_image0 = new ImageWidget(m_clickable0);
        m_image0->setImage(":/assets/images/sofa2d.png");
        connect(m_clickable0, SIGNAL(pressed()), this, SLOT(furniturePressed()));
        connect(m_clickable0, SIGNAL(released()), this, SLOT(furnitureReleased()));
        scene->addWidget(m_image0);

        update();
    }

    void MapApp::furniturePressed()
    {
        qDebug("p");
    }

    void MapApp::furnitureReleased()
    {
        qDebug("r");
    }


    void MapApp::changePinchScaleFactor(qreal delta)
    {
        m_currentScaleFactor *= delta;

        m_currentScaleFactor = helpers::maxf(helpers::minf(m_currentScaleFactor, 10.0), .1);

        background->scale(delta, delta);

        update();
    }

    void MapApp::changePinchRotationAngle(qreal delta)
    {
        m_currentRotationAngle += delta;
        graphicsView->rotate(delta);
        //printf("%f\n", m_currentRotationAngle);
        update();
    }

	TitleBarWidget *MapApp::titleBar()
	{
		return m_titleBar;
	}

} // namespace ipn
