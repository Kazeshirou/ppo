/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "treewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *open;
    QAction *insertroute;
    QAction *deleteroute;
    QAction *undo;
    QAction *redo;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    TreeWidget *routes;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTextEdit *polyline;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QPlainTextEdit *import_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *filemenu;
    QMenu *routemenu;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1181, 789);
        open = new QAction(MainWindow);
        open->setObjectName(QStringLiteral("open"));
        insertroute = new QAction(MainWindow);
        insertroute->setObjectName(QStringLiteral("insertroute"));
        deleteroute = new QAction(MainWindow);
        deleteroute->setObjectName(QStringLiteral("deleteroute"));
        undo = new QAction(MainWindow);
        undo->setObjectName(QStringLiteral("undo"));
        redo = new QAction(MainWindow);
        redo->setObjectName(QStringLiteral("redo"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        routes = new TreeWidget(centralwidget);
        routes->setObjectName(QStringLiteral("routes"));
        routes->setMinimumSize(QSize(590, 300));
        routes->setContextMenuPolicy(Qt::DefaultContextMenu);
        routes->setAcceptDrops(true);
        routes->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        routes->setEditTriggers(QAbstractItemView::DoubleClicked);
        routes->setTabKeyNavigation(true);
        routes->setProperty("showDropIndicator", QVariant(false));
        routes->setDragEnabled(false);
        routes->setDragDropMode(QAbstractItemView::NoDragDrop);
        routes->setDefaultDropAction(Qt::TargetMoveAction);
        routes->setAlternatingRowColors(false);
        routes->setSelectionMode(QAbstractItemView::SingleSelection);
        routes->setSelectionBehavior(QAbstractItemView::SelectRows);
        routes->setTextElideMode(Qt::ElideNone);
        routes->setSortingEnabled(false);
        routes->setProperty("topLevelItemCount", QVariant(0));
        routes->header()->setDefaultSectionSize(100);

        verticalLayout->addWidget(routes);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        polyline = new QTextEdit(centralwidget);
        polyline->setObjectName(QStringLiteral("polyline"));
        polyline->setAutoFormatting(QTextEdit::AutoNone);
        polyline->setReadOnly(true);

        verticalLayout_2->addWidget(polyline);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        import_2 = new QPlainTextEdit(centralwidget);
        import_2->setObjectName(QStringLiteral("import_2"));

        verticalLayout_3->addWidget(import_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1181, 26));
        filemenu = new QMenu(menubar);
        filemenu->setObjectName(QStringLiteral("filemenu"));
        routemenu = new QMenu(menubar);
        routemenu->setObjectName(QStringLiteral("routemenu"));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(filemenu->menuAction());
        menubar->addAction(routemenu->menuAction());
        menubar->addAction(menu->menuAction());
        filemenu->addAction(open);
        routemenu->addAction(insertroute);
        routemenu->addAction(deleteroute);
        menu->addAction(undo);
        menu->addAction(redo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        open->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
#ifndef QT_NO_SHORTCUT
        open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        insertroute->setText(QApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
#ifndef QT_NO_SHORTCUT
        insertroute->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_NO_SHORTCUT
        deleteroute->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
#ifndef QT_NO_TOOLTIP
        deleteroute->setToolTip(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        deleteroute->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        undo->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
#ifndef QT_NO_SHORTCUT
        undo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        redo->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214", nullptr));
#ifndef QT_NO_SHORTCUT
        redo->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("MainWindow", "\320\234\320\260\321\200\321\210\321\200\321\203\321\202\321\213", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = routes->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\320\224\320\273\320\270\320\275\320\260", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\260", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\320\270\320\273\320\260\320\271\320\275", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202 \320\270\320\267 \320\277\320\276\320\273\320\270\320\273\320\260\320\271\320\275\320\260", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202", nullptr));
        filemenu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        routemenu->setTitle(QApplication::translate("MainWindow", "\320\234\320\260\321\200\321\210\321\200\321\203\321\202", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
