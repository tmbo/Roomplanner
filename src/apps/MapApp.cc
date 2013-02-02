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
#include "apps/SettingsApp.h"
#include "SettingsMapper.h"


namespace ipn
{

    MapApp::MapApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
	{
        m_frameWidget = frameWidget;

        m_room = new RoomWidget(this);
        m_room->move(0, 0);
        m_room->resize(240, 240);

        m_addButton = new ButtonWidget(this);
        m_addButton->setInactiveImages(":/assets/images/buttons/button_add.png");
        m_addButton->move(198, 2);

        m_deleteButton = new ButtonWidget(this);
        m_deleteButton->setInactiveImages(":/assets/images/buttons/button_delete.png");
        m_deleteButton->move(2, 198);
        m_deleteButton->setHidden(true);


        m_editButton = new ButtonWidget(this);
        m_editButton->setInactiveImages(":/assets/images/buttons/button_edit.png");
        m_editButton->move(198, 198);
        m_editButton->setHidden(true);
        connect(m_editButton, SIGNAL(clicked()), this, SLOT(editFurniture()));

        m_settingsApp = new SettingsApp(m_frameWidget);
        connect(m_settingsApp, SIGNAL(settingsDone(int, int)), this, SLOT(settingsSet(int, int)));

        m_furniturePickerApp = new FurniturePickerApp(m_frameWidget);

        connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(deleteFurniture()));
        connect(m_addButton, SIGNAL(clicked()), this, SLOT(showOverlay()));
        connect(m_furniturePickerApp, SIGNAL(furnitureSelected(int,int,int)), this, SLOT(placeFurniture(int,int,int)));

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
        m_frameWidget->pushApp(m_furniturePickerApp);
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
        SettingsMapper element = m_room->getSelectedFurniture();
        m_settingsApp->setFurnitureIndex(element.m_id);
        m_settingsApp->setSettings(element.m_color, element.m_size);
        m_frameWidget->pushApp(m_settingsApp);
    }


    void MapApp::settingsSet(int size, int color){
        m_room->deleteFurniture();
        //get id i
        m_frameWidget->popApp(1);
        m_room->addFurniture(0, size, color);
    }

} // namespace ipn
