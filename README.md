
## Upcoming Changes

Sources for the project will be added on 14.02.2023. Stay tuned!

# FdF - Wire Mesh Visualizer

FdF (Fil de Fer) is a 3D mesh visualizer that takes a wire mesh as input and generates a graphical representation of it. This project uses the minilibx library for graphical representation and comes bundled with the source code for the library.

## Prerequisites

- A MacOS-based operating system
- GCC Compiler

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

1. Clone the repository to your local machine:

git clone https://github.com/Vili-Valtteri/FdF.git fdf

2. Change your working directory to the cloned repository:

cd fdf

3. Compile the program using the Makefile:

make

4. Run the program by passing a wire mesh file as an argument:

./fdf <path-to-mesh-file>


## Wire Mesh Format

The wire mesh file is a text file that contains the 3D coordinates of the points that make up the mesh. Each line in the file represents a vertex and its x, y, and z coordinates are separated by spaces.

Example mesh file:  
0 0 0  
1 0 0  
1 1 0  
0 1 0  
0 0 1  
1 0 1  
1 1 1  
0 1 1  


## Controls

Once the program is running, you can interact with the mesh using the following controls:

- `↑`, `↓`, `←`, `→`: move the mesh up, down, left, and right respectively.
- `W`, `A`, `S`, `D`: rotate the mesh along the x-axis, y-axis, z-axis, and x-y plane respectively.
- `+`, `-`: zoom in and out of the mesh.
- `ESC`: exit the program.

## Built With

- minilibx - A minimalistic graphics library for MacOS.

## Author

- Vili-Valtteri Laine
