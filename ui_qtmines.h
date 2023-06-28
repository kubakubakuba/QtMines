/********************************************************************************
** Form generated from reading UI file 'qtmines.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMINES_H
#define UI_QTMINES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtMines
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QtMines)
    {
        if (QtMines->objectName().isEmpty())
            QtMines->setObjectName(QString::fromUtf8("QtMines"));
        QtMines->resize(800, 600);
        centralwidget = new QWidget(QtMines);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QtMines->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QtMines);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        QtMines->setMenuBar(menubar);
        statusbar = new QStatusBar(QtMines);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QtMines->setStatusBar(statusbar);

        retranslateUi(QtMines);

        QMetaObject::connectSlotsByName(QtMines);
    } // setupUi

    void retranslateUi(QMainWindow *QtMines)
    {
        QtMines->setWindowTitle(QCoreApplication::translate("QtMines", "QtMines", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtMines: public Ui_QtMines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMINES_H
