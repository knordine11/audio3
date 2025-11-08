// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QAudioDevice)
QT_FORWARD_DECLARE_CLASS(QAudioInput)
QT_FORWARD_DECLARE_CLASS(QAudioSource)
QT_FORWARD_DECLARE_CLASS(QChart)
QT_FORWARD_DECLARE_CLASS(QLineSeries)

class XYSeriesIODevice;

class Widget : public QWidget
{
    Q_OBJECT
public:

    void stop_mic_streem();
    explicit Widget(const QAudioDevice &deviceInfo, QWidget *parent = nullptr);
    ~Widget();

    void start_mic_stream();
    void stop_mic_stream();
    QAudioSource *m_audioSource = nullptr;

private:

    XYSeriesIODevice *m_device = nullptr;
    QChart *m_chart = nullptr;
    QLineSeries *m_series = nullptr;
    QAudioInput *m_audioInput = nullptr;
};

#endif
