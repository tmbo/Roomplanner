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
        connect(m_titleBar, SIGNAL(leftButtonClicked()), m_frameWidget, SLOT(popApp()));


    }

    void ColorPickerApp::setColors(int furnitureIndex) {
        m_furnitureIndex = furnitureIndex;
        m_color0->setBrush(colorValue(furnitureIndex, 0));
        m_color1->setBrush(colorValue(furnitureIndex, 1));
        m_color2->setBrush(colorValue(furnitureIndex, 2));
    }

    QColor ColorPickerApp::colorValue(int furnitureIndex, int colorIndex) {

        switch(furnitureIndex) {
            case 0:
                switch(colorIndex) {
                    case 0: return QColor();
                    case 1: return QColor();
                    default : return QColor();
                }
            case 1:
                switch(colorIndex) {
                    case 0: return QColor();
                    case 1: return QColor();
                    default : return QColor();
                }
            default:
                switch(colorIndex) {
                    case 0: return QColor();
                    case 1: return QColor();
                    default : return QColor();
                }
        }
    }

    void ColorPickerApp::mousePressEvent(QMouseEvent *event){

        QGraphicsItem *item = m_graphicsView->itemAt(event->pos() - this->pos());

        if (item == m_color0)
        {
            m_frameWidget->popApp();
            emit inputFinished(m_furnitureIndex, colorValue(m_furnitureIndex, 0));
        }
        if (item == m_color1)
        {
            m_frameWidget->popApp();
            emit inputFinished(m_furnitureIndex, colorValue(m_furnitureIndex, 1));
        }
        if (item == m_color2)
        {
            m_frameWidget->popApp();
            emit inputFinished(m_furnitureIndex, colorValue(m_furnitureIndex, 2));
        }
    }
}
