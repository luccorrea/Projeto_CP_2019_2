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
#ifndef AURORA_VECTOR_H
#define AURORA_VECTOR_H

#include <aurora/Global.h>

#include <ostream>

// In�cio de "namespace" da biblioteca
AURORA_NAMESPACE_BEGIN

// Declara��o de tipo incompleto no cabe�alho evita depend�ncia c�clica de arquivos
class Matrix2;
class Matrix3;
class Matrix4;

// Vetor real 1x2
class Vector2 {
public:
    // Componentes do vetor
    double x, y;

    // Construtor padr�o (vetor zero)
    Vector2();
    // Construtor c�pia
    Vector2(const Vector2 & vector2);
    // Construtor para valores iniciais
    Vector2(double x, double y);
    // Destrutor padr�o
    ~Vector2();

    // Sobrecarga da opera��o "vetor[i]" (retorno mut�vel)
    double & operator [](size_t i);
    // Sobrecarga da opera��o "vetor[i]" (retorno imut�vel)
    const double & operator [](size_t i) const;
    // Sobrecarga da opera��o "+vetor"
    Vector2 operator +() const;
    // Sobrecarga da opera��o "-vetor"
    Vector2 operator -() const;
    // Sobrecarga da opera��o "vetorA + vetorB"
    Vector2 operator +(const Vector2 & rhs) const;
    // Sobrecarga da opera��o "vetorA - vetorB"
    Vector2 operator -(const Vector2 & rhs) const;
    // Sobrecarga da opera��o "vetor * matriz2"
    Vector2 operator *(const Matrix2 & rhs) const;
    // Sobrecarga da opera��o "matriz2 * vetor"
    friend Vector2 operator *(const Matrix2 & lhs, const Vector2 & rhs);
    // Sobrecarga da opera��o "vetor * matriz3"
    Vector2 operator *(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "matriz3 * vetor"
    friend Vector2 operator *(const Matrix3 & lhs, const Vector2 & rhs);
    // Sobrecarga da opera��o "vetor * escalar"
    Vector2 operator *(double rhs) const;
    // Sobrecarga da opera��o "escalar * vetor"
    friend Vector2 operator *(double lhs, const Vector2 & rhs);
    // Sobrecarga da opera��o "vetor / escalar"
    Vector2 operator /(double rhs) const;
    // Sobrecarga da opera��o "escalar / vetor"
    friend Vector2 operator /(double lhs, const Vector2 & rhs);
    // Sobrecarga da opera��o "vetorA += vetorB"
    Vector2 & operator +=(const Vector2 & rhs);
    // Sobrecarga da opera��o "vetorA -= vetorB"
    Vector2 & operator -=(const Vector2 & rhs);
    // Sobrecarga da opera��o "vetor *= matrix2"
    Vector2 & operator *=(const Matrix2 & rhs);
    // Sobrecarga da opera��o "vetor *= matrix3"
    Vector2 & operator *=(const Matrix3 & rhs);
    // Sobrecarga da opera��o "vetor *= escalar"
    Vector2 & operator *=(double rhs);
    // Sobrecarga da opera��o "vetor /= escalar"
    Vector2 & operator /=(double rhs);
    // Sobrecarga da opera��o "vetorA == vetorB"
    bool operator ==(const Vector2 & rhs) const;
    // Sobrecarga da opera��o "vetorA != vetorB"
    bool operator !=(const Vector2 & rhs) const;
    // Sobrecarga da opera��o "sa�da << vetor" (imprimir sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Vector2 & rhs);

    // Retorna produto escalar
    double dot(const Vector2 & rhs) const;
    // Retorna produto vetorial
    double cross(const Vector2 & rhs) const;
    // Normaliza vetor (vetor unit�rio)
    Vector2 & normalize();
    // Retorna comprimento do vetor ao quadrado
    double length2() const;
    // Retorna comprimento do vetor
    double length() const;
    // Retorna valores m�nimos (por componente)
    Vector2 min(const Vector2 & rhs) const;
    // Retorna valores m�ximos (por componente)
    Vector2 max(const Vector2 & rhs) const;
};

// Vetor real 1x3
class Vector3 {
public:
    // Componentes do vetor
    double x, y, z;

