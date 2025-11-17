#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

/*
 * 00E0: CLS
 *
 * Clears the display.
 *
 * This instruction resets the entire video buffer by
 * setting all pixels to zero. Effectively, it wipes
 * the screen and prepares it for the next frame.
 */
void OP_00E0();

/*
 * 00EE: RET
 *
 * Returns from a subroutine.
 *
 * The top value on the stack contains the return address,
 * which points to the instruction immediately after the
 * subroutine call. We pop this address from the stack and
 * restore it into the program counter. This replaces the
 * preemptive `pc += 2` increment performed earlier.
 */
void OP_00EE();

/*
 * 1nnn: JP addr
 *
 * Jumps to the specified address nnn.
 *
 * This instruction sets the program counter directly to nnn,
 * transferring execution to that memory location. Since a jump
 * does not preserve the return address, it performs no stack
 * interaction and does not push the current PC onto the stack.
 */
void OP_1nnn();

/*
 * 2nnn: CALL addr
 *
 * Calls the subroutine located at address nnn.
 *
 * This instruction pushes the current program counter onto
 * the stack so execution can return after the subroutine
 * completes. Because Cycle() has already advanced the PC by 2,
 * the stored return address correctly points to the instruction
 * following this CALL. Returning to the CALL itself would cause
 * an infinite loop of CALLs and RETs, so preserving the
 * incremented PC is essential for proper control flow.
 */
void OP_2nnn();

/*
 * 3xkk: SE Vx, byte
 *
 * Skips the next instruction if Vx equals kk.
 *
 * Because the program counter has already been incremented
 * by 2 in Cycle(), skipping an instruction simply requires
 * incrementing the PC by an additional 2. This moves execution
 * past the next instruction when the equality condition is met.
 */
void OP_3xkk();

/*
 * 4xkk: SNE Vx, byte
 *
 * Skips the next instruction if Vx does not equal kk.
 *
 * Since the program counter has already been incremented by 2
 * in Cycle(), skipping the next instruction is achieved by
 * incrementing the PC by an additional 2. This advances execution
 * past the following instruction when the inequality condition holds.
 */
void OP_4xkk();

/*
 * 5xy0: SE Vx, Vy
 *
 * Skips the next instruction if Vx equals Vy.
 *
 * Because the program counter has already been incremented by 2
 * in Cycle(), skipping the next instruction is done by incrementing
 * the PC by an additional 2. Execution advances past the next
 * instruction whenever the equality condition is satisfied.
 */
void OP_5xy0();

/*
 * 6xkk: LD Vx, byte
 *
 * Loads the immediate value kk into register Vx.
 *
 * This instruction performs a direct assignment, replacing the
 * current contents of Vx with the provided 8-bit constant.
 */
void OP_6xkk();

/*
 * 7xkk: ADD Vx, byte
 *
 * Adds the immediate value kk to register Vx.
 *
 * The result is stored back into Vx. This addition wraps around
 * on overflow, as values are kept within 8-bit boundaries.
 */
void OP_7xkk();

/*
 * 8xy0: LD Vx, Vy
 *
 * Loads the value of register Vy into register Vx.
 *
 * This instruction performs a direct assignment, replacing the
 * contents of Vx with the current value stored in Vy.
 */
void OP_8xy0();

/*
 * 8xy1: OR Vx, Vy
 *
 * Performs a bitwise OR between Vx and Vy, storing the result in Vx.
 *
 * Each bit in Vx is set to 1 if either the corresponding bit in Vx
 * or Vy is 1. This instruction does not affect the VF flag.
 */
void OP_8xy1();

/*
 * 8xy2: AND Vx, Vy
 *
 * Performs a bitwise AND between Vx and Vy, storing the result in Vx.
 *
 * Each bit in Vx is set to 1 only if the corresponding bit in both
 * Vx and Vy is 1. This instruction does not modify the VF flag.
 */
void OP_8xy2();

/*
 * 8xy3: XOR Vx, Vy
 *
 * Performs a bitwise XOR between Vx and Vy, storing the result in Vx.
 *
 * Each bit in Vx is set to 1 if the corresponding bits in Vx and Vy
 * differ, and set to 0 if they are the same. This instruction does
 * not affect the VF flag.
 */
void OP_8xy3();

/*
 * 8xy4: ADD Vx, Vy
 *
 * Adds the values of Vx and Vy, storing the 8-bit result in Vx and
 * setting VF to indicate whether a carry occurred.
 *
 * If the sum of Vx and Vy exceeds 255 (8-bit range), VF is set to 1
 * to signal an overflow. Otherwise, VF is cleared to 0. Only the
 * lowest 8 bits of the computed sum are written back to Vx.
 */
