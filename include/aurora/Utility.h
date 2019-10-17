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
#ifndef AURORA_UTILITY_H
#define AURORA_UTILITY_H

#include <aurora/Global.h>

#include <string>

// In�cio de "namespace" da biblioteca
AURORA_NAMESPACE_BEGIN

// Declara��o de tipo incompleto no cabe�alho evita depend�ncia c�clica de arquivos
class Vector2;
class Vector3;
class Color3;
class Color4;
class Image3;
class TriangleMesh;

// L� imagem RGB de um arquivo Netpbm PPM
Image3 * readImage(const std::string & filename);
// Escreve imagem RGB para um arquivo Netpbm PPM
bool writeImage(const std::string & filename, const Image3 * image3);

// L� objeto geom�trico triangulado de um arquivo Wavefront OBJ
TriangleMesh * readMesh(const std::string & filename);
// Escreve objeto geom�trico triangulado para um arquivo Wavefront OBJ
bool writeMesh(const std::string & filename, const TriangleMesh * triangleMesh);

// Retorna coordenadas baric�ntricas de ponto
Vector3 barycentric(
    const Vector3 & point,
    const Vector3 & vertex0, const Vector3 & vertex1, const Vector3 & vertex2);
// Retorna normal de plano definido por tr�s pontos (tri�ngulo)
Vector3 calculateNormal(
    const Vector3 & vertex0, const Vector3 & vertex1, const Vector3 & vertex2);

// Retorna tempo atual em milisegundos (geralmente desde 00:00 horas de 1 de janeiro de 1970 UTC)
size_t time();

// Inicializa gerador de amostras com semente aleat�ria
void randomSeed(size_t seed);
// Retorna amostra aleat�ria uniforme no intervalo real "[0, 1)"
double uniformRandom();
// Retorna amostra alet�ria uniforme (ponto 2D) dentro de c�rculo de raio unit�rio
Vector2 uniformSampleDisk(const Vector2 & sample);
// Retorna amostra alet�ria conc�ntrica (ponto 2D) dentro de c�rculo de raio unit�rio
Vector2 concentricSampleDisk(const Vector2 & sample);
// Retorna amostra aleat�ria uniforme (vetor de dire��o 3D) em hemisf�rio de raio unit�rio
Vector3 uniformSampleHemisphere(const Vector2 & sample);
// Retorna amostra aleat�ria uniforme (vetor de dire��o 3D) em hemisf�rio de raio unit�rio com peso de cosseno
Vector3 uniformSampleCosineWeightedHemisphere(const Vector2 & sample);
// Retorna amostra aleat�ria uniforme (ponto 3D) em superf�cie triangular
Vector3 uniformSampleTriangle(const Vector2 & sample);

// Retorna vetor real 1x3 como cor RGB linear
Color3 toColor3(const Vector3 & vector3);
// Retorna vetor real 1x3 como cor RGBA linear
Color4 toColor4(const Vector3 & vector3);

// Fim de "namespace" da biblioteca
AURORA_NAMESPACE_END

#endif
