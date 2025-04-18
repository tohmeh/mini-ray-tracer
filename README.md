# Mini-Ray-Tracer

A lightweight ray tracing implementation for 3D graphics rendering.

##  Overview

Ray tracing is a powerful rendering technique that simulates the behavior of light rays to generate photorealistic images. This project implements a small-scale ray tracer as an introduction to 3D graphics programming.

##  Mathematical Foundations

1. ### Vector Mathematics

- #### Vector and Point Representation

	In 3D space, both points and vectors are represented as triplets:
	- Points: `(x, y, z)` - coordinates in 3D space
	- Vectors: `(v_x, v_y, v_z)` - direction and magnitude

- #### Essential Vector Operations

	| Operation | Description | Formula | Use Case |
	|-----------|-------------|---------|----------|
	| Addition | Combines two vectors | `(v₁.x + v₂.x, v₁.y + v₂.y, v₁.z + v₂.z)` | Moving points, combining directions |
	| Subtraction | Difference between vectors | `(v₁.x - v₂.x, v₁.y - v₂.y, v₁.z - v₂.z)` | Finding direction between points |
	| Scalar Multiplication | Scales a vector | `(v.x * s, v.y * s, v.z * s)` | Adjusting vector length |
	| Dot Product | Scalar result of two vectors | `v₁.x * v₂.x + v₁.y * v₂.y + v₁.z * v₂.z` | Calculating alignment between vectors |
	| Cross Product | Vector perpendicular to two inputs | `(v₁.y * v₂.z - v₁.z * v₂.y, v₁.z * v₂.x - v₁.x * v₂.z, v₁.x * v₂.y - v₁.y * v₂.x)` | Computing surface normals |
	| Length | Magnitude of a vector | `√(v.x² + v.y² + v.z²)` | Measuring distance |
	| Normalization | Creates unit vector | `v / length(v)` | Standardizing direction vectors |



2. ### Quadratic Equation Solving
	Ray-sphere intersections often involve solving quadratic equations:
	```
	a * t² + b * t + c = 0
	```
	**Solution**:

	`t = (-b ± √(b² - 4ac)) / 2a`
	Where the discriminant `Δ = b² - 4ac` indicates:
	- `Δ > 0`: Two intersection points
	- `Δ = 0`: One intersection point (tangent)
	- `Δ < 0`: No intersection


</br>
</br>
</br>

<pre style="color:red">	 ⚠️ Note: From now on, the math is specific to the ray tracer</pre>

<br>
<br>

<pre style="color:white; text-align:center">In a ray tracing program, we start with a camera, some objects, and a light source. During execution, we send rays (which are like lines) from the camera through each pixel on the screen. To do this, we use certain equations to define the direction and position of each ray. If a ray hits an object in the scene, we color that pixel using the object’s color. But how do we know if a ray hits something? Back in high school, we learned that a line intersects a function if the equation becomes solvable when we plug in values — it's similar here. Each object (like a sphere, plane, or cylinder) has its own equation. We plug the ray’s formula into the object’s equation and, after simplifying, we usually get a quadratic equation. If that equation has a solution, it means there’s an intersection. Once we render all basic objects, we apply ambient lighting — a general brightness added to all colors to simulate surrounding light. Then comes normal lighting, where we calculate how light hits the surface using the dot product between the light direction and the surface normal (which is a vector pointing out from the surface). Finally, we handle shadows by sending a ray from the intersection point to the light source. If something blocks that ray, the point is in shadow; if not, it’s lit. </pre>

3. ### Ray Mathematics

	#### Ray Definition
	A ray in 3D space is defined by its parametric equation:
	```
	P(t) = b + t * D
	```

	Where:
	- `P(t)` is any point along the ray
	- `b` is the origin point (where the ray starts)
	- `D` is the direction vector (normalized)
	- `t` is a non-negative scalar parameter (t ≥ 0)

	For our ray tracer, we need to determine:
	1. The origin `b` of each ray (camera position)
	2. The direction vector `D` for each pixel in our image

	#### Ray Generation Equations

	For a camera with position `camera.position`, direction `camera.direction`, and field of view `camera.fov`, the ray for pixel (i, j) is:

	**Origin equation:**
	```
	ray.b = camera.position
	```

	**Direction equation:**
	```
	ray.D = normalize(pixel_x * right + pixel_y * up + camera.direction)
	```

	Where:
	- `pixel_x = (2 * ((i + 0.5) / WIDTH) - 1) * aspect_ratio * scale`
	- `pixel_y = (1 - 2 * ((j + 0.5) / HEIGHT)) * scale`
	- `scale = tan(fov_rad / 2)`
	- `fov_rad = camera.fov * π / 180`
	- `aspect_ratio = WIDTH / HEIGHT`
	- `right = compute_right_vector(camera.direction)`
	- `up = cross_product(camera.direction, right)`

	
