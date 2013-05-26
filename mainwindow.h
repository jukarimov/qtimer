#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QDir>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *atimer;

    bool    isTimerActive;
    bool    isAlarmActive;

private slots:
    void startButton_pushed();
    void stopButton_pushed();
    void setButton_pushed();
    void unsetButton_pushed();

    void checkBox_Timer_clicked();
    void checkBox_Alarm_clicked();

    void timeout();
    void update();

    void aupdate();

    void alarmDateTime_changed(QDateTime);

    void mplayer();
};

#endif // MAINWINDOW_H
