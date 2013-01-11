#include "NumberPickerApp.h"
#include "IPodFrameWidget.h"
#include "widgets/ButtonWidget.h"
#include "widgets/ImageWidget.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/FlickArea.h"
#include "widgets/TextWidget.h"
#include "widgets/TitleBarWidget.h"
#include <math.h>

#define BIG_FONT_SIZE 17

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

		m_areas.push_back(new ImageWidget(this));
        m_areas.back()->setImage(":/assets/images/backgrounds/numberslider_area");
        m_areas.back()->move(47,69);

		m_areas.push_back(new ImageWidget(this));
        m_areas.back()->setImage(":/assets/images/backgrounds/numberslider_area");
        m_areas.back()->move(100,69);

//		m_areas.push_back(new ImageWidget(this));
//        m_areas.back()->setImage(":/assets/images/backgrounds/numberslider_area");
//        m_areas.back()->move(147,69);

        for (int i = 0; i < 2; i++)
		{
			m_flickareas[i] = new FlickArea(this);
			m_flickareas[i]->resize(40, 140);
            m_flickareas[i]->move(4 + (i+1)*48, 69);
            m_flickareas[i]->setMoveAfterRelease(true);
	
			m_flicktexts[i] = new TextWidget(m_flickareas[i]);
            m_flicktexts[i]->setFontSize(BIG_FONT_SIZE);
			m_flicktexts[i]->resize(40,((int)(1.5*BIG_FONT_SIZE)*30));

            int multiplicator;
            (i==0)? multiplicator = 1 : multiplicator = 10;
            m_flicktexts[i]->setText(sliderText(multiplicator));

			connect(m_flickareas[i],SIGNAL(ready()), this, SLOT(updateSnapper()));
		}

        m_comma = new ImageWidget(this);
        m_comma->setImage(":/assets/images/backgrounds/comma");
        m_comma->move(94,144);

		m_frame = new ImageWidget(this);
        m_frame->setImage(":/assets/images/backgrounds/numberslider_frame");
        m_frame->move(47,68);
        m_frame->resize(100,144);

		m_selectorframe = new ImageWidget(this);
        m_selectorframe->setImage(":/assets/images/backgrounds/numberslider_selectorframe");
        m_selectorframe->move(47,122);
        m_selectorframe->resize(100,36);

		m_topshadow = new ImageWidget(this);
        m_topshadow->setImage(":/assets/images/backgrounds/numberslider_topshadow");
        m_topshadow->move(47,69);
        m_topshadow->resize(100,48);

		m_bottomshadow = new ImageWidget(this);
        m_bottomshadow->setImage(":/assets/images/backgrounds/numberslider_bottomshadow");
        m_bottomshadow->move(47,163);
        m_bottomshadow->resize(100,48);

        m_label = new TextWidget(this);
        m_label->move(200,160);
        m_label->setFontSize(BIG_FONT_SIZE);
        m_label->setText("m");

        connect(m_titleBar, SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_titleBar, SIGNAL(rightButtonClicked()), m_frameWidget, SLOT(popApp()));
        hide();

	}

    QString NumberPickerApp::sliderText(int multiplicator)
	{
		QString s = "";
		for (int i = -2; i < 28; i++)
		{
            s.append(QString("%1").arg((i + 10) % 10 * multiplicator));
			s.append("\n");
		}
		return s;
	}


	int NumberPickerApp::getNumberFor(int position)
	{
        //return m_number[position];
	}

    int NumberPickerApp::getNumber()
	{
//		int result = 0;
//        for (int i = 0; i < 2; i++)
//		{
//			result += getNumberFor(i) * pow(10.0, (4.0 - i));
//		}
//		return result;
	}

	void NumberPickerApp::setWheelToValue(int position, int value)
	{
		int lineHeight = (int)(1.5*BIG_FONT_SIZE);
        int offset = (value - 1) * (lineHeight) + OFFSET + (lineHeight*10) + (lineHeight * CORRECTVALUE);
		m_flicktexts[position]->move(0,-offset);
		snapWheel(position);
	}

    void NumberPickerApp::setValue(int meters, int centimeters)
    {
        //display is in meters
        setWheelToValue(1,centimeters / 10); //numberpicker thinks it only uses numbers 0-9
        setWheelToValue(0,meters);
	}

	void NumberPickerApp::snapWheel(int position)
	{
		int lineHeight = (int)(1.5*BIG_FONT_SIZE);
		int snapoffset = ((((int)((m_flickareas[position]->absoluteScrollPosition().y())/lineHeight)*lineHeight))+OFFSET)%(lineHeight*10)+(lineHeight*10);
		m_flicktexts[position]->move(0,-(snapoffset));

		m_number[position] = (((snapoffset %(lineHeight*10+OFFSET)) - (lineHeight * CORRECTVALUE))/lineHeight) % 10;
	}

	void NumberPickerApp::setWheelInactive(int position)
	{
		m_flickareas[position]->setInactive();
		m_flicktexts[position]->setColor(QColor(200,200,200));
	}

	void NumberPickerApp::setWheelActive(int position)
	{
		m_flickareas[position]->setActive();
		m_flicktexts[position]->setColor(Qt::black);
	}

	void NumberPickerApp::updateSnapper()
	{
		int i = 0;
        for (; i < 2; i++)
		{
			if (sender() == m_flickareas[i]) break;
		}

		snapWheel(i);
	}



} // namespace ipn

