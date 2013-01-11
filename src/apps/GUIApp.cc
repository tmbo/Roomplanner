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
        m_flickArea->resize(240, 200);

        m_signalMapper = new QSignalMapper();

        createFurnitureEntry(0, ":/assets/images/furniture/karlstad.png");
        createFurnitureEntry(1, ":/assets/images/furniture/sater.png");
        createFurnitureEntry(2, ":/assets/images/furniture/ektorp.png");

		m_pageIndicator = new PageIndicatorWidget(this);
        m_pageIndicator->setNumberOfSegments(3);
		m_pageIndicator->move(120 - m_pageIndicator->width() / 2, 224);

        connect(m_flickArea, SIGNAL(moved()), this, SLOT(updatePageIndicator()));

        connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(emitFurnitureSelected(int)));
	}

    void GUIApp::createFurnitureEntry(int idx, QString imagePath){
        m_clickable[idx] = new ClickableWidget(m_flickArea);

        m_clickable[idx]->resize(240, 200);
        m_clickable[idx]->move(280 * idx,0);

        m_image[idx] = new ImageWidget(m_clickable[idx]);
        m_image[idx]->setImage(imagePath);
        m_image[idx]->resize(240, 200);

        m_signalMapper->setMapping(m_clickable[idx], idx);
        connect(m_clickable[idx], SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    }

    TitleBarWidget *GUIApp::titleBar()
    {
        return m_titleBar;
    }

	void GUIApp::updatePageIndicator()
	{
		m_pageIndicator->setPosition(m_flickArea->relativeScrollPosition().x());
	}

    void GUIApp::emitFurnitureSelected(int idx)
    {
        emit furnitureSelected(idx);
    }

} // namespace ipn