    // Construtor padr�o (vetor zero)
    Vector3();
    // Construtor c�pia
    Vector3(const Vector3 & vector3);
    // Construtor para valores iniciais
    Vector3(double x, double y, double z);
    // Destrutor padr�o
    ~Vector3();

    // Sobrecarga da opera��o "vetor[i]" (retorno mut�vel)
    double & operator [](size_t i);
    // Sobrecarga da opera��o "vetor[i]" (retorno imut�vel)
    const double & operator [](size_t i) const;
    // Sobrecarga da opera��o "+vetor"
    Vector3 operator +() const;
    // Sobrecarga da opera��o "-vetor"
    Vector3 operator -() const;
    // Sobrecarga da opera��o "vetorA + vetorB"
    Vector3 operator +(const Vector3 & rhs) const;
    // Sobrecarga da opera��o "vetorA - vetorB"
    Vector3 operator -(const Vector3 & rhs) const;
    // Sobrecarga da opera��o "vetor * matriz3"
    Vector3 operator *(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "matriz3 * vetor"
    friend Vector3 operator *(const Matrix3 & lhs, const Vector3 & rhs);
    // Sobrecarga da opera��o "vetor * matriz4"
    Vector3 operator *(const Matrix4 & rhs) const;
    // Sobrecarga da opera��o "matriz4 * vetor"
    friend Vector3 operator *(const Matrix4 & lhs, const Vector3 & rhs);
    // Sobrecarga da opera��o "vetor * escalar"
    Vector3 operator *(double rhs) const;
    // Sobrecarga da opera��o "escalar * vetor"
    friend Vector3 operator *(double lhs, const Vector3 & rhs);
    // Sobrecarga da opera��o "vetor / escalar"
    Vector3 operator /(double rhs) const;
    // Sobrecarga da opera��o "escalar / vetor"
    friend Vector3 operator /(double lhs, const Vector3 & rhs);
    // Sobrecarga da opera��o "vetorA += vetorB"
    Vector3 & operator +=(const Vector3 & rhs);
    // Sobrecarga da opera��o "vetorA -= vetorB"
    Vector3 & operator -=(const Vector3 & rhs);
    // Sobrecarga da opera��o "vetor *= matrix3"
    Vector3 & operator *=(const Matrix3 & rhs);
    // Sobrecarga da opera��o "vetor *= matrix4"
    Vector3 & operator *=(const Matrix4 & rhs);
    // Sobrecarga da opera��o "vetor *= escalar"
    Vector3 & operator *=(double rhs);
    // Sobrecarga da opera��o "vetor /= escalar"
    Vector3 & operator /=(double rhs);
    // Sobrecarga da opera��o "vetorA == vetorB"
    bool operator ==(const Vector3 & rhs) const;
    // Sobrecarga da opera��o "vetorA != vetorB"
    bool operator !=(const Vector3 & rhs) const;
    // Sobrecarga da opera��o "sa�da << vetor" (imprimir sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Vector3 & rhs);

    // Retorna produto escalar
    double dot(const Vector3 & rhs) const;
    // Retorna produto triplo ou misto
    double triple(const Vector3 & a, const Vector3 & b) const;
    // Retorna produto vetorial
    Vector3 cross(const Vector3 & rhs) const;
    // Normaliza vetor (vetor unit�rio)
    Vector3 & normalize();
    // Retorna comprimento do vetor ao quadrado
    double length2() const;
    // Retorna comprimento do vetor
    double length() const;
    // Retorna valores m�nimos (por componente)
    Vector3 min(const Vector3 & rhs) const;
    // Retorna valores m�ximos (por componente)
    Vector3 max(const Vector3 & rhs) const;
};

// Fim de "namespace" da biblioteca
AURORA_NAMESPACE_END

#endif
