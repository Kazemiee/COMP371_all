#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <Eigen/Dense>

class Ray
{
public:
  Eigen::Vector3d origin;
  Eigen::Vector3d direction;
  double minInput = std::numeric_limits<double>::lowest();
  double maxInput = std::numeric_limits<double>::max();
  
  Ray(Eigen::Vector3d originInput, Eigen::Vector3d directionInput, double min, double max){
    origin = originInput;
    direction = directionInput.normalized();
    minInput = min;
    maxInput = max;
  }
  Ray(Eigen::Vector3d originInput, Eigen::Vector3d directionInput, double min){
    origin = originInput;
    direction = directionInput.normalized();
    minInput = min;
  }
  Ray(Eigen::Vector3d originInput, Eigen::Vector3d directionInput){
    origin = originInput;
    direction = directionInput.normalized();
  }
  ~Ray() = default;

  Eigen::Vector3d operator ()(double t) const {
    return (direction * t) + origin;
  }

  friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    os << "Ray: origin [" << ray.origin(0) << ", " << ray.origin(1) << ", " << ray.origin(2) << "],\n";
    os << "Ray: direction [" << ray.direction(0) << ", " << ray.direction(1) << ", " << ray.direction(2) << "],\n";
    os << "Ray: minInput  [" << ray.minInput << "],\n";
    os << "Ray: maxInput  [" << ray.maxInput << "]";
    return os;
  }
};