#ifndef FURNITUREPICKERAPP_H
#define FURNITUREPICKERAPP_H

#include "App.h"

namespace ipn
{
    class BackgroundWidget;
    class PickerWidget;
    class GUIApp;
    class IPodFrameWidget;
    class TitleBarWidget;
    class DummyApp;

    class FurniturePickerApp : public App
    {
        Q_OBJECT

        public:
            FurniturePickerApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

        public slots:
            void openSofaGUI();
            void hideAndPropagate(int, int, int);

        signals:
            void furnitureSelected(int, int, int);

        private:
            BackgroundWidget* m_back;
            PickerWidget* m_picker;
            GUIApp *m_guiApp;
            IPodFrameWidget* m_frameWidget;
            DummyApp *m_dummyApp;
    };
}

#endif // FURNITUREPICKERAPP_H
