#pragma once

struct InitialConditions
{
  InitialConditions(double angle_, double angularVelocity_): 
    angle(angle_), 
    angularVelocity(angularVelocity_) 
  {}

  double angle;
  double angularVelocity;
};
