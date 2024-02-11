[Portuguese](README-pt.md)

# RISC-I Emulator

This project was created with the purpose of delving deeper into the knowledge of RISC-I opcodes. It has not been extensively tested and may present numerous issues, so do not consider this project as a faithful emulation of the RISC-I proposed by David A. Patterson. Not only is it incomplete, but it also contains decisions made by me that fundamentally differ from the original RISC-I model proposed.

## Simple Documentation

Most instructions have the following characteristics:

- They consist of 6 bytes.
- They include: opcode (1 byte), operand1 (2 bytes), operand2 (2 bytes), operand3 (1 byte).

---

**How operands work:**

An operand can either result in an immediate value or a value stored in a register.

We have registers from 0x00 to 0x1F; above that, it is impossible to retrieve a value from a register.

Therefore, the first byte informs which register should be retrieved. If this value is above 0x1F (starting from 0x20), the emulator will retrieve the immediate value in the second byte.

For example:

- 0x0100 -> retrieves the value in the register (0x01).
- 0xFF05 -> retrieves the immediate value 0x05 since the value of the first byte (0xFF) is greater than 0x1F.

**Exception for Third Operand**

As the third operand consists of only one byte, it **always** represents a register.

---

**Dictionary:**

Op1: first operand, provides the 2 bytes corresponding to the first operand

Op2: second operand, provides the 2 bytes corresponding to the second operand

Op3: third operand, provides the byte corresponding to the third operand
<br>

a: Value in Op1 (can be either a value in a register or a direct value)

b: Value in Op2 (can be either a value in a register or a direct value)

---

## Instruction Structure

 - Add: (0x01): 
     - 0x01 - opcode
     - 0x0000 - op1
     - 0x0000 - op2
     - 0x00 - op3 (destination register)
     - Operation: `registers[op3] = a+b`
     - Example:
        - `0x01FF01FF0401`
            - Opcode: 0x01 (add)
            - Op1: 0xFF01 (value 1)
            - Op2: 0xFF04 (value 4)
            - Op3: 0x01 (store result in register 01)
            
        - `0x010001FF0502`
            - Opcode: 0x01 (add)
            - Op1: 0x0001 (value in register 01, value = 5)
            - Op2: 0xFF05 (value 5)
            - Op3: 0x02 (store result in register 2)

- ADDC  (0x02):
  - 
  - Functions similarly to ADD, but increments by one if the carry flag is activated.
  
---
- Sub (0x03) & SUBC (0x04):
  - 
  - Function similarly to ADD and ADDC, but perform subtraction. Opcode varies.

---
- AND (0x06):
  - 
  - Performs bitwise AND operation between values `a` and `b`, storing the result in `op3`.
  - Operation: `registers[op3] = a & b`

---
- OR (0x07):
  - 
   - Performs bitwise OR operation between values `a` and `b`, storing the result in `op3`.
   - Operation: `registers[op3] = a | b`

---
- XOR (0x08):
  - 
   - Performs bitwise XOR operation between values `a` and `b`, storing the result in `op3`.
   - Operation: `registers[op3] = a ^ b`
   
---
- SLL (0x09), Shift Left Logical:
  - 
  - Performs left shift operation on value `a` by the number of shifts determined by `b`, storing the result in `op3`.
  - Operation: `registers[op3] = a << b`
 
---
- SRL (0x0A), Shift Right Logical:
  - 
  - Performs right shift operation on value `a` by the number of shifts determined by `b`, storing the result in `op3`.
  - Operation: `registers[op3] = a >>> b`
  
---
- SRA (0x0B), Shift Right Arithmetic:
  - 
   - Performs arithmetic right shift operation on value `a` by the number of shifts determined by `b`, storing the result in `op3`.
   - Operation: `registers[op3] = a >> b`
   
---
- LDL (0x0C), Load
  - 
  - Loads data from memory at position `a + b` and stores its value in `op3`.
  - `registers[op3] = memory[a+b]`
  - Note: Memory is byte-addressable, so the operation involves retrieving 4 bytes from the specified address and calculating the integer value to be stored.
  
---
- STL (0x0B), Store:
  - 
  - Stores values from register `op3` into memory location `a + b`.
  - `memory[a+b] = registers[op3]`
  - Note: Similar to loading, but involves storing the register value into 4 memory addresses.
  
---
- JMP
- JMPR
- CALL
- RET

