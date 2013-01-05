#include "MapApp.h"
#include "helpers.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/FlickArea.h"
#include <stdio.h>
#include "widgets/ButtonWidget.h"

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

        scene = new QGraphicsScene(graphicsView);
        graphicsView->setScene(scene);

        backgroundPixmap = new QPixmap(":/img/backgrounds/map.png");
        background = scene->addPixmap(*backgroundPixmap);

        m_currentScaleFactor = 1.0;
        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
        update();
    }

    void MapApp::changePinchScaleFactor(qreal delta)
    {
        m_currentScaleFactor *= delta;

        m_currentScaleFactor = helpers::maxf(helpers::minf(m_currentScaleFactor, 10.0), .1);

        background->scale(delta, delta);

        update();
    }

	TitleBarWidget *MapApp::titleBar()
	{
		return m_titleBar;
	}

} // namespace ipn
