#include "loader.h"
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include "../models/model.h"
#include <string>
#include "../models/scene.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/tinygltf/tiny_gltf.h"

using namespace std;

unsigned long getFileLength(ifstream& file) {
  if(!file.good()) return 0;

  unsigned long pos=file.tellg();
  file.seekg(0, ios::end);
  unsigned long len = file.tellg();
  file.seekg(ios::beg);

  return len;
}

int readFile(string filename, string* file) {
  cout << "Reading file " << filename << endl;
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
  bool success = true;

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
  cout << "Loading shader program" << endl;
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

  cout << "Loaded shader program" << endl;

  return programID;
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

