#include "FurniturePickerApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/PickerWidget.h"
#include "IPodFrameWidget.h"
#include "apps/GUIApp.h"
#include "apps/MenuApp.h"
#include "apps/DummyApp.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/ScalableButtonWidget.h"
#include "widgets/PageIndicatorWidget.h"

namespace ipn
{

    FurniturePickerApp::FurniturePickerApp(IPodFrameWidget* frameWidget, QWidget *parent) : App(parent)
    {
        m_back = new BackgroundWidget(this);
        m_back->setColor(BackgroundWidget::BG_GRAY);
        m_back->move(0, 0);

        m_frameWidget = frameWidget;

        m_guiApp = new GUIApp(m_frameWidget);
        m_dummyApp = new DummyApp();
        m_dummyApp->setText("Unfortunately all\n items in this category\n have been sold out.\n We are very sorry.");

        m_pageIndicator = new PageIndicatorWidget(this);
        m_pageIndicator->setNumberOfSegments(1);
        m_pageIndicator->move(120 - m_pageIndicator->width() / 2, 224);

        addButton(0, "Couch", ":/assets/images/icons/icon_couch.png");
        addButton(1, "Bed", ":/assets/images/icons/icon_bed.png");
        addButton(2, "Chair", ":/assets/images/icons/icon_chair.png");

        connect(m_guiApp, SIGNAL(furnitureSelected(int, int, int)), this, SLOT(hideAndPropagate(int, int, int)));
    }

    void FurniturePickerApp::openSofaGUI(){
        m_frameWidget->pushApp(m_guiApp);
    }

    void FurniturePickerApp::openDummy(){
        m_frameWidget->pushApp(m_dummyApp);
    }

    void FurniturePickerApp::hideAndPropagate(int i, int size, int color){
        m_frameWidget->popApp(3);
        emit furnitureSelected(i, size, color);
    }

    void FurniturePickerApp::addButton(int position, QString title, QString iconImage)
    {
        m_buttons[position] = new ScalableButtonWidget(this);
        m_buttons[position]->show();
        m_buttons[position]->setImage(":/img/buttons/default");
        m_buttons[position]->resize(64, 64);
        m_buttons[position]->setTitle(title);
        m_buttons[position]->setIconImage(iconImage);
        m_buttons[position]->move(20 + 72*(position%3), 12 + 120*(position/3));

        if(position == 0)
            connect(m_buttons[position], SIGNAL(clicked()), this, SLOT(openSofaGUI()));
        else
            connect(m_buttons[position], SIGNAL(clicked()), this, SLOT(openDummy()));
    }

} // namespace ipn
