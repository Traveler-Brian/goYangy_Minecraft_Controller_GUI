//Version Beta 1.1
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTConcurrent"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "iostream"
#include "time.h"
#include "QScrollBar"
#include "QTextCursor"
#include "QFile"
#include "QMessageBox"
#include "QBitmap"
#include "QPainter"
using namespace std;

//bool running = true;

void delay(int sec)
{
time_t _t;
_t = time (NULL);
while(time (NULL) <= _t + sec){};
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
ui->setupUi(this);

this->setStyleSheet("background:rgb(53,53,53);");

ui->lineEdit->setStyleSheet("background:rgb(45,45,45);border-top-left-radius: 10px;border-bottom-left-radius: 10px;border: 1px solid rgb(73,73,73);color:white;font-family:'consolas'");
ui->pushButton->setStyleSheet("background: rgb(78,78,78); border-top-right-radius: 10px;border-bottom-right-radius:10px;margin-left:0px;");
ui->textBrowser_2->setStyleSheet("background:rgb(45,45,45);border:1px solid rgb(73,73,73);border-radius: 10px;color:white;font-family: 'consolas';text-indent: 100px;");
ui->textBrowser->setStyleSheet("background:rgb(45,45,45);border:none;color:white;font-family: 'consolas';text-indent: 100px;overflow:hidden;");
ui->toolButton->setStyleSheet("background: rgb(78,78,78); border-top-left-radius: 10px;border-bottom-right-radius:10px;color:white;");

ui->toolButton_2->setStyleSheet("background: rgb(78,78,78); border-top-left-radius: 10px;border-bottom-right-radius:10px;color:white;");
ui->toolButton_3->setStyleSheet("background: rgb(78,78,78); border-top-left-radius: 10px;border-bottom-right-radius:10px;color:white;");
ui->toolButton_4->setStyleSheet("background: rgb(78,78,78); border-top-left-radius: 10px;border-bottom-right-radius:10px;color:white;");


/*QBitmap bmp(this->size());

    bmp.fill();

    QPainter p(&bmp);

    p.setPen(Qt::NoPen);

    p.setBrush(Qt::black);

    p.drawRoundedRect(bmp.rect(),20,20);

    setMask(bmp);*/

    //Testing Area
    /*QByteArray line;
    QFile file("Verify.harum");
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

       while (!file.atEnd()) {
            line = file.readLine();
           //qDebug()<<(line);
       }*/

qDebug() << "App path : " << qApp->applicationDirPath();
       if(QFile::exists(qApp->applicationDirPath()+"/Verify.harum"))
       {
           QByteArray line;
               QFile file(qApp->applicationDirPath()+"/Verify.harum");
                  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                      return;

                  while (!file.atEnd()) {
                       line = file.readLine();
                      qDebug()<<(line);
                  }

                  if((QString)line.constData() != "" && (QString)line.constData()!="\n")
                  {

     serverId = line;
     //Testing Area
        setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    //ui->menubar->addAction("Exit (&E)",this,SLOT(ExitClicked()));
    //connect(ui->actionExit_Application, SIGNAL(triggered()), this, SLOT(ExitClicked()));
    //ui->textBrowser->setStyleSheet("background: black; color:white;");
    ui->textBrowser->setText("Connecting To Server...");
    running = true;
    connect(ui->textBrowser, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));

    connect(this, &MainWindow::TestSignal1, ui->textBrowser, &QTextBrowser::setText);

    connect(this, &MainWindow::setValue, ui->textBrowser->verticalScrollBar(), &QScrollBar::setValue);
    connect(this, &MainWindow::getValue, ui->textBrowser->verticalScrollBar(), &QScrollBar::maximum);
    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->pushButton,SIGNAL(clicked()));
    //connect(this, &MainWindow::TestSignal2, ui->textBrowser, &QTextBrowser::moveCursor);
    //running = true;


    //ui->lineEdit->setStyleSheet("border-top: 2px 2px 2px solid white");

             connect(&watcher2,&QFutureWatcher<void>::finished,this,&MainWindow::Finished);
             future2 = QtConcurrent::run(this,&MainWindow::getLog);
             watcher2.setFuture(future2);




                  }else{
                      ui->pushButton->setEnabled(false);
                      ui->textBrowser->setText("ServerId not set! Please set your serverId in the verify.harum file!");
                      //ui->textBrowser->setStyleSheet("background: black; color:red;");
                      ui->toolButton->setEnabled(false);
                      ui->toolButton_2->setEnabled(false);
                      ui->toolButton_3->setEnabled(false);
                      ui->toolButton_4->setEnabled(false);
                  }
       }else{
            ui->pushButton->setEnabled(false);
            ui->textBrowser->setText("ServerId not set! Please set your serverId in the verify.harum file!");
            //ui->textBrowser->setStyleSheet("background: black; color:red;");
            ui->toolButton->setEnabled(false);
            ui->toolButton_2->setEnabled(false);
            ui->toolButton_3->setEnabled(false);
            ui->toolButton_4->setEnabled(false);
            QFile file(qApp->applicationDirPath()+"/Verify.harum");
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                    return;

                QTextStream out(&file);
                out << "";
       }

}

