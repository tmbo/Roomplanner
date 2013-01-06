#include "SettingsApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/SwitchButtonWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/SliderWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/FlickArea.h"
#include "widgets/NumberSpinnerWidget.h"
#include "widgets/PageIndicatorWidget.h"

namespace ipn
{

    SettingsApp::SettingsApp(QWidget *parent) : App(parent)
    {
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);
        m_back->move(0, 0);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Settings");
        m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);
        m_titleBar->addButton(TitleBarWidget::BUTTON_DONE);

        m_switchButton = new SwitchButtonWidget(this);
        m_switchButton->move(48, 56);
        m_switchButton->setTitle("a switch button");

        m_slider = new SliderWidget(this);
        m_slider->setWidth(160);
        m_slider->move(16, 128);
        m_slider->setTitle("a slider");

        m_flickArea = new NumberSpinnerWidget(0, 90, 10, this);
        m_flickArea->move(0, 176);
        m_flickArea->resize(240, 64);

    }

    TitleBarWidget *SettingsApp::titleBar()
    {
        return m_titleBar;
    }

    void SettingsApp::updatePageIndicator()
    {
        m_pageIndicator->setPosition(m_flickArea->relativeScrollPosition().x());
    }

} // namespace ipn
