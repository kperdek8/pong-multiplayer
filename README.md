# Pong Multiplayer

## About

In this project I am planning to create simple Pong game and implement as many low level features as possible.

## Planned Features

* Multithreading
* Multiplayer with basic networking
* Rendering using SDL (with future plans to replace it with OpenGL/Vulkan context)
* Audio processing for sound effects
* AI opponent

## Roadmap

### 1. Setup

1.1 **Set Up Project**

- [x] Define project's roadmap.
- [x] Set up directory structure.
- [x] Set up CMake files and make them modular.
- [x] Set up GitHub repository.

### 2. Basic Game Implementation

2.1 **Implement Core Game Logic**

- [x] Create basic game mechanics (ball movement, paddle control).
- [x] Implement collision detection for ball and paddles.
- [x] Add scoring system.

2.2 **Basic Rendering**

- [X] Set up a simple game window using SDL.
- [X] Render game elements (ball, paddles, background).
- [ ] Set up scene handler

2.3 **Input Handling**

- [ ] Implement keyboard input for paddle control.
- [ ] Add basic mouse input handling.

### 3. Multithreading

3.1 **Multithreading Basics**

- [ ] Separate game logic and rendering into different threads.

### 4. Networking and Multiplayer

4.1 **Basic Networking**

- [ ] Set up server-client architecture.
- [ ] Implement basic data transmission for game state.

### 5. Gameplay Enhancement

5.1 **Game Rules**

- [ ] Add new game rules e.g. different ball physics/behaviour, paddle sizes etc.
- [ ] Make game rules selectable.

### 6. Audio Integration

5.1 **Sound Effects**

- [ ] Add sound effects for in-game events (ball hit, score).

### 7. Artificial Intelligence

6.1 **Basic AI**

- [ ] Implement a simple AI opponent.
- [ ] Create different difficulty levels.

### 8. Advanced Rendering (OpenGL)

7.1 **OpenGL Setup**

- [ ] Initialize OpenGL window.
- [ ] Render game elements using OpenGL.
- [ ] Render text/fonts using OpenGL.

7.2 **Shaders and Effects**

- [ ] Implement basic shaders for rendering.
- [ ] Add visual effects like shadows, reflections, etc.
- [ ] Add particles
