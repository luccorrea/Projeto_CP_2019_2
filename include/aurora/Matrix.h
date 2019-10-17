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
#ifndef AURORA_MATRIX_H
#define AURORA_MATRIX_H

#include <aurora/Global.h>

#include <ostream>

// In�cio de "namespace" da biblioteca
AURORA_NAMESPACE_BEGIN

// Declara��o de tipo incompleto no cabe�alho evita depend�ncia c�clica de arquivos
class Vector2;
class Vector3;

// Matriz real 2x2
class Matrix2 {
private:
    // Elementos da matriz
    double m[2][2];

public:
    // Construtor padr�o (matriz zero)
    Matrix2();
    // Construtor c�pia
    Matrix2(const Matrix2 & matrix2);
    // Construtor para valores iniciais
    Matrix2(
        double m00, double m01,
        double m10, double m11);
    // Destrutor padr�o
    ~Matrix2();

    // Sobrecarga da opera��o "matriz[i]" permite opera��o "matriz[i][j]" (retorno mut�vel)
    double * operator [](size_t i);
    // Sobrecarga da opera��o "matriz[i]" permite opera��o "matriz[i][j]" (retorno imut�vel)
    const double * operator [](size_t i) const;
    // Sobrecarga da opera��o "+matriz"
    Matrix2 operator +() const;
    // Sobrecarga da opera��o "-matriz"
    Matrix2 operator -() const;
    // Sobrecarga da opera��o "matrizA + matrizB"
    Matrix2 operator +(const Matrix2 & rhs) const;
    // Sobrecarga da opera��o "matrizA - matrizB"
    Matrix2 operator -(const Matrix2 & rhs) const;
    // Sobrecarga da opera��o "matrizA * matrizB"
    Matrix2 operator *(const Matrix2 & rhs) const;
    // Sobrecarga da opera��o "matriz * escalar"
    Matrix2 operator *(double rhs) const;
    // Sobrecarga da opera��o "escalar * matriz"
    friend Matrix2 operator *(double lhs, const Matrix2 & rhs);
    // Sobrecarga da opera��o "matrizA / matrizB" realiza opera��o "matrizA.inverse(matrizB)"
    Matrix2 operator /(const Matrix2 & rhs) const;
    // Sobrecarga da opera��o "matriz / escalar"
    Matrix2 operator /(double rhs) const;
    // Sobrecarga da opera��o "matrizA += matrizB"
    Matrix2 & operator +=(const Matrix2 & rhs);
    // Sobrecarga da opera��o "matrizA -= matrizB"
    Matrix2 & operator -=(const Matrix2 & rhs);
    // Sobrecarga da opera��o "matrizA *= matrizB"
    Matrix2 & operator *=(const Matrix2 & rhs);
    // Sobrecarga da opera��o "matriz *= escalar"
    Matrix2 & operator *=(double rhs);
    // Sobrecarga da opera��o "matrizA /= matrizB" realiza opera��o "matrizA = matrizA.inverse(matrizB)"
    Matrix2 & operator /=(const Matrix2 & rhs);
    // Sobrecarga da opera��o "matriz /= escalar"
    Matrix2 & operator /=(double rhs);
    // Sobrecarga da opera��o "matrizA == matrizB"
    bool operator ==(const Matrix2 & rhs) const;
    // Sobrecarga da opera��o "matrizA != matrizB"
    bool operator !=(const Matrix2 & rhs) const;
    // Sobrecarga da opera��o "sa�da << matriz" (imprimir sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Matrix2 & rhs);

    // Retorna determinante
    double determinant() const;
    // Retorna tra�o
    double trace() const;
    // Retorna menor da submatriz sem a linha "i" e coluna "j"
    double minor(size_t i, size_t j) const;
    // Transp�e matriz (matriz transposta)
    Matrix2 & transpose();
    // Retorna inversa
    Matrix2 inverse() const;
    // Retorna adjunta
    Matrix2 adjugate() const;
};

// Matriz real 3x3
class Matrix3 {
private:
    // Elementos da matriz
    double m[3][3];

public:
    // Construtor padr�o (matriz zero)
    Matrix3();
    // Construtor c�pia
    Matrix3(const Matrix3 & matrix3);
    // Construtor para valores iniciais
    Matrix3(
        double m00, double m01, double m02,
        double m10, double m11, double m12,
        double m20, double m21, double m22);
    // Destrutor padr�o
    ~Matrix3();

