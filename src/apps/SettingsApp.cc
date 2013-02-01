#include "SettingsApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/ScalableButtonWidget.h"
#include "widgets/CircleWidget.h"
#include "apps/FurniturePickerApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/PickerWidget.h"
#include "IPodFrameWidget.h"
#include "apps/GUIApp.h"
#include "apps/DummyApp.h"
#include "widgets/TitleBarWidget.h"
#include "apps/NumberPickerApp.h"
#include "apps/ColorPickerApp.h"
#include <QtGui>

#include <stdio.h>

namespace ipn
{

    SettingsApp::SettingsApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
    {
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);
        m_back->move(0, 0);

        m_frameWidget = frameWidget;


        m_picker = new PickerWidget(this);
        m_picker->move(0, 48);

        m_picker->addEntry("Size", "");

        CircleWidget *circleWidget = new CircleWidget(m_picker);
        circleWidget->setDiameter(90);
        m_picker->addEntry("Color", circleWidget);

        resetSettings();

        m_numberPicker = new NumberPickerApp(frameWidget);
        m_colorPicker = new ColorPickerApp(frameWidget);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Furniture settings");
        m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_DONE);

        //connect(m_picker, SIGNAL(entryChanged()), this, SLOT(openFurnitureApp()));
        connect(m_titleBar, SIGNAL(rightButtonClicked()),this,SLOT(emitSettingsDone()));
        connect(m_picker, SIGNAL(entryChanged()),this,SLOT(showValueChanger()));
        connect(m_numberPicker, SIGNAL(inputFinished(int,QString)), SLOT(sizeSettingChanged(int, QString)));
        connect(m_colorPicker, SIGNAL(inputFinished(int,QColor)), SLOT(colorSettingChanged(int,QColor)));
    }

    void SettingsApp::resetSettings(){
        m_picker->setValue(0, QString("90 x 90 cm"));
        m_picker->setValue(1, m_colorPicker->colorValue(m_furniture, 0));
        m_size = 0;
        m_color = 0;
    }

    void SettingsApp::emitSettingsDone(){
        emit settingsDone(m_size, m_color);
    }

    void SettingsApp::showValueChanger(){
        if(m_picker->activeEntry() == 0){
            m_numberPicker->setIndex(0);
            m_frameWidget->pushApp(m_numberPicker);
        }
        else{
            m_colorPicker->setColors(m_furniture);
            m_frameWidget->pushApp(m_colorPicker);
        }
         m_picker->setActiveEntry(-1);
    }

    void SettingsApp::sizeSettingChanged(int value, QString userValue){
        m_size = value;
        m_picker->setValue(0, userValue);
    }

    void SettingsApp::colorSettingChanged(int value, QColor userValue){
        m_color = value;
        m_picker->setValue(1, userValue);
    }
    void SettingsApp::setFurnitureIndex(int value){
        m_furniture = value;
    }



} // namespace ipn
