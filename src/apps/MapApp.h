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
    class FurnitureViewer;
    class SettingsApp;

	class MapApp : public App
	{
		Q_OBJECT

		public:
            MapApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

            inline bool isOpaque() { return true; }

			TitleBarWidget *titleBar();
            ButtonWidget *m_deleteButton;
            ButtonWidget *m_editButton;


        public slots:
            void showOverlay();
            void placeFurniture(int, int, int);
            void furniturePressed();
            void furnitureReleased();
            void deleteFurniture();
            void editFurniture();
            void hideAndPropagate(int, int, int);

		private:
            IPodFrameWidget *m_frameWidget;
            FurnitureViewer *m_furnitureViewer;
            RoomWidget *m_room;

            ButtonWidget *m_addButton;
            ListMenuApp* m_menu;
	};

} // namespace ipn

#endif /* end of include guard: IPN_MAPAPP_H */
