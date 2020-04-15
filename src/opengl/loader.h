#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "models/model.h"
#include "models/scene.h"

#ifndef _LOADER_H
#define _LOADER_H

using namespace std;

class Loader {
  private:
    static unsigned long get_file_length(ifstream& file);
    static int read_file(string filename, string* file);

  public:
    static bool load_shader(GLuint shader, string filename);
    static GLuint load_shader_program(string vertex_filename, string fragment_filename);
    static bool load_gltf(std::string path, Scene* scene);
    static bool load_obj(
        string path,
        std::vector<uint>& out_indices,
        std::vector<glm::vec3>& out_vertices,
        std::vector<glm::vec2>& out_uvs,
        std::vector<glm::vec3>& out_normals);
    static GLuint create_vao(
        std::vector<unsigned int>* indices,
        std::vector<glm::vec3>* vertices,
        std::vector<glm::vec2>* uvs,
        std::vector<glm::vec3>* normals);
    static bool load_scene(string path, Scene* scene);
    static bool load_model(string path, Model* model);

};


#endif
