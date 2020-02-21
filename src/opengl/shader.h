#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
  private:
    GLuint projectionID;
    GLuint viewID;
    GLuint modelID;
  public:
    GLuint programID;

  public:
    Shader(std::string filename, bool has_geometry);
};

#endif
