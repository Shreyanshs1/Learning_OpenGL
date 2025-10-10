## 2025-09-23 — OpenGL Learning

**Decision:** Chose OpenGL for learning game development.  
**Alternatives considered:** DirectX 11, DirectX 12, Vulkan, Metal.  
**Why chosen:** OpenGL is cross-platform and a good starting point for beginners.

## 2025-09-24 — Windowing Library

**Decision:** Use GLFW for windowing.  
**Alternatives considered:** SDL2.  
**Why chosen:** GLFW has a simpler syntax and is easier for beginners.  

## 2025-09-25 — Project Directory Structure

**Decision:** Changed directory structure of the project according to The Cherno’s YouTube Visual Studio setup for C++.  
**Alternatives considered:** Leaving the default directory structure.  
**Why chosen:** The custom structure is better suited for larger projects such as a game engine.  

## 2025-09-26 — GLFW Binaries

**Decision:** Downloaded 64-bit binaries of GLFW instead of 32-bit.  
**Alternatives considered:** 32-bit binaries.  
**Why chosen:** The 32-bit binaries were giving errors due to incompatibility.  

## 2025-09-26 — OpenGL Function Loader

**Decision:** Use GLEW to load OpenGL functions.  
**Alternatives considered:** GLAD.  
**Why chosen:** Following The Cherno’s YouTube tutorial.

## 2025-10-10 — Git revert

**Decision:** Revert entire project to initial commit.  
**Step Required** Use git log to find commit hash.
Use git reset --hard <hash> command to reset the branch.
Use git push origin main --force-with-lease to force push the changes into remote repository.
**Why chosen:** Easier compared to manually undo all changes.

## 2025-10-11 — OpenGL Function Loader

**Decision:** Starting to use GLAD.  
**Alternatives considered:** GLEW.  
**Why chosen:** GLEW is outdated, even cherno doesnt use it now.
