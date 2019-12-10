#include <fstream>

#include "image.hpp"

Image::Image(unsigned width, unsigned height): width_(width), height_(height), len_(3*width*height)
{
  pixels_ = new unsigned char[len_];
}

Image::Image(const Image& other)
{
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;

  pixels_ = new unsigned char[len_];
  for(unsigned int i = 0; i < len_; ++i)
    pixels_[i] = other.pixels_[i];
}

Image::Image(Image&& other) noexcept
{
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;
  pixels_ = other.pixels_;

  other.pixels_ = nullptr;
}

Image::~Image()
{
  delete[] pixels_;
}

void Image::clear(const Color& color)
{
  for(unsigned y = 0; y < height_; ++y)
  {
    for(unsigned x = 0; x < width_; ++x)
    {
      int index = 3*(y*width_ + x);
      pixels_[index]   = color.r;
      pixels_[index+1] = color.g;
      pixels_[index+2] = color.b;
    }
  }
}

void Image::fillCircle(unsigned int cx, unsigned int cy, unsigned int r, const Color& color)
{
  int minX = cx - r;
  int minY = cy - r;
  int maxX = cx + r + 1;
  int maxY = cy + r + 1;

  minX = minX < 0 ? 0 : minX;
  minY = minY < 0 ? 0 : minY;
  maxX = (unsigned)maxX > width_ ? width_ : maxX;
  maxY = (unsigned)maxY > height_ ? height_ : maxY;

  for(int y = minY; y < maxY; ++y)
  {
    for(int x = minX; x < maxX; ++x)
    {
      if((x - cx)*(x - cx) + (y - cy)*(y - cy) <= r*r)
      {
        int index = 3*(y*width_ + x);
        pixels_[index]   = color.r;
        pixels_[index+1] = color.g;
        pixels_[index+2] = color.b;
      }
    }
  }
}

void Image::drawLine(int x1, int y1, int x2, int y2, const Color& color)
{
  int dx, dy, d, xi, yi;
  int x = x1, y = y1;

  if(x1 < x2)
  {
    dx = x2 - x1;
    xi = 1;
  }
  else
  {
    dx = x1 - x2;
    xi = -1;
  }

  if(y1 < y2)
  {
    dy = y2 - y1;
    yi = 1;
  }
  else
  {
    dy = y1 - y2;
    yi = -1;
  }

  if(dx > dy)
  {
    d = 2*dy - dx;
    while(x != x2)
    {
      setPixel(x, y, color);
      if(d > 0)
      {
        y += yi;
        d = d - 2*dx;
      }
      d = d + 2*dy;
      x += xi;
    }
  }
  else
  {
    d = 2*dx - dy;
    while(y != y2)
    {
      setPixel(x, y, color);
      if(d > 0)
      {
        x += xi;
        d = d - 2*dy;
      }
      d = d + 2*dx;
      y += yi;
    }
  }
}

void Image::setPixel(int x, int y, const Color& color)
{
  if(x >= 0 && x < (long)width_ && y >= 0 && y < (long)height_)
  {
    int index = 3*(y*width_ + x);
    pixels_[index]   = color.r;
    pixels_[index+1] = color.g;
    pixels_[index+2] = color.b;
  }
}

void Image::save(const char* filename) const
{
  std::ofstream file;
  file.open(filename, std::ios::binary);
  file << "P6\n" << width_ << " " << height_ << "\n255\n";
  file.write(reinterpret_cast<char*>(pixels_), len_);
  file.close();
}

Color Image::getPixel(unsigned int x, unsigned int y) const
{
  if(x < width_ && y < height_)
  {
    int index = 3*(y*width_ + x);
    return Color{pixels_[index], pixels_[index+1], pixels_[index+2]};
  }
  return Color{0, 0, 0};
}

unsigned int Image::getWidth() const
{
  return width_;
}

unsigned int Image::getHeight() const
{
  return height_;
}

Image& Image::operator=(const Image& other)
{
  if(this == &other)
    return *this;

  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;

  if(pixels_)
    delete[] pixels_;

  pixels_ = new unsigned char[len_];
  for(unsigned int i = 0; i < len_; ++i)
    pixels_[i] = other.pixels_[i];

  return *this;
}

Image& Image::operator=(Image&& other) noexcept
{
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;
  pixels_ = other.pixels_;

  other.pixels_ = nullptr;

  return *this;
}