    // Sobrecarga da opera��o "matriz[i]" permite opera��o "matriz[i][j]" (retorno mut�vel)
    double * operator [](size_t i);
    // Sobrecarga da opera��o "matriz[i]" permite opera��o "matriz[i][j]" (retorno imut�vel)
    const double * operator [](size_t i) const;
    // Sobrecarga da opera��o "+matriz"
    Matrix3 operator +() const;
    // Sobrecarga da opera��o "-matriz"
    Matrix3 operator -() const;
    // Sobrecarga da opera��o "matrizA + matrizB"
    Matrix3 operator +(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "matrizA - matrizB"
    Matrix3 operator -(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "matrizA * matrizB"
    Matrix3 operator *(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "matriz * escalar"
    Matrix3 operator *(double rhs) const;
    // Sobrecarga da opera��o "escalar * matriz"
    friend Matrix3 operator *(double lhs, const Matrix3 & rhs);
    // Sobrecarga da opera��o "matrizA / matrizB" realiza opera��o "matrizA.inverse(matrizB)"
    Matrix3 operator /(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "matriz / escalar"
    Matrix3 operator /(double rhs) const;
    // Sobrecarga da opera��o "matrizA += matrizB"
    Matrix3 & operator +=(const Matrix3 & rhs);
    // Sobrecarga da opera��o "matrizA -= matrizB"
    Matrix3 & operator -=(const Matrix3 & rhs);
    // Sobrecarga da opera��o "matrizA *= matrizB"
    Matrix3 & operator *=(const Matrix3 & rhs);
    // Sobrecarga da opera��o "matriz *= escalar"
    Matrix3 & operator *=(double rhs);
    // Sobrecarga da opera��o "matrizA /= matrizB" realiza opera��o "matrizA = matrizA.inverse(matrizB)"
    Matrix3 & operator /=(const Matrix3 & rhs);
    // Sobrecarga da opera��o "matriz /= escalar"
    Matrix3 & operator /=(double rhs);
    // Sobrecarga da opera��o "matrizA == matrizB"
    bool operator ==(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "matrizA != matrizB"
    bool operator !=(const Matrix3 & rhs) const;
    // Sobrecarga da opera��o "sa�da << matriz" (imprimir sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Matrix3 & rhs);

    // Configura como matriz identidade
    Matrix3 & setIdentity();
    // Configura como matriz de transla��o "T" a partir dos deslocamentos "(dx, dy)"
    Matrix3 & setTranslation(const Vector2 & translation);
    // Configura como matriz de rota��o "R" anti-hor�ria a partir de um �ngulo de Euler "a" em radiano
    Matrix3 & setRotation(double rotation);
    // Configura como matriz de escala "S" a partir dos fatores de escala "(sx, sy)"
    Matrix3 & setScaling(const Vector2 & scaling);
    // Configura como matriz de deforma��o "Sh" a partir dos componentes de deforma��o "(shx, shy)"
    Matrix3 & setShearing(const Vector2 & shearing);
    // Configura como matriz de transforma��o "M = S Sh R T"
    Matrix3 & setTransformation(
        const Vector2 & translation, double rotation,
        const Vector2 & scaling, const Vector2 & shearing);

    // Retorna determinante
    double determinant() const;
    // Retorna tra�o
    double trace() const;
    // Retorna menor da submatriz sem a linha "i" e coluna "j"
    double minor(size_t i, size_t j) const;
    // Transp�e matriz (matriz transposta)
    Matrix3 & transpose();
    // Retorna inversa
    Matrix3 inverse() const;
    // Retorna adjunta
    Matrix3 adjugate() const;
};

// Matriz real 4x4
class Matrix4 {
private:
    // Elementos da matriz
    double m[4][4];

public:
    // Construtor padr�o (matriz zero)
    Matrix4();
    // Construtor c�pia
    Matrix4(const Matrix4 & matrix4);
    // Construtor para valores iniciais
    Matrix4(
        double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33);
    // Destrutor padr�o
    ~Matrix4();

    // Sobrecarga da opera��o "matriz[i]" permite opera��o "matriz[i][j]" (retorno mut�vel)
    double * operator [](size_t i);
    // Sobrecarga da opera��o "matriz[i]" permite opera��o "matriz[i][j]" (retorno imut�vel)
    const double * operator [](size_t i) const;
    // Sobrecarga da opera��o "+matriz"
    Matrix4 operator +() const;
    // Sobrecarga da opera��o "-matriz"
    Matrix4 operator -() const;
    // Sobrecarga da opera��o "matrizA + matrizB"
    Matrix4 operator +(const Matrix4 & rhs) const;
    // Sobrecarga da opera��o "matrizA - matrizB"
    Matrix4 operator -(const Matrix4 & rhs) const;
    // Sobrecarga da opera��o "matrizA * matrizB"
    Matrix4 operator *(const Matrix4 & rhs) const;
    // Sobrecarga da opera��o "matriz * escalar"
    Matrix4 operator *(double rhs) const;
    // Sobrecarga da opera��o "escalar * matriz"
    friend Matrix4 operator *(double lhs, const Matrix4 & rhs);
    // Sobrecarga da opera��o "matrizA / matrizB" realiza opera��o "matrizA.inverse(matrizB)"
    Matrix4 operator /(const Matrix4 & rhs) const;
    // Sobrecarga da opera��o "matriz / escalar"
    Matrix4 operator /(double rhs) const;
    // Sobrecarga da opera��o "matrizA += matrizB"
    Matrix4 & operator +=(const Matrix4 & rhs);
    // Sobrecarga da opera��o "matrizA -= matrizB"
    Matrix4 & operator -=(const Matrix4 & rhs);
    // Sobrecarga da opera��o "matrizA *= matrizB"
    Matrix4 & operator *=(const Matrix4 & rhs);
    // Sobrecarga da opera��o "matriz *= escalar"
    Matrix4 & operator *=(double rhs);
    // Sobrecarga da opera��o "matrizA /= matrizB" realiza opera��o "matrizA = matrizA.inverse(matrizB)"
    Matrix4 & operator /=(const Matrix4 & rhs);
    // Sobrecarga da opera��o "matriz /= escalar"
    Matrix4 & operator /=(double rhs);
    // Sobrecarga da opera��o "matrizA == matrizB"
    bool operator ==(const Matrix4 & rhs) const;
    // Sobrecarga da opera��o "matrizA != matrizB"
    bool operator !=(const Matrix4 & rhs) const;
    // Sobrecarga da opera��o "sa�da << matriz" (imprimir sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Matrix4 & rhs);

    // Configura como matriz identidade
    Matrix4 & setIdentity();
    // Configura como matriz de transla��o "T" a partir dos deslocamentos "(dx, dy, dz)"
    Matrix4 & setTranslation(const Vector3 & translation);
    // Configura como matriz de rota��o "R = Rx Ry Rz" anti-hor�ria a partir dos �ngulos de Euler "(ax, ay, az)" em radiano
    Matrix4 & setRotation(const Vector3 & rotation);
    // Configura como matriz de escala "S" a partir dos fatores de escala "(sx, sy, sz)"
    Matrix4 & setScaling(const Vector3 & scaling);
    // Configura como matriz de deforma��o "Sh" a partir dos componentes de deforma��o "(shxy, shxz, shyz)"
    Matrix4 & setShearing(const Vector3 & shearing);
    // Configura como matriz de transforma��o "M = S Sh R T"
    Matrix4 & setTransformation(
        const Vector3 & translation, const Vector3 & rotation,
        const Vector3 & scaling, const Vector3 & shearing);

    // Retorna determinante
    double determinant() const;
    // Retorna tra�o
    double trace() const;
    // Retorna menor da submatriz sem a linha "i" e coluna "j"
    double minor(size_t i, size_t j) const;
    // Transp�e matriz (matriz transposta)
    Matrix4 & transpose();
    // Retorna inversa
    Matrix4 inverse() const;
    // Retorna adjunta
    Matrix4 adjugate() const;
};

// Fim de "namespace" da biblioteca
AURORA_NAMESPACE_END

#endif
