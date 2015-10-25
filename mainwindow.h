#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool activeFile;    //value which tells if a file has been loaded or not

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
