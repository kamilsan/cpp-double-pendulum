#pragma once

#include "pendulumParams.hpp"
#include "initialConditions.hpp"

class Pendulum
{
public:
  Pendulum(double g, const PendulumParams& params, const InitialConditions& initialConditions): 
    g_(g), 
    len_(params.armLength), 
    mass_(params.mass), 
    theta_(initialConditions.angle), 
    angularVelocity_(initialConditions.angularVelocity) 
  {}

  void update(double stepSize);

  double getTheta() const;
  double getLength() const;

private:
  double g_;
  double len_;
  double mass_;
  double theta_;
  double angularVelocity_;

  double calculateAngularAcceleration(double theta) const;
};