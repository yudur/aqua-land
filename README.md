# Aqua Land - Water Reservoir Simulation

A water reservoir simulation game built with HTML/CSS/JavaScript and C using the Raylib library.

## Project Structure

```
aqua-land/
└── web
    ├── index.html          # Landing page
    ├── in-game.html        # Web-based
    ├── assets/             # Images and icons
    │   ├── ondas.png
    │   ├── chover.png
    │   ├── sol.png
    │   └── reset.png
    └── game/               # C implementation
        ├── main.c          # Source code
        └── main.exe        # Compiled executable
```

### Running

Simply open `index.html` in your browser. No setup required!

---

## C Version with Raylib

### Prerequisites

#### 1. MSYS2 (Windows)

MSYS2 provides a Unix-like environment on Windows with package management.

**Installation:**

1. Download MSYS2 from [https://www.msys2.org/](https://www.msys2.org/)
2. Run the installer and install to `C:\msys64` (default location)
3. After installation, open **MSYS2 MINGW64** terminal (NOT MSYS2 MSYS!)

**Update MSYS2:**

```bash
pacman -Syu
```

Close the terminal when prompted, then reopen it and run:

```bash
pacman -Su
```

#### 2. Install Development Tools

In the **MSYS2 MINGW64** terminal, install the compiler and Raylib:

```bash
# Install GCC compiler and build tools
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make

# Install Raylib graphics library
pacman -S mingw-w64-x86_64-raylib
```

#### 3. VS Code Setup (Optional but Recommended)

**Install VS Code Extensions:**

- C/C++ (Microsoft)
- C/C++ Extension Pack

**Configure IntelliSense:**

Create `.vscode/c_cpp_properties.json`:

```json
{
  "configurations": [
    {
      "name": "Win32",
      "includePath": ["${workspaceFolder}/**", "C:/msys64/mingw64/include"],
      "defines": ["_DEBUG", "UNICODE", "_UNICODE"],
      "compilerPath": "C:/msys64/mingw64/bin/gcc.exe",
      "cStandard": "c17",
      "cppStandard": "c++17",
      "intelliSenseMode": "windows-gcc-x64"
    }
  ],
  "version": 4
}
```

**Configure Build Task:**

Create `.vscode/tasks.json`:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build Aqua Land",
      "type": "shell",
      "command": "C:/msys64/mingw64/bin/gcc.exe",
      "args": [
        "${workspaceFolder}/game/main.c",
        "-o",
        "${workspaceFolder}/game/main.exe",
        "-lraylib",
        "-lopengl32",
        "-lgdi32",
        "-lwinmm"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"],
      "detail": "Compile with Raylib"
    }
  ]
}
```

### Compiling the Game

#### Option 1: Using VS Code

1. Open the project folder in VS Code
2. Press `Ctrl+Shift+B` to build
3. The executable `main.exe` will be created in the `game/` folder

#### Option 2: Using Command Line

**In PowerShell (Windows):**

```powershell
cd game
C:\msys64\mingw64\bin\gcc.exe main.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

**In MSYS2 MINGW64 Terminal:**

```bash
cd game
gcc main.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Resolving DLL Issues

If you get "DLL not found" errors when running `main.exe`, copy these files from `C:\msys64\mingw64\bin\` to your `game/` folder:

```
libraylib.dll
glfw3.dll
libgcc_s_seh-1.dll
libwinpthread-1.dll
```

**Quick copy command (PowerShell):**

```powershell
Copy-Item C:\msys64\mingw64\bin\libraylib.dll game\
Copy-Item C:\msys64\mingw64\bin\glfw3.dll game\
Copy-Item C:\msys64\mingw64\bin\libgcc_s_seh-1.dll game\
Copy-Item C:\msys64\mingw64\bin\libwinpthread-1.dll game\
```

### Running the Game

**Option 1: Double-click** `main.exe` in File Explorer

**Option 2: From terminal:**

```powershell
cd game
.\main.exe
```

**Option 3: Using VS Code:**

```powershell
cd game
Start-Process .\main.exe
```

---

## How to Play

### Controls

- **Chover (Rain)**: Click to add water (+10%)
- **Evaporar (Evaporate)**: Click to remove water (-10%)
- **Reiniciar (Reset)**: Click to reset water level to 20%

### Water Levels

- **0-29%**: 🔴 Critical (Red)
- **30-59%**: 🟠 Moderate (Orange)
- **60-100%**: 🟢 Good (Green)

The color-coded indicator bar on the left shows your current water level status.

---

## Troubleshooting

### Problem: "raylib.h not found"

**Solution:** Make sure Raylib is installed:

```bash
pacman -S mingw-w64-x86_64-raylib
```

### Problem: "undefined reference to InitWindow"

**Solution:** Add linking flags to your compile command:

```
-lraylib -lopengl32 -lgdi32 -lwinmm
```

### Problem: "glfw3.dll not found" when running

**Solution:** Copy the DLL from MSYS2 to your game folder:

```powershell
Copy-Item C:\msys64\mingw64\bin\glfw3.dll game\
```

### Problem: Window opens and immediately closes

**Solution:** Run from terminal to see error messages:

```powershell
cd game
.\main.exe
```

---

## Learning Resources

### Raylib Documentation

- Official Website: [https://www.raylib.com/](https://www.raylib.com/)
- API Reference: [https://www.raylib.com/cheatsheet/cheatsheet.html](https://www.raylib.com/cheatsheet/cheatsheet.html)
- Examples: [https://www.raylib.com/examples.html](https://www.raylib.com/examples.html)

## Code Overview

### Key Features

1. **Dynamic Color System**: Water level determines indicator color (red/orange/green)
2. **Gradient Rendering**: Manual gradient drawing using color interpolation
3. **Interactive Controls**: Mouse-based button interaction
4. **Responsive Visuals**: Bars that grow/shrink with water level

**Enjoy the simulation! 💧**
