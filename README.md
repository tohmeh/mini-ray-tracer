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


	> ⚠️ **Note:** From now on, the math is specific to the ray tracer, not general math.

	### 3. Ray Mathematics

	#### Ray Definition :
	think of the ray as a ligne in the 3d dimension graph where direction vector is a slop, and origin point is the b in the famous childhood equation y=ax + b. This is the closet definition to my mind, ray components :
	- **Origin point**: The point from which the ray originates, typically denoted as `O` or `b`
	- **Direction vector**: A unit vector indicating the ray's direction, typically denoted as `D`

	The parametric equation of a ray is:
	```
	P(t) = O + t * D
	```

	Where:
	- `P(t)` is a point along the ray at parameter `t`
	- `t` is a non-negative scalar (t ≥ 0)
	- For any value of `t`, `P(t)` gives a point along the ray

	#### Camera and Ray Generation

	Ray generation is a fundamental step in ray tracing where we define rays that originate from the camera and pass through each pixel of the image plane.

	##### Coordinate Systems

	To generate rays properly, we need three perpendicular vectors that define the camera's orientation:
	1. **Forward vector**: Camera's viewing direction (normalized)
	2. **Right vector**: Perpendicular to the viewing direction, pointing to the right
	3. **Up vector**: Perpendicular to both forward and right vectors

	These vectors form an orthonormal basis for the camera's coordinate system.

	##### Field of View (FOV)

	The field of view determines how much of the scene is visible, measured in degrees. A wider FOV covers more of the scene but with more distortion.

	The relationship between FOV and the image plane size is:
	```
	scale = tan(FOV_radians / 2)
	```

	Where `scale` determines how far the corners of the image plane are from the center.

	##### Ray Generation Process

	1. **Convert FOV to radians**: 
	   ```
	   fov_rad = FOV_degrees * π / 180
	   ```

	2. **Calculate aspect ratio**:
	   ```
	   aspect_ratio = width / height
	   ```

	3. **Compute scale factor**:
	   ```
	   scale = tan(fov_rad / 2)
	   ```

	4. **For each pixel (i, j) in the image**:
	
	   a. Calculate normalized device coordinates (NDC):
	   ```
	   pixel_x = (2 * ((i + 0.5) / width) - 1) * aspect_ratio * scale
	   pixel_y = (1 - 2 * ((j + 0.5) / height)) * scale
	   ```
	
	   b. Transform NDC to world space direction:
	   ```
	   ray_dir = pixel_x * right + pixel_y * up + forward
	   ```
	
	   c. Normalize the direction vector:
	   ```
	   ray_dir = normalize(ray_dir)
	   ```
	
	   d. Create the ray:
	   ```
	   ray.origin = camera.position
	   ray.direction = ray_dir
	   ```

	##### The Role of Orthogonal Vectors

	Computing the right vector from the camera direction:
	```
	right = normalize(cross_product(world_up, direction))
	```

	Where `world_up` is typically (0, 1, 0).

	Computing the up vector:
	```
	up = cross_product(direction, right)
	```

	These orthogonal vectors ensure that the rays are generated correctly with respect to the camera's orientation.

	#### Ray-Object Intersections

	The core of a ray tracer is determining if and where a ray intersects objects in the scene.

	##### Ray-Sphere Intersection

	For a sphere with center `C` and radius `r`, a point `P` is on the sphere if:
	```
	|P - C|² = r²
	```

	Substituting the ray equation:
	```
	|O + t*D - C|² = r²
	```

	Expanding:
	```
	(O + t*D - C)·(O + t*D - C) = r²
	(D·D)t² + 2(D·(O-C))t + (O-C)·(O-C) - r² = 0
	```

	This is a quadratic equation:
	```
	a = D·D
	b = 2(D·(O-C))
	c = (O-C)·(O-C) - r²
	```

	If the ray direction is normalized, then `a = 1`, simplifying the equation.

	##### Ray-Plane Intersection

	For a plane defined by a point `P₀` and normal vector `n`, a point `P` is on the plane if:
	```
	(P - P₀)·n = 0
	```

	Substituting the ray equation:
	```
	(O + t*D - P₀)·n = 0
	```

	Solving for `t`:
	```
	t = (P₀ - O)·n / (D·n)
	```

	If `D·n = 0`, the ray is parallel to the plane (no intersection).

	##### Ray-Triangle Intersection

	Using the Möller–Trumbore algorithm:

	For a triangle with vertices `V₀`, `V₁`, and `V₂`, the intersection point can be represented as:
	```
	P = (1-u-v)V₀ + uV₁ + vV₂
	```

	Where `u` and `v` are barycentric coordinates.

	Setting up the equation:
	```
	O + t*D = (1-u-v)V₀ + uV₁ + vV₂
	```

	Rearranging:
	```
	[-D, V₁-V₀, V₂-V₀] [t, u, v]ᵀ = O-V₀
	```

	This can be solved using Cramer's rule or matrix inversion.

	#### Shading and Lighting

	Once an intersection is found, the color of the pixel is determined by:

	1. **Ambient Lighting**: Basic illumination present everywhere
	   ```
	   ambient_color = material_color * ambient_intensity
	   ```

	2. **Diffuse Lighting**: Lighting based on the angle between the surface normal and light direction
	   ```
	   diffuse_factor = max(0, normal·light_dir)
	   diffuse_color = material_color * light_color * diffuse_factor
	   ```

	3. **Specular Lighting**: Highlights on shiny surfaces
	   ```
	   reflection = reflect(-light_dir, normal)
	   specular_factor = pow(max(0, reflection·view_dir), shininess)
	   specular_color = light_color * specular_factor
	   ```

	4. **Shadows**: Determined by casting a ray from the intersection point to the light source
	   ```
	   shadow_ray.origin = intersection_point + normal * small_offset
	   shadow_ray.direction = light_direction
	   ```
	   If the shadow ray intersects any object before reaching the light, the point is in shadow.

	5. **Reflections**: Calculated by casting a ray in the reflection direction
	   ```
	   reflection_dir = reflect(ray_dir, normal)
	   reflection_ray.origin = intersection_point + normal * small_offset
	   reflection_ray.direction = reflection_dir
	   ```

	### 4. Implementation Notes

	The ray tracer follows these core principles:
	1. Cast rays from a virtual camera through each pixel
	2. Detect intersections with scene objects
	3. Calculate lighting at intersection points
	4. Determine pixel colors based on material properties and light interactions

	### 5. Getting Started

	*[Include instructions for building and running your ray tracer here]*

	### 6. Examples

	*[Include sample renders produced by your ray tracer here]*

	### 7. Resources

	For those interested in learning more about ray tracing:
	- [Ray Tracing in One Weekend](https://raytracing.github.io/)
	- [Scratchapixel](https://www.scratchapixel.com/)