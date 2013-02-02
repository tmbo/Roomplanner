#include "FurnitureViewer.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/ImageWidget.h"
#include "widgets/ClickableWidget.h"
#include "apps/SettingsApp.h"
#include "IPodFrameWidget.h"
#include <stdio.h>

namespace ipn
{
    FurnitureViewer::FurnitureViewer(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
    {

        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);
        m_back->move(0, 0);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->move(0, 0);
        //m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);
        m_titleBar->addButton(TitleBarWidget::BUTTON_EDIT);

        m_frameWidget = frameWidget;
        m_image = new ImageWidget(this);

        m_settingsApp = new SettingsApp(m_frameWidget);

        connect(m_titleBar, SIGNAL(rightButtonClicked()), this, SLOT(openSettings()));
        connect(m_settingsApp, SIGNAL(settingsDone(int, int)), this, SLOT(emitFurnitureSelected(int, int)));

    }

    void FurnitureViewer::openSettings()
    {
        m_settingsApp->setFurnitureIndex(m_idx);
        m_settingsApp->setSettings(m_size, m_color);
        m_frameWidget->pushApp(m_settingsApp);
    }

    void FurnitureViewer::setSettings(int idx, int size, int color)
    {
        m_image->setImage(":/assets/images/furniture/karlstad.png");
        m_image->resize(240, 200);
        m_image->move(0, 40);
        update();
        m_idx = idx;
        m_size = size;
        m_color = color;
    }

    void FurnitureViewer::emitFurnitureSelected(int size, int color)
    {
       emit furnitureSelected(m_idx, size, color);
    }

    TitleBarWidget *FurnitureViewer::titleBar()
    {
        return m_titleBar;
    }

}
