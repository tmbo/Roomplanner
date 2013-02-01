#ifndef IPN_LISTMENUAPP_H
#define IPN_LISTMENUAPP_H

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
    class MapApp;

    class ListMenuApp : public App
    {
        Q_OBJECT

        public:
            ListMenuApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

        public slots:
            void openMapApp();

        protected:
            BackgroundWidget* m_back;
            PickerWidget* m_picker;
            MapApp* m_mapApp;
            IPodFrameWidget* m_frameWidget;
            DummyApp *m_dummyApp;
    };

} // namespace ipn

#endif /* end of include guard: IPN_MENUAPP_H */
