#pragma once

struct PendulumParams
{
  PendulumParams(double armLength_, double mass_): 
    armLength(armLength_),
    mass(mass_)
  {} 

  double armLength;
  double mass;
};
