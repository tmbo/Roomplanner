#ifndef IPN_SETTINGSAPP_H
#define IPN_SETTINGSAPP_H

#include "App.h"

namespace ipn
{

    class BackgroundWidget;
    class TitleBarWidget;
    class SwitchButtonWidget;
    class SliderWidget;
    class TextWidget;
    class PageIndicatorWidget;
    class NumberSpinnerWidget;

    class SettingsApp : public App
    {
        Q_OBJECT

        public:
            SettingsApp(QWidget *parent = 0);

            inline bool isOpaque() {return true;}

            TitleBarWidget *titleBar();

        protected slots:
            void updatePageIndicator();

        private:
            BackgroundWidget *m_back;
            TitleBarWidget *m_titleBar;
            SwitchButtonWidget *m_switchButton;
            SliderWidget *m_slider;

            TextWidget *m_scrollText;
            NumberSpinnerWidget *m_flickArea;
            PageIndicatorWidget *m_pageIndicator;
    };

} // namespace ipn

#endif /* end of include guard: IPN_SETTINGSAPP_H */
