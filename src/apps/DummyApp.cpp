#include "DummyApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/SwitchButtonWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/SliderWidget.h"
#include "widgets/TextWidget.h"


namespace ipn
{

    DummyApp::DummyApp(QWidget *parent) : App(parent)
    {
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);
        m_back->move(0, 0);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Sorry");
        m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);

        m_textArea = new TextWidget(this);
        m_textArea->move(10, 40);
        m_textArea->setColor(QColor(Qt::white));
        m_textArea->resize(240, 180);
        m_textArea->setFontSize(20);
        m_textArea->setText("DummyApp");

        hide();
    }

    TitleBarWidget *DummyApp::titleBar()
    {
        return m_titleBar;
    }

    void DummyApp::setText(QString text)
    {
        m_textArea->setText(text);
    }

} // namespace ipn
