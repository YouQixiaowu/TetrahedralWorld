// Frances Y. Kuo
//
// Email: <f.kuo@unsw.edu.au>
// School of Mathematics and Statistics
// University of New South Wales
// Sydney NSW 2052, Australia
// 
// Last updated: 21 October 2008
//
//   You may incorporate this source code into your own program 
//   provided that you
//   1) acknowledge the copyright owner in your program and publication
//   2) notify the copyright owner by email
//   3) offer feedback regarding your experience with different direction numbers
//
//
// -----------------------------------------------------------------------------
// Licence pertaining to sobol.cc and the accompanying sets of direction numbers
// -----------------------------------------------------------------------------
// Copyright (c) 2008, Frances Y. Kuo and Stephen Joe
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
// 
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
// 
//     * Neither the names of the copyright holders nor the names of the
//       University of New South Wales and the University of Waikato
//       and its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// -----------------------------------------------------------------------------
#pragma once

#include <cstdlib> // *** Thanks to Leonhard Gruenschloss and Mike Giles   ***
#include <cmath>   // *** for pointing out the change in new g++ compilers ***
#include <random>
#include <vector> 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

template<class T>
class Sobol
{
private:
    class Vec
    {
    private:
        T* _ptrData;
        size_t _dim;
    public:
        Vec(T* ptrData, size_t dim) :
            _ptrData(ptrData),
            _dim(dim)
        {
        }
        /* 只读的 */
        T operator[](size_t i)
        {
            if (i < _dim)
            {
                return _ptrData[i];
            }
            else
            {
                throw "索引超出维度范围";
            }
        }
    };

    std::vector<T> _points;
    size_t _number;
    size_t _dimension;
public:
    /* 返回字节长度 */
    size_t len()
    {
        return _number * _dimension * sizeof(T);
    }
    /* 返回元素数量 */
    size_t size()
    {
        return  _number * _dimension;
    }
    /* 数据数量（行数） */
    size_t num()
    {
        return _number;
    }
    /* 维度（列数） */
    size_t dim()
    {
        return _dimension;
    }
    /* 获取数据指针 */
    T* data()
    {
        return _points;
    }

    Vec operator[](size_t i)
    {
        if (i < _number)
        {
            return Vec(&(_points[i * _dimension]), _dimension);
        }
        else
        {
            throw "索引超出数量范围";
        }
    }

    /* 打乱次序 */
    void disorder()
    {
        std::vector<int> v(_number);
        for (int i = 0; i < _number; ++i) {
            v[i] = i;
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));
        std::vector<T> NEW_POINTS(_number * _dimension);
        for (int i = 0; i < _number; ++i) {
            for (size_t j = 0; j < _dimension; j++)
            {
                NEW_POINTS[i * _dimension + j] = _points[v[i] * _dimension + j];
            }
        }
        _points.swap(NEW_POINTS);
    }

    Sobol(size_t N, size_t D) :
        _points(N*D),
        _number(N),
        _dimension(D)
    {
        std::ifstream infile("new-joe-kuo-6.21201", std::ios::in);
        if (!infile) {
            std::cout << "Input file containing direction numbers cannot be found!\n";
            exit(1);
        }
        char buffer[1000];
        infile.getline(buffer, 1000, '\n');

        // L = max number of bits needed 
        unsigned L = (unsigned)ceil(log((double)N) / log(2.0));

        // C[i] = index from the right of the first zero bit of i
        unsigned* C = new unsigned[N];
        C[0] = 1;
        for (unsigned i = 1; i <= N - 1; i++) {
            C[i] = 1;
            unsigned value = i;
            while (value & 1) {
                value >>= 1;
                C[i]++;
            }
        }

        // POINTS[i][j] = the jth component of the ith point
        //                with i indexed from 0 to N-1 and j indexed from 0 to D-1
        for (unsigned j = 0; j <= D - 1; j++) _points[0 * D + j] = 0;

        // ----- Compute the first dimension -----

        // Compute direction numbers V[1] to V[L], scaled by pow(2,32)
        unsigned* V = new unsigned[L + (size_t)1];
        for (unsigned i = 1; i <= L; i++) V[i] = 1 << (32 - i); // all m's = 1

        // Evalulate X[0] to X[N-1], scaled by pow(2,32)
        unsigned* X = new unsigned[N];
        X[0] = 0;
        for (unsigned i = 1; i <= N - 1; i++) {
            X[i] = X[i - 1] ^ V[C[i - 1]];
            _points[i * D + 0] = (T)X[i] / pow(2.0, 32); // *** the actual points
            //        ^ 0 for first dimension
        }

        // Clean up
        delete[] V;
        delete[] X;


        // ----- Compute the remaining dimensions -----
        for (unsigned j = 1; j <= D - 1; j++) {

            // Read in parameters from file 
            unsigned d, s;
            unsigned a;
            infile >> d >> s >> a;
            unsigned* m = new unsigned[s + (size_t)1];
            for (unsigned i = 1; i <= s; i++) infile >> m[i];

            // Compute direction numbers V[1] to V[L], scaled by pow(2,32)
            unsigned* V = new unsigned[L + (size_t)1];
            if (L <= s) {
                for (unsigned i = 1; i <= L; i++) V[i] = m[i] << (32 - i);
            }
            else {
                for (unsigned i = 1; i <= s; i++) V[i] = m[i] << (32 - i);
                for (unsigned i = s + 1; i <= L; i++) {
                    V[i] = V[i - s] ^ (V[i - s] >> s);
                    for (unsigned k = 1; k <= s - 1; k++)
                        V[i] ^= (((a >> (s - 1 - k)) & 1) * V[i - k]);
                }
            }

            // Evalulate X[0] to X[N-1], scaled by pow(2,32)
            unsigned* X = new unsigned[N];
            X[0] = 0;
            for (unsigned i = 1; i <= N - 1; i++) {
                X[i] = X[i - 1] ^ V[C[i - 1]];
                _points[i * D + j] = (T)X[i] / pow(2.0, 32); // *** the actual points
                //             ^ j for dimension (j+1)
            }

            // Clean up
            delete[] m;
            delete[] V;
            delete[] X;
        }
        delete[] C;
    }

    ~Sobol()
    {
    }

};

/*
int main(void)
{
    // display points
    std::cout << std::setprecision(20);
    size_t N = 10000;
    size_t D = 2;
    Sobol<float> sobol_c(N, D);
    Sobol<float> sobol_v(N, D);
    sobol_v.disorder();

    std::ofstream file("data.txt");
    for (unsigned i = 0; i <= N - 1; i++) {
        for (unsigned j = 0; j <= D - 1; j++) file << sobol_c[i][j] << " ";
        for (unsigned j = 0; j <= D - 1; j++) file << sobol_v[i][j] << " ";
        file << std::endl;
    }
    file << std::endl;

    return 0;
}
*/