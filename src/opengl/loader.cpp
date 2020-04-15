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

unsigned long get_file_length(ifstream& file) {
  if(!file.good()) return 0;

  file.seekg(0, ios::end);
  unsigned long len = file.tellg();
  file.seekg(ios::beg);

  return len;
}

int read_file(string filename, string* file) {
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

bool load_shader(GLuint shader, string filename) {
  string data;
  read_file(filename, &data);
  const char *source[] = {data.c_str()};
  glShaderSource(shader, 1, source, NULL);

  glCompileShader(shader);

  GLint did_shader_compile = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &did_shader_compile );
  if (did_shader_compile != GL_TRUE) {
    GLint max_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

    // The maxLength includes the NULL character
    std::vector<GLchar> error_log(max_length);
    glGetShaderInfoLog(shader, max_length, &max_length, &error_log[0]);

    cout << "Unable to compile shader!" << endl;
    cout << "At " << filename << ":" << endl;
    cout << error_log.data();
    return false;
  }
  return true;
}

GLuint load_shader_program(string vertex_filename, string fragment_filename) {
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  bool res = load_shader(vertex_shader, vertex_filename);
  if (!res) {
    exit(1);
  }
  res = load_shader(fragment_shader, fragment_filename);
  if (!res) {
    exit(1);
  }

  GLuint program_id = glCreateProgram();

  glAttachShader(program_id, vertex_shader);
  glAttachShader(program_id, fragment_shader);

  glLinkProgram(program_id);

  return program_id;
}

bool load_gltf(std::string path, Scene* scene) {
  tinygltf::Model loaded_model;
  tinygltf::TinyGLTF ctx;
  std::string err;
  std::string warn;
  bool ret = ctx.LoadBinaryFromFile(&loaded_model, &err, &warn, path.c_str());
  if (!ret) {
    cout << "Failed to load gltf file " << path << endl;
    return false;
  }

  tinygltf::Material loaded_material;
  Material* material;
  std::vector<Material*> materials = std::vector<Material*>();
  for (ulong i = 0; i < loaded_model.materials.size(); i++) {
    loaded_material = loaded_model.materials.at(i);
    material = new Material();
    std::vector<double> base_color = loaded_material.pbrMetallicRoughness.baseColorFactor;
    material->color = glm::vec3(base_color.at(0), base_color.at(1), base_color.at(2));
    materials.push_back(material);
  }

  for (ulong i = 0; i < loaded_model.nodes.size(); i++) {
    tinygltf::Node& node = loaded_model.nodes.at(i);
    if (node.mesh != -1) {
      tinygltf::Mesh& mesh = loaded_model.meshes.at(node.mesh);
      tinygltf::Primitive& primitive = mesh.primitives.at(0);

      std::vector<uint>*      vec_indices   = new std::vector<uint>();
      std::vector<glm::vec3>* vec_positions = new std::vector<glm::vec3>();
      std::vector<glm::vec2>* vec_uvs       = new std::vector<glm::vec2>();
      std::vector<glm::vec3>* vec_normals   = new std::vector<glm::vec3>();
      tinygltf::Accessor&     indices_accessor    = loaded_model.accessors[primitive.indices];
      tinygltf::BufferView&   indices_bufferView  = loaded_model.bufferViews[indices_accessor.bufferView];
      const tinygltf::Buffer& indices_buffer      = loaded_model.buffers[indices_bufferView.buffer];
      tinygltf::Accessor&     position_accessor   = loaded_model.accessors[primitive.attributes["POSITION"]];
      tinygltf::BufferView&   position_bufferView = loaded_model.bufferViews[position_accessor.bufferView];
      const tinygltf::Buffer& position_buffer     = loaded_model.buffers[position_bufferView.buffer];
      // tinygltf::Accessor&     uv_accessor         = loaded_model.accessors[primitive.attributes["TEXCOORD_0"]];
      // tinygltf::BufferView&   uv_bufferView       = loaded_model.bufferViews[uv_accessor.bufferView];
      // const tinygltf::Buffer& uv_buffer           = loaded_model.buffers[uv_bufferView.buffer];
      tinygltf::Accessor&     normal_accessor     = loaded_model.accessors[primitive.attributes["NORMAL"]];
      tinygltf::BufferView&   normal_bufferView   = loaded_model.bufferViews[normal_accessor.bufferView];
      const tinygltf::Buffer& normal_buffer       = loaded_model.buffers[normal_bufferView.buffer];

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

      uint vao = create_vao(vec_indices, vec_positions, vec_uvs, vec_normals);
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

bool load_obj(
    string path,
    std::vector<uint>& out_indices,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
) {
  std::vector<unsigned int> vertex_indices, uv_indices, normal_indices;
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
      unsigned int vertex_index[3], uv_index[3], normal_index[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
          &vertex_index[0], &uv_index[0], &normal_index[0],
          &vertex_index[1], &uv_index[1], &normal_index[1],
          &vertex_index[2], &uv_index[2], &normal_index[2]);
      if (matches != 9) {
        cout << "Found face that is not a triangle when loading " << path << " (obj loader)" << endl;
        return false;
      }
      vertex_indices.push_back(vertex_index[0]);
      vertex_indices.push_back(vertex_index[1]);
      vertex_indices.push_back(vertex_index[2]);
      uv_indices    .push_back(uv_index[0]);
      uv_indices    .push_back(uv_index[1]);
      uv_indices    .push_back(uv_index[2]);
      normal_indices.push_back(normal_index[0]);
      normal_indices.push_back(normal_index[1]);
      normal_indices.push_back(normal_index[2]);
    }
  }
  out_indices  = vector<uint>(vertex_indices.size());
  out_vertices = vector<glm::vec3>(vertices.size());
  out_uvs      = vector<glm::vec2>(vertices.size());
  out_normals  = vector<glm::vec3>(vertices.size());
  for (uint i = 0; i < vertex_indices.size(); i++) {
    uint vertex_index = vertex_indices[i] - 1;
    uint uv_index     = uv_indices[i] - 1;
    uint normal_index = normal_indices[i] - 1;

    out_indices[i] = vertex_index;
    out_vertices[vertex_index] = vertices.at(vertex_index);
    out_uvs[vertex_index]      =      uvs.at(uv_index);
    out_normals[vertex_index]  =  normals.at(normal_index);
  }
  return true;
}

GLuint create_vao(
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

bool load_scene(string path, Scene* scene) {
  if (path.rfind(".glb") == (path.size() - string(".glb").size())) {
    if (!load_gltf(path, scene)) {
      return false;
    }
  } else {
    cout << "Unrecognized file format " << path << ", failed to load scene" << endl;
    return false;
  }
  return true;
}

bool load_model(string path, Model* model) {
  if (path.rfind(".obj") == (path.size() - string(".obj").size())) {
    std::vector<uint> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    if (!load_obj(path, indices, vertices, uvs, normals)) {
      return false;
    }
    GLuint vao = create_vao(&indices, &vertices, &uvs, &normals);
    uint length = indices.size();
    model->vao = vao;
    model->length = length;
  } else {
    cout << "Unrecognized file format " << path << ", failed to load model" << endl;
    return false;
  }
  return true;
}

