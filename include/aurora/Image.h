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
#ifndef AURORA_IMAGE_H
#define AURORA_IMAGE_H

#include <aurora/Global.h>

#include <vector>
#include <ostream>

// In�cio de "namespace" da biblioteca
AURORA_NAMESPACE_BEGIN

// Declara��o de tipo incompleto no cabe�alho evita depend�ncia c�clica de arquivos
class Color3;
class Color4;

// Imagem de pixels RGB
class Image3 {
private:
    size_t width; // Resolu��o horizontal
    size_t height; // Resolu��o vertical
    std::vector<Color3> pixels; // Matriz de pixels RGB no formato linha majorit�ria

public:
    // Construtor padr�o (imagem nula)
    Image3();
    // Construtor c�pia
    Image3(const Image3 & image3);
    // Construtor para aloca��o de pixels RGB
    Image3(size_t width, size_t height);
    // Construtor para par�metros iniciais
    Image3(size_t width, size_t height, const std::vector<Color3> & pixels);
    // Destrutor padr�o
    ~Image3();

    // Sobrecarga da opera��o "imagem[i]" (retorno mut�vel)
    Color3 & operator [](size_t i);
    // Sobrecarga da opera��o "imagem[i]" (retorno imut�vel)
    const Color3 & operator [](size_t i) const;
    // Sobrecarga da opera��o "imagem(i, j)" (retorno mut�vel)
    Color3 & operator ()(size_t i, size_t j);
    // Sobrecarga da opera��o "imagem(i, j)" (retorno imut�vel)
    const Color3 & operator ()(size_t i, size_t j) const;
    // Sobrecarga da opera��o "+imagem"
    Image3 operator +() const;
    // Sobrecarga da opera��o "-imagem"
    Image3 operator -() const;
    // Sobrecarga da opera��o "imagemA + imagemB"
    Image3 operator +(const Image3 & rhs) const;
    // Sobrecarga da opera��o "imagemA - imagemB"
    Image3 operator -(const Image3 & rhs) const;
    // Sobrecarga da opera��o "imagem * escalar"
    Image3 operator *(double rhs) const;
    // Sobrecarga da opera��o "escalar * imagem"
    friend Image3 operator *(double lhs, const Image3 & rhs);
    // Sobrecarga da opera��o "imagem / escalar"
    Image3 operator /(double rhs) const;
    // Sobrecarga da opera��o "imagemA += imagemB"
    Image3 & operator +=(const Image3 & rhs);
    // Sobrecarga da opera��o "imagemA -= imagemB"
    Image3 & operator -=(const Image3 & rhs);
    // Sobrecarga da opera��o "imagem *= escalar"
    Image3 & operator *=(double rhs);
    // Sobrecarga da opera��o "imagem /= escalar"
    Image3 & operator /=(double rhs);
    // Sobrecarga da opera��o "imagemA == imagemB"
    bool operator ==(const Image3 & rhs) const;
    // Sobrecarga da opera��o "imagemA != imagemB"
    bool operator !=(const Image3 & rhs) const;
    // Sobrecarga da opera��o "sa�da << imagem" (imprimir informa��es na sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Image3 & rhs);

    // Configura um pixel RGB pelos �ndices
    Image3 & setPixel(size_t i, size_t j, const Color3 & pixel);
    // Retorna pixel RGB pelos �ndices
    const Color3 & getPixel(size_t i, size_t j) const;
    // Retorna resolu��o horizontal
    size_t getWidth() const;
    // Retorna resolu��o vertical
    size_t getHeight() const;
    // Retorna n�mero de pixels
    size_t getPixelCount() const;
    // Retorna rela��o entre resolu��o horizontal e vertical (propor��o)
    double getAspectRatio() const;

    // Cria imagem por c�pia
    Image3 & create(const Image3 & image3);
    // Cria imagem alocando mem�ria para pixels RGB
    Image3 & create(size_t width, size_t height);
    // Cria imagem com par�metros iniciais
    Image3 & create(size_t width, size_t height, const std::vector<Color3> & pixels);

