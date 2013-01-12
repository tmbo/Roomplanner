#ifndef IPN_NUMBERPICKERAPP_H
#define IPN_NUMBERPICKERAPP_H

#ifdef __APPLE__
#define OFFSET 2
#define CORRECTVALUE 0
#else
#define OFFSET 11
#define CORRECTVALUE -1
#endif

// Ok, this is legacy shit. You need to specify the number of items you intend to use.
#define REAL_ITEM_COUNT 3
// Then you need to supply a fake ITEM_COUNT which is big enough to cover the widget.
// This needs to be a multiple of REAL_ITEM_COUNT
#define ITEM_COUNT 9 // should be >= 9

//#include "BaseScreen.h"
#include "App.h"


class QString;

namespace ipn
{

	class ButtonWidget;
	class ImageWidget;
	class FlickArea;
	class TextWidget;
    class TitleBarWidget;
    class BackgroundWidget;
    class IPodFrameWidget;

    class NumberPickerApp : public App
	{
        Q_OBJECT

		public:
            NumberPickerApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);
            QString value();
            int index();
            QString textValue(int i);
            void setIndex(int value);

		signals:
            void inputFinished(int index, QString text);

		private:
            //ArchiPod::PickerRole m_role;
            BackgroundWidget *m_back;
            TitleBarWidget *m_titleBar;
			ButtonWidget *m_activeButton;
			ImageWidget *m_frame;
			ImageWidget *m_selectorframe;
			ImageWidget *m_topshadow;
			ImageWidget *m_bottomshadow;
			ImageWidget *m_comma;
            ImageWidget *m_area;
            int m_selectedIndex;


            QString textForNumber(int number);
            QString sliderText();
            void snapWheel();


            void setWheelActive();
            void setWheelInactive();
		
        protected slots:
			void updateSnapper();
            void triggerFinish();

		protected:
			ButtonWidget *m_buttons[3];
            FlickArea *m_flickarea;
            TextWidget *m_flicktext;
            TextWidget *m_label;
            IPodFrameWidget *m_frameWidget;


	};
} //namespace ipn


#endif /* IPN_NUMBERPICKERAPP_H */
