# cub3D

**cub3D** is a raycasting-based 3D engine inspired by early first-person shooters like *Wolfenstein 3D*. It renders a 3D maze from a `.cub` file using MiniLibX, and allows interactive movement, camera rotation, wall collisions, and even shooting animations.

This project was developed in collaboration with my course mate [Murilo](https://github.com/murilodsd).

---

## Features

- **Raycasting Engine**: Simulates a first-person 3D view using a raycasting algorithm.
- **Directional Textures**: Renders different textures for each wall direction (North, South, East, West).
- **Texture Requirements**: All textures must be `.xpm` images sized **256×256 pixels**.
- **Custom Colors**: Supports RGB color configuration for both floor and ceiling.
- **Map Parsing**: Parses `.cub` scene files with flexible element ordering and layout.
- **Player Movement**: Navigate the maze using `W`, `A`, `S`, and `D` keys.
- **Camera Rotation**: Use arrow keys or mouse movement *(bonus)* to rotate the view.
- **Wall Collision**: Prevents walking through walls *(bonus)*.
- **Shooting Mechanic**: Click to shoot; displays an animated gun sprite *(bonus)*.
- **Robust Exit Handling**: Clean exit via `ESC`, window close button, or internal error.

---

## Installation

> ⚠️ **MiniLibX is required but not bundled.** Install it manually before compiling.

### Clone the repository

```bash
git clone git@github.com:danielarjordao/cub3D.git
```

### Install MiniLibX (for Linux)
```bash
cd cub3D/lib
git clone https://github.com/42Paris/minilibx-linux.git minilibx
sudo apt-get install libxext-dev libx11-dev
```

### Compile the project
```bash
cd ..
make
```

## Usage
```bash
./cub3D maps/example.cub
```
The program takes exactly one argument: the path to a valid .cub map file.

### Controls
| Key / Action       | Function                     |
| ------------------ | ---------------------------- |
| `W`, `A`, `S`, `D` | Move forward/left/back/right |
| `←`, `→`           | Rotate camera                |
| `Mouse Move`       | Rotate view (bonus)          |
| `Mouse Click`      | Shoot (bonus)                |
| `ESC` / `X` icon   | Exit the game                |

### Map File Format (.cub)
A valid .cub file contains:

Texture paths for all four wall directions:
```bash
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm
```
Textures must be .xpm files, and must be 256×256 pixels.

Floor and ceiling RGB colors:
```bash
F 30,30,30
C 200,200,255
```
Values must be in the range 0–255.

Map layout made of:
- 1: wall
- 0: empty space
- N, S, E, W: player start position + direction
- ' ' (space): empty, treated as out-of-bounds (only allowed outside the external wall border)

#### Map Rules
- The map must be enclosed entirely by walls (1).
- Only one player start position is allowed.
- The map must come last in the file.
- Spaces ' ' are valid characters, but only outside the playable area (i.e., between outer walls).
- You must handle misaligned maps and space-padding safely.

Example .cub file
```bash
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 30,30,30
C 200,200,255

        1111111111
        1000000001
1111111110N0000001
100000000000000001
111111111111111111
```

### Makefile Targets
- `make` / `make all` — Build the program
- `make clean` — Delete object files
- `make fclean` — Delete objects and executable
- `make re` — Rebuild everything
- `make bonus` — Compile with bonus features
