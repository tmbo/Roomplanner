#include "FurniturePickerApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/PickerWidget.h"
#include "IPodFrameWidget.h"
#include "apps/GUIApp.h"
#include "widgets/TitleBarWidget.h"

namespace ipn
{

    FurniturePickerApp::FurniturePickerApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
    {
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_TRANSPARENT);
        m_back->move(0, 0);

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Select a category");
        m_titleBar->move(0, 0);
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);

        m_frameWidget = frameWidget;

        m_picker = new PickerWidget(this);
        m_picker->addEntry("Couches");
        m_picker->addEntry("Chairs");
        m_picker->addEntry("Beds");
        m_picker->move(0, 48);

        m_guiApp = new GUIApp();

        connect(m_guiApp, SIGNAL(furnitureSelected(int)), this, SLOT(hideAndPropagate(int)));
        connect(m_picker, SIGNAL(entryChanged()), this, SLOT(openSofaGUI()));
        connect(m_guiApp->titleBar(), SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_titleBar, SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
    }

    void FurniturePickerApp::openSofaGUI(){

        if (m_picker->activeEntry() == 0)
        {
            m_frameWidget->pushApp(m_guiApp);
        } else {

        }
        m_picker->setActiveEntry(-1);

    }

    void FurniturePickerApp::hideAndPropagate(int i){
        m_frameWidget->popApp(3);
        emit furnitureSelected(i);
    }
}
