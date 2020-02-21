#include "shader.h"
#include "loader.h"
#include <GL/glew.h>
#include <string>
#include <iostream>

using namespace std;

Shader::Shader(string filename, bool has_geometry) {
  cout << "Loading shader program" << endl;
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint geometryShader;
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (has_geometry) {
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
  }

  bool res = loadShader(vertexShader, filename + "_vertex.glsl");
  if (!res) {
    exit(1);
  }
  res = loadShader(fragmentShader, filename + "_fragment.glsl");
  if (!res) {
    exit(1);
  }
  if (has_geometry) {
    res = loadShader(geometryShader, filename + "_geometry.glsl");
    if (!res) {
      exit(1);
    }
  }

  programID = glCreateProgram();

  glAttachShader(programID, vertexShader);
  glAttachShader(programID, fragmentShader);
  if (has_geometry) {
    glAttachShader(programID, geometryShader);
  }

  glLinkProgram(programID);

  cout << "Loaded shader program" << endl;
}
