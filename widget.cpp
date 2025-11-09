// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "widget.h"
#include "fftstuff.h"
#include "xyseriesiodevice.h"

#include <QAudioDevice>
#include <QAudioInput>
#include <QAudioSource>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout>

#include <QTimer>
#include <QDebug>
int fr_start = 0;
int fr_size= 2048*2;
int fr_end = fr_size - fr_start;

Widget::Widget(const QAudioDevice &deviceInfo, QWidget *parent)
    : QWidget(parent)

    , m_chart(new QChart)
    , m_series(new QLineSeries)
{
    auto chartView = new QChartView(m_chart);
    m_chart->addSeries(m_series);
    auto axisX = new QValueAxis;
    axisX->setRange(0, XYSeriesIODevice::sampleCount);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    auto axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    axisY->setTitleText("Audio level");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    m_chart->legend()->hide();
    m_chart->setTitle("Data from the microphone (" + deviceInfo.description() + ')');

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);

    // Auido

    m_audioInput = new QAudioInput(deviceInfo, this);

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleFormat(QAudioFormat::UInt8);

    m_audioSource = new QAudioSource(deviceInfo, formatAudio);
    m_audioSource->setBufferSize(1000);

    m_device = new XYSeriesIODevice(m_series, this);
    m_device->open(QIODevice::WriteOnly);
    start_mic_stream();
}

Widget::~Widget()
{
    m_audioSource->stop();
    m_device->close();
    delete m_audioInput;
    delete m_device;
}


void Widget::start_mic_stream()
{
    m_audioSource->start(m_device);
    qDebug() << "started";
    QTimer::singleShot(100, this, &Widget::stop_mic_stream);
    qDebug() << " AFTER QTimer ";
}

void Widget::stop_mic_stream()
{
    m_audioSource->stop();
    qDebug() << "mic STOPPED ";
    m_device->close();
    qDebug() << "device CLOSED ";
    FftStuff pa;

    pa.make_sin(100,fr_start,fr_size);
    pa.DoIt(fr_start,fr_size);
    // pa.DoIt(100,fr_size);
}
