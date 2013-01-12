#ifndef IPN_PICKERWIDGET_H
#define IPN_PICKERWIDGET_H

#include <QWidget>

namespace ipn
{

	class TextWidget;
	class ImageWidget;

	class PickerWidget : public QWidget
	{
		Q_OBJECT

		public:
			PickerWidget(QWidget *parent = 0);

			void addEntry(QString text);
            void addEntry(QString text, QString value);
            void addEntry(QString text, QWidget* value);
            void setValue(int idx, QString value);
            void setValue(int idx, QColor value);
			int activeEntry();
			QString activeEntryText();
			void setActiveEntry(int activeEntry);

		signals:
			void entryChanged();

		protected:
			virtual void paintEvent(QPaintEvent *event);
			virtual void mousePressEvent(QMouseEvent *event);
			virtual void mouseReleaseEvent(QMouseEvent *event);

		private:
			QVector<TextWidget*> m_entries;
            QVector<QWidget*> m_values;
			ImageWidget *m_entryDownImage, *m_checkmarkImage;
			int m_activeEntry;
			int m_highlightedEntry;
	};

} // namespace ipn

#endif // IPN_PICKERWIDGET_H
