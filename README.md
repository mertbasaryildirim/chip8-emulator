<div align="center">
  <img src="assets/chip8-cover.png" alt="chip8-emulator-cover">
</div>

# CHIP-8 Emulator

> A minimal, fast, and fully-implemented CHIP-8 emulator written in C — built with clean architecture, readable instruction decoding, and accurate behavior inspired by modern CHIP-8 specifications.

---

## 📖 Description

This project is a complete CHIP-8 emulator implemented in C, designed with clarity, correctness, and maintainability in mind.  
It faithfully reproduces the behavior of a modern CHIP-8 virtual machine, including:

- A 4 KB memory model
- 16 general-purpose registers
- A 16-level call stack
- Timers (delay & sound)
- Input keypad handling
- Full display instructions and XOR-based drawing
- Complete opcode support, implemented one-by-one with readable, isolated logic

The emulator focuses on _transparency over abstraction_ — each instruction (from `0x00E0` to `0xFx65`) is individually defined, decoded, and executed in a clean structure that makes the execution model easy to understand and extend. The project’s architecture makes it ideal for developers exploring low-level systems, interpreters, or virtual machine design.

Whether you want to load classic CHIP-8 ROMs, study virtual machine execution, or experiment with emulator development, this project offers a compact yet complete foundation.

---

## ▶️ How to Run

Running the CHIP-8 emulator is straightforward and requires only a ROM file and the executable.  
Follow the steps below to get started:

### 1) Download the Latest Release

Download the most recent version of the emulator from the **Releases** page:

👉 https://github.com/mertbasaryildirim/chip8-emulator/releases

### 2) Extract the Archive

Unzip the downloaded `.zip` file to any directory of your choice.

### 3) Place Your ROM File

Copy the CHIP-8 ROM file you want to run into the same directory where `chip8.exe` is located.

### 4) Run the Emulator

Execute the emulator with your ROM file as an argument:

```bash
/chip8.exe <ROM_FILE>
```

For example:

```bash
/chip8.exe TETRIS.bin
```

---

## 🎥 Demo

<div align="center">
  <video src="demo.mp4" controls style="max-width: 100%; border-radius: 12px;">
    Your browser does not support the video tag.
  </video>
</div>

The video below demonstrates the emulator running a sample CHIP-8 game, showcasing the rendered graphics and overall runtime behavior.
