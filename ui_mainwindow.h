/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionCloseFile;
    QAction *actionFullscreen;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *sidebar;
    QVBoxLayout *verticalLayout;
    QTreeWidget *publicationTree;
    QPushButton *pushButton;
    QFrame *graph;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionCloseFile = new QAction(MainWindow);
        actionCloseFile->setObjectName(QString::fromUtf8("actionCloseFile"));
        actionFullscreen = new QAction(MainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(400, 500));
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        sidebar = new QWidget(centralWidget);
        sidebar->setObjectName(QString::fromUtf8("sidebar"));
        sidebar->setMinimumSize(QSize(200, 400));
        sidebar->setMaximumSize(QSize(500, 16777215));
        verticalLayout = new QVBoxLayout(sidebar);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        publicationTree = new QTreeWidget(sidebar);
        publicationTree->setObjectName(QString::fromUtf8("publicationTree"));
        publicationTree->setMinimumSize(QSize(200, 400));
        publicationTree->setMaximumSize(QSize(500, 16777215));
        publicationTree->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        verticalLayout->addWidget(publicationTree);

        pushButton = new QPushButton(sidebar);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout_2->addWidget(sidebar);

        graph = new QFrame(centralWidget);
        graph->setObjectName(QString::fromUtf8("graph"));
        graph->setFrameShape(QFrame::StyledPanel);
        graph->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(graph);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(graph);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(450, 400));

        horizontalLayout->addWidget(label);


        horizontalLayout_2->addWidget(graph);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionCloseFile);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuView->addAction(actionFullscreen);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionFullscreen, SIGNAL(triggered()), MainWindow, SLOT(showFullScreen()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Team Honeydew", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionCloseFile->setText(QApplication::translate("MainWindow", "Close File", 0, QApplication::UnicodeUTF8));
        actionFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = publicationTree->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Total", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Summary", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Open File", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
