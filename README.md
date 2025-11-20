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

## ⌨️ Keyboard Mapping

CHIP-8 uses a 16-key hexadecimal keypad.  
This emulator maps those keys to a modern keyboard as follows:

```
Keypad       Keyboard
|1|2|3|C| => |1|2|3|4|
|4|5|6|D| => |Q|W|E|R|
|7|8|9|E| => |A|S|D|F|
|A|0|B|F| => |Z|X|C|V|
```

This layout preserves the original 4×4 CHIP-8 keypad structure while providing a more comfortable input experience on a standard **QWERTY keyboard**.

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
chip8.exe <ROM_FILE>
```

For example:

```bash
chip8.exe TETRIS.bin
```

---

## 📚 References

The resources below were used as part of the research and development process for this emulator.  
They may also serve as valuable starting points for anyone learning about CHIP-8 or exploring emulator design concepts:

- https://austinmorlan.com/posts/chip8_emulator/
- https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
- https://github.com/eshyong/Chip-8-Emulator

---

## 🎥 Demo

Here’s a short demo of the emulator running **Pong**, one of the most popular and classic games developed for CHIP-8. The video shows the emulator’s display output and how the game plays in real time.

<div align="center">
  <video src="https://github.com/user-attachments/assets/37b04c4d-4d26-4236-8dc4-be529e96569f" controls style="max-width: 50%; border-radius: 12px;">
    Your browser does not support the video tag.
  </video>
</div>
