#include "GestureApp.h"
#include "widgets/BackgroundWidget.h"
#include "widgets/TitleBarWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/ScalableButtonWidget.h"

namespace ipn
{

	GestureApp::GestureApp(QWidget *pParent) : App(pParent)
	{
		m_back = new BackgroundWidget(this);
		m_back->setColor(BackgroundWidget::BG_TRANSPARENT);
		m_back->move(0, 0);

		m_lastGesture = new TitleBarWidget(this);
		setLastGesture("<perform a gesture>");

		m_swipeAngleText = new TextWidget(this);
		m_swipeAngleText->setColor(Qt::white);
		m_swipeAngleText->move(0, 48);
		m_swipeAngleText->resize(240, 48);

		m_scaleFactorText = new TextWidget(this);
		m_scaleFactorText->setColor(Qt::white);
		m_scaleFactorText->move(0, 96);
		m_scaleFactorText->resize(240, 48);

		m_rotationAngleText = new TextWidget(this);
		m_rotationAngleText->setColor(Qt::white);
		m_rotationAngleText->move(0, 144);
		m_rotationAngleText->resize(240, 48);

		m_quitButton = new ScalableButtonWidget(this);
		m_quitButton->move(148, 184);
		m_quitButton->resize(80, 48);
		m_quitButton->setImage(":/img/buttons/default");
		m_quitButton->setText("exit");
		connect(m_quitButton, SIGNAL(clicked()), this, SIGNAL(quitButtonClicked()));

		m_currentScaleFactor = 1.0;
		m_currentRotationAngle = 0.0;

		// Connect gestures:
		connect(this, SIGNAL(swipeTriggered(qreal)), this, SLOT(swipe(qreal)));
		connect(this, SIGNAL(swipeRightTriggered()), this, SLOT(swipeRight()));
		connect(this, SIGNAL(swipeUpTriggered()), this, SLOT(swipeUp()));
		connect(this, SIGNAL(swipeDownTriggered()), this, SLOT(swipeDown()));
		connect(this, SIGNAL(swipeLeftTriggered()), this, SLOT(swipeLeft()));
		connect(this, SIGNAL(pinchRotationAngleChanged(qreal)), this, SLOT(changePinchRotationAngle(qreal)));
		connect(this, SIGNAL(pinchScaleFactorChanged(qreal)), this, SLOT(changePinchScaleFactor(qreal)));
		connect(this, SIGNAL(pinchInTriggered()), this, SLOT(pinchIn()));
		connect(this, SIGNAL(pinchOutTriggered()), this, SLOT(pinchOut()));
	}

	void GestureApp::setLastGesture(QString gesture)
	{
		m_lastGesture->setTitle(gesture);

		update();
	}

	void GestureApp::changePinchRotationAngle(qreal delta)
	{
		m_currentRotationAngle += delta;
		m_rotationAngleText->setText("rotation angle: " + QString::number(m_currentRotationAngle) + "°");

		update();
	}

	void GestureApp::changePinchScaleFactor(qreal delta)
	{
		m_currentScaleFactor *= delta;
		m_scaleFactorText->setText("scaleFactor: " + QString::number(m_currentScaleFactor) + "x");

		update();
	}

	void GestureApp::pinchIn()
	{
		setLastGesture("pinch in");
	}

	void GestureApp::pinchOut()
	{
		setLastGesture("pinch out");
	}

	void GestureApp::swipeLeft()
	{
		setLastGesture("swipe left");
	}

	void GestureApp::swipeUp()
	{
		setLastGesture("swipe up");
	}

	void GestureApp::swipeRight()
	{
		setLastGesture("swipe right");
	}

	void GestureApp::swipeDown()
	{
		setLastGesture("swipe down");
	}

	void GestureApp::swipe(qreal angle)
	{
		m_swipeAngleText->setText("swipe angle: " + QString::number(angle) + "°");

		update();
	}

} // namespace ipn
