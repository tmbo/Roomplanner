#include "SettingsMapper.h"

namespace ipn
{
    SettingsMapper::SettingsMapper(QGraphicsPixmapItem *item, int id, int color, int size)
    {
        m_item = item;
        m_id = id;
        m_color = color;
        m_size = size;
    }
    SettingsMapper::SettingsMapper()
    {
        m_item = 0;
        m_id = 0;
        m_color = 0;
        m_size = 0;
    }
}
