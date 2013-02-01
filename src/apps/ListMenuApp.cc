#include "ListMenuApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/ScalableButtonWidget.h"
#include "apps/FurniturePickerApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/PickerWidget.h"
#include "IPodFrameWidget.h"
#include "apps/GUIApp.h"
#include "apps/DummyApp.h"
#include "apps/MapApp.h"
#include "widgets/TitleBarWidget.h"

namespace ipn
{

    ListMenuApp::ListMenuApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
    {
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);
        m_back->move(0, 0);

        m_frameWidget = frameWidget;

        m_mapApp = new MapApp(m_frameWidget);
        m_dummyApp = new DummyApp(this);
        m_dummyApp->setText("This feature\n has not yet\n been implemented!");

        m_picker = new PickerWidget(this);
        m_picker->addEntry("Current room");
        m_picker->addEntry("Edit room");
        m_picker->addEntry("Select another room");
        m_picker->move(0, 0);

        connect(m_picker, SIGNAL(entryChanged()), this, SLOT(openMapApp()));
    }

    void ListMenuApp::openMapApp(){

        if (m_picker->activeEntry() == 0)
        {
            m_frameWidget->pushApp(m_mapApp);
        } else {
            m_frameWidget->pushApp(m_dummyApp);
        }

        m_picker->setActiveEntry(-1);

    }

} // namespace ipn
