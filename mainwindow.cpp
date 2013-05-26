#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startButton, SIGNAL(pressed()), this, SLOT(startButton_pushed()));
    connect(ui->stopButton, SIGNAL(pressed()), this, SLOT(stopButton_pushed()));

    timer = new QTimer(this);
    atimer = new QTimer(this);
    atimer->

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(atimer, SIGNAL(timeout()), this, SLOT(aupdate()));

    QDateTime dt;
    ui->dateTimeEdit->setDateTime(dt.currentDateTime());

    connect(ui->setButton, SIGNAL(pressed()), this, SLOT(setButton_pushed()));
    connect(ui->unsetButton, SIGNAL(pressed()), this, SLOT(unsetButton_pushed()));

    connect(ui->checkBox_Timer, SIGNAL(clicked()), this, SLOT(checkBox_Timer_clicked()));
    connect(ui->checkBox_Alarm, SIGNAL(clicked()), this, SLOT(checkBox_Alarm_clicked()));
    connect(ui->dateTimeEdit, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(alarmDateTime_changed(QDateTime)));

    isTimerActive = false;
    isAlarmActive = false;
}

void MainWindow::aupdate()
{
    qDebug() << "aupdate";

    if (isAlarmActive) {

        QDate d = ui->dateTimeEdit->date();
        QTime t = ui->dateTimeEdit->time();

        QDate dNow = QDate().currentDate();
        QTime tNow = QTime().currentTime();

        int dy = d.year() - dNow.year();
        int dm = d.month() - dNow.month();
        int dd = d.day() - dNow.day();

        int th = t.hour() - tNow.hour();
        int tm = t.minute() - tNow.minute();
        int ts = t.second() - tNow.second();

        qDebug() << th << tm << ts;


        if (dy <= 0 && dm <= 0 && dd <= 0 && th <= 0 && tm <= 0 && ts <= 0) {
            qDebug() << "alarm!!!";
            atimer->stop();
            isAlarmActive = false;
            ui->unsetButton->setEnabled(false);
            ui->setButton->setEnabled(true);
            mplayer();
        }
    }
}

void MainWindow::alarmDateTime_changed(QDateTime t)
{
    qDebug() << "changed:" << t.toString();
}

void MainWindow::checkBox_Alarm_clicked()
{
    if (ui->checkBox_Alarm->isChecked()) {
        ui->dateTimeEdit->setEnabled(true);
        ui->setButton->setEnabled(true);
        ui->unsetButton->setEnabled(true);
    } else {
        ui->dateTimeEdit->setEnabled(false);
        ui->setButton->setEnabled(false);
        ui->unsetButton->setEnabled(false);
        isAlarmActive = false;
    }
}

void MainWindow::checkBox_Timer_clicked()
{
    if (ui->checkBox_Timer->isChecked()) {
        ui->timeEdit->setEnabled(true);
        ui->startButton->setEnabled(true);
        ui->stopButton->setEnabled(true);
    } else {
        timer->stop();
        ui->timeEdit->setEnabled(false);
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(false);
        isTimerActive = false;
    }
}

void MainWindow::setButton_pushed()
{
    qDebug() << "set";
    atimer->start(1000);
    isAlarmActive = true;

    ui->setButton->setEnabled(false);
    ui->unsetButton->setEnabled(true);
}

void MainWindow::unsetButton_pushed()
{
    qDebug() << "unset";
    atimer->stop();
    isAlarmActive = false;

    ui->setButton->setEnabled(true);
    ui->unsetButton->setEnabled(false);
}

void MainWindow::startButton_pushed()
{
    qDebug() << "start";
    isTimerActive = true;

    timer->start(1000);

    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainWindow::timeout()
{
    qDebug() << "tada!";
}

void MainWindow::update()
{
    qDebug() << "tik";

    if (isTimerActive) {

        QTime c = ui->timeEdit->time();

        int h, m, s;

        h = c.hour(), m = c.minute(), s = c.second();

        if (--s == -1) {
            if (!h && !m) {
                s = 0;
                timer->stop();
                isTimerActive = false;

                ui->startButton->setEnabled(true);

                mplayer();

                return;
            }
            else if (h && !m) {
                if (--h < 0)
                    h = 0;
                m = 59;
                s = 59;
                goto out;
            }
            else {
                s = 59;
                if (!--m == -1) {
                    m = 59;
                    --h;
                }
            }
        }
        else if (!s && !m && h > 0) {
            --h;
            m = 59;
            s = 59;
        }
out:
        qDebug() << h << m << s;

        c.setHMS(h, m, s);

        ui->timeEdit->setTime(c);
    }
}

void MainWindow::stopButton_pushed()
{
    qDebug() << "stop";
    timer->stop();
    isTimerActive = false;

    QTime c = ui->timeEdit->time();

    c.setHMS(0, 0, 0);

    ui->timeEdit->setTime(c);

    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void MainWindow::mplayer()
{
    QString script;
    script.append(QDir::homePath());
    script.append(QDir::separator());
    script.append("play.sh");

    QByteArray cmd;
    cmd.append(script.toUtf8());

    system(cmd.data());
}

MainWindow::~MainWindow()
{
    delete ui;
}
