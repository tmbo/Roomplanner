#include "PickerWidget.h"
#include "TextWidget.h"
#include "ImageWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

#define NO_ENTRY -1

namespace ipn
{

	PickerWidget::PickerWidget(QWidget *parent) : QWidget(parent)
	{
		m_entries = QVector<TextWidget*>();
		m_highlightedEntry = NO_ENTRY;
		m_activeEntry = NO_ENTRY;

		m_entryDownImage = new ImageWidget(this);
		m_entryDownImage->setImage(":/img/picker/entry_down.png");
		m_entryDownImage->hide();

		m_checkmarkImage = new ImageWidget(this);
		m_checkmarkImage->setImage(":/img/picker/checkmark.png");
		m_checkmarkImage->hide();
	}

    void PickerWidget::addEntry(QString text)
	{
		int numberOfEntries = m_entries.size();

		TextWidget *newEntry = new TextWidget(this);
		newEntry->setColor(Qt::white);
		newEntry->setText(text);
		newEntry->setAlignment(Qt::AlignLeft);
        newEntry->resize(184, newEntry->textHeight());
		newEntry->move(16, 12 + 48 * numberOfEntries);

        ImageWidget *arrow = new ImageWidget(this);
        arrow->setImage(":/assets/images/buttons/arrow.png");
        arrow->resize(32,32);
        arrow->move(200, 12 + 48 * numberOfEntries);

		m_entries.append(newEntry);

		resize(240, (numberOfEntries + 1) * 48);
		update();
	}

    void PickerWidget::addEntry(QString text, QString value)
    {
        TextWidget *valueEntry = new TextWidget(this);
        valueEntry->setColor(Qt::white);
        valueEntry->setText(value);
        valueEntry->setAlignment(Qt::AlignLeft);

        addEntry(text, valueEntry);
    }

    void PickerWidget::addEntry(QString text, QWidget* value)
    {
        int numberOfEntries = m_entries.size();

        TextWidget *newEntry = new TextWidget(this);
        newEntry->setColor(Qt::white);
        newEntry->setText(text);
        newEntry->setAlignment(Qt::AlignLeft);
        newEntry->resize(184, newEntry->textHeight());
        newEntry->move(16, 12 + 48 * numberOfEntries);

        value->resize(100, value->height());
        value->move(100, 12 + 48 * numberOfEntries);

        ImageWidget *arrow = new ImageWidget(this);
        arrow->setImage(":/assets/images/buttons/arrow.png");
        arrow->resize(32,32);
        arrow->move(200, 12 + 48 * numberOfEntries);

        m_entries.append(newEntry);

        resize(240, (numberOfEntries + 1) * 48);
        update();
    }

	void PickerWidget::paintEvent(QPaintEvent*)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);

		QPen pen(QColor(179, 179, 179));
		pen.setWidth(2);
		painter.setPen(pen);

		if (m_highlightedEntry != NO_ENTRY)
		{
			m_entryDownImage->move(8, m_highlightedEntry * 48);
			m_entryDownImage->show();
		}
		else
			m_entryDownImage->hide();

		if (m_activeEntry != NO_ENTRY)
		{
			m_checkmarkImage->move(204, 14 + m_activeEntry * 48);
			m_checkmarkImage->show();
		}
		else
			m_checkmarkImage->hide();

		for (int i = 1; i < m_entries.size(); i++)
			painter.drawLine(QPoint(8 + 1, i * 48 - 1), QPoint(width() - 8 - 1, i * 48 - 1));
	}

	void PickerWidget::mousePressEvent(QMouseEvent *event)
	{
		if (event->pos().y() < 0 || event->pos().y() > m_entries.size() * 48)
		{
			m_highlightedEntry = -1;
			return;
		}

		m_highlightedEntry = event->pos().y() / 48;

		update();
	}

	void PickerWidget::mouseReleaseEvent(QMouseEvent *event)
	{
		QRect highlightedEntryRect = QRect(0, m_highlightedEntry * 48,
			240, (m_highlightedEntry + 1) * 48);

		if (highlightedEntryRect.contains(event->pos()))
		{
			m_activeEntry = m_highlightedEntry;
			emit entryChanged();
		}

		m_highlightedEntry = -1;

		update();
	}

	int PickerWidget::activeEntry()
	{
		return m_activeEntry;
	}

	QString PickerWidget::activeEntryText()
	{
		if (m_activeEntry == NO_ENTRY || m_activeEntry >= m_entries.size())
			return QString();

		return m_entries[m_activeEntry]->text();
	}

	void PickerWidget::setActiveEntry(int activeEntry)
	{
		m_activeEntry = activeEntry;

		update();
	}

}
