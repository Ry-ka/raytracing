# README - Final Project

## Author Information
- **Name:** Sungwoo Kang
- **Student ID:** 107609094

## Program Description
This program is a ray tracer based off of the code and guide provided in Ray Tracer Over the Weekend. It extends the existing code to create a custom scene that can be animated. It also includes support for polygons using triangle based mesh through importing custom obj files. This directory includes an animated sequence of an icosphere (loaded using the obj file) orbiting about a central sphere and rotating about its own axis. A comparable scene is also included using POVray. The frame data and code is all included within this directory.

## File Organization
- `custom scenes`: This folder includes the mp4 files for the custom scenes. Inside you will find both the generated video for the project implementation as well as the Pov ray comparison.
- `frames`: This folder includes the frame data for the implementation custom scene.
- `frames_pov`: This folder includes the frame data for the povray custom scene.
- `povfiles`: This folder includes everything that was used to generate the povray scene.
- `Readme.md`: The documentation file providing details about the program, including build and run instructions.

## Highlights
The implementation is based off of the "Ray Tracing over the Weekend" guide, so the changes and additions to that code base will be highlighted here.
- `main.cpp`: This file is the main driver that hosts the scene. It defines static spheres (one in the center and smaller random spheres scattered around it) as well as an icosphere loaded in from the icosphere.obj file. The icosphere rotates about its own axis while orbiting around the large central sphere. The central sphere is composed of a reflective material and the icosphere is composed of a water like material. This was done to show off the ray tracer's capabilities such as reflection and refraction. 
- `triangle.h`: This file is both the header and the implementation of the triangle class, which is an implementation of the hittable interface. This class mainly allows the mesh to use it in order to load obj files and create triangle based objects, which can then be ray tested for ray-triangle intersections. The main algorithm is the Möller–Trumbore intersection algorithm. [Here](https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm) you can find more information on this algorithm.
- `mesh.h`: This header and implementation file defines the mesh class, which is an implementation of the hittbel class and uses the triangle class to create complex objects defined in obj files composed of triangles. It allows importation of custom obj files to load them into the ray tracer. It supports transformations and material handling and vertex and triangle storage. It delegates the hit function to the triangle class.
- `transform.h`: This header and implementation file is a helper class (composed of static functions) to manage the transformations of the mesh easier. The eigen class is used (included in the directory) to manage the complex matrix math and management. This class supports basic transformations such as scale, rotate, and translations.

## Comparison Between POVray and the Ray Tracer
- `Render Times`: The main difference that I noticed between the two is that my implementation of the ray tracer is maginitudes slower. The 240 frames took approximately 10 hours to render and save, while the 240 frames from the povray took less than 10 minutes. This is mainly due to the fact that the guide "Ray Tracer over the Weekend" prioritizes code simplicity and readability over runtime efficiency for the sake of the readers. 
- `Capabilities`: I can't comment on this too much because my knowledge of POV ray is very limited. I tried to create a similar scene in povray, but as you can see from the videos in custom scenes it wasn't exactly the same. I'm sure that POV ray has many features that dwarf this code in terms of use. 

## A Word on the Orbit Math
Although I call it an orbit, it's not an orbit in the scientific sense. It's a cicular path with a radius large enough to look like an orbit around the central sphere. This was mainly included to create an interesting scene to render. It rotates in the xz plane, and has no y-coordinate changes. The funtions `cos(theta) * orbit_radius` and `sin(theta) * orbit_radius` can be used to calculate the x and z positions along the unit circle contained within the xz plane respectively. 


## How to Build and Run the Program

1. Extract the project files if they are archived.

    ```bash
    unzip 9094Final.zip
    ```

2. Navigate to the project directory:

    ```bash
    cd 9094Final
    ```

3. To make the program, run:

    ```bash
    make clean
    make
    ```

4. To run the program, run:

    ```bash
    ./raytracer
    ```
