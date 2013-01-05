#include "MapApp.h"
#include "helpers.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/FlickArea.h"
#include "widgets/ImageWidget.h"
#include <stdio.h>

namespace ipn
{

	MapApp::MapApp(QWidget *parent) : App(parent)
	{
		m_titleBar = new TitleBarWidget(this);
		m_titleBar->setTitle("MapApp");
		m_titleBar->move(0, 0);
		m_titleBar->addButton(TitleBarWidget::BUTTON_BACK);

		m_flickArea = new FlickArea(this);
		m_flickArea->resize(240, 192);
		m_flickArea->move(0, 48);

		m_image = new ImageWidget(m_flickArea);
		m_image->setImage(":/img/backgrounds/map.png");

        m_currentScaleFactor = 1.0;
        m_currentRotationAngle = 0;
        m_imageOriginalSize = m_image->size();

        connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
        connect(this, SIGNAL(pinchRotationAngleChanged(qreal)), this, SLOT(changePinchRotationAngle(qreal)));
	}

    void MapApp::changePinchScaleFactor(qreal delta)
    {
        m_currentScaleFactor *= delta;

        m_currentScaleFactor = helpers::maxf(helpers::minf(m_currentScaleFactor, 10.0), .1);

        m_image->resize(
                    m_imageOriginalSize.width() * m_currentScaleFactor,
                    m_imageOriginalSize.height() * m_currentScaleFactor
        );

        printf("%i\n", m_image->pos().x());

        update();
    }

    void MapApp::changePinchRotationAngle(qreal delta)
    {
        m_currentRotationAngle += delta;
        printf("%f\n", m_currentRotationAngle);
        update();
    }

	TitleBarWidget *MapApp::titleBar()
	{
		return m_titleBar;
	}

} // namespace ipn
