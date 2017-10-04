TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Sock.cpp \
    Selectfunc.cpp \
    FuncFactory.cpp \
    Abstract.cpp \
    Pass.cpp \
    My_Sql.cpp \
    Regi.cpp \
    MyTools.cpp \
    Func/ChPw.cpp \
    Func/Dest.cpp \
    Func/Draw.cpp \
    Func/Hist.cpp \
    Func/Inqu.cpp \
    Func/Open.cpp \
    Func/Save.cpp \
    Func/Tran.cpp

HEADERS += \
    Sock.h \
    mark.h \
    Selectfunc.h \
    DynBase.h \
    FuncFactory.h \
    Abstract.h \
    Pass.h \
    My_Sql.h \
    Regi.h \
    MyTools.h \
    Func/ChPw.h \
    Func/Dest.h \
    Func/Draw.h \
    Func/Func.h \
    Func/Hist.h \
    Func/Inqu.h \
    Func/Open.h \
    Func/Save.h \
    Func/Tran.h

LIBS += -L/usr/lib -lpthread
LIBS += -L/usr/lib -lmysqlclient

QMAKE_CXXFLAGS += -std=c++0x

