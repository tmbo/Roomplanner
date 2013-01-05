#include "GUIApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/SwitchButtonWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/SliderWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/FlickArea.h"
#include "widgets/ImageWidget.h"
#include "widgets/PageIndicatorWidget.h"
#include "widgets/ClickableWidget.h"
#include <QSignalMapper.h>
#include <stdio.h>

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

        m_clickable0 = new ClickableWidget(m_flickArea);
        m_clickable0->resize(240, 200);
        m_clickable0->move(0,0);

        m_image0 = new ImageWidget(m_clickable0);
        m_image0->setImage(":/assets/images/sater.png");
        m_image0->resize(240, 200);

        m_clickable1 = new ClickableWidget(m_flickArea);
        m_clickable1->resize(240, 200);
        m_clickable1->move(240,0);

        m_image1 = new ImageWidget(m_clickable1);
        m_image1->setImage(":/assets/images/karlstad.png");
        m_image1->resize(240, 200);

        m_clickable2 = new ClickableWidget(m_flickArea);
        m_clickable2->resize(240, 200);
        m_clickable2->move(240 * 2,0);

        m_image2 = new ImageWidget(m_clickable2);
        m_image2->setImage(":/assets/images/ektorp.png");
        m_image2->resize(240, 200);

		m_pageIndicator = new PageIndicatorWidget(this);
        m_pageIndicator->setNumberOfSegments(3);
		m_pageIndicator->move(120 - m_pageIndicator->width() / 2, 224);

        QSignalMapper *signalMapper = new QSignalMapper(this);
        signalMapper->setMapping(m_clickable0, 0);
        signalMapper->setMapping(m_clickable1, 1);
        signalMapper->setMapping(m_clickable2, 2);

        connect(m_flickArea, SIGNAL(moved()), this, SLOT(updatePageIndicator()));
        connect(m_clickable0, SIGNAL(released()), signalMapper, SLOT(map()));
        connect(m_clickable1, SIGNAL(released()), signalMapper, SLOT(map()));
        connect(m_clickable2, SIGNAL(released()), signalMapper, SLOT(map()));

        connect(m_clickable0, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(m_clickable1, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(m_clickable2, SIGNAL(clicked()), signalMapper, SLOT(map()));

        connect(m_clickable0, SIGNAL(pressed()), signalMapper, SLOT(map()));
        connect(m_clickable1, SIGNAL(pressed()), signalMapper, SLOT(map()));
        connect(m_clickable2, SIGNAL(pressed()), signalMapper, SLOT(map()));

        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(furnitureSelected(int)));
	}

	TitleBarWidget *GUIApp::titleBar()
	{
		return m_titleBar;
	}

	void GUIApp::updatePageIndicator()
	{
		m_pageIndicator->setPosition(m_flickArea->relativeScrollPosition().x());
	}

    void GUIApp::furnitureSelected(int idx)
    {

       printf("Idx ");
    }

} // namespace ipn