    // Aplica corre��o gamma � imagem
    Image3 & applyGamma(double gamma);
    // Aplica corre��o de exposi��o � imagem
    Image3 & applyExposure(double exposure);
    // Satura cor (linear)
    Image3 & saturate();
};

// Imagem de pixels RGBA
class Image4 {
private:
    size_t width; // Resolu��o horizontal
    size_t height; // Resolu��o vertical
    std::vector<Color4> pixels; // Matriz de pixels RGBA no formato linha majorit�ria

public:
    // Construtor padr�o (imagem nula)
    Image4();
    // Construtor c�pia
    Image4(const Image4 & image4);
    // Construtor para aloca��o de pixels RGBA
    Image4(size_t width, size_t height);
    // Construtor para par�metros iniciais
    Image4(size_t width, size_t height, const std::vector<Color4> & pixels);
    // Destrutor padr�o
    ~Image4();

    // Sobrecarga da opera��o "imagem[i]" (retorno mut�vel)
    Color4 & operator [](size_t i);
    // Sobrecarga da opera��o "imagem[i]" (retorno imut�vel)
    const Color4 & operator [](size_t i) const;
    // Sobrecarga da opera��o "imagem(i, j)" (retorno mut�vel)
    Color4 & operator ()(size_t i, size_t j);
    // Sobrecarga da opera��o "imagem(i, j)" (retorno imut�vel)
    const Color4 & operator ()(size_t i, size_t j) const;
    // Sobrecarga da opera��o "+imagem"
    Image4 operator +() const;
    // Sobrecarga da opera��o "-imagem"
    Image4 operator -() const;
    // Sobrecarga da opera��o "imagemA + imagemB"
    Image4 operator +(const Image4 & rhs) const;
    // Sobrecarga da opera��o "imagemA - imagemB"
    Image4 operator -(const Image4 & rhs) const;
    // Sobrecarga da opera��o "imagem * escalar"
    Image4 operator *(double rhs) const;
    // Sobrecarga da opera��o "escalar * imagem"
    friend Image4 operator *(double lhs, const Image4 & rhs);
    // Sobrecarga da opera��o "imagem / escalar"
    Image4 operator /(double rhs) const;
    // Sobrecarga da opera��o "imagemA += imagemB"
    Image4 & operator +=(const Image4 & rhs);
    // Sobrecarga da opera��o "imagemA -= imagemB"
    Image4 & operator -=(const Image4 & rhs);
    // Sobrecarga da opera��o "imagem *= escalar"
    Image4 & operator *=(double rhs);
    // Sobrecarga da opera��o "imagem /= escalar"
    Image4 & operator /=(double rhs);
    // Sobrecarga da opera��o "imagemA == imagemB"
    bool operator ==(const Image4 & rhs) const;
    // Sobrecarga da opera��o "imagemA != imagemB"
    bool operator !=(const Image4 & rhs) const;
    // Sobrecarga da opera��o "sa�da << imagem" (imprimir informa��es na sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const Image4 & rhs);

    // Configura um pixel RGBA pelos �ndices
    Image4 & setPixel(size_t i, size_t j, const Color4 & pixel);
    // Retorna pixel RGBA pelos �ndices
    const Color4 & getPixel(size_t i, size_t j) const;
    // Retorna resolu��o horizontal
    size_t getWidth() const;
    // Retorna resolu��o vertical
    size_t getHeight() const;
    // Retorna n�mero de pixels
    size_t getPixelCount() const;
    // Retorna rela��o entre resolu��o horizontal e vertical (propor��o)
    double getAspectRatio() const;

    // Cria imagem por c�pia
    Image4 & create(const Image4 & image4);
    // Cria imagem alocando mem�ria para pixels RGBA
    Image4 & create(size_t width, size_t height);
    // Cria imagem com par�metros iniciais
    Image4 & create(size_t width, size_t height, const std::vector<Color4> & pixels);

    // Aplica corre��o gamma � imagem
    Image4 & applyGamma(double gamma);
    // Aplica corre��o de exposi��o � imagem
    Image4 & applyExposure(double exposure);
    // Satura cor (linear)
    Image4 & saturate();
};

// Fim de "namespace" da biblioteca
AURORA_NAMESPACE_END

#endif
