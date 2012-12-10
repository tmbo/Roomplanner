#include "GUIApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/SwitchButtonWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/SliderWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/FlickArea.h"
#include "widgets/ImageWidget.h"
#include "widgets/PageIndicatorWidget.h"

namespace ipn
{

	GUIApp::GUIApp(QWidget *parent) : App(parent)
	{
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);
        m_back->move(0, 0);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Select a sofa");
        m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);

		m_flickArea = new FlickArea(this);
        m_flickArea->move(0, 50);
        m_flickArea->resize(240, 150);

        m_image[0] = new ImageWidget(m_flickArea);
        m_image[0]->setImage(":/img/backgrounds/map.png");

        m_image[1] = new ImageWidget(m_flickArea);
        m_image[1]->setImage(":/img/backgrounds/map.png");
/*
		m_scrollText = new TextWidget(m_flickArea);
		m_scrollText->setText("Scroll me! Lorem ipsum dolor sit amet adscipsing consectetur ...");
		m_scrollText->move(128, 0);
		m_scrollText->resize(768, 64);
		m_scrollText->setColor(Qt::white);
		m_scrollText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
*/
		m_pageIndicator = new PageIndicatorWidget(this);
		m_pageIndicator->setNumberOfSegments(6);
		m_pageIndicator->move(120 - m_pageIndicator->width() / 2, 224);

		connect(m_flickArea, SIGNAL(moved()), this, SLOT(updatePageIndicator()));
	}

	TitleBarWidget *GUIApp::titleBar()
	{
		return m_titleBar;
	}

	void GUIApp::updatePageIndicator()
	{
		m_pageIndicator->setPosition(m_flickArea->relativeScrollPosition().x());
	}

} // namespace ipn
