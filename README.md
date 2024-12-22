# Graphic Api
## A C++ 20 graphic api using OpenGL 4.6
The library offers a way to use low-level graphic features in an object-oriented way, such as Meshes, Shaders, Textures, Buffers... while keeping consistency thanks to check between C++ and shaders struct layout.\
I recently integrated new OpenGL things like [DSA](https://www.khronos.org/opengl/wiki/Direct_State_Access), [SSBOs](https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object) and [SPIR-V](https://www.khronos.org/opengl/wiki/SPIR-V) shaders.

### Input system
It handles keyboard, mouse and gamepad in a unified way (like Unity and Unreal). Each input can be remapped and have modifiers like normalize or dead zone.

### Maths
The library adds classes for Vector 2/3/4, Matrix of any dimensions, Quaternion and Transform.

### Examples
You can find some code samples in the [Test](https://github.com/Renberget/Engine/tree/master/Test) folder. The image used for testing comes from [here](https://aamatniekss.itch.io/fantasy-knight-free-pixelart-animated-character).

### External dependencies
- GLFW 3.4
- OpenGL 4.6
- stb_image 2.30
- stb_image_write 1.16

### Goal
I plan to add more features to make my a fully functionnal game engine.
