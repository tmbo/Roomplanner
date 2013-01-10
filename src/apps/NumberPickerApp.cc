#include "NumberPickerApp.h"
#include "widgets/ButtonWidget.h"
#include "widgets/ImageWidget.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/FlickArea.h"
#include "widgets/TextWidget.h"
#include "widgets/TitleBarWidget.h"
#include <math.h>

#define BIG_FONT_SIZE 18

namespace ipn
{
	NumberPickerApp::NumberPickerApp(QWidget *parent) 
        : App(parent)
	{
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->move(0, 0);
        m_titleBar->setTitle("Width");
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);
        m_titleBar->addButton(TitleBarWidget::BUTTON_DONE);

		m_areas.push_back(new ImageWidget(this));
        m_areas.back()->setImage(":/assets/images/backgrounds/numberslider_area");
        m_areas.back()->move(47,69);

		m_areas.push_back(new ImageWidget(this));
        m_areas.back()->setImage(":/assets/images/backgrounds/numberslider_area");
        m_areas.back()->move(100,69);

		m_areas.push_back(new ImageWidget(this));
        m_areas.back()->setImage(":/assets/images/backgrounds/numberslider_area");
        m_areas.back()->move(147,69);

        for (int i = 0; i < 3; i++)
		{
			m_flickareas[i] = new FlickArea(this);
			m_flickareas[i]->resize(40, 140);
            m_flickareas[i]->move(4 + (i+1)*48, 69);
            m_flickareas[i]->setMoveAfterRelease(true);
	
			m_flicktexts[i] = new TextWidget(m_flickareas[i]);
            m_flicktexts[i]->setFontSize(BIG_FONT_SIZE);
			m_flicktexts[i]->resize(40,((int)(1.5*BIG_FONT_SIZE)*30));
			m_flicktexts[i]->setText(sliderText());

			connect(m_flickareas[i],SIGNAL(ready()), this, SLOT(updateSnapper()));
		}

        m_comma = new ImageWidget(this);
        m_comma->setImage(":/assets/images/backgrounds/comma");
        m_comma->move(94,144);

		m_frame = new ImageWidget(this);
        m_frame->setImage(":/assets/images/backgrounds/numberslider_frame");
        m_frame->move(47,68);
        m_frame->resize(147,144);

		m_selectorframe = new ImageWidget(this);
        m_selectorframe->setImage(":/assets/images/backgrounds/numberslider_selectorframe");
        m_selectorframe->move(47,122);
        m_selectorframe->resize(147,36);

		m_topshadow = new ImageWidget(this);
        m_topshadow->setImage(":/assets/images/backgrounds/numberslider_topshadow");
        m_topshadow->move(47,69);
        m_topshadow->resize(147,48);

		m_bottomshadow = new ImageWidget(this);
        m_bottomshadow->setImage(":/assets/images/backgrounds/numberslider_bottomshadow");
        m_bottomshadow->move(47,163);
        m_bottomshadow->resize(147,48);

        m_label = new TextWidget(this);
        m_label->move(200,160);
        m_label->setFontSize(BIG_FONT_SIZE);
        //m_label->resize(40,((int)(1.5*BIG_FONT_SIZE)*30));
        m_label->setText("m");



//		connect(m_titleBar, SIGNAL(cancelButtonClicked()), this, SLOT(hideAway()));
//		connect(m_titleBar, SIGNAL(checkButtonClicked()), this, SLOT(accepted()));
	}

//    void NumberPickerApp::setUnitTo(QString unit)
//    {
//        int old = millimeters();
//        setUnit(unit);
//        setValue(old);
//    }

    void NumberPickerApp::setUnit(QString unit)
    {
//        for (int i = 0; i < 3; i++)
//        {
//            m_buttons[i]->setActive(false);
//        }
		
//        if (unit == "m")
//        {
//            setWheelActive(3);
//            setWheelActive(4);
//            m_buttons[0]->setActive(true);
//        } else if (unit == "cm") {
//            setWheelActive(3);
//            setWheelInactive(4);
//            m_buttons[1]->setActive(true);
//        } else if (unit == "mm") {
//            setWheelInactive(4);
//            setWheelInactive(3);
//            m_buttons[2]->setActive(true);
//        };
        m_unit = unit;
    }

//    void NumberPickerApp::updateUnit()
//    {
//        for (int i = 0; i < 3; i++)
//        {
//            if (sender() == m_buttons[i])
//                setUnitTo("m");
//        }
//    }

	QString NumberPickerApp::sliderText()
	{
		QString s = "";
		for (int i = -2; i < 28; i++)
		{
			s.append(QString("%1").arg((i + 10) % 10));
			s.append("\n");
		}
		return s;
	}

    QString NumberPickerApp::currentUnit()
    {
        return m_unit;
    }

	int NumberPickerApp::getNumberFor(int position)
	{
		return m_number[position];
	}

	int NumberPickerApp::getNumber()
	{
		int result = 0;
		for (int i = 0; i < 5; i++)
		{
			result += getNumberFor(i) * pow(10.0, (4.0 - i));
		}
		return result;
	}

    int NumberPickerApp::millimeters()
    {
        float factor = 1/100.0;
        if (currentUnit() == "m")
        {
            factor = 10.0;
        }
        else if (currentUnit() == "cm")
        {
            factor = 1/10.0;
        }
        float result = getNumber() * factor;

        return (int) result;
    }

	void NumberPickerApp::accepted()
	{
        emit inputFinished(millimeters(), m_unit);
        //hideAway();
	}

	void NumberPickerApp::setWheelToValue(int position, int value)
	{
		int lineHeight = (int)(1.5*BIG_FONT_SIZE);
		int offset = value * (lineHeight) + OFFSET + (lineHeight*10) + (lineHeight * CORRECTVALUE);
		m_flicktexts[position]->move(0,-offset);
		snapWheel(position);
	}

	void NumberPickerApp::setValue(int value)
	{
		float value_in_unit = (float) value;
        if (currentUnit() == "m")
		{
			value_in_unit /= 1000.0;
		}
        else if (currentUnit() == "cm")
		{
			value_in_unit /= 10.0;	
		}

		int plainvalue = (int) (value_in_unit * 100);

        for (int i = 0; i < 3; i++)
		{
			int current = plainvalue % 10;
			plainvalue = plainvalue / 10;
            setWheelToValue(2-i,current);
		}
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
		for (; i < 5; i++)
		{
			if (sender() == m_flickareas[i]) break;
		}

		snapWheel(i);
	}

    void NumberPickerApp::inputNumber(int millimeters, QString unit)
    {
        setUnit(unit);
        setValue(millimeters);
        //m_role = role;
        //comeToFront();
    }


} // namespace ipn

