#ifndef SETTINGSMAPPER_H
#define SETTINGSMAPPER_H

#include <QtCore>
#include <QtGui>

namespace ipn
{
    class SettingsMapper
    {
    public:
        SettingsMapper();
        SettingsMapper(QGraphicsPixmapItem *item, int id, int color, int size);
        int m_id;
        int m_color;
        int m_size;
        QGraphicsPixmapItem *m_item;
    };
}
#endif // SETTINGSMAPPER_H
