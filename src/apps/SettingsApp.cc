#include "SettingsApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/ScalableButtonWidget.h"
#include "apps/FurniturePickerApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/PickerWidget.h"
#include "IPodFrameWidget.h"
#include "apps/GUIApp.h"
#include "apps/DummyApp.h"
#include "widgets/TitleBarWidget.h"
#include "apps/NumberPickerApp.h"

#include <stdio.h>

namespace ipn
{

    SettingsApp::SettingsApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
    {
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_TRANSPARENT);
        m_back->move(0, 0);

        m_frameWidget = frameWidget;

        m_picker = new PickerWidget(this);
        m_picker->addEntry("Size","2,1 x 1,5 m");
        m_picker->addEntry("Color", "RED");
        m_picker->move(0, 48);

        m_numberPicker = new NumberPickerApp(frameWidget);
        //m_colorPicker = 0;

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Settings");
        m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);
        m_titleBar->addButton(TitleBarWidget::BUTTON_DONE);

        //connect(m_picker, SIGNAL(entryChanged()), this, SLOT(openFurnitureApp()));
        connect(m_titleBar, SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_titleBar, SIGNAL(rightButtonClicked()),this,SIGNAL(settingsDone()));
        connect(m_picker, SIGNAL(entryChanged()),this,SLOT(showValueChanger()));
    }

    void SettingsApp::showValueChanger(){
        if(m_picker->activeEntry() == 0)
            m_frameWidget->pushApp(m_numberPicker);
        /*else
            m_frameWidget->pushApp(m_colorPicker);*/
    }

} // namespace ipn
