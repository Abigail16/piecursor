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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    QPoint mousePosPoint;

    const int OuterCircleR = 60;
    const int InnerCircleR = 35;
};

#endif // MAINWINDOW_H