void MainWindow::ExitClicked()
{
    cout<<"Exit Clicked!"<<endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::autoScroll()
{
    QTextCursor cursor =  ui->textBrowser->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textBrowser->setTextCursor(cursor);
}

void MainWindow::getLog()
{
    while(running)
    {



        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QString url = "https://minerooms.com/console/"+serverId;
        QNetworkRequest request;
        request.setUrl(QUrl(url));
        request.setRawHeader("Cookie","__cfduid=d12e7ff4fe25c0162d956d594642f23601582446396;_ga=GA1.2.500865953.1582446399;_gat=1;_gid=GA1.2.1164300349.1582446399;_mineroom_web_session=SGJCd3ptck9RZXB0ZWZwK3UwK29XTzdydHNiSW8vb1dQUDc4RjlCWVFPT2hiSFJRRTdTWUlkMVhBSzBSM0tKay9sNC9YVlVPcEs0cmNXK2Vzemg2WTI3am94SVYyVVRzMktLa1A0TGlHOVpTanFQUWZvNGsxTWZFbURQcVpnNW1ac1VDM1VnWXpEMGFUVkFvYkNrRTRvL3UyTTU5V2pMK1kwSFVndmdQUUIzYlNZTktrWFRWTTlGMG1DTzFJMjdwZGFWWUZ5U21ybU5oRU1xRGZwajJLTC9EamNOK0NNTHpmVnJ0YjlweGtvYXM0RFg0YW9MTWMwNlpzSTMzK2JrTXNnMVRpeGFwanBjNm8vZW1WanluSDBhNk1UTVE0cHdYWEZHSlVHUGJDQU09LS0zS1k4ek5NMzhoT2ZDOFVpUUVBNEtBPT0%3D--c061a7b38b0c008c3c04bca75b217621993acb48");

        QNetworkReply *pReply = manager->get(request);
        QEventLoop eventLoop;
        QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();

        QByteArray bytes = pReply->readAll();

        qint64 first = 0;
        qint64 second = 0;

        QString weborigin = (QString)bytes.constData();

        weborigin.replace("&#39;","'");
        weborigin.replace("&lt;","<");
        weborigin.replace("&gt;",">");
        weborigin.replace("&quot;","\"");

        string webpage = weborigin.toUtf8().constData();

        for(int i=0;i<webpage.length();i++)
        {
            if(webpage[i] == 'e' && webpage[i+1] == 'd' && webpage[i+2] == '>')
            {
                first = i+3;
                break;
            }
        }
        for(int i=0;i<webpage.length();i++)
        {

            if(webpage[i] == '<' && webpage[i+1] == '/' && i > first)
            {
                second = i;
                break;
            }
        }
        cout<<first<<second<<endl;
        string console = "";
        for(int i=first;i<second;i++)
        {
            cout<<webpage[i];
            console += webpage[i];
        }

        TestSignal1(QString::fromStdString(console));

        //TestSignal2(QTextCursor::End);
        //ui->textBrowser->moveCursor(QTextCursor::End);
        //setValue(ui->textBrowser->verticalScrollBar()->maximum());

        //delay(1);
    }
}

void MainWindow::Finished()
{

}

void MainWindow::on_toolButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure to start your server?");
    QPushButton *connectButton = msgBox.addButton(tr("Confirm"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
    msgBox.setStyleSheet("background: rbg(43,43,43);color:white;");
    connectButton->setStyleSheet("background: rgb(73,73,73);color:white;");
    abortButton->setStyleSheet("background: rgb(73,73,73);color:white;");
    msgBox.exec();

    if (msgBox.clickedButton() == connectButton) {
        QNetworkAccessManager *manager = new QNetworkAccessManager();
            QString url = "https://minerooms.com/docker/start_server/"+serverId;
            QNetworkRequest request;
            request.setUrl(QUrl(url));
            request.setRawHeader("Cookie","__cfduid=d12e7ff4fe25c0162d956d594642f23601582446396;_ga=GA1.2.500865953.1582446399;_gat=1;_gid=GA1.2.1164300349.1582446399;_mineroom_web_session=SGJCd3ptck9RZXB0ZWZwK3UwK29XTzdydHNiSW8vb1dQUDc4RjlCWVFPT2hiSFJRRTdTWUlkMVhBSzBSM0tKay9sNC9YVlVPcEs0cmNXK2Vzemg2WTI3am94SVYyVVRzMktLa1A0TGlHOVpTanFQUWZvNGsxTWZFbURQcVpnNW1ac1VDM1VnWXpEMGFUVkFvYkNrRTRvL3UyTTU5V2pMK1kwSFVndmdQUUIzYlNZTktrWFRWTTlGMG1DTzFJMjdwZGFWWUZ5U21ybU5oRU1xRGZwajJLTC9EamNOK0NNTHpmVnJ0YjlweGtvYXM0RFg0YW9MTWMwNlpzSTMzK2JrTXNnMVRpeGFwanBjNm8vZW1WanluSDBhNk1UTVE0cHdYWEZHSlVHUGJDQU09LS0zS1k4ek5NMzhoT2ZDOFVpUUVBNEtBPT0%3D--c061a7b38b0c008c3c04bca75b217621993acb48");

            QNetworkReply *pReply = manager->get(request);
            QEventLoop eventLoop;
            QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();

            QByteArray bytes = pReply->readAll();
            qDebug() << bytes;
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
    }
    /*QNetworkAccessManager *manager = new QNetworkAccessManager();
    QString url = "https://minerooms.com/docker/start_server/"+serverId;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Cookie","__cfduid=d12e7ff4fe25c0162d956d594642f23601582446396;_ga=GA1.2.500865953.1582446399;_gat=1;_gid=GA1.2.1164300349.1582446399;_mineroom_web_session=SGJCd3ptck9RZXB0ZWZwK3UwK29XTzdydHNiSW8vb1dQUDc4RjlCWVFPT2hiSFJRRTdTWUlkMVhBSzBSM0tKay9sNC9YVlVPcEs0cmNXK2Vzemg2WTI3am94SVYyVVRzMktLa1A0TGlHOVpTanFQUWZvNGsxTWZFbURQcVpnNW1ac1VDM1VnWXpEMGFUVkFvYkNrRTRvL3UyTTU5V2pMK1kwSFVndmdQUUIzYlNZTktrWFRWTTlGMG1DTzFJMjdwZGFWWUZ5U21ybU5oRU1xRGZwajJLTC9EamNOK0NNTHpmVnJ0YjlweGtvYXM0RFg0YW9MTWMwNlpzSTMzK2JrTXNnMVRpeGFwanBjNm8vZW1WanluSDBhNk1UTVE0cHdYWEZHSlVHUGJDQU09LS0zS1k4ek5NMzhoT2ZDOFVpUUVBNEtBPT0%3D--c061a7b38b0c008c3c04bca75b217621993acb48");

    QNetworkReply *pReply = manager->get(request);
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray bytes = pReply->readAll();
    qDebug() << bytes;*/
}

void MainWindow::on_toolButton_2_triggered(QAction *arg1)
{

}

void MainWindow::on_toolButton_3_triggered(QAction *arg1)
{

}

void MainWindow::on_toolButton_4_triggered(QAction *arg1)
{

}

void MainWindow::on_toolButton_4_clicked()
{
    QMessageBox msgBox;
    QPushButton *connectButton = msgBox.addButton(tr("Confirm"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
msgBox.setText("Are you sure to quit?");
msgBox.setStyleSheet("background: rbg(43,43,43);color:white;");
connectButton->setStyleSheet("background: rgb(73,73,73);color:white;");
abortButton->setStyleSheet("background: rgb(73,73,73);color:white;");
    msgBox.exec();

    if (msgBox.clickedButton() == connectButton) {
        running = false;
        this->close();
        terminate();
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
    }

}

void MainWindow::on_toolButton_2_clicked()
{
    /*QMessageBox msgBox;
    QPushButton *connectButton = msgBox.addButton(tr("Confirm"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == connectButton) {
        // connect
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
    }*/
    QMessageBox msgBox;
        QPushButton *connectButton = msgBox.addButton(tr("Confirm"), QMessageBox::ActionRole);
        QPushButton *abortButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
        msgBox.setStyleSheet("background: rbg(43,43,43);color:white;");
        connectButton->setStyleSheet("background: rgb(73,73,73);color:white;");
        abortButton->setStyleSheet("background: rgb(73,73,73);color:white;");
        msgBox.setText("Are you sure to stop server?");
        msgBox.exec();

        if (msgBox.clickedButton() == connectButton) {
            QNetworkAccessManager *manager = new QNetworkAccessManager();
            QString url = "https://minerooms.com/docker/stop_server/"+serverId;
            QNetworkRequest request;
            request.setUrl(QUrl(url));
            request.setRawHeader("Cookie","__cfduid=d12e7ff4fe25c0162d956d594642f23601582446396;_ga=GA1.2.500865953.1582446399;_gat=1;_gid=GA1.2.1164300349.1582446399;_mineroom_web_session=SGJCd3ptck9RZXB0ZWZwK3UwK29XTzdydHNiSW8vb1dQUDc4RjlCWVFPT2hiSFJRRTdTWUlkMVhBSzBSM0tKay9sNC9YVlVPcEs0cmNXK2Vzemg2WTI3am94SVYyVVRzMktLa1A0TGlHOVpTanFQUWZvNGsxTWZFbURQcVpnNW1ac1VDM1VnWXpEMGFUVkFvYkNrRTRvL3UyTTU5V2pMK1kwSFVndmdQUUIzYlNZTktrWFRWTTlGMG1DTzFJMjdwZGFWWUZ5U21ybU5oRU1xRGZwajJLTC9EamNOK0NNTHpmVnJ0YjlweGtvYXM0RFg0YW9MTWMwNlpzSTMzK2JrTXNnMVRpeGFwanBjNm8vZW1WanluSDBhNk1UTVE0cHdYWEZHSlVHUGJDQU09LS0zS1k4ek5NMzhoT2ZDOFVpUUVBNEtBPT0%3D--c061a7b38b0c008c3c04bca75b217621993acb48");

            QNetworkReply *pReply = manager->get(request);
            QEventLoop eventLoop;
            QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();

            QByteArray bytes = pReply->readAll();
            qDebug() << bytes;
        } else if (msgBox.clickedButton() == abortButton) {
            // abort
        }

}

void MainWindow::on_toolButton_3_clicked()
{
    QMessageBox msgBox;
        QPushButton *connectButton = msgBox.addButton(tr("Confirm"), QMessageBox::ActionRole);
        QPushButton *abortButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
msgBox.setText("Are you sure to renew?");
msgBox.setStyleSheet("background: rbg(43,43,43);color:white;");
connectButton->setStyleSheet("background: rgb(73,73,73);color:white;");
abortButton->setStyleSheet("background: rgb(73,73,73);color:white;");
        msgBox.exec();

        if (msgBox.clickedButton() == connectButton) {
            QNetworkAccessManager *manager = new QNetworkAccessManager();
            QString url = "https://minerooms.com/docker/add_hour/"+serverId;
            QNetworkRequest request;
            request.setUrl(QUrl(url));
            request.setRawHeader("Cookie","__cfduid=d12e7ff4fe25c0162d956d594642f23601582446396;_ga=GA1.2.500865953.1582446399;_gat=1;_gid=GA1.2.1164300349.1582446399;_mineroom_web_session=SGJCd3ptck9RZXB0ZWZwK3UwK29XTzdydHNiSW8vb1dQUDc4RjlCWVFPT2hiSFJRRTdTWUlkMVhBSzBSM0tKay9sNC9YVlVPcEs0cmNXK2Vzemg2WTI3am94SVYyVVRzMktLa1A0TGlHOVpTanFQUWZvNGsxTWZFbURQcVpnNW1ac1VDM1VnWXpEMGFUVkFvYkNrRTRvL3UyTTU5V2pMK1kwSFVndmdQUUIzYlNZTktrWFRWTTlGMG1DTzFJMjdwZGFWWUZ5U21ybU5oRU1xRGZwajJLTC9EamNOK0NNTHpmVnJ0YjlweGtvYXM0RFg0YW9MTWMwNlpzSTMzK2JrTXNnMVRpeGFwanBjNm8vZW1WanluSDBhNk1UTVE0cHdYWEZHSlVHUGJDQU09LS0zS1k4ek5NMzhoT2ZDOFVpUUVBNEtBPT0%3D--c061a7b38b0c008c3c04bca75b217621993acb48");

            QNetworkReply *pReply = manager->get(request);
            QEventLoop eventLoop;
            QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();

            QByteArray bytes = pReply->readAll();
            qDebug() << bytes;
        } else if (msgBox.clickedButton() == abortButton) {
            // abort
        }

}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << ui->lineEdit->text();
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QString url = "https://minerooms.com/console/"+serverId;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Cookie","__cfduid=d12e7ff4fe25c0162d956d594642f23601582446396;_ga=GA1.2.500865953.1582446399;_gat=1;_gid=GA1.2.1164300349.1582446399;_mineroom_web_session=SGJCd3ptck9RZXB0ZWZwK3UwK29XTzdydHNiSW8vb1dQUDc4RjlCWVFPT2hiSFJRRTdTWUlkMVhBSzBSM0tKay9sNC9YVlVPcEs0cmNXK2Vzemg2WTI3am94SVYyVVRzMktLa1A0TGlHOVpTanFQUWZvNGsxTWZFbURQcVpnNW1ac1VDM1VnWXpEMGFUVkFvYkNrRTRvL3UyTTU5V2pMK1kwSFVndmdQUUIzYlNZTktrWFRWTTlGMG1DTzFJMjdwZGFWWUZ5U21ybU5oRU1xRGZwajJLTC9EamNOK0NNTHpmVnJ0YjlweGtvYXM0RFg0YW9MTWMwNlpzSTMzK2JrTXNnMVRpeGFwanBjNm8vZW1WanluSDBhNk1UTVE0cHdYWEZHSlVHUGJDQU09LS0zS1k4ek5NMzhoT2ZDOFVpUUVBNEtBPT0%3D--c061a7b38b0c008c3c04bca75b217621993acb48");
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded; charset=utf-8");
    QString sendText = ui->lineEdit->text();
    QString input = "";
    QString tellRaw1 = "";
    QString tellRaw2 = "";
    if(sendText[0] == ':' && sendText[1] == 's' && sendText[2] == 'a' && sendText[3] == 'y' && sendText[4] == ' ')
    {
        for(int i=5;i<sendText.length();i++)
        {
            tellRaw1 += sendText[i];
        }
        tellRaw2 = "tellraw @a \"<PleasantGoat84> "+tellRaw1+"\"";
        input = tellRaw2;
    }else{
     input = ui->lineEdit->text();
//     /"msg="+ui->lineEdit->text().toUtf8().toPercentEncoding()+"&data-action=save_file";
    }
    auto data = "msg="+input.toUtf8().toPercentEncoding()+"&data-action=save_file";
    QNetworkReply *pReply = manager->post(request,data);
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray bytes = pReply->readAll();
    qDebug() << bytes;
    ui->lineEdit->setText("");
}
