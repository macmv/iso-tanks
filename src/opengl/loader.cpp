#include "loader.h"
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../models/model.h"
#include <string>
#include "../models/scene.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>
#include "../models/material.h"

using namespace std;

unsigned long getFileLength(ifstream& file) {
  if(!file.good()) return 0;

  file.seekg(0, ios::end);
  unsigned long len = file.tellg();
  file.seekg(ios::beg);

  return len;
}

int readFile(string filename, string* file) {
  string line;
  ifstream stream(filename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      file->append(line);
      file->append("\n");
    }
    stream.close();
  } else {
    cout << "Unable to open file" << endl;
    return 1;
  }

  return 0;
}

bool loadShader(GLuint shader, string filename) {
  string data;
  readFile(filename, &data);
  const char *source[] = {data.c_str()};
  glShaderSource(shader, 1, source, NULL);

  glCompileShader(shader);

  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &vShaderCompiled );
  if (vShaderCompiled != GL_TRUE) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

    cout << "Unable to compile shader!" << endl;
    cout << "At " << filename << ":" << endl;
    cout << errorLog.data();
    return false;
  }
  return true;
}

GLuint loadShaderProgram(string vertexFilename, string fragmentFilename) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  bool res = loadShader(vertexShader, vertexFilename);
  if (!res) {
    exit(1);
  }
  res = loadShader(fragmentShader, fragmentFilename);
  if (!res) {
    exit(1);
  }

  GLuint programID = glCreateProgram();

  glAttachShader(programID, vertexShader);
  glAttachShader(programID, fragmentShader);

  glLinkProgram(programID);

  return programID;
}

bool loadGLTF(std::string path, Scene* scene) {
  tinygltf::Model loadedModel;
  tinygltf::TinyGLTF ctx;
  std::string err;
  std::string warn;
  bool ret = ctx.LoadBinaryFromFile(&loadedModel, &err, &warn, path.c_str());
  if (!ret) {
    cout << "Failed to load gltf file " << path << endl;
    return false;
  }

  tinygltf::Material loadedMaterial;
  Material* material;
  std::vector<Material*> materials = std::vector<Material*>();
  for (ulong i = 0; i < loadedModel.materials.size(); i++) {
    loadedMaterial = loadedModel.materials.at(i);
    material = new Material();
    std::vector<double> baseColor = loadedMaterial.pbrMetallicRoughness.baseColorFactor;
    material->color = glm::vec3(baseColor.at(0), baseColor.at(1), baseColor.at(2));
    materials.push_back(material);
  }

  for (ulong i = 0; i < loadedModel.nodes.size(); i++) {
    tinygltf::Node& node = loadedModel.nodes.at(i);
    if (node.mesh != -1) {
      tinygltf::Mesh& mesh = loadedModel.meshes.at(node.mesh);
      tinygltf::Primitive& primitive = mesh.primitives.at(0);

      std::vector<uint>*      vec_indices   = new std::vector<uint>();
      std::vector<glm::vec3>* vec_positions = new std::vector<glm::vec3>();
      std::vector<glm::vec2>* vec_uvs       = new std::vector<glm::vec2>();
      std::vector<glm::vec3>* vec_normals   = new std::vector<glm::vec3>();
      tinygltf::Accessor&     indices_accessor    = loadedModel.accessors[primitive.indices];
      tinygltf::BufferView&   indices_bufferView  = loadedModel.bufferViews[indices_accessor.bufferView];
      const tinygltf::Buffer& indices_buffer      = loadedModel.buffers[indices_bufferView.buffer];
      tinygltf::Accessor&     position_accessor   = loadedModel.accessors[primitive.attributes["POSITION"]];
      tinygltf::BufferView&   position_bufferView = loadedModel.bufferViews[position_accessor.bufferView];
      const tinygltf::Buffer& position_buffer     = loadedModel.buffers[position_bufferView.buffer];
      // tinygltf::Accessor&     uv_accessor         = loadedModel.accessors[primitive.attributes["TEXCOORD_0"]];
      // tinygltf::BufferView&   uv_bufferView       = loadedModel.bufferViews[uv_accessor.bufferView];
      // const tinygltf::Buffer& uv_buffer           = loadedModel.buffers[uv_bufferView.buffer];
      tinygltf::Accessor&     normal_accessor     = loadedModel.accessors[primitive.attributes["NORMAL"]];
      tinygltf::BufferView&   normal_bufferView   = loadedModel.bufferViews[normal_accessor.bufferView];
      const tinygltf::Buffer& normal_buffer       = loadedModel.buffers[normal_bufferView.buffer];

      // bufferView byteoffset + accessor byteoffset tells you where the actual position data is within the buffer. From there
      // you should already know how the data needs to be interpreted.

      const short* indices   = reinterpret_cast<const short*>(&indices_buffer.data[ indices_bufferView.byteOffset  + indices_accessor.byteOffset]);
      const float* positions = reinterpret_cast<const float*>(&position_buffer.data[position_bufferView.byteOffset + position_accessor.byteOffset]);
      // const float* uvs       = reinterpret_cast<const float*>(&uv_buffer.data[      uv_bufferView.byteOffset       + uv_accessor.byteOffset]);
      const float* normals   = reinterpret_cast<const float*>(&normal_buffer.data[  normal_bufferView.byteOffset   + normal_accessor.byteOffset]);

      for (size_t i = 0; i < indices_accessor.count; ++i) {
        vec_indices->push_back(indices[i]);
      }
      for (size_t i = 0; i < position_accessor.count; ++i) {
        // Positions are Vec3 components, so for each vec3 stride, offset for x, y, and z.
        vec_positions->push_back(glm::vec3(positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]));
        vec_uvs      ->push_back(glm::vec2(0, 0));
        vec_normals  ->push_back(glm::vec3(normals[i * 3 + 0],   normals[i * 3 + 1],   normals[i * 3 + 2]));
      }

      uint vao = createVAO(vec_indices, vec_positions, vec_uvs, vec_normals);
      Model* model = new Model(node.name, vao, vec_indices->size());
      if (primitive.material >= 0) {
        model->material = materials.at(primitive.material);
      }
      ModelInstance* instance = new ModelInstance(model);

      if (node.translation.size() != 0) {
        instance->transform = glm::translate(instance->transform, glm::vec3(
              node.translation.at(0),
              node.translation.at(1),
              node.translation.at(2)));
      }
      if (node.rotation.size() != 0) {
        instance->transform = instance->transform * glm::toMat4(glm::quat(
              node.rotation.at(3),
              node.rotation.at(0),
              node.rotation.at(1),
              node.rotation.at(2)));
      }
      if (node.scale.size() != 0) {
        instance->transform = glm::scale(instance->transform, glm::vec3(
              node.scale.at(0),
              node.scale.at(1),
              node.scale.at(2)));
      }

      scene->models->insert(instance);
    }
  }
  return true;
}

