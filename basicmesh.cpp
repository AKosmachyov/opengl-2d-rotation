#include "basicmesh.h"
#include "mesh.h"

Mesh* createCube( float half )
{
  float sx = 1.0f * half;
  float sy = 1.0f * half;
  float sz = 1.0f * half;

  GLushort numVertices = 24;
  GLushort numIndices = 36;

  VertexData vertices[] = {
    { QVector3D(-sx, -sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, -sy, +sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, -sy, +sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, -sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, +sy, -sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, +sy, +sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, +sy, +sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, -sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, -sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, +sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, -sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, -sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, +sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, -sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, -sy, -sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, -sy, +sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(-sx, +sy, +sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(-sx, +sy, -sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(+sx, -sy, -sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(+sx, -sy, +sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, +sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, +sy, -sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(1.0f, 0.0f) }
  };

  GLushort indices[] = {
    0, 2, 1,
    0, 3, 2,
    4, 5, 6,
    4, 6, 7,
    8, 9, 10,
    8, 10, 11,
    12, 15, 14,
    12, 14, 13,
    16, 17, 18,
    16, 18, 19,
    20, 23, 22,
    20, 22, 21
  };

  return Mesh::create(vertices, numVertices, indices, numIndices);
}

Mesh* createCubeQUADS( float half )
{
  float sx = 1.0f * half;
  float sy = 1.0f * half;
  float sz = 1.0f * half;

  GLushort numVertices = 8;
  GLushort numIndices = 24;

  VertexData vertices[] = {
      { QVector3D(-sx, -sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
      { QVector3D(sx, -sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
      { QVector3D(sx, sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
      { QVector3D(-sx, sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
      { QVector3D(-sx, -sy, sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
      { QVector3D(-sx, sy, sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
      { QVector3D(sx, -sy, sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
      { QVector3D(sx, sy, sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) }
  };

  GLushort indices[] = {
      0, 1, 2, 3,
      0, 4, 5, 3,
      6, 1, 2, 7,
      0, 1, 6, 4,
      4, 6, 7, 5,
      5, 3, 2, 7
  };

  return Mesh::create(vertices, numVertices, indices, numIndices);
}
