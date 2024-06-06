QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Apple.cpp \
        Game_Engine.cpp \
        RenderEngine.cpp \
        Snake.cpp \
        Texture_Manager.cpp \
        main.cpp \
        stdafx.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Apple.h \
    Game_Engine.h \
    RenderEngine.h \
    Snake.h \
    Texture_Manager.h \
    stdafx.h

INCLUDEPATH += "C:/Qt/SFML/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include"

LIBS += -L"C:/Qt/SFML/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}
LIBS += -LDwmapi.lib