bool loadOBJ (
    string path,
    std::vector<uint>& out_indices,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
) {
  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;
  FILE* file = fopen(path.c_str(), "r");
  if (file == NULL) {
    cout << "Failed to open the file " << path << " (obj loader)" << endl;
    return false;
  }
  while (true) {
    char lineHeader[128];
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) {
      break; // EOF = End Of File. Quit the loop.
    }
    if (strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      vertices.push_back(vertex);
    } else if (strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y );
      uvs.push_back(uv);
    } else if (strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
      normals.push_back(normal);
    } else if (strcmp(lineHeader, "f") == 0) {
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
          &vertexIndex[0], &uvIndex[0], &normalIndex[0],
          &vertexIndex[1], &uvIndex[1], &normalIndex[1],
          &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if (matches != 9) {
        cout << "Found face that is not a triangle when loading " << path << " (obj loader)" << endl;
        return false;
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      uvIndices    .push_back(uvIndex[0]);
      uvIndices    .push_back(uvIndex[1]);
      uvIndices    .push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }
  }
  out_indices  = vector<uint>(vertexIndices.size());
  out_vertices = vector<glm::vec3>(vertices.size());
  out_uvs      = vector<glm::vec2>(vertices.size());
  out_normals  = vector<glm::vec3>(vertices.size());
  for (uint i = 0; i < vertexIndices.size(); i++) {
    uint vertexIndex = vertexIndices[i] - 1;
    uint uvIndex     = uvIndices[i] - 1;
    uint normalIndex = normalIndices[i] - 1;

    out_indices[i] = vertexIndex;
    out_vertices[vertexIndex] = vertices.at(vertexIndex);
    out_uvs[vertexIndex]      = uvs.at(uvIndex);
    out_normals[vertexIndex]  = normals.at(normalIndex);
  }
  return true;
}

GLuint createVAO(
  std::vector <unsigned int>* indices,
  std::vector <glm::vec3>* vertices,
  std::vector <glm::vec2>* uvs,
  std::vector <glm::vec3>* normals
) {
  GLuint vao;
  GLuint vbo;
  GLuint ibo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(uint), indices->data(), GL_STATIC_DRAW);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(glm::vec3), vertices->data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, uvs->size() * sizeof(glm::vec3), uvs->data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, normals->size() * sizeof(glm::vec3), normals->data(), GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return vao;
}

bool loadScene(string path, Scene* scene) {
  if (path.rfind(".glb") == (path.size() - string(".glb").size())) {
    if (!loadGLTF(path, scene)) {
      return false;
    }
  } else {
    cout << "Unrecognized file format " << path << ", failed to load scene" << endl;
    return false;
  }
  return true;
}

bool loadModel(string path, Model* model) {
  if (path.rfind(".obj") == (path.size() - string(".obj").size())) {
    std::vector<uint> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    if (!loadOBJ(path, indices, vertices, uvs, normals)) {
      return false;
    }
    GLuint vao = createVAO(&indices, &vertices, &uvs, &normals);
    uint length = indices.size();
    model->vao = vao;
    model->length = length;
  } else {
    cout << "Unrecognized file format " << path << ", failed to load model" << endl;
    return false;
  }
  return true;
}

