*This project has been created as part of the 42 curriculum by mvillavi, fbanzo-s.*

# cub3D — My first RayCaster with miniLibX

## Description

cub3D is a 3D maze exploration game inspired by Wolfenstein 3D, the legendary first-person shooter developed by id Software in 1992. The project implements ray-casting to render a dynamic, textured first-person perspective view of a maze defined by a `.cub` configuration file.

The goal is to navigate through a maze rendered in pseudo-3D, with different wall textures depending on the cardinal direction faced (North, South, East, West), configurable floor and ceiling colors, and a set of bonus features including enemies, doors, and a minimap.

### Bonus features implemented
- **Minimap** — a small top-down overlay showing the player's position and surroundings in real time.
- **Doors** — vertical doors use the `|` character and horizontal doors use `_` in the map. Players can open and close them by walking up to them.
- **Enemies** — represented by the `e` character in the map. The parser detects their presence automatically and the game adapts accordingly.

> Note: there is no separate `make bonus` rule. A single `make` compiles the full program with all features included.

---

## Instructions

### Dependencies

- A Linux system with OpenGL and GLFW3 installed (required by MLX42).
- `cc` compiler, `cmake`, and standard build tools.

Install dependencies on Ubuntu/Debian:
```bash
sudo apt-get install -y libglfw3-dev libgl1-mesa-dev
```

### Compilation

```bash
make
```

This compiles the full project including all bonus features (minimap, doors, enemies). There is no separate bonus target.

To clean object files:
```bash
make clean
```

To fully clean (including the binary):
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

### Execution

```bash
./cub3D maps/<map_name>.cub
```

Example maps are provided in the `maps/` directory:
- `maps/small.cub` — a simple map for quick testing
- `maps/hallway.cub` — a corridor-based map
- `maps/enemies.cub` — a map with enemies
- `maps/alone.cub` — a map without enemies

### Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move forward / left / backward / right |
| `←` `→` | Rotate the camera left / right |
| `E` | Interact with doors (open/close) |
| `ESC` | Quit the program |
| Mouse | Rotate the point of view |

---

## Map Format

Maps use the `.cub` extension. The configuration file must declare the following elements before the map:

```
NO ./path/to/north_texture.png
SO ./path/to/south_texture.png
WE ./path/to/west_texture.png
EA ./path/to/east_texture.png

F R,G,B
C R,G,B
```

### Map characters

| Character | Meaning |
|-----------|---------|
| `1` | Wall |
| `0` | Empty floor |
| `N` `S` `E` `W` | Player spawn + initial direction |
| `\|` | Vertical door |
| `_` | Horizontal door |
| `e` | Enemy spawn point |

The map must be fully enclosed by walls. It must be the last element in the `.cub` file.

---

## Resources

### Ray-casting & graphics
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for the ray-casting algorithm, DDA, and texture mapping.
- [Ray-casting in C — Ismail Assil](https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13) — a practical C-focused walkthrough of the ray-casting implementation.
- [Wolfenstein 3D Ray-casting in C — Tim Allan Wheeler](https://timallanwheeler.com/blog/2023/04/01/wolfenstein-3d-raycasting-in-c/) — another C implementation reference, useful for cross-checking approaches.
- [ray-cast reference project by Saxsori](https://github.com/Saxsori/ray-cast) — a 42-student implementation used as a conceptual reference.
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) — the graphics library used in this project.
- [Wolfenstein 3D (playable)](http://users.atw.hu/wolf3d/) — the original game that inspired this project.

### How AI was used

**Gemini** was used in the following ways during this project:

- **Understanding mathematics** — Gemini was the main tool used to understand the mathematical concepts behind ray-casting: vectors, trigonometry, the DDA algorithm, projection formulas, and texture coordinate calculations. It complemented the written guides by explaining concepts interactively.
- **Debugging help** — when stuck on specific bugs (e.g., incorrect texture offsets, wall collision edge cases), Gemini was used to explain potential causes and suggest approaches. All suggestions were reviewed, tested, and adapted manually.
- **Code review** — portions of the parser and validator were discussed with Gemini to spot potential issues, which were then verified against the subject requirements and tested by both partners.
- **README writing** — this README was drafted with AI assistance and reviewed/edited to accurately reflect the actual implementation.

