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
    class IPodFrameWidget;
    class ClickableWidget;
    class RoomWidget;
    class ListMenuApp;

	class MapApp : public App
	{
		Q_OBJECT

		public:
            MapApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

            inline bool isOpaque() { return true; }

            ButtonWidget *m_deleteButton;


        public slots:
            void showOverlay();
            void placeFurniture(int, int, int);
            void furniturePressed();
            void furnitureReleased();
            void deleteFurniture();

		private:
            IPodFrameWidget *m_frameWidget;

            RoomWidget *m_room;

            ButtonWidget *m_addButton;
            ListMenuApp* m_menu;
	};

} // namespace ipn

#endif /* end of include guard: IPN_MAPAPP_H */
