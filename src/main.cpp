#include <cmath>
#include <string>

#include "image.hpp"
#include "point.hpp"
#include "doublePendulum.hpp"

int main()
{
  Image img{512, 512};

  const PendulumParams firstSegementParams{0.2, 2.0};
  const InitialConditions firstSegementInitial{M_PI/4, 0};
  const PendulumParams secondSegementParams{0.2, 2.0};
  const InitialConditions secondSegementInitial{M_PI/2, 0};

  DoublePendulum pendulum{9.81, 
    firstSegementParams, firstSegementInitial, 
    secondSegementParams, secondSegementInitial};

  const unsigned int SIMULATION_STEPS = 1000;
  const double STEP_SIZE = 0.01;
  const double PIXELS_PER_METER = 1000;

  const Point anchor = Point{static_cast<int>(0.5 * img.getWidth()), 0};

  for(unsigned int step = 0; step < SIMULATION_STEPS; ++step)
  {
    pendulum.update(STEP_SIZE);

    const double theta1 = pendulum.getTheta1();
    const double theta2 = pendulum.getTheta2();

    const int x1 = anchor.x + PIXELS_PER_METER*pendulum.getLength1()*std::sin(theta1) + 0.5;
    const int y1 = anchor.y + PIXELS_PER_METER*pendulum.getLength1()*std::cos(theta1) + 0.5;
    const int x2 = x1 + PIXELS_PER_METER*pendulum.getLength2()*std::sin(theta2) + 0.5;
    const int y2 = y1 + PIXELS_PER_METER*pendulum.getLength2()*std::cos(theta2) + 0.5;

    const Point bobPos1 = Point{x1, y1};
    const Point bobPos2 = Point{x2, y2};

    img.clear(Color::White);
    img.drawLine(anchor, bobPos1, Color::Black);
    img.drawLine(bobPos1, bobPos2, Color::Black);
    img.fillCircle(bobPos1, 10, Color::Black);
    img.fillCircle(bobPos2, 10, Color::Black);

    const std::string fileName = "frames/frame" + std::to_string(step) + ".ppm";
    img.save(fileName.c_str());
  }

  return 0;
}