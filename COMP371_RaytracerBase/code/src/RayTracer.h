#pragma once

#include "../external/json.hpp"

#include <string>
#include <Eigen/Dense>

class RayTracer
{
private:
  nlohmann::json sceneJson;

  std::string outputFile;

  Eigen::Vector2d resolution;

  void GetJsonInfo(nlohmann::json sceneJSON);
  void SavePPM(std::string file_name,
  const std::vector<double>& buffer, int dimx, int dimy, double gammaIn);
public:
  RayTracer(nlohmann::json sceneJSON);
  ~RayTracer();

  void run();
};