void OP_8xy4();

/*
 * 8xy5: SUB Vx, Vy
 *
 * Subtracts Vy from Vx, storing the result in Vx, and sets VF to
 * indicate whether a borrow did *not* occur.
 *
 * If Vx is greater than Vy, the subtraction can be performed without
 * borrowing, so VF is set to 1. Otherwise, VF is set to 0 to indicate
 * that a borrow would occur. The final 8-bit result of Vx - Vy is then
 * stored back into Vx.
 */
void OP_8xy5();

/*
 * 8xy6: SHR Vx
 *
 * Shifts the value in Vx one bit to the right (division by 2),
 * storing the shifted result back into Vx. The least significant bit
 * before the shift is placed into VF.
 *
 * If the least significant bit of Vx is 1, VF is set to 1 to indicate
 * that a bit was shifted out. Otherwise, VF is cleared to 0. Vx is then
 * updated to Vx >> 1, keeping only the lower 8 bits of the result.
 */
void OP_8xy6();

/*
 * 8xy7: SUBN Vx, Vy
 *
 * Sets Vx to Vy minus Vx and updates VF to indicate whether a borrow
 * did *not* occur.
 *
 * If Vy is greater than Vx, the subtraction can be performed without
 * borrowing, so VF is set to 1. Otherwise, VF is cleared to 0. The
 * computed 8-bit result of Vy - Vx is then stored back into Vx.
 */
void OP_8xy7();

/*
 * 8xyE: SHL Vx {, Vy}
 *
 * Shifts the value in Vx one bit to the left (multiplication by 2),
 * storing the shifted result back into Vx. The most significant bit
 * before the shift is placed into VF.
 *
 * If the most significant bit of Vx is 1, VF is set to 1 to indicate
 * that a bit was shifted out during the left shift. Otherwise, VF is
 * cleared to 0. Vx is then updated to Vx << 1, with only the lower
 * 8 bits preserved.
 */
void OP_8xyE();

/*
 * 9xy0: SNE Vx, Vy
 *
 * Skips the next instruction if Vx does not equal Vy.
 *
 * Since the program counter has already been incremented by 2
 * in Cycle(), skipping the following instruction is done by
 * incrementing the PC by an additional 2 when Vx and Vy differ.
 * Execution continues past the next instruction only if the
 * inequality condition is met.
 */
void OP_9xy0();

/*
 * Annn: LD I, addr
 *
 * Loads the 12-bit address nnn into the index register I.
 *
 * This instruction performs a direct assignment, updating I to point
 * to the specified memory location. No flags or other registers are
 * affected.
 */
void OP_Annn();

/*
 * Bnnn: JP V0, addr
 *
 * Jumps to the address nnn plus the value in register V0.
 *
 * This instruction sets the program counter to (nnn + V0), allowing
 * for position-dependent jumps based on the contents of V0. No stack
 * operations are performed, and no flags are modified.
 */
void OP_Bnnn();

/*
 * Cxkk: RND Vx, byte
 *
 * Generates a random 8-bit value, ANDs it with kk, and stores the
 * result in Vx.
 *
 * A random byte (0–255) is produced, then masked using a bitwise AND
 * with the immediate value kk. This allows controlled randomness,
 * where kk determines which bits may be set in the final result.
 * No flags are modified by this instruction.
 */
void OP_Cxkk();

/*
 * Dxyn: DRW Vx, Vy, nibble
 *
 * Draws an n-byte tall sprite at coordinates (Vx, Vy) using the bytes
 * starting at memory location I, and sets VF to indicate whether any
 * pixels were unset as a result of drawing (collision).
 *
 * The sprite is always 8 pixels wide and n pixels tall. For each of the
 * n bytes, we iterate over its 8 bits (columns) and map any set bits to
 * pixels on the display at (Vx + column, Vy + row). If a sprite pixel
 * is "on" and the corresponding screen pixel is already set, toggling it
 * off via XOR indicates a collision and VF is set to 1. Otherwise, VF is
 * cleared to 0 when no such collisions occur. The screen pixels are
 * updated using XOR drawing semantics, typically by XORing with
 * 0xFFFFFFFF for "on" pixels in a 32-bit video buffer.
 */
void OP_Dxyn();

