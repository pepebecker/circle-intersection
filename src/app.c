#include <stdbool.h>
#include "app.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define WIDTH 640
#define HEIGHT 480

typedef struct {
  float x, y;
} vec2;

typedef struct {
  vec2 a, b;
  bool success;
} CircleIntersection;

vec2 shoulder = {WIDTH / 2.0, HEIGHT / 2.0};
vec2 elbow = {0, 0};
vec2 hand = {WIDTH / 2.0, HEIGHT / 2.0};
float shoulderR = 75;
float handR = 100;

CircleIntersection getIntersection(vec2 c0, float r0, vec2 c1, float r1) {
  float a, dx, dy, d, h, rx, ry;
  float x2, y2;

  // dx and dy are the vertical and horizontal distances between
  // the circle centers.
  dx = c1.x - c0.x;
  dy = c1.y - c0.y;

  // Determine the straight-line distance between the centers.
  d = sqrt((dy * dy) + (dx * dx));

  // Check for solvability.
  if (d > (r0 + r1)) {
    // no solution. circles do not intersect.
    return (CircleIntersection){0, 0, false};
  }
  if (d < ABS(r0 - r1)) {
    // no solution. one circle is contained in the other
    return (CircleIntersection){0, 0, false};
  }

  // 'point 2' is the point where the line through the circle
  // intersection points crosses the line between the circle
  // centers.


  // Determine the distance from point 0 to point 2.
  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

  // Determine the coordinates of point 2.
  x2 = c0.x + (dx * a/d);
  y2 = c0.y + (dy * a/d);

  // Determine the distance from point 2 to either of the
  // intersection points.
  h = sqrt((r0*r0) - (a*a));

  // Now determine the offsets of the intersection points from
  // point 2.
  rx = -dy * (h/d);
  ry = dx * (h/d);

  // Determine the absolute intersection points.
  float xi = x2 + rx;
  float xi_prime = x2 - rx;
  float yi = y2 + ry;
  float yi_prime = y2 - ry;

  return (CircleIntersection){{xi, yi}, {xi_prime, yi_prime}, true};
}

void gameLoop(float deltaTime) {
  setDrawColor(255, 255, 255, 255);
  clearScreen();

  setDrawColor(255, 0, 0, 255);
  drawCircle(shoulder.x, shoulder.y, shoulderR);
  drawCircle(shoulder.x, shoulder.y, 2);

  setDrawColor(0, 0, 255, 255);
  drawCircle(hand.x, hand.y, handR);
  drawCircle(hand.x, hand.y, 2);

  CircleIntersection intersection = getIntersection(shoulder, shoulderR, hand, handR);

  if (intersection.success) {
    // if (intersection.a.y > intersection.b.y) {
    if (true) {
      elbow.x = intersection.a.x;
      elbow.y = intersection.a.y;
    } else {
      elbow.x = intersection.b.x;
      elbow.y = intersection.b.y;
    }

    setDrawColor(0, 0, 0, 255);
    drawLine(shoulder.x, shoulder.y, elbow.x, elbow.y);
    drawLine(hand.x, hand.y, elbow.x, elbow.y);
    drawCircle(elbow.x, elbow.y, 2);
  }
}

void onMouseMove(int x, int y) {
  hand.x = x;
  hand.y = y;
}

void onQuit() {
  destroyWindow();
}

void start() {
  init();
  createWindow("Circle Intersection", 640, 480);
  setOnMouseMove(onMouseMove);
  runGameLoop(gameLoop, onQuit);
}
