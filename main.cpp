#include <cmath>
#include <string>

#include "image.hpp"
#include "pendulum.hpp"

int main()
{
  Image img{512, 512};
  Pendulum pendulum{9.81, 0.2, 1, M_PI/3};

  const unsigned int SIMULATION_STEPS = 1000;
  const double STEP_SIZE = 0.01;
  const double PIXELS_PER_METER = 1200;

  const double anchorX = 0.5*img.getWidth();
  const double anchorY = 0.0;

  for(unsigned int step = 0; step < SIMULATION_STEPS; ++step)
  {
    pendulum.update(STEP_SIZE);
    const double theta = pendulum.getTheta();
    const int x = anchorX + PIXELS_PER_METER*pendulum.getLength()*std::sin(theta) + 0.5;
    const int y = anchorY + PIXELS_PER_METER*pendulum.getLength()*std::cos(theta) + 0.5;

    img.clear(Color{255, 255, 255});
    img.drawLine(anchorX, anchorY, x, y, Color{0, 0, 0});
    img.fillCircle(x, y, 10, Color{0, 0, 0});

    const std::string fileName = "frames/frame" + std::to_string(step) + ".ppm";
    img.save(fileName.c_str());
  }

  return 0;
}