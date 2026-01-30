<div align="center">

  <img src="docs/SMB3.png" alt="Super Mario Icon" width="300">

  # Super Mario World 6-9

  ![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B)
  ![Qt](https://img.shields.io/badge/Framework-Qt-41CD52?style=for-the-badge&logo=qt)
  ![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

  <br>

  **A recreation of the famous World 6-9 level using [C++](https://isocpp.org/) and the [Qt Framework](https://www.qt.io/).**

</div>

---

## 📝 About The Project

This project is a faithful reproduction of the **World 6-9** level from the Super Mario universe. The goal was to build a platformer game engine from scratch using **C++** and **Qt**, handling physics, collisions, and enemy AI.

---

## 🗺️ Level Map

Here is the complete layout of the level we recreated. The game features underwater mechanics, pipes, and complex collisions just like the original.

![World 6-9 Map](docs/SMB3_World_6-9_Map.png)

---

## 🚀 How to Run

Choose your preferred way to get the game running:

<details>
<summary><b>🎮 Download & Play (Ready to Run)</b></summary>

If you just want to play without compiling the code:

1. Go to the **[Releases](https://github.com/giusalfieri/Super_mario/releases)** page.
2. Download the `.zip` file for your OS (e.g., `SuperMario_Win64.zip`).
3. Extract the archive to a folder of your choice.
4. Run the executable `supermario3.exe` (Windows) or `supermario3` (Linux/Mac).
</details>

<details>
<summary><b>🛠️ Build from Source (Step-by-Step)</b></summary>

Follow these detailed instructions to set up the environment and compile the project manually.

### 1. Prerequisites
* **Git**: To clone the repository.
* **CMake (3.16+)**: For build management.
* **Compiler**: 
    * **Windows**: Visual Studio 2019/2022 with C++ workload.
    * **Linux**: GCC/G++.
    * **Mac**: Clang (Xcode).
* **Qt 5.15.2 DevBinaries**: Download the specific binaries for your OS from our [Releases](https://github.com/giusalfieri/Super_mario/releases) (e.g., `qt-5.15.2-win64-msvc.zip
`) and extract them locally.

### 2. Cloning
```bash
git clone https://github.com/giusalfieri/Super_mario.git
cd Super_mario
```

### 3. Configuration (Windows - Visual Studio)
1. Launch Visual Studio and select **"Open a local folder"**.
2. Navigate to and select the project root directory; Visual Studio will automatically detect the `CMakeLists.txt` file.
3. From the top menu, navigate to **Project > CMake Settings**.
4. Locate the **CMake variables and cache** section and click **Add**:
    * **Name**: `CMAKE_PREFIX_PATH`
    * **Value**: The local path where you extracted the DevBinaries (e.g., `C:/Qt/5.15.2/msvc2019_64`).
5. Save the configuration (**Ctrl + S**); Visual Studio will then automatically generate the CMake cache.

### 4. Configuration (Linux / macOS - Terminal)
Open your terminal in the project root directory and execute the following commands:

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="/your/extracted/qt/path"
cmake --build .
```

### 5. Build & Execution
* **Visual Studio**: Select `supermario3.exe` from the startup item dropdown and press **F5** to compile and launch the game.
* **Terminal**: Locate and run the generated executable within the `build` directory.

> [!Note for Windows Users]
>  The CMake configuration is scripted to automatically invoke `windeployqt`. This utility bundles all required Qt shared libraries (.dll) and essential plugins (audio, platforms) directly into the output folder, ensuring a seamless "out-of-the-box" execution experience.

</details>

---

## 👥 Contributors

Our development team has worked to recreate this classic experience with modern tools:

| Name            | GitHub Account                                       |
|-----------------|------------------------------------------------------|
| **Giuseppe Alfieri** | [@giusalfieri](https://github.com/giusalfieri)       |
| **Nico Fiorini** | [@capocattiveria](https://github.com/capocattiveria) |
| **Jacopo Saccocci** |                                  |
