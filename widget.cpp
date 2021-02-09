#include "widget.h"
#include "ui_widget.h"
#include "wiegand.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    wiegandInit(D0_PIN, D1_PIN);
    tempo.setSingleShot(true);
    connect(&tempo,&QTimer::timeout,this,&Widget::onTimertempo_timeout);
    tempo.start(500);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onTimertempo_timeout()
{
    int bitLen = wiegandGetPendingBitCount();
    if (bitLen == 0)
        tempo.start(500);
    else
    {
        char data[100];
        QByteArray trame;
        bitLen = wiegandReadData((void *)data, 100);
        int bytes = bitLen / 8 + 1;
        qDebug() <<  bitLen << " " << bytes;
        for (int i = 0; i < bytes; i++)
        {
            trame.push_back(data[i]);
        }
        ui->lineEditCode->setText(trame.toHex().toUpper());
        tempo.start(500);


    }
}

