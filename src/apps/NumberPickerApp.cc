#include "NumberPickerApp.h"
#include "IPodFrameWidget.h"
#include "widgets/ButtonWidget.h"
#include "widgets/ImageWidget.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/FlickArea.h"
#include "widgets/TextWidget.h"
#include "widgets/TitleBarWidget.h"
#include <math.h>

#define BIG_FONT_SIZE 18
#define POINTS_TO_PIXELS 1.3
#define LINE_HEIGHT_MULTIPLIER 1.5

#define LINE_HEIGHT (int)(POINTS_TO_PIXELS * LINE_HEIGHT_MULTIPLIER * BIG_FONT_SIZE)

namespace ipn
{
    NumberPickerApp::NumberPickerApp(IPodFrameWidget* frameWidget, QWidget *parent)
        : App(parent)
	{

        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Width");
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);
        m_titleBar->addButton(TitleBarWidget::BUTTON_DONE);

        m_frameWidget = frameWidget;

        m_area = new ImageWidget(this);
        m_area->setImage(":/assets/images/backgrounds/numberslider_area");
        m_area->move(70,72);
        m_area->resize(100, 140);

        m_flickarea = new FlickArea(this);
        m_flickarea->resize(94, 140);
        m_flickarea->move(73, 72);
        m_flickarea->setMoveAfterRelease(true);

        m_flicktext = new TextWidget(m_flickarea);
        m_flicktext->setFontSize(BIG_FONT_SIZE);
        m_flicktext->setLineHeight(LINE_HEIGHT_MULTIPLIER);
        m_flicktext->resize(94, LINE_HEIGHT * ITEM_COUNT * 3);

        m_flicktext->setText(sliderText());

        connect(m_flickarea, SIGNAL(ready()), this, SLOT(updateSnapper()));

		m_frame = new ImageWidget(this);
        m_frame->setImage(":/assets/images/backgrounds/numberslider_frame");
        m_frame->move(70, 73);
        m_frame->resize(100, 144);

		m_selectorframe = new ImageWidget(this);
        m_selectorframe->setImage(":/assets/images/backgrounds/numberslider_selectorframe");
        m_selectorframe->move(70, 125);
        m_selectorframe->resize(100, 36);

		m_topshadow = new ImageWidget(this);
        m_topshadow->setImage(":/assets/images/backgrounds/numberslider_topshadow");
        m_topshadow->move(70, 72);
        m_topshadow->resize(100, 48);

		m_bottomshadow = new ImageWidget(this);
        m_bottomshadow->setImage(":/assets/images/backgrounds/numberslider_bottomshadow");
        m_bottomshadow->move(70, 166);
        m_bottomshadow->resize(100, 48);

        connect(m_titleBar, SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_titleBar, SIGNAL(rightButtonClicked()), m_frameWidget, SLOT(popApp()));
        hide();

	}

    QString NumberPickerApp::sliderText()
	{
        QString s = "100x240\n200x480\n300x720\n";
        return s.repeated(
            // we draw everything thrice: top, middle, bottom
            3 *
            // if ITEM_COUNT is big enough there shouldn't be white spaces
            (ITEM_COUNT / REAL_ITEM_COUNT)
        );
	}

    int NumberPickerApp::value()
    {
        return m_selectedIndex;
    }

    void NumberPickerApp::setValue(int value)
	{
        int offsetToCenter = ((int)(m_flickarea->height() / 2)) / LINE_HEIGHT;
        int offset = (value - offsetToCenter) * (LINE_HEIGHT) + (LINE_HEIGHT * ITEM_COUNT);
        m_flicktext->move(0, -offset);
        snapWheel();
	}

    void NumberPickerApp::snapWheel()
	{
        int displayIndex =
            (int)(
                (m_flickarea->absoluteScrollPosition().y() +
                .5 * LINE_HEIGHT) // but we want the cut right in between two numbers
            / LINE_HEIGHT);

        int snapoffset = (displayIndex % ITEM_COUNT + ITEM_COUNT) * LINE_HEIGHT;
        m_flicktext->move(0, -snapoffset);

        int offsetToCenter = ((int)(m_flickarea->height() / 2)) / LINE_HEIGHT;
        m_selectedIndex = (displayIndex + offsetToCenter) % ITEM_COUNT % REAL_ITEM_COUNT;
	}

    void NumberPickerApp::setWheelInactive()
	{
        m_flickarea->setInactive();
        m_flicktext->setColor(QColor(200, 200, 200));
	}

    void NumberPickerApp::setWheelActive()
	{
        m_flickarea->setActive();
        m_flicktext->setColor(Qt::black);
	}

	void NumberPickerApp::updateSnapper()
	{
        snapWheel();
	}



} // namespace ipn

