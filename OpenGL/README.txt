# OpenGL Shader-Based Renderer – Assignment 4

This project is part of a university-level Computer Graphics course.  
It replaces a legacy software rasterizer with a modern **OpenGL 4.6 hardware renderer** using the programmable pipeline and custom GLSL shaders.

---

## Features Implemented

- Support for **Phong** and **Gouraud shading** via vertex and fragment shaders  
- Per-fragment lighting using material properties and up to 2 lights  
- Texture mapping using **FreeImage** (`.png`, `.jpg`)  
- Modular object loading from Wavefront `.obj` files (supports `v`, `vt`, `vn`, and `f`)  
- Normal computation and per-vertex averaging (if normals are not provided)  
- Visual debug mode with per-vertex coloring  
- Optional double-sided lighting support  
- Scene transformations via MVP matrices  
- will be added: Planned support for animation, deformation, and normal mapping

---

## Example Screenshot

> --need to add -- 

---

## Requirements

- **OpenGL 4.6+** core profile  
- **GLEW** or **GLAD** (OpenGL function loader)  
- **FreeGLUT** (window + input)  
- **FreeImage** (image loading)  
- **GLM** (math library)

---

##  Build Instructions (Visual Studio)

1. Open the provided Visual Studio solution (`Assignment4.sln`)
2. Set the "OpenGL" project as **Startup Project**
3. Build & Run  
4. Use the GUI (AntTweakBar) to toggle lighting options, models, etc.

---

## Notes

- Models must be in `.obj` format and may include `vt` and `vn` data.
- Texture coordinates (`vt`) are respected per-`face`, not per-vertex, which ensures proper mapping.
- Shader switching and lighting parameters are adjustable at runtime.
- Texture blending is done via the Phong and Gouraud model – including ambient, diffuse, and specular contributions.
  
---

## Credits

- Based on starter code provided by [Computer Graphics / Ophir Weber]
- Texture loading via [FreeImage](https://freeimage.sourceforge.io)
- Model parsing based on Wavefront OBJ format
- OpenGL programming and shader design by [Your Name]

---

## To Be Done

- [ ] Add deformation shader
- [ ] Add animation (Bezier + SLERP)
- [ ] Integrate normal mapping for more realism
