#ifndef IPN_GUIAPP_H
#define IPN_GUIAPP_H

#include "App.h"
#include <QSignalMapper.h>
namespace ipn
{

	class BackgroundWidget;
	class TitleBarWidget;
	class SwitchButtonWidget;
	class SliderWidget;
    class TextWidget;
	class FlickArea;
    class ImageWidget;
    class ClickableWidget;
    class SettingsApp;
    class IPodFrameWidget;

	class GUIApp : public App
	{
		Q_OBJECT

		public:
            GUIApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

			inline bool isOpaque() {return true;}


		protected slots:
            void openSettings(int);
            void emitFurnitureSelected(int, int);

        signals:
            void furnitureSelected(int, int, int);

		private:
            BackgroundWidget *m_back;
			SwitchButtonWidget *m_switchButton;
			SliderWidget *m_slider;
            ImageWidget *m_image[9];
            ClickableWidget *m_clickable[9];
            QSignalMapper *m_signalMapper;
            SettingsApp* m_settingsApp;
            IPodFrameWidget* m_frameWidget;
            int m_couch;

            TextWidget *m_scrollText;
            FlickArea *m_flickArea;

            void createFurnitureEntry(int, QString);
	};

} // namespace ipn

#endif /* end of include guard: IPN_GUIAPP_H */
