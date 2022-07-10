/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRestart;
    QAction *actionEasy;
    QAction *actionIntermediate;
    QAction *actionAdvanced;
    QAction *actionExit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionRestart = new QAction(MainWindow);
        actionRestart->setObjectName(QString::fromUtf8("actionRestart"));
        actionEasy = new QAction(MainWindow);
        actionEasy->setObjectName(QString::fromUtf8("actionEasy"));
        actionIntermediate = new QAction(MainWindow);
        actionIntermediate->setObjectName(QString::fromUtf8("actionIntermediate"));
        actionAdvanced = new QAction(MainWindow);
        actionAdvanced->setObjectName(QString::fromUtf8("actionAdvanced"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(actionRestart);
        menu->addSeparator();
        menu->addAction(actionEasy);
        menu->addSeparator();
        menu->addAction(actionIntermediate);
        menu->addSeparator();
        menu->addAction(actionAdvanced);
        menu->addSeparator();
        menu->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRestart->setText(QCoreApplication::translate("MainWindow", "\346\226\260\346\270\270\346\210\217", nullptr));
        actionEasy->setText(QCoreApplication::translate("MainWindow", "\345\210\235\347\272\247", nullptr));
        actionIntermediate->setText(QCoreApplication::translate("MainWindow", "\344\270\255\347\272\247", nullptr));
        actionAdvanced->setText(QCoreApplication::translate("MainWindow", "\351\253\230\347\272\247", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
