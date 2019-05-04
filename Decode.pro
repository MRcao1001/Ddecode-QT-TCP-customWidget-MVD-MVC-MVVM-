#-------------------------------------------------
#
# Project created by QtCreator 2019-02-21T22:30:21
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Decode
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lz

SOURCES += \
    Public_part/main.cpp\
    Public_part/Decode.cpp \
    Public_part/log.cpp\
    Public_part/LoginAndRegWindow.cpp \
    Public_part/DecodeAnimation.cpp \
    Public_part/MessageWindow.cpp \
    Public_part/DecodeBaseWindow.cpp \
    DataBase_patr/DataBaseManager.cpp \
    TCP_part/TCP_Manager.cpp \
    TCP_part/TCPServer.cpp \
    TCP_part/TCPClient.cpp \
    DataModel/UserInfoModel.cpp \
    DataModel/UserInfo.cpp \
    DataModel/ExamPaperModel.cpp \
    DataModel/ExamChoiceQusetion.cpp \
    DataModel/ExamRoomModel.cpp \
    DataModeView/UserInfoFrame.cpp \
    DataModeView/ExamChoiceQusetionFrame.cpp \
    DataModeView/ExamRoomModelView.cpp \
    DataDelegate/ExamPaperDelegate.cpp \
    DataDelegate/UserInfoDelegate.cpp \
    Server_part/ServerWindow.cpp\
    Client_part/ClientWindow.cpp\
    Client_part/LeftBar.cpp \
    Client_part/AnswerSheet.cpp \
    Client_part/ExmaPaperwindow.cpp \
    Public_part/QFlowLayout.cpp

HEADERS += \
        Public_part/Decode.h \
    Public_part/DecodeBaseWindow.h \
    Public_part/LoginAndRegWindow.h \
    Public_part/MessageWindow.h \
    Public_part/log.h\
    Public_part/DecodeAnimation.h \
    DataBase_patr/DataBaseManager.h \  
    DataModel/UserInfoModel.h \
    DataModel/UserInfo.h \
    DataModel/ExamChoiceQusetion.h \
    DataModel/ExamRoomModel.h \
    DataModel/ExamPaperModel.h \
    DataModeView/UserInfoFrame.h \   
    DataModeView/ExamChoiceQusetionFrame.h \
    DataModeView/ExamRoomModelView.h\
    DataDelegate/ExamPaperDelegate.h \
    DataDelegate/UserInfoDelegate.h \
    TCP_part/TCPServer.h \
    TCP_part/TCPClient.h \
    TCP_part/TCP_Manager.h \
    Server_part/ServerWindow.h\
    Client_part/ClientWindow.h\
    Client_part/LeftBar.h \
    Client_part/ExmaPaperwindow.h \
    Client_part/AnswerSheet.h \
    Public_part/QFlowLayout.h

FORMS += \
    Public_part/Decode.ui \
    Server_part/ServerWindow.ui\
    Client_part/ClientWindow.ui\
    TCP_part/TCPServer.ui \
    TCP_part/TCPClient.ui \
    Client_part/LeftBar.ui \
    Client_part/AnswerSheet.ui \
    Public_part/DecodeBaseWindow.ui \
    Public_part/LoginAndRegWindow.ui \
    DataModeView/UserInfoFrame.ui \
    DataModeView/ExamChoiceQusetionFrame.ui \
    Client_part/ExmaPaperwindow.ui\
    Public_part/MessageWindow.ui


RC_ICONS = Decode.ico

RESOURCES += \
    qss.qrc \
    img.qrc

DISTFILES +=

