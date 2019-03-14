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
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    QPoint lastMousePosPoint;
    QPoint currentMousePosPoint;

    enum Direction {Right, LowerRight, Lower, LowerLeft, Left, UpperLeft, Upper, UpperRight} choseToolDirection;

    Direction calcDirection(QPoint last, QPoint current);

    const int OuterCircleR = 60;
    const int InnerCircleR = 35;
};

#endif // MAINWINDOW_H
