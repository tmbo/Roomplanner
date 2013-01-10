#include "MapApp.h"
#include "helpers.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/FlickArea.h"
#include <stdio.h>
#include "widgets/ButtonWidget.h"
#include "IPodFrameWidget.h"
#include "widgets/ImageWidget.h"
#include "widgets/RoomWidget.h"
#include "apps/ListMenuApp.h"
#include "apps/FurniturePickerApp.h"

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

        m_deleteButton = new ButtonWidget(this);
        m_deleteButton->setInactiveImages(":/assets/images/button_delete.png");
        m_deleteButton->move(10,5);
        m_deleteButton->setHidden(true);
        connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(deleteFurniture()));


        m_menu = new ListMenuApp(m_frameWidget);

        m_currentScaleFactor = 1.0;

        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));

        connect(m_addButton, SIGNAL(clicked()), this, SLOT(showOverlay()));

        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
        connect(this, SIGNAL(pinchRotationAngleChanged(qreal)), this, SLOT(changePinchRotationAngle(qreal)));
        connect(m_menu->m_furniturePicker, SIGNAL(furnitureSelected(int)), this, SLOT(placeFurniture(int)));
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
        m_frameWidget->pushApp(m_menu);
    }

    void MapApp::placeFurniture(int idx)
    {
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

    void MapApp::deleteFurniture()
    {
        m_room->deleteFurniture();
        m_deleteButton->setHidden(true);
    }

	TitleBarWidget *MapApp::titleBar()
	{
		return m_titleBar;
	}

} // namespace ipn