4. ### Ray-Object Intersection Mathematics

	#### Ray-Sphere Intersection

	To determine if a ray intersects a sphere, we need to solve:

	**Equation:**
	For a sphere with center `C` and radius `r`, a point `P` is on the sphere if:
	```
	|P - C|² = r²
	```

	Substituting the ray equation `P(t) = b + t*D`:
	```
	|b + t*D - C|² = r²
	```

	This expands to a quadratic equation:
	```
	a * t² + b * t + c = 0
	```

	Where:
	- `a = dot_product(D, D)`
	- `b = 2 * dot_product(D, (b - C))`
	- `c = dot_product((b - C), (b - C)) - r²`

	
	#### Ray-Plane Intersection

	**Equation:**
	For a plane defined by a point `P₀` and normal vector `n`, a point `P` is on the plane if:
	```
	(P - P₀) · n = 0
	```

	Substituting the ray equation:
	```
	(b + t*D - P₀) · n = 0
	```

	Solving for `t`:
	```
	t = ((P₀ - b) · n) / (D · n)
	```

	#### Ray-Cylinder Intersection

	For a cylinder with center `C`, axis `A`, radius `r`, and height `h`, we need to:

	1. Project the ray onto a plane perpendicular to the cylinder axis
	2. Determine if this projected ray intersects the circle on that plane
	3. Check if the intersection point is within the cylinder's height

	**Equation:**
	We first remove the axis component from both the ray direction and origin-center vector:
	```
	rd_proj = D - (D · A)A
	oc_proj = (b - C) - ((b - C) · A)A
	```

	Then solve the quadratic equation:
	```
	a * t² + b * t + c = 0
	```

	Where:
	- `a = dot_product(rd_proj, rd_proj)`
	- `b = 2 * dot_product(rd_proj, oc_proj)`
	- `c = dot_product(oc_proj, oc_proj) - r²`

	

5. ### Surface Normal Calculation

	Surface normals are essential for lighting calculations. They indicate the direction perpendicular to a surface at a specific point.

	#### Sphere Normal

	For a sphere, the normal at any point is simply the vector from the center to that point, normalized:

	```
	N = normalize(P - C)
	```

	Where:
	- `P` is the intersection point
	- `C` is the sphere center

	In our implementation:
	```
	N = subtract_vectors(intersection, sphere.center)
	return normalize_vector(N)
	```

	#### Plane Normal

	For a plane, the normal is already defined as part of the plane:

	```
	N = normalize(plane.normal)
	```

	#### Cylinder Normal

	For a cylinder, we need to:
	1. Find the closest point on the cylinder axis to the intersection point
	2. Calculate the vector from that point to the intersection

	```
	projection_length = (P - C) · A
	projected_point = C + (projection_length * A)
	N = normalize(P - projected_point)
	```

	Where:
	- `P` is the intersection point
	- `C` is the cylinder center
	- `A` is the cylinder axis (normalized)

	In our implementation:
	```
	to_point = subtract_vectors(intersection, cylinder.center)
	projection_length = dot_product(to_point, cylinder.axis)
	projected_point = add_vectors(cylinder.center, multiply_vector_by_scalar(cylinder.axis, projection_length))
	normal = subtract_vectors(intersection, projected_point)
	return normalize_vector(normal)
	```
