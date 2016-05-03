#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <vector>

bool parseObj(
  const std::string filePath,
  std::vector<glm::vec3> & out_vertices,
  std::vector<glm::vec2> & out_uvs,
  std::vector<glm::vec3> & out_normals
);

#endif
