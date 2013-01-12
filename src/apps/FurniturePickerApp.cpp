#include "FurniturePickerApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/PickerWidget.h"
#include "IPodFrameWidget.h"
#include "apps/GUIApp.h"
#include "apps/DummyApp.h"
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

        m_guiApp = new GUIApp(m_frameWidget);
        m_dummyApp = new DummyApp();
        m_dummyApp->setText("Unfortunately all\n items in this category\n have been sold out.\n We are very sorry.");

        connect(m_picker, SIGNAL(entryChanged()), this, SLOT(openSofaGUI()));
        connect(m_titleBar, SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));

        connect(m_guiApp, SIGNAL(furnitureSelected(int, int, int)), this, SLOT(hideAndPropagate(int, int, int)));
        connect(m_guiApp->titleBar(), SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_dummyApp->titleBar(), SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));

    }

    void FurniturePickerApp::openSofaGUI(){

        if (m_picker->activeEntry() == 0)
        {
            m_frameWidget->pushApp(m_guiApp);
        } else {
            m_frameWidget->pushApp(m_dummyApp);
        }
        m_picker->setActiveEntry(-1);

    }

    void FurniturePickerApp::hideAndPropagate(int i, int size, int color){
        m_frameWidget->popApp(4);
        emit furnitureSelected(i, size, color);
    }
}
