#ifndef FURNITUREPICKERAPP_H
#define FURNITUREPICKERAPP_H

#include "App.h"

namespace ipn
{
    class BackgroundWidget;
    class PageIndicatorWidget;
    class GUIApp;
    class IPodFrameWidget;
    class TitleBarWidget;
    class DummyApp;
    class BackgroundWidget;
    class TitleBarWidget;
    class ScalableButtonWidget;

    class FurniturePickerApp : public App
    {
        Q_OBJECT

        public:
            FurniturePickerApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

        public slots:
            void openSofaGUI();
            void openDummy();
            void hideAndPropagate(int, int, int);

        signals:
            void furnitureSelected(int, int, int);

        private:
            BackgroundWidget* m_back;
            GUIApp *m_guiApp;
            IPodFrameWidget* m_frameWidget;
            PageIndicatorWidget *m_pageIndicator;
            DummyApp *m_dummyApp;
            ScalableButtonWidget *m_buttons[8];
            void addButton(int position, QString title, QString iconImage);
    };
}

#endif // FURNITUREPICKERAPP_H
