#include "ColorPickerApp.h"
#include "IPodFrameWidget.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/TitleBarWidget.h"
#include <QGridLayout>

namespace ipn
{
    ColorPickerApp::ColorPickerApp(IPodFrameWidget* frameWidget, QWidget *parent)
        : App(parent)
    {
        m_frameWidget = frameWidget;

        m_graphicsView = new QGraphicsView(this);
        m_graphicsView->setSceneRect(0, 0, 240, 240);
        m_graphicsView->setBackgroundBrush(QBrush(QColor(59, 59, 59)));
        m_scene = new QGraphicsScene(m_graphicsView);

        m_graphicsView->setScene(m_scene);

        QPen pen;

        m_color0 = m_scene->addEllipse( 20, 100, 50, 50, pen, QBrush(QColor(255, 0, 0) ));
        m_color1 = m_scene->addEllipse( 90, 100, 50, 50, pen, QBrush(QColor(0, 255, 0) ));
        m_color2 = m_scene->addEllipse( 160, 100, 50, 50, pen, QBrush(QColor(0, 0, 255) ));

        m_titleBar = new TitleBarWidget(this);
        m_titleBar->setTitle("Color");
        m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);
        m_titleBar->addButton(TitleBarWidget::BUTTON_DONE);
        connect(m_titleBar, SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));
        connect(m_titleBar, SIGNAL(rightButtonClicked()), m_frameWidget, SLOT(popApp()));

    }

    void ColorPickerApp::setColors(int furnitureIndex) {
        switch(furnitureIndex) {
            case 0:
                m_color0->setBrush(QColor(100, 0, 0));
                m_color1->setBrush(QColor(100, 0, 0));
                m_color2->setBrush(QColor(100, 0, 0));
                break;
            case 1:
                m_color0->setBrush(QColor(100, 100, 0));
                m_color1->setBrush(QColor(100, 100, 0));
                m_color2->setBrush(QColor(100, 100, 0));
                break;
            default:
                m_color0->setBrush(QColor(100, 0, 100));
                m_color1->setBrush(QColor(100, 0, 100));
                m_color2->setBrush(QColor(100, 0, 100));
        }
    }
}
