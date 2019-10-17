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
#ifndef AURORA_TRIANGLE_MESH_H
#define AURORA_TRIANGLE_MESH_H

#include <aurora/Global.h>

#include <vector>
#include <ostream>

// In�cio de "namespace" da biblioteca
AURORA_NAMESPACE_BEGIN

// Declara��o de tipo incompleto no cabe�alho evita depend�ncia c�clica de arquivos
class Vector2;
class Vector3;

// Geometria representada por tri�ngulos (v�rtices em ordem anti-hor�ria)
class TriangleMesh {
private:
    std::vector<Vector3> vertices; // Lista de v�rtices
    std::vector<Vector3> normals; // Lista de vetores normais
    std::vector<Vector2> textureCoordinates; // Lista de coordenadas de textura
    std::vector<size_t> vertexIndices; // Lista de �ndices de v�rtices por tri�ngulo
    std::vector<size_t> normalIndices; // Lista de �ndices de vetores normais por tri�ngulo
    std::vector<size_t> textureIndices; // Lista de �ndices de coordenadas de textura por tri�ngulo

public:
    // Construtor padr�o (geometria nula)
    TriangleMesh();
    // Construtor c�pia
    TriangleMesh(const TriangleMesh & triangleMesh);
    // Construtor para aloca��o de par�metros
    TriangleMesh(size_t vertexCount, size_t triangleCount,
        size_t normalCount = 0, size_t textureCoordinateCount = 0);
    // Construtor simples para par�metros iniciais
    TriangleMesh(
        const std::vector<Vector3> & vertices,
        const std::vector<size_t> & vertexIndices);
    // Construtor parcial para par�metros iniciais
    TriangleMesh(
        const std::vector<Vector3> & vertices,
        const std::vector<Vector3> & normals,
        const std::vector<size_t> & vertexIndices,
        const std::vector<size_t> & normalIndices);
    // Construtor completo para par�metros iniciais
    TriangleMesh(
        const std::vector<Vector3> & vertices,
        const std::vector<Vector3> & normals,
        const std::vector<Vector2> & textureCoordinates,
        const std::vector<size_t> & vertexIndices,
        const std::vector<size_t> & normalIndices,
        const std::vector<size_t> & textureIndices);
    // Destrutor padr�o
    ~TriangleMesh();

    // Sobrecarga da opera��o "geometriaA == geometriaB"
    bool operator ==(const TriangleMesh & rhs) const;
    // Sobrecarga da opera��o "geometriaA != geometriaB"
    bool operator !=(const TriangleMesh & rhs) const;
    // Sobrecarga da opera��o "sa�da << geometria" (imprimir informa��es na sa�da de dados)
    friend std::ostream & operator <<(std::ostream & lhs, const TriangleMesh & rhs);

    // Configura lista de v�rtices
    TriangleMesh & setVertices(const std::vector<Vector3> & vertices);
    // configura lista de vetores normais
    TriangleMesh & setNormals(const std::vector<Vector3> & normals);
    // Configura lista de coordenadas de textura
    TriangleMesh & setTextureCoordinates(const std::vector<Vector2> & textureCoordinates);
    // Configura lista de �ndices de v�rtices por tri�ngulo
    TriangleMesh & setVertexIndices(const std::vector<size_t> & vertexIndices);
    // Configura lista de �ndices de vetores normais por tri�ngulo
    TriangleMesh & setNormalIndices(const std::vector<size_t> & normalIndices);
    // Configura lista de �ndices de coordenadas de textura por tri�ngulo
    TriangleMesh & setTextureIndices(const std::vector<size_t> & textureIndices);
    // Configura v�rtice pelo �ndice
    TriangleMesh & setVertex(size_t i, const Vector3 & vertex);
    // Configura vetor normal pelo �ndice
    TriangleMesh & setNormal(size_t i, const Vector3 & normal);
    // Configura coordenadas de textura pelo �ndice
    TriangleMesh & setTextureCoordinates(size_t i, const Vector2 & textureCoordinates);
    // Configura os �ndices dos v�rtices de um tri�ngulo
    TriangleMesh & setVertexIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Configura os �ndices dos vetores normais de um tri�ngulo
    TriangleMesh & setNormalIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Configura os �ndices das coordenadas de textura de um tri�ngulo
    TriangleMesh & setTextureIndices(size_t i, size_t v0, size_t v1, size_t v2);
    // Retorna lista de v�rtices
    const std::vector<Vector3> & getVertices() const;
    // Retorna lista de vetores normais
    const std::vector<Vector3> & getNormals() const;
    // Retorna lista de coordenadas de textura
    const std::vector<Vector2> & getTextureCoordinates() const;
    // Retorna lista de �ndices de v�rtices por tri�ngulo
    const std::vector<size_t> & getVertexIndices() const;
    // Retorna lista de �ndices de vetores normais por tri�ngulo
    const std::vector<size_t> & getNormalIndices() const;
    // Retorna lista de �ndices de coordenadas de textura por tri�ngulo
    const std::vector<size_t> & getTextureIndices() const;
    // Retorna v�rtice pelo �ndice
    const Vector3 & getVertex(size_t i) const;
    // Retorna vetor normal pelo �ndice
    const Vector3 & getNormal(size_t i) const;
    // Retorna coordenadas de textura pelo �ndice
    const Vector2 & getTextureCoordinates(size_t i) const;
    // Retorna �ndices dos v�rtices de um tri�ngulo
    void getVertexIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna �ndices dos vetores normais de um tri�ngulo
    void getNormalIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna �ndices das coordenadas de textura de um tri�ngulo
    void getTextureIndices(size_t i, size_t & v0, size_t & v1, size_t & v2) const;
    // Retorna n�mero de v�rtices
    size_t getVertexCount() const;
    // Retorna n�mero de vetores normais
    size_t getNormalCount() const;
    // Retorna n�mero de coordenadas de textura
    size_t getTextureCoordinateCount() const;
    // Retorna n�mero de tri�ngulos
    size_t getTriangleCount() const;
    // Retorna se geometria tem vetores normais
    bool hasNormals() const;
    // Retorna se geometria tem coordenadas de textura
    bool hasTextureCoordinates() const;

    // Cria geometria por c�pia
    TriangleMesh & create(const TriangleMesh & triangleMesh);
    // Cria geometria alocando mem�ria para atributos
    TriangleMesh & create(
        size_t vertexCount, size_t triangleCount,
        size_t normalCount = 0, size_t textureCoordinateCount = 0);
    // Cria geometria com atributos m�nimos
    TriangleMesh & create(
        const std::vector<Vector3> & vertices,
        const std::vector<size_t> & vertexIndices);
    // Cria geometria com atributos opcionais
    TriangleMesh & create(
        const std::vector<Vector3> & vertices,
        const std::vector<Vector3> & normals,
        const std::vector<size_t> & vertexIndices,
        const std::vector<size_t> & normalIndices);
    // Cria geometria com todos atributos
    TriangleMesh & create(
        const std::vector<Vector3> & vertices,
        const std::vector<Vector3> & normals,
        const std::vector<Vector2> & textureCoordinates,
        const std::vector<size_t> & vertexIndices,
        const std::vector<size_t> & normalIndices,
        const std::vector<size_t> & textureIndices);
};

// Fim de "namespace" da biblioteca
AURORA_NAMESPACE_END

#endif
