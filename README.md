# Tetris-Replica
---
## A classic Tetris remade in C++ using TMPL8

**Tetris-Replica** is a project where I tried to recreate one of the most iconic games ever made.  
The game features falling Tetrominoes, line clearing, rotation, scoring, and proper grid collision detection — all implemented from scratch.

---

## Features

- Fully working **10×20** Tetris grid
- Classic **Tetromino shapes** (randomly spawned)
- Horizontal movement + rotation support
- Automatic gravity + fast-drop mode
- Piece locking & static grid handling
- Full-line detection and deletion
- Score increments based on cleared lines
- Simple colored tiles displayed from a sprite sheet

---

## Gameplay

Move and rotate Tetrominoes as they fall to complete and clear rows.  
Survive as long as possible and keep the grid from filling up!

### Controls
| Key | Action |
|-----|--------|
| **A** | Move Left |
| **D** | Move Right |
| **R** | Rotate Piece |
| **Hold Q** | Fast Drop |

Each locked piece becomes part of the static grid, triggering line checks and score updates.

---

## Project Notes

This project was created as a **C++ learning exercise** to improve:

- Collision detection with a static grid
- Array-based shape manipulation
- Rotation via matrix transformations
- Input reading and timing logic for falling pieces
- Grid rendering and score display

---

## Future Enhancements

- Add more polished UI and game-over screen
- Smooth movement and animations
- Hard-drop and hold piece functions
- Game over contidion
- Better sprite work and background
