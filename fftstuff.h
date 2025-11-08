#ifndef FFTSTUFF_H
#define FFTSTUFF_H

#include <QObject>
#include "fftw3/fftw3.h"
#include <cmath>

class FftStuff : public QObject
{
    Q_OBJECT
public:
    explicit FftStuff(QObject *parent = nullptr);
    void DoIt();
    static double abs(fftw_complex);
    static double bin_freq(size_t, size_t, double);


signals:
};

#endif // FFTSTUFF_H
