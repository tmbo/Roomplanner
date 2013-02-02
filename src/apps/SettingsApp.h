#ifndef IPN_SETTINGSAPP_H
#define IPN_SETTINGSAPP_H

#include "App.h"
#include "ImageWidget.h"

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
    class ImageWidget;

    class SettingsApp : public App
    {
        Q_OBJECT

        public:
            SettingsApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);
            void resetSettings();
            void setFurnitureIndex(int);
            void setSettings(int, int);

        private:
            ImageWidget *m_image;

        public slots:
            void showValueChanger();
            void sizeSettingChanged(int, QString);
            void colorSettingChanged(int, QColor);
            void emitSettingsDone();

        signals:
            void settingsDone(int size, int color);

        protected:
            BackgroundWidget* m_back;
            PickerWidget* m_picker;
            TitleBarWidget* m_titleBar;
            IPodFrameWidget* m_frameWidget;
            NumberPickerApp* m_numberPicker;
            ColorPickerApp* m_colorPicker;
            ImageWidget* m_previewImage;

            int m_size;
            int m_color;
            int m_furniture;
    };

} // namespace ipn

#endif /* end of include guard: IPN_SETTINGSAPP_H */
