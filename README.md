# OpenGL Shader-Based Renderer – Assignment 4

**Course**: Computer Graphics  
**Instructor**: Dr. Ophir Weber  
**Student**: Ofri Caspi  
**Submission Date**: July 2025  

This project is part of a university-level Computer Graphics course.  
It replaces a legacy software rasterizer with a modern **OpenGL 4.6 hardware renderer** using the programmable pipeline and custom GLSL shaders.

---

## Features Implemented

- Support for **Phong** and **Gouraud shading** via vertex and fragment shaders  
- Per-fragment lighting  with material properties and up to 2 dynamic lights  
- Texture mapping using **FreeImage** (`.png`, `.jpg`)  
- Wavefront `.obj` model loader (supports `v`, `vt`, `vn`, `f`)
- Automatic normal computation and vertex averaging if normals are missing 
- Visualization of normals and bounding box
- Optional double-sided lighting support  
- Scene transformations via MVP matrices  

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
- Shader switching and lighting parameters are adjustable at runtime.
- Texture blending is done via the Phong and Gouraud model – including ambient, diffuse, and specular contributions.
  
---

## Credits

- Based on starter code provided by [Computer Graphics / Ophir Weber]
- Texture loading via [FreeImage](https://freeimage.sourceforge.io)
- Model parsing based on Wavefront OBJ format
- OpenGL programming and shader design by Ofri Caspi