6. ### Lighting and Shading

	The lighting model in our ray tracer combines multiple components to create realistic illumination. Each component simulates a different aspect of how light interacts with surfaces.

	#### 6.1 Components of the Lighting Model

	#### Ambient Lighting
	Ambient lighting represents indirect light that has bounced around the scene, providing base illumination even to areas not directly lit:

	```
	ambient_color = object_color * ambient_intensity
	```

	Where:
	- `object_color` is the intrinsic color of the object
	- `ambient_intensity` is a scene-wide ambient light level (typically 0.1-0.3)

	#### Diffuse Lighting (Lambertian Reflection)
	Diffuse lighting models light scattered equally in all directions from a matte surface. The intensity depends on the angle between the surface normal and light direction:

	```
	diffuse_intensity = max(0, dot(N, L)) * light_brightness
	diffuse_color = object_color * diffuse_intensity
	```

	Where:
	- `N` is the normalized surface normal vector
	- `L` is the normalized vector pointing toward the light source
	- `light_brightness` is the intensity of the light source
	- The `max(0, ...)` ensures surfaces facing away from the light receive no diffuse lighting

	#### Specular Lighting (Phong Model)
	Specular lighting creates highlights on shiny surfaces, simulating mirror-like reflection:

	```
	R = reflect(-L, N)  // Reflection of light direction around normal
	V = normalize(camera_position - intersection_point)  // View direction
	specular_intensity = pow(max(0, dot(R, V)), shininess) * light_brightness
	specular_color = specular_intensity * specular_color_factor
	```

	Where:
	- `R` is the reflection vector
	- `V` is the normalized view direction
	- `shininess` controls the size of the highlight (higher values = smaller, sharper highlights)
	- `specular_color_factor` typically uses a white or light gray color

	#### Attenuation
	Light diminishes with distance. The attenuation formula models this falloff:

	```
	distance = length(light_position - intersection_point)
	attenuation = 1.0 / (1.0 + a * distance + b * distance²)
	```

	Where:
	- `a` and `b` are coefficients controlling the rate of falloff
	- Common values: `a = 0.01`, `b = 0.001`

	#### 6.2 Shadow Calculation

	To determine if a point is in shadow:

	1. Create a shadow ray from the intersection point toward the light:
	   ```
	   shadow_ray_origin = intersection_point + normal * EPSILON  // EPSILON prevents self-shadowing
	   shadow_ray_direction = normalize(light_position - shadow_ray_origin)
	   ```

	2. Test for intersections with all objects in the scene:
	   ```
	   if any_intersection(shadow_ray_origin, shadow_ray_direction, scene_objects, 0, distance_to_light)
	       point_is_in_shadow = true
	   else
	       point_is_in_shadow = false
	   ```

	3. If the point is in shadow, exclude diffuse and specular components, leaving only ambient lighting

	#### 6.3 Unified Lighting Equation

	The final pixel color combines all lighting components:

	```
	if (in_shadow)
	    final_color = ambient_color
	else
	    final_color = ambient_color + 
	                  (diffuse_color + specular_color) * attenuation
	```

	Expanded form:

	```
	final_color = object_color * ambient_intensity +
	              (1 - in_shadow) * [
	                  object_color * max(0, dot(N, L)) * light_brightness +
	                  pow(max(0, dot(R, V)), shininess) * specular_color_factor * light_brightness
	              ] * (1.0 / (1.0 + a * distance + b * distance²))
	```

	In the implementation, we calculate this separately for each RGB color channel and clamp final values to the 0-255 range.

	#### 6.4 Implementation in the Ray Tracer

	In the render loop:

	1. Calculate the intersection point and surface normal
	2. Apply ambient lighting to the base object color
	3. For each light source:
	   - Check if the point is in shadow
	   - If not, calculate diffuse and specular contributions
	   - Apply attenuation based on distance
	   - Add these contributions to the final color
	4. Clamp RGB values to valid range (0-255)
	5. Set the pixel color

	This process repeats for every pixel in the rendered image, creating a complete scene with realistic lighting, shadows, and surface highlights.



<br>
<br>
<br>

## Conclusion

This mini ray tracer project has been an enjoyable and educational first step into the world of 3D graphics programming. Implementing these fundamental ray tracing concepts from scratch provided valuable insights into how light simulation works in computer graphics. While this implementation focuses on core functionality with basic primitives and lighting models, it establishes a foundation for further exploration. I'm excited to continue learning and expanding my knowledge in 3D graphics in the future, potentially exploring advanced features like reflection, refraction, texture mapping, and more sophisticated lighting models.