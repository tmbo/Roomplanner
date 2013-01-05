#include "MapApp.h"
#include "helpers.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/FlickArea.h"
#include <stdio.h>
#include "widgets/ButtonWidget.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/PickerWidget.h"
#include "IPodFrameWidget.h"
#include "apps/GUIApp.h"

namespace ipn
{

    MapApp::MapApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
	{
        /*m_titleBar = new TitleBarWidget(this);
		m_titleBar->setTitle("MapApp");
		m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);*/

        m_frameWidget = frameWidget;

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

        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_TRANSPARENT);
        m_back->move(0, 0);
        m_back->hide();

        m_picker = new PickerWidget(this);
        m_picker->addEntry("Betten");
        m_picker->addEntry("Stühle");
        m_picker->addEntry("Sofas");
        m_picker->setActiveEntry(2);
        m_picker->move(0, 0);
        m_picker->hide();
        m_guiApp=new GUIApp();
        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));

        connect(m_addButton, SIGNAL(clicked()), this, SLOT(showOverlay()));

        update();
    }

    void MapApp::changePinchScaleFactor(qreal delta)
    {
        m_currentScaleFactor *= delta;

        m_currentScaleFactor = helpers::maxf(helpers::minf(m_currentScaleFactor, 10.0), .1);

        background->scale(delta, delta);

        update();
    }

    void MapApp::showOverlay()
    {
        m_back->show();

        m_picker->show();

        connect(m_picker, SIGNAL(entryChanged()), this, SLOT(openSofaGUI()));
    }

    void MapApp::openSofaGUI(){
        m_frameWidget->pushApp(m_guiApp);
        connect(m_guiApp->titleBar(), SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_guiApp, SIGNAL(furnitureSelected(int)), this, SLOT(placeFurniture(int)));
    }

    void MapApp::placeFurniture(int idx)
    {
        m_back->hide();
        m_picker->hide();
        m_frameWidget->popApp();

        printf("idx: %d\n", idx);
        // do whatever needs to be done with the new furniture
    }

	TitleBarWidget *MapApp::titleBar()
	{
		return m_titleBar;
	}

} // namespace ipn
