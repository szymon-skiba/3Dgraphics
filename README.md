# Phong Shading Simulation

This project demonstrates the implementation of Phong shading. The simulation displays a shaded sphere that can be interactively manipulated to observe the effects of different lighting and material properties.

## Features

- Real-time Phong shading effects.
- Interactive controls to modify lighting and material properties such as diffuse, specular, and ambient components.
- Adjustable light position using keyboard controls.
- Rotation of scene along y axis for visualisation of algorithm effects. 
- Resettable rotation for quick orientation resets.

## Prerequisites

Before building and running this project, ensure you have the following installed:
- OpenGL


These libraries are essential for rendering and managing OpenGL contexts and inputs. Make sure your development environment is set up to use these libraries.

## Building the Project with Makefile

To build this project, use the command **make** in the project directory.

This will compile the source files and link the required libraries into an executable named `sphere`. To clean the build, use **make clean**.

## Running the Simulation

After building the project, you can run the simulation by executing **./sphere**.

## Controls

- **Arrow Keys**: Move the light source in X and Y directions.
- **C and V**: Move the light source closer or further away in the Z direction.
- **Q, A**: Increase or decrease the diffuse component.
- **W, S**: Increase or decrease the ambient component.
- **E, D**: Increase or decrease the specular component.
- **R, F**: Increase or decrease the shininess exponent.
- **T, G**: Increase or decrease the number of slices and stacks on the sphere.
- **Z, X**: Rotate the scene left or right.
- **Space**: Reset the rotation of the sphere to the initial orientation.

## Contributing

Contributions to this project are welcome. Please fork the repository and submit pull requests with any enhancements or bug fixes.

