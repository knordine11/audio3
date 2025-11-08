#include "fftstuff.h"
#include <iostream>
#include "fftw3/fftw3.h"
#include <cmath>
#include <iomanip>

FftStuff::FftStuff(QObject *parent)
    : QObject{parent}
{

}

void FftStuff::DoIt()
{
    fftw_complex* in, * out;
    fftw_plan p;

    const size_t N = 512;
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    double Pi = 3.14159265358979323846;
    double Fs = 44100.0/64;
    double freq = 200.0;
    double T = 1.0 / Fs;
    for (size_t i = 0; i < N; i++)
    {
        in[i][0] = std::cos(2 * Pi * freq * i * T);
        in[i][1] = 0.0;
    }

    fftw_execute(p); /* repeat as needed */

    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    for (size_t i = 0; i < N; i++)
    {
        std::cout << FftStuff::bin_freq(i, N, Fs) << " Hz : " << FftStuff::abs(out[i]) << std::endl;
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

double FftStuff::abs(fftw_complex c)
{
    return std::sqrt(c[0] * c[0] + c[1] * c[1]);
}

double FftStuff::bin_freq(size_t n, size_t Fs, double N)
{
    return n * Fs / N;

}
