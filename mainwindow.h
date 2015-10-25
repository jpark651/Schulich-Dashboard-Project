#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void unactive();    //Method if user closes

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
