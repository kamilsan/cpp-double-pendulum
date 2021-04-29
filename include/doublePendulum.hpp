#pragma once

#include <utility>

#include "pendulumParams.hpp"
#include "initialConditions.hpp"

class DoublePendulum
{
public:
  DoublePendulum(double g, 
    const PendulumParams& params1, const InitialConditions& initialConditions1,
    const PendulumParams& params2, const InitialConditions& initialConditions2): 
    g_(g), 
    l1_(params1.armLength), 
    m1_(params1.mass),
    l2_(params2.armLength),
    m2_(params2.mass), 
    theta1_(initialConditions1.angle),
    theta2_(initialConditions2.angle),
    angularVelocity1_(initialConditions1.angularVelocity),
    angularVelocity2_(initialConditions2.angularVelocity) 
  {}

  void update(double stepSize);

  double getTheta1() const;
  double getTheta2() const;
  double getLength1() const;
  double getLength2() const;

private:
  double g_;
  double l1_;
  double m1_;
  double l2_;
  double m2_;
  double theta1_;
  double theta2_;
  double angularVelocity1_;
  double angularVelocity2_;

  std::pair<double, double> calculateAngularAccelerations(double theta1, double theta2);
};