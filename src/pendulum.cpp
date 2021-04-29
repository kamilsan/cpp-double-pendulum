#include "pendulum.hpp"

#include <cmath>

void Pendulum::update(double stepSize)
{
  const double K0 = stepSize*angularVelocity_;
  const double L0 = stepSize*calculateAngularAcceleration(theta_);

  const double K1 = stepSize*(angularVelocity_ + 0.5*L0);
  const double L1 = stepSize*calculateAngularAcceleration(theta_ + 0.5*K0);

  const double K2 = stepSize*(angularVelocity_ + 0.5*L1);
  const double L2 = stepSize*calculateAngularAcceleration(theta_ + 0.5*K1);

  const double K3 = stepSize*(angularVelocity_ + L2);
  const double L3 = stepSize*calculateAngularAcceleration(theta_ + K2);

  theta_ += 1.0/6.0*(K0+2.0*K1+2.0*K2+K3);
  angularVelocity_ += 1.0/6.0*(L0+2.0*L1+2.0*L2+L3);
}

double Pendulum::getTheta() const
{
  return theta_;
}

double Pendulum::getLength() const
{
  return len_;
}

double Pendulum::calculateAngularAcceleration(double theta) const
{
  return -g_/len_ * std::sin(theta);
}