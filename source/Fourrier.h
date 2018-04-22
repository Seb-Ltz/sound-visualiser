//
// Created by sebas on 21/04/2018.
//


#pragma once

#include <complex>

class Fourrier {

public:
    static void separate(std::complex<double>* a, int n);
    static void fft2(std::complex<double>* X, int N);

};



