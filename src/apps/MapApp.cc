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
#include "widgets/ImageWidget.h"
#include "widgets/RoomWidget.h"

namespace ipn
{

    MapApp::MapApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
	{
        /*m_titleBar = new TitleBarWidget(this);
		m_titleBar->setTitle("MapApp");
		m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);*/

        m_frameWidget = frameWidget;

        m_room = new RoomWidget(this);
        m_room->move(0, 0);
        m_room->resize(240, 240);

//        m_flickArea = new FlickArea(this);
//        m_flickArea->resize(240, 240);
//        m_flickArea->move(0, 0);

//        graphicsView = new QGraphicsView(m_flickArea);
//        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
//        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

//        m_currentScaleFactor = 1.0;
//        m_currentRotationAngle = 0;

//        scene = new QGraphicsScene(graphicsView);
//        graphicsView->setScene(scene);

//        background = scene->addPixmap(QPixmap(":/img/backgrounds/map.png"));
//        background->setTransformationMode(Qt::SmoothTransformation);

        m_addButton = new ButtonWidget(this);
        m_addButton->setInactiveImages(":/assets/images/add.png");
        m_addButton->move(203,5);

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
        connect(m_picker, SIGNAL(entryChanged()), this, SLOT(openSofaGUI()));

        m_guiApp=new GUIApp();
        connect(m_guiApp->titleBar(), SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_guiApp, SIGNAL(furnitureSelected(int)), this, SLOT(placeFurniture(int)));


        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));

        connect(m_addButton, SIGNAL(clicked()), this, SLOT(showOverlay()));

        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
        connect(this, SIGNAL(pinchRotationAngleChanged(qreal)), this, SLOT(changePinchRotationAngle(qreal)));

//        m_clickable0 = new ClickableWidget(m_flickArea);
//        m_image0 = new ImageWidget(m_clickable0);
//        m_image0->setImage(":/assets/images/sofa2d.png");
//        connect(m_clickable0, SIGNAL(pressed()), this, SLOT(furniturePressed()));
//        connect(m_clickable0, SIGNAL(released()), this, SLOT(furnitureReleased()));
//        scene->addWidget(m_image0);
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
//        qreal newScaleFactor = helpers::maxf(helpers::minf(m_currentScaleFactor * delta, 10.0), .1);
//        background->setTransformOriginPoint(background->pos());
//        background->scale(newScaleFactor / m_currentScaleFactor, newScaleFactor / m_currentScaleFactor);
//        m_currentScaleFactor = newScaleFactor;

//        update();
    }

    void MapApp::showOverlay()
    {
        m_back->show();

        m_picker->show();
    }

    void MapApp::openSofaGUI(){
        m_picker->setActiveEntry(-1);
        m_frameWidget->pushApp(m_guiApp);
    }

    void MapApp::placeFurniture(int idx)
    {
        m_back->hide();
        m_picker->hide();
        m_frameWidget->popApp();

        printf("idx: %d\n", idx);
        // do whatever needs to be done with the new furniture
        m_room->addFurniture(idx);
    }

    void MapApp::changePinchRotationAngle(qreal delta)
    {
//        m_currentRotationAngle += delta;
//        background->rotate(delta);
//        //printf("%f\n", m_currentRotationAngle);
//        update();
    }

	TitleBarWidget *MapApp::titleBar()
	{
		return m_titleBar;
	}

} // namespace ipn
