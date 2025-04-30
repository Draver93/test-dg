# Test Project
<p align="center">
<img src="./example/screenshot.png" alt="Cube" width="100%">
</p>

This is a lightweight real-time 3D engine built for Android using C++, OpenGL ES 3.0, and CMake, designed as a test project for showcasing engine architecture and real-time rendering capabilities.

## About the Project

The engine demonstrates core ECS (Entity Component System) principles and modern rendering practices on Android devices. The focus was on clean architecture, extensibility, and performance.

### Key Features

- ✅ Written in C++ with OpenGL ES 3.0
- ✅ Built using Android Studio + CMake with automatic dependency fetching
- ✅ Custom ECS system (GameObject + Component model)
- ✅ GLTF model loading via TinyGLTF
- ✅ Support for multiple cameras with scene-active selection
- ✅ Custom `Transform` component supporting position, scale, and rotation via quaternions
- ✅ Real-time directional + point light system (up to 8 lights)
- ✅ Custom material system with automatic uniform binding
- ✅ Basic input/event system
- ✅ Component-based scripting support

### Default Scene

The default scene loads a single cube model with 3 dynamic light sources.  
The cube has a `Script` component attached that handles its rotation using the engine's event system.

---

This project was created as part of a technical test submission. Feel free to explore or reach out for any clarifications.
