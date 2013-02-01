#ifndef FURNITUREVIEWER_H
#define FURNITUREVIEWER_H

#include "App.h"

namespace ipn
{
    class BackgroundWidget;
    class TitleBarWidget;
    class ImageWidget;
    class ClickableWidget;
    class SettingsApp;
    class IPodFrameWidget;

    class FurnitureViewer : public App
    {
        Q_OBJECT

        public:
            FurnitureViewer(IPodFrameWidget* frameWidget, QWidget *parent = 0);
            void setSettings(int, int, int);
            TitleBarWidget *titleBar();

        protected slots:
            void openSettings();
            void emitFurnitureSelected(int, int);

        signals:
            void furnitureSelected(int, int, int);

        private:
            BackgroundWidget *m_back;
            TitleBarWidget *m_titleBar;
            ImageWidget *m_image;
            ClickableWidget *m_clickable;
            SettingsApp* m_settingsApp;
            IPodFrameWidget* m_frameWidget;
            int m_idx;
            int m_size;
            int m_color;

    };
}

#endif // FURNITUREVIEWER_H
