#pragma once

#include "color.hpp"

class Image
{
  public:
    Image(unsigned width, unsigned height);
    Image(const Image& other);
    Image(Image&& other) noexcept;

    ~Image();

    void clear(const Color& color);
    void fillCircle(unsigned int x, unsigned int y, unsigned int r, const Color& color);
    void drawLine(int x1, int y1, int x2, int y2, const Color& color);
    void setPixel(int x, int y, const Color& color);

    void save(const char* filename) const;
    Color getPixel(unsigned int x, unsigned int y) const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    Image& operator=(const Image& other);
    Image& operator=(Image&& other) noexcept;
  private:
    unsigned char* pixels_;
    unsigned width_;
    unsigned height_;
    unsigned len_;
};