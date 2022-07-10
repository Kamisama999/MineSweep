#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTimer>
#include "MineMap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_actionRestart_triggered();
    void on_actionExit_triggered();
    void on_actionEasy_triggered();
    void on_actionIntermediate_triggered();
    void on_actionAdvanced_triggered();
    void on_sectime();

private:
    Ui::MainWindow *ui;
    MineMap mineMap;
    int offsetx,offsety;
    QTimer *runtime;
};
#endif // MAINWINDOW_H
