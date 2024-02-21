#pragma once

#include "RayTracer.h"
#include "../external/json.hpp"

#include <iostream>
#include <ios>
#include <vector>
#include <limits>
#include <math.h>
#include <Eigen/Dense>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <ctime>

#define _USE_MATH_DEFINES

RayTracer::RayTracer(nlohmann::json sceneJSON)
{
  this->sceneJson = sceneJSON;
}

RayTracer::~RayTracer()
{
}

void RayTracer::run(){
  for (auto itr = sceneJson["output"].begin(); itr!= sceneJson["output"].end(); itr++)
  {
    if (itr->contains("filename"))
    {
      outputFile = (*itr)["filename"].get<std::string>();
    }

    resolution = Eigen::Vector2d(0,0);
    int i = 0;
    for (auto itr2 =(*itr)["size"].begin(); itr2!= (*itr)["size"].end(); itr2++)
    {
      if (i<2)
      {
        resolution[i++] = (*itr2).get<double>();
      }
    }

    std::vector<double> buffer(3*resolution[0]*resolution[1]);

    for (int y = 0; y < resolution[1]; y++)
    {
      for (int x = 0; x < resolution[0]; x++)
      {
        buffer[3*y*resolution[0]+3*x+0] = 0;
        buffer[3*y*resolution[0]+3*x+1] = 0;
        buffer[3*y*resolution[0]+3*x+2] = 0;
      }
    }
    SavePPM(outputFile, buffer, resolution[0], resolution[1], 1);
  }
}

void RayTracer::SavePPM(std::string file, const std::vector<double>& buffer,
                        int dimX, int dimY, double gammaIn){
  std::ofstream outputStream(file, std::ios_base::out | std::ios_base::binary);

  outputStream << "P6" << std::endl << dimX << ' ' << dimY << std::endl << "255" << std::endl;

  for (int y = 0; y < dimY; y++){
    for (int x = 0; x < dimX; x++)
    {
      outputStream << (char) (255.0 * pow(buffer[3*y*dimX+3*x+0], (double)1 / (double)gammaIn)) << 
      (char) (255.0 * pow(buffer[3*y*dimX+3*x+1], (double)1 / (double)gammaIn)) << 
      (char) (255.0 * pow(buffer[3*y*dimX+3*x+2], (double)1 / (double)gammaIn));
    }
  }
  outputStream.close();
}