#ifndef IPN_PRETTYCLICKABLEWIDGET_H
#define IPN_PRETTYCLICKABLEWIDGET_H

#include "ClickableWidget.h"

class QLinearGradient;

namespace ipn
{

	class PrettyClickableWidget : public ClickableWidget
	{
		Q_OBJECT

		struct GradientInfo {
			bool enabled;
			unsigned char alpha;
		};

		public:
			enum GradientPosition {
				TOP_GRADIENT    = 0,
				BOTTOM_GRADIENT = 1,
				LEFT_GRADIENT   = 2,
				RIGHT_GRADIENT  = 3,
				GRAD_COUNT = 4
			};
		
			PrettyClickableWidget(QWidget *parent = 0);

			inline int gradientWidth() { return m_gradientWidth; };
			inline void setGradientWidth(int gradientWidth) { m_gradientWidth = gradientWidth; };
			
			inline unsigned char gradientGrey() { return m_gradientGray; };
			inline void setGradientGray(unsigned char value) { m_gradientGray = value; };

			bool gradientEnabled(GradientPosition pos);
			void setGradientEnabled(GradientPosition pos, bool enabled);

			unsigned char gradientAlpha(GradientPosition pos);
			void setGradientAlpha(GradientPosition pos, unsigned char alpha);

			void setAllGradientsEnabled(bool enabled);
		protected:
			int m_gradientWidth;
			unsigned char m_gradientGray;
			struct GradientInfo m_gradients[GRAD_COUNT];

			QLinearGradient gradientForPosition(int pos);
			virtual void paintEvent(QPaintEvent *event);
			bool gradientIndexExists(int pos) { return 0 <= pos && pos < GRAD_COUNT; };
	};


} // namespace ipn

#endif // IPN_PRETTYCLICKABLEWIDGET_H

