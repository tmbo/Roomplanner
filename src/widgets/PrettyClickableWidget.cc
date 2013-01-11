#include "PrettyClickableWidget.h"
#include <QResizeEvent>
#include <QPainter>

namespace ipn
{

	PrettyClickableWidget::PrettyClickableWidget(QWidget *parent) : ClickableWidget(parent)
	{
		m_gradientWidth = 40;
		m_gradientGray = 0x66;

		for (int pos = 0; pos < GRAD_COUNT; ++pos) {
			m_gradients[pos].enabled = false;
			m_gradients[pos].alpha = 0xff;
		}
	}

	void PrettyClickableWidget::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::NoPen));
		
		for (int pos = 0; pos < GRAD_COUNT; ++pos)	{
			if (m_gradients[pos].enabled)
				painter.fillRect(rect(), gradientForPosition(pos));
		}
	}

	bool PrettyClickableWidget::gradientEnabled(GradientPosition pos)
	{
		return gradientIndexExists(pos) && m_gradients[pos].enabled;
	}

	void PrettyClickableWidget::setGradientEnabled(GradientPosition pos, bool enabled)
	{
		if (!gradientIndexExists(pos))
			return;
		m_gradients[pos].enabled = enabled;
	}

	QLinearGradient PrettyClickableWidget::gradientForPosition(int pos)
	{
		int whitePos = (pos == TOP_GRADIENT || pos == LEFT_GRADIENT);
		QLinearGradient linearGrad;

		switch (pos) {
			case TOP_GRADIENT:
				linearGrad = QLinearGradient(0, 0, 0, m_gradientWidth);
				break;
			case BOTTOM_GRADIENT:
				linearGrad = QLinearGradient(0, height() - m_gradientWidth, 0, height());
				break;
			case LEFT_GRADIENT:
				linearGrad = QLinearGradient(0, 0, m_gradientWidth, 0);
				break;
			case RIGHT_GRADIENT:
				linearGrad = QLinearGradient(width() - m_gradientWidth, 0, width(), 0); 
				break;
		}

		linearGrad.setColorAt(!whitePos, QColor(m_gradientGray, m_gradientGray, m_gradientGray, m_gradients[pos].alpha));
		linearGrad.setColorAt(whitePos, QColor(0xff, 0xff, 0xff, 0));

		return linearGrad;
	}

	unsigned char PrettyClickableWidget::gradientAlpha(GradientPosition pos)
	{
		if (!gradientIndexExists(pos))
			return 0;
		return m_gradients[pos].alpha;
	}

	void PrettyClickableWidget::setGradientAlpha(GradientPosition pos, unsigned char alpha)
	{
		if (!gradientIndexExists(pos))
			return;
		m_gradients[pos].alpha = alpha;
	}
	
	void PrettyClickableWidget::setAllGradientsEnabled(bool enabled)
	{
		for (int pos = 0; pos < GRAD_COUNT; ++pos)
			m_gradients[pos].enabled = enabled;
	}
} // namespace ipn

