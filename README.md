# Mini-Ray-Tracer

A lightweight ray tracing implementation for 3D graphics rendering.

##  Overview

Ray tracing is a powerful rendering technique that simulates the behavior of light rays to generate photorealistic images. This project implements a small-scale ray tracer as an introduction to 3D graphics programming.

<br>

<pre style="color:white; text-align:center">In a ray tracing program, we start with a camera, some objects, and a light source. During execution, we send rays (which are like lines) from the camera through each pixel on the screen. To do this, we use certain equations to define the direction and position of each ray. If a ray hits an object in the scene, we color that pixel using the object’s color. But how do we know if a ray hits something? Back in high school, we learned that a line intersects a function if the equation becomes solvable when we plug in values — it's similar here. Each object (like a sphere, plane, or cylinder) has its own equation. We plug the ray’s formula into the object’s equation and, after simplifying, we usually get a quadratic equation. If that equation has a solution, it means there’s an intersection. Once we render all basic objects, we apply ambient lighting — a general brightness added to all colors to simulate surrounding light. Then comes normal lighting, where we calculate how light hits the surface using the dot product between the light direction and the surface normal (which is a vector pointing out from the surface). Finally, we handle shadows by sending a ray from the intersection point to the light source. If something blocks that ray, the point is in shadow; if not, it’s lit. </pre>


## Conclusion

This mini ray tracer project has been an enjoyable and educational first step into the world of 3D graphics programming. Implementing these fundamental ray tracing concepts from scratch provided valuable insights into how light simulation works in computer graphics. While this implementation focuses on core functionality with basic primitives and lighting models, it establishes a foundation for further exploration. I'm excited to continue learning and expanding my knowledge in 3D graphics in the future, potentially exploring advanced features like reflection, refraction, texture mapping, and more sophisticated lighting models.
