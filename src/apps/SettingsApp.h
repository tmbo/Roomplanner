#ifndef IPN_SETTINGSAPP_H
#define IPN_SETTINGSAPP_H

#include "App.h"

namespace ipn
{

    class BackgroundWidget;
    class TitleBarWidget;
    class ScalableButtonWidget;
    class PickerWidget;
    class IPodFrameWidget;
    class FurniturePickerApp;
    class DummyApp;
    class NumberPickerApp;
    class ColorPickerApp;

    class SettingsApp : public App
    {
        Q_OBJECT

        public:
            SettingsApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

        public slots:
            void showValueChanger();
        signals:
            void settingsDone();

        protected:
            BackgroundWidget* m_back;
            PickerWidget* m_picker;
            TitleBarWidget* m_titleBar;
            IPodFrameWidget* m_frameWidget;
            NumberPickerApp* m_numberPicker;
            ColorPickerApp* m_colorPicker;

    };

} // namespace ipn

#endif /* end of include guard: IPN_SETTINGSAPP_H */
