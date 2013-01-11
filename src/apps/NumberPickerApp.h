#ifndef IPN_NUMBERPICKERAPP_H
#define IPN_NUMBERPICKERAPP_H

#ifdef __APPLE__
#define OFFSET 2
#define CORRECTVALUE 0
#else
#define OFFSET 11
#define CORRECTVALUE -1
#endif

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

		signals:
            void inputFinished(int millimeters, QString unit);

		public slots:
            void inputNumber(int milimeters = 0, QString unit = "m");
            //void setUnitTo(QString u);

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
			QVector<ImageWidget*> m_areas;
			int m_number[5];
            QString m_unit;
            QString currentUnit();

			QString textForNumber(int number);
			QString sliderText();
			void snapWheel(int position);
			int getNumber();
			int getNumberFor(int position);
			void setValue(int value);
			void setWheelToValue(int position, int value);
			int millimeters();

			void setWheelActive(int position);
			void setWheelInactive(int position);

            void setUnit(QString unit);
		
		protected slots:
            //void updateUnit();
			void updateSnapper();
			void accepted();

		protected:
			ButtonWidget *m_buttons[3];
			FlickArea *m_flickareas[5];
			TextWidget *m_flicktexts[5];
            TextWidget *m_label;
            IPodFrameWidget *m_frameWidget;


	};
} //namespace ipn


#endif /* IPN_NUMBERPICKERAPP_H */