/*
 * Ex9E: SKP Vx
 *
 * Skips the next instruction if the key corresponding to the value
 * in register Vx is currently pressed.
 *
 * Because the program counter has already been incremented by 2
 * in Cycle(), skipping the next instruction is done by adding an
 * additional 2 to the PC when the key is detected as pressed.
 * This allows conditional flow control based on user input.
 */
void OP_Ex9E();

/*
 * ExA1: SKNP Vx
 *
 * Skips the next instruction if the key corresponding to the value
 * in register Vx is *not* currently pressed.
 *
 * Since the program counter has already been incremented by 2 in
 * Cycle(), skipping the next instruction is accomplished by adding
 * an additional 2 to the PC when the key is not pressed. This enables
 * conditional branching based on the absence of user input.
 */
void OP_ExA1();

/*
 * Fx07: LD Vx, DT
 *
 * Loads the current value of the delay timer into register Vx.
 *
 * This instruction performs a simple read operation: whatever value
 * the delay timer currently holds is copied directly into Vx. The
 * delay timer itself is not modified by this instruction.
 */
void OP_Fx07();

/*
 * Fx0A: LD Vx, K
 *
 * Waits for a key press and stores the value of the pressed key into Vx.
 *
 * This is a blocking instruction: execution should pause until the user
 * presses a key. The typical implementation achieves this by repeating
 * the same opcode until a key is detected—done by subtracting 2 from the
 * program counter when no key is pressed, causing the instruction to run
 * again on the next cycle. Once a key is pressed, its value is stored in Vx,
 * and execution continues normally.
 */
void OP_Fx0A();

/*
 * Fx15: LD DT, Vx
 *
 * Sets the delay timer to the value stored in register Vx.
 *
 * This instruction performs a direct assignment, updating the delay
 * timer so it begins counting down from Vx at 60 Hz. No other
 * registers or flags are affected.
 */
void OP_Fx15();

/*
 * Fx18: LD ST, Vx
 *
 * Sets the sound timer to the value stored in register Vx.
 *
 * This instruction updates the sound timer so it begins counting
 * down from Vx at 60 Hz. While the sound timer is non-zero, the
 * system is expected to produce a tone. No other registers or
 * flags are modified.
 */
void OP_Fx18();

/*
 * Fx1E: ADD I, Vx
 *
 * Adds the value in register Vx to the index register I.
 *
 * The result is stored back into I. Some CHIP-8 interpreters set VF
 * when this addition overflows 0x0FFF, but the original specification
 * does *not* modify VF here, so VF should remain unchanged in a
 * standard implementation.
 */
void OP_Fx1E();

/*
 * Fx29: LD F, Vx
 *
 * Sets the index register I to the memory location of the sprite
 * representing the hexadecimal digit stored in Vx.
 *
 * CHIP-8 font sprites are stored starting at memory address 0x50,
 * with each digit's sprite occupying 5 bytes. By multiplying the
 * value in Vx by 5 and adding it to 0x50, we obtain the address of
 * the first byte of the corresponding character sprite and store it
 * in I.
 */
void OP_Fx29();

/*
 * Fx33: LD B, Vx
 *
 * Stores the Binary-Coded Decimal (BCD) representation of Vx into
 * three consecutive memory locations starting at I.
 *
 * The value in Vx is split into its decimal hundreds, tens, and ones
 * digits. The hundreds digit is written to memory at I, the tens digit
 * to I+1, and the ones digit to I+2. This is done by repeatedly taking
 * the remainder modulo 10 to extract the right-most digit, then dividing
 * by 10 to shift the number right. Only integer values are stored, and
 * the original value of Vx is not modified.
 */
void OP_Fx33();

/*
 * Fx55: LD [I], Vx
 *
 * Stores registers V0 through Vx into memory starting at the address I.
 *
 * Each register from V0 up to and including Vx is copied sequentially
 * into memory beginning at I. That is, V0 is written to I, V1 to I+1,
 * V2 to I+2, and so on until Vx is stored. The index register I may or
 * may not be incremented after the transfer depending on the interpreter
 * variant, but in the original CHIP-8 specification, I remains unchanged.
 */
void OP_Fx55();

/*
 * Fx65: LD Vx, [I]
 *
 * Loads registers V0 through Vx from memory starting at the address I.
 *
 * Each register from V0 up to and including Vx is filled with the values
 * stored in memory beginning at I. Specifically, the byte at I is loaded
 * into V0, the byte at I+1 into V1, and so on until Vx is populated.
 * As with Fx55, the original CHIP-8 specification leaves the index
 * register I unchanged after the transfer, though some later variants
 * increment it.
 */
void OP_Fx65();

#endif