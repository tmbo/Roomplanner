#ifndef IPN_MAPAPP_H
#define IPN_MAPAPP_H

#include "App.h"
#include <QtCore>
#include <QtGui>

namespace ipn
{
	class TitleBarWidget;
	class FlickArea;
	class ImageWidget;
    class ButtonWidget;
    class ClickableWidget;

	class MapApp : public App
	{
		Q_OBJECT

		public:
			MapApp(QWidget *parent = 0);

            inline bool isOpaque() { return true; }

			TitleBarWidget *titleBar();


        public slots:
            void changePinchScaleFactor(qreal delta);
            void changePinchRotationAngle(qreal delta);
            void furniturePressed();
            void furnitureReleased();


		private:
            TitleBarWidget *m_titleBar;
            FlickArea *m_flickArea;

            qreal m_currentScaleFactor, m_currentRotationAngle;
            ButtonWidget *m_addButton;
            QSize m_imageOriginalSize;
            QPoint m_imageTranslation;

            ClickableWidget *m_clickable0;
            ImageWidget *m_image0;
            QGraphicsView *graphicsView;
            QGraphicsScene *scene;
            QGraphicsPixmapItem *background;

            QPixmap *backgroundPixmap;
            QPixmap *m_furniture;
	};

} // namespace ipn

#endif /* end of include guard: IPN_MAPAPP_H */
