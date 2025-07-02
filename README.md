# Computer Graphics Chess

A 3D Chess Game with Custom Engine and Client

---

## Project Overview

**Computer Graphics Chess** is a fully hand-crafted 3D chess game developed in C++ with a custom-built graphics engine and client. The project demonstrates advanced computer graphics techniques, scene management, and interactive gameplay, all rendered in real time. The chessboard and pieces are visualized in a 3D environment, with a scene imported from an external OVO file and multiple camera perspectives.

---

## Features

- **Custom Graphics Engine**: Built from scratch, supporting scene graphs, mesh rendering, materials, lights, and cameras.
- **Interactive Chess Gameplay**: Full chess logic, including piece selection, movement, turn management, undo/redo, and win detection.
- **Scene Import**: Loads a 3D scene from an OVO file, including board, pieces, and environment.
- **Multiple Cameras**: Switch between fixed and free camera views for immersive gameplay.
- **Dynamic Lighting**: Toggle spotlights and interact with scene lighting in real time.
- **Keyboard and Mouse Controls**: Intuitive controls for both chess moves and camera navigation.

---

## Architecture Overview

### Engine
- The `engine/` directory contains the core graphics engine, responsible for rendering, scene management, camera handling, and object manipulation.
- The engine exposes a C++ API for initializing the window, setting callbacks, managing the scene graph, and rendering.

### Client
- The `client/` directory contains the chess game logic and user interface.
- Handles user input, chess rules, piece movement, and communicates with the engine for rendering and scene updates.

### Scene Import (OVO)
- The scene is described in an external `.ovo` file (`scena1.ovo`), which is parsed at runtime using the custom `OVOParser`.
- The parser reconstructs the scene graph, including nodes, meshes, materials, and lights, and integrates it into the engine.

### Camera System
- Two main cameras are set up: a "White" camera and a "Black" (free) camera, both using perspective projection.
- Users can switch between cameras and control the free camera with WASD and rotation keys.

### Chess Logic
- The chess rules are implemented in the `ChessLogic` class, which manages piece states, turn order, move validation, undo/redo, and win conditions.
- Each piece is represented by the `Piece` class, tracking its type, color, and position.

---

## Installation

### Prerequisites
- **C++20** compatible compiler (tested with GCC and MSVC)
- **OpenGL** development libraries
- **FreeGLUT** and **FreeImage** libraries (provided in `dependencies/`)
- **CMake** or **Make** (for Linux)
- **Visual Studio 2022+** (for Windows, optional)

### Building on Linux
1. Install required system packages:
   ```sh
   sudo apt-get install build-essential libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev libfreeimage-dev
   ```
2. From the project root, build the engine and client:
   ```sh
   make
   ```
   This will compile both the engine and client. Binaries will be placed in `engine/bin/` and `client/`.

### Building on Windows
- Open `baseline.sln` in Visual Studio 2022 or later.
- Build the solution (both `engine` and `client` projects will be built).
- Ensure the required DLLs (e.g., `engine.dll`, `FreeImage.dll`, `freeglut.dll`) are available in the executable directory or in your system PATH.

---

## Usage

### Running the Game
- On Linux:
  ```sh
  cd client
  ./chessGame
  ```
- On Windows:
  - Run `client.exe` from the `demo/Windows/` directory or from your build output.

### Controls

**Game Controls:**
- **Left Mouse Click**: Select a chess piece
- **Arrow Keys**: Move selected piece
- **Enter**: Confirm move
- **Z**: Undo last move
- **V**: Redo last move
- **R**: Reset game
- **ESC**: Quit game

**Environment Controls:**
- **L**: Toggle spotlight
- **C**: Switch camera

**Free Camera Controls:**
- **W/A/S/D**: Move camera
- **Q/E/Y/X**: Rotate camera

---

## Project Structure

```
ComputerGraphicsChess/
  engine/         # Custom graphics engine (core rendering, scene, camera, etc.)
  client/         # Chess game logic, main application, and assets
  dependencies/   # Third-party libraries (FreeGLUT, FreeImage, GLM)
  demo/           # Pre-built binaries and assets for Windows/Linux
  Makefile        # Top-level build script
  README.md       # Project documentation
```

---

## Contributing

Contributions are welcome! Please open issues or pull requests for bug fixes, improvements, or new features. For major changes, please discuss them via issue first.

---

## Author

- Marco Lorusso
- SUPSI - Bachelor of Science in Computer Science

---
