# 🐍 Goose Game (Gioco dell’Oca)

This project is a text-based implementation of the classic **Goose Game**, entirely developed in **Italian** as required for a university programming course. It includes support for saving games, displaying player rankings, and multiple modular features.

---

## 📁 Project Structure

- `src/` — C source code organized into modules  
  - `main.c`, `costanti.h` — Main program entry and constants  
  - `modulo_*/` — Submodules handling different game logic  
  - `file_di_gioco/` — Menu texts, game rules, and save data (binary and text files)
- `doc/` — HTML documentation generated from the source code
- `out/` — Folder where the executable is created after running the `.bat` file
- `compila_ed_esegui.bat` — Batch script to compile and run the game on Windows

## ▶️ How to Run

1. Clone or download this repository.
2. Run the `compila_ed_esegui.bat` file (double-click on Windows):
   - Compiles the source code automatically.
   - The executable is placed in the `out/` folder.
   - The game will start in the command-line interface.

📌 **Note**: A C compiler is required (e.g., GCC via MinGW or Dev-C++).

---

## 🎮 Game Features

- Console-based text interface
- Start new games and resume saved ones
- Player ranking system with persistent scores
- In-game help and rule sections
- Data persistence through binary files

---

## 📄 Documentation

Technical documentation is available in the `doc/` folder.  
To read it, open `index.html` in your browser.

📝 **Note**: All source code comments and documentation are in Italian.

---

## ✅ Requirements

- OS: Windows
- Compiler: Any ANSI C compatible compiler (e.g., GCC)

---

## 👤 Author

This project was developed by Luca Ardito, student ID 777818 at the University of Bari (Uniba). It was carried out during the 2022-2023 academic year for the Programmi Lab course, taught by Professor Fabio Abbattista.

