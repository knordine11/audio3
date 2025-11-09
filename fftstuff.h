// #ifndef FFTSTUFF_H
// #define FFTSTUFF_H

// #include <QObject>
// #include "fftw3/fftw3.h"
// #include <cmath>

// class FftStuff : public QObject
// {
//     Q_OBJECT
// public:
//     explicit FftStuff(QObject *parent = nullptr);
//     void DoIt();
//     static double abs(fftw_complex);
//     static double bin_freq(size_t, size_t, double);


// signals:
// };

// #endif // FFTSTUFF_H
//-------------------------------------------
#ifndef FFTSTUFF_H
#define FFTSTUFF_H

#include <QObject>
#include "fftw3/fftw3.h"
#include <cmath>
// #include <QChart>

extern double rec_arr[];
extern int rec_arr_cnt;
extern int arr_size;

class FftStuff : public QObject
{
    Q_OBJECT
public:
    explicit FftStuff(QObject *parent = nullptr);
    // void DoIt();
    void DoIt(int beg, int lengh);
    void DoIt2(double freq);
    static double abs(fftw_complex);
    static double bin_freq(size_t, size_t, double);
    void bin_to_freq(int bin);

    void make_sin(double freq ,int beg, int leng);
    void look_rec_arr(int beg, int end);
    void graph_rec_arr(int beg, int end);



signals:
};

#endif // FFTSTUFF_H
