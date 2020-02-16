#include "loader.h"
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

unsigned long getFileLength(ifstream& file) {
  if(!file.good()) return 0;

  unsigned long pos=file.tellg();
  file.seekg(0, ios::end);
  unsigned long len = file.tellg();
  file.seekg(ios::beg);

  return len;
}

int readFile(string filename, string file) {
  cout << "Reading file " << filename << endl;
  string line;
  ifstream stream(filename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      file.append(line);
    }
    stream.close();
  } else {
    cout << "Unable to open file" << endl;
  }

  return 0;
}

bool loadShader(GLuint shader, string filename) {
  bool success = true;

  string data;
  readFile(filename, data);
  const char *source[] = {data.c_str()};
  glShaderSource(shader, 1, source, NULL);

  glCompileShader(shader);

  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &vShaderCompiled );
  if (vShaderCompiled != GL_TRUE) {
    printf("Unable to compile shader %d!\n", shader);
    return false;
  }
}

GLuint loadShaderProgram(string vertexFilename, string fragmentFilename) {
  cout << "Loading shader program" << endl;
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  loadShader(vertexShader, vertexFilename);
  loadShader(fragmentShader, fragmentFilename);

  GLuint programID = glCreateProgram();

  glAttachShader(programID, vertexShader);
  glAttachShader(programID, fragmentShader);

  glLinkProgram(programID);

  cout << "Loaded shader program" << endl;

  return programID;
}

bool loadOBJ (
  const char* path,
  std::vector <glm::vec3>& out_vertices,
  std::vector <glm::vec2>& out_uvs,
  std::vector <glm::vec3>& out_normals
) {
  std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector <glm::vec3> temp_vertices;
  std::vector <glm::vec2> temp_uvs;
  std::vector <glm::vec3> temp_normals;
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    cout << "Failed to open the file !" << endl;
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
      temp_vertices.push_back(vertex);
    } else if (strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y );
      temp_uvs.push_back(uv);
    } else if (strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
      temp_normals.push_back(normal);
    } else if (strcmp(lineHeader, "f") == 0) {
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
          &vertexIndex[0], &uvIndex[0], &normalIndex[0],
          &vertexIndex[1], &uvIndex[1], &normalIndex[1],
          &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if (matches != 9) {
        printf("Found face that is not a triangle!\n");
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
};
