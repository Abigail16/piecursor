#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bigwheel.h"
#include "piecursor.h"
#include "toolbar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);

private:

    Ui::MainWindow *ui;

    Cursor *cursor = nullptr;//鼠标选择
    int iconNumber;//哪一块


    QTimer *timer;//计时
    QTime *TimeRecord;

    QPoint currentMousePosPoint;

private slots:
    void updateTime();//功能选择
    void on_Toolbar_4_clicked() { if (cursor != nullptr) delete cursor; setCursor(Qt::ArrowCursor); cursor = new ToolBar(Cursor::Four); }
    void on_Toolbar_8_clicked() { if (cursor != nullptr) delete cursor; setCursor(Qt::ArrowCursor); cursor = new ToolBar(Cursor::Eight); }
    void on_PieCursor_4_clicked() { if (cursor != nullptr) delete cursor; setCursor(Qt::BlankCursor); cursor = new PieCursor(Cursor::Four); }
    void on_PieCursor_8_clicked() { if (cursor != nullptr) delete cursor; setCursor(Qt::BlankCursor); cursor = new PieCursor(Cursor::Eight); }
    void on_BigWheel_4_clicked() { if (cursor != nullptr) delete cursor; setCursor(Qt::ArrowCursor); cursor = new BigWheel(Cursor::Four); }
    void on_BigWheel_8_clicked() { if (cursor != nullptr) delete cursor; setCursor(Qt::ArrowCursor); cursor = new BigWheel(Cursor::Eight); }
};

#endif // MAINWINDOW_H
