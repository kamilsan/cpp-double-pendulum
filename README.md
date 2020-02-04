# Double pendulum

Simple simulation of double pendulum's motion, that uses Runge-Kutta 4 algorithm to solve motion equations.
Custom, minimalistic image class is used to render animation frames, that then can be converted into video using ffmpeg.



## Usage

In order to build this application run the following command:

```bash
make
```

Make a directory for animation frames:

```bash
mkdir frames
```

Run:

```bash
./program
```

And to make a video from produced frames:

```bash
ffmpeg -framerate 30 -i frames/frame%d.ppm -c:v libx264 -pix_fmt yuv420p -crf 23 output.mp4
```