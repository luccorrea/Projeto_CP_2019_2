// Copyright (c) 2019, Danilo Peixoto. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Evita redefini��o de s�mbolos do arquivo de cabe�alho (caso j� tenha sido inclu�do)
#ifndef AURORA_MATH_H
#define AURORA_MATH_H

#include <aurora/Global.h>

// Constantes num�ricas
#define AURORA_E 2.71828182845904523536
#define AURORA_PI 3.14159265358979323846
#define AURORA_INV_PI 0.31830988618379067154
#define AURORA_SQRT_2 1.41421356237309504880
#define AURORA_EPSILON 2.2204460492503131e-016
#define AURORA_INFINITY 1.7976931348623158e+308
#define AURORA_THRESHOLD 1.0000000000000000e-006

AURORA_NAMESPACE_BEGIN // In�cio do "namespace" da biblioteca

// Retorna valor delimitado por m�nimo e m�ximo
double clamp(double x, double a, double b);
// Retorna valor delimitado no intervalo [0, 1]
double saturate(double x);
// Converte �ngulo de radiano para grau
double degrees(double x);
// Converte �ngulo de grau para radiano
double radians(double x);

// Fim de "namespace" da biblioteca
AURORA_NAMESPACE_END

#endif
