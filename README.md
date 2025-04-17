# mini-ray-tracer
Ray tracing is a well-known 3D rendering technique that simulates the behavior of light rays to generate realistic images. This project is a small-scale implementation of a ray tracer, and it marks my first step into the world of 3D graphics. I really enjoyed working on it and learning how rendering works at a low level.
## 📚 Prerequisites (Brief & Simple)

Before building a ray tracer, it's helpful to understand a few basic math concepts. Here's a quick rundown:

- **Vectors and Points in 3D**  
  A point or a direction in space is usually represented as `(x, y, z)`. Vectors are used to define directions, while points define positions. You’ll use them everywhere — for rays, camera setup, object positions, and lighting.

- **Dot Product**  
  The dot product between two vectors gives a scalar (a number) that tells you how aligned they are.  
  - If the result is 0 → vectors are perpendicular.  
  - If it’s positive → they point in roughly the same direction.  
  - It’s often used in lighting calculations (e.g., diffuse lighting).

- **Cross Product**  
  The cross product of two vectors gives a third vector that's perpendicular to both.  
  It’s used to build coordinate systems, especially to compute a camera’s orientation in space.

- **Ray Equation**  
  A ray is a function:  
  `P(t) = Origin + t * Direction`  
  - `Origin` is where the ray starts.  
  - `Direction` is a normalized vector.  
  - `t` is a distance scalar.  
  You use this to move along the ray and check for intersections with objects.

- **Solving Quadratic Equations**  
  Some intersections (like ray-sphere) result in quadratic equations:  
  `a*t² + b*t + c = 0`  
  Solving this gives you the `t` values where a ray hits the object (if any).

- **Basic Linear Algebra**  
  Things like matrix multiplication and transformations aren’t always required in a mini ray tracer, but having a general sense of how objects and vectors behave in space is very useful.

- **Color Representation**  
  Colors are usually represented using RGB (Red, Green, Blue) values between 0 and 255.  
  When light hits an object, you calculate how much light it receives and adjust its color accordingly. This gives a sense of shading and depth.

Most of these concepts become clear once you implement them — don’t worry if they seem abstract at first.
