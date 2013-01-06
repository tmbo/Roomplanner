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
    class BackgroundWidget;
    class PickerWidget;
    class GUIApp;
    class IPodFrameWidget;
    class ClickableWidget;

	class MapApp : public App
	{
		Q_OBJECT

		public:
            MapApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

            inline bool isOpaque() { return true; }

			TitleBarWidget *titleBar();


        public slots:
            void changePinchScaleFactor(qreal delta);
            void showOverlay();
            void openSofaGUI();
            void placeFurniture(int);
            void changePinchRotationAngle(qreal delta);
            void furniturePressed();
            void furnitureReleased();

		private:
            IPodFrameWidget *m_frameWidget;

            TitleBarWidget *m_titleBar;
            FlickArea *m_flickArea;

            qreal m_currentScaleFactor, m_currentRotationAngle;
            ButtonWidget *m_addButton;
            GUIApp *m_guiApp;

            QSize m_imageOriginalSize;
            QPoint m_imageTranslation;
            BackgroundWidget* m_back;
            PickerWidget* m_picker;

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
