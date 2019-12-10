#pragma once

class Pendulum
{
public:
  Pendulum(double g, double len, double mass, double theta): 
    g_(g), len_(len), mass_(mass), theta_(theta), angularVelocity_(0) {}

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