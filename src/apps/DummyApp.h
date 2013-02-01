#ifndef IPN_SETTINGSAPP_H
#define IPN_SETTINGSAPP_H

#include "App.h"

namespace ipn
{

    class BackgroundWidget;
    class TitleBarWidget;
    class TextWidget;

    class DummyApp : public App
    {
        Q_OBJECT

        public:
            DummyApp(QWidget *parent = 0);
            TitleBarWidget *titleBar();

        public slots:
            void setText(QString text);


        private:
            BackgroundWidget *m_back;
            TextWidget *m_textArea;
    };

} // namespace ipn

#endif /* end of include guard: IPN_DUMMYAPP_H */
