# Add files and directories to ship with the application
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xE30C4A33

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the
# MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Display a console to display debug messages.
CONFIG += console

SOURCES += \
	src/main.cc \
	src/MainWindow.cc \
	src/IPodFrameWidget.cc \
	src/helpers.cc \
	src/apps/GUIApp.cc \
	src/apps/MapApp.cc \
	src/apps/App.cc \
	src/widgets/TitleBarWidget.cc \
	src/widgets/TitleBarButtonWidget.cc \
	src/widgets/TextWidget.cc \
	src/widgets/PageIndicatorWidget.cc \
	src/widgets/ImageWidget.cc \
	src/widgets/ClickableWidget.cc \
	src/widgets/ButtonWidget.cc \
	src/widgets/ScalableButtonWidget.cc \
	src/widgets/SwitchButtonWidget.cc \
	src/widgets/SliderWidget.cc \
	src/widgets/BackgroundWidget.cc \
	src/widgets/FlickArea.cc \
	src/widgets/MarkingMenu.cc \
	src/widgets/PickerWidget.cc \
	src/widgets/OverlayWidget.cc \
	src/apps/MenuApp.cc \
	src/widgets/RoomWidget.cc \
	src/widgets/NumberSpinnerWidget.cpp \
    src/apps/FurniturePickerApp.cpp \
    src/apps/ListMenuApp.cc \
    src/apps/NumberPickerApp.cc \
    src/widgets/PrettyClickableWidget.cc \
    src/apps/DummyApp.cpp \
    src/apps/SettingsApp.cc \
    src/apps/ColorPickerApp.cpp \
    src/widgets/CircleWidget.cpp \
    src/apps/FurnitureViewer.cpp \
    src/SettingsMapper.cpp
	
HEADERS += \
	src/MainWindow.h \
	src/IPodFrameWidget.h \
	src/helpers.h \
	src/apps/GUIApp.h \
	src/apps/MapApp.h \
	src/apps/App.h \
	src/widgets/TitleBarWidget.h \
	src/widgets/TitleBarButtonWidget.h \
	src/widgets/TextWidget.h \
	src/widgets/PageIndicatorWidget.h \
	src/widgets/ImageWidget.h \
	src/widgets/ClickableWidget.h \
	src/widgets/ButtonWidget.h \
	src/widgets/ScalableButtonWidget.h \
	src/widgets/SwitchButtonWidget.h \
	src/widgets/SliderWidget.h \
	src/widgets/BackgroundWidget.h \
	src/widgets/FlickArea.h \
	src/widgets/MarkingMenu.h \
	src/widgets/PickerWidget.h \
	src/widgets/OverlayWidget.h \
	src/apps/MenuApp.h \
	src/widgets/RoomWidget.h \
	src/widgets/NumberSpinnerWidget.h \
    src/apps/FurniturePickerApp.h \
    src/apps/ListMenuApp.h \
    src/apps/NumberPickerApp.h \
    src/widgets/PrettyClickableWidget.h \
    src/apps/DummyApp.h \
    src/apps/SettingsApp.h \
    src/apps/ColorPickerApp.h \
    src/widgets/CircleWidget.h \
    src/apps/FurnitureViewer.h \
    src/SettingsMapper.h

INCLUDEPATH += src src/apps src/widgets

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

RESOURCES += \
	resources.qrc

macx:LIBS += -framework CoreFoundation

OTHER_FILES +=

