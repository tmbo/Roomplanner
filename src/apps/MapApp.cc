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
#include "apps/FurnitureViewer.h"


namespace ipn
{

    MapApp::MapApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
	{
        m_frameWidget = frameWidget;

        m_room = new RoomWidget(this);
        m_room->move(0, 0);
        m_room->resize(240, 240);

        m_addButton = new ButtonWidget(this);
        m_addButton->setInactiveImages(":/assets/images/buttons/button_menu.png");
        m_addButton->move(198, 2);
        connect(m_addButton, SIGNAL(clicked()), this, SLOT(showOverlay()));

        m_deleteButton = new ButtonWidget(this);
        m_deleteButton->setInactiveImages(":/assets/images/buttons/button_delete.png");
        m_deleteButton->move(2, 198);
        m_deleteButton->setHidden(true);
        connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(deleteFurniture()));

        m_editButton = new ButtonWidget(this);
        m_editButton->setInactiveImages(":/assets/images/buttons/button_edit.png");
        m_editButton->move(198, 198);
        m_editButton->setHidden(true);
        connect(m_editButton, SIGNAL(clicked()), this, SLOT(editFurniture()));

        m_menu = new ListMenuApp(m_frameWidget);
        connect(m_menu->m_furniturePicker, SIGNAL(furnitureSelected(int, int, int)), this, SLOT(placeFurniture(int, int, int)));

        m_furnitureViewer = new FurnitureViewer(m_frameWidget);
        connect(m_furnitureViewer, SIGNAL(furnitureSelected(int, int, int)), this, SLOT(hideAndPropagate(int, int, int)));
        connect(m_furnitureViewer->titleBar(), SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));

    }

    void MapApp::furniturePressed()
    {
        qDebug("p");
    }

    void MapApp::furnitureReleased()
    {
        qDebug("r");
    }


    void MapApp::showOverlay()
    {
        m_room->unselectFurniture();
        m_frameWidget->pushApp(m_menu);
    }

    void MapApp::placeFurniture(int idx, int size, int color)
    {
        m_room->addFurniture(idx, size, color);
    }


    void MapApp::deleteFurniture()
    {
        m_room->deleteFurniture();
        m_deleteButton->setHidden(true);
    }

    void MapApp::editFurniture()
    {
        m_frameWidget->pushApp(m_furnitureViewer);
    }


    void MapApp::hideAndPropagate(int i, int size, int color){
        m_room->deleteFurniture();
        m_frameWidget->popApp(2);
        m_room->addFurniture(i, size, color);
    }

} // namespace ipn
