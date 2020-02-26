#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent>
#include <QCursor>
#include <QTextCursor>
#include <QScrollBar>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void ExitClicked();
    void autoScroll();

private:
    Ui::MainWindow *ui;

    QFuture<QString> future1;
    QFuture<void> future2;

    QFutureWatcher<void> watcher1;
    QFutureWatcher<void> watcher2;

    QFuture<QString> future3;
    QFuture<void> future4;

    QFutureWatcher<void> watcher3;
    QFutureWatcher<void> watcher4;



    QString lastCommand = "";
    string consoleText = "";
    bool running = false;

    void getLog();
    void Finished();
    void AutoScroller();
    void FinishedScroller();
    QString serverId = "";
    //void ExitClicked();
signals:
    void TestSignal1(QString);
    //void TestSignal2(QTextCursor::MoveOperation);
    void setValue(int);
    int getValue();
    void cursorPositionChanged();
    bool checkBox();
    QString getText();
private slots:
    void on_toolButton_clicked();
    void on_toolButton_2_triggered(QAction *arg1);
    void on_toolButton_3_triggered(QAction *arg1);
    void on_toolButton_4_triggered(QAction *arg1);
    void on_toolButton_4_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_pushButton_clicked();
protected:
    virtual void keyPressEvent(QKeyEvent *ev);
};
#endif // MAINWINDOW_H
