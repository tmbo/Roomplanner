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
    class FurniturePickerApp;
    class ListMenuApp;
    class SettingsApp;

	class MapApp : public App
	{
		Q_OBJECT

		public:
            MapApp(IPodFrameWidget* frameWidget, QWidget *parent = 0);

            inline bool isOpaque() { return true; }

            ButtonWidget *m_deleteButton;
            ButtonWidget *m_editButton;


        public slots:
            void showOverlay();
            void placeFurniture(int, int, int);
            void furniturePressed();
            void furnitureReleased();
            void deleteFurniture();
            void editFurniture();
            void settingsSet(int, int);

		private:
            IPodFrameWidget *m_frameWidget;
            SettingsApp *m_settingsApp;
            RoomWidget *m_room;

            ButtonWidget *m_addButton;

            FurniturePickerApp *m_furniturePickerApp;
	};

} // namespace ipn

#endif /* end of include guard: IPN_MAPAPP_H */
