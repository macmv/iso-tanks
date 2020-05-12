#include <iostream>
#include <reactphysics3d.h>
#include <glm/glm.hpp>

using namespace std;

int main() {
  cout << "Test stuff here!" << endl;
  // Array with the vertices coordinates of the convex mesh
  vector<glm::vec3> vertices(4);
  vertices.at(0) = glm::vec3(0, 3, 3);
  vertices.at(1) = glm::vec3(0, 3, -3);
  vertices.at(2) = glm::vec3(0, -3, -3);
  vertices.at(3) = glm::vec3(0, -3, 3);

  // Array with the vertices indices for each face of the mesh
  vector<uint> indices(6);
  indices[0]=0; indices[1]=1; indices[2]=2;
  indices[3]=3; indices[4]=2; indices[5]=1;

  // Description of the six faces of the convex mesh
  vector<rp3d::PolygonVertexArray::PolygonFace> faces(2);
  for (int f = 0; f < faces.size(); f++) {
    rp3d::PolygonVertexArray::PolygonFace face;
    // First vertex of the face in the indices array
    face.indexBase = f * 3;

    // Number of vertices in the face
    face.nbVertices = 3;

    faces.at(f) = face;
  }

  // Create the polygon vertex array
  rp3d::PolygonVertexArray* polygonVertexArray = new rp3d::PolygonVertexArray(vertices.size(), vertices.data(), sizeof(glm::vec3),
      indices.data(), sizeof(uint), faces.size(), faces.data(),
      rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
      rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

  // Create the polyhedron mesh
  rp3d::PolyhedronMesh* polyhedronMesh = new rp3d::PolyhedronMesh(polygonVertexArray);

  // Create the convex mesh collision shape
  rp3d::ConvexMeshShape* convexMeshShape = new rp3d::ConvexMeshShape(polyhedronMesh);

  cout << "Created convex mesh shape at " << convexMeshShape << endl;
}
