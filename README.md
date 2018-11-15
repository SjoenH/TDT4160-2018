# TDT4160-2018
Hi, and Welcome.
I hope this is helpful in preparation for the exam. 
If you find anything wrong, please do not hesitate in sending a pull-request.

**NB**. Exercise 4,5 and 6 have more throughout explanations in the **.md**-files.

Best Regards,
Henry.


# Table of contents
- [TDT4160-2018](#tdt4160-2018)
- [Table of contents](#table-of-contents)
- [Exercise 4](#exercise-4)
    - [SOLUTION, step by step](#solution-step-by-step)
    - [Answer](#answer)
- [Exercise 5](#exercise-5)
    - [Table of contents](#table-of-contents-1)
    - [Solution for the hasty](#solution-for-the-hasty)
    - [The lazymans Quickstart to the instruction set architecture](#the-lazymans-quickstart-to-the-instruction-set-architecture)
        - [ldi](#ldi)
        - [mul](#mul)
        - [sub](#sub)
        - [cmp](#cmp)
        - [jgt](#jgt)
    - [Step by step Exercise solutions](#step-by-step-exercise-solutions)
        - [If %r0 = 2](#if-r0--2)
        - [If %r0 = 3](#if-r0--3)
        - [If %r0 = 4](#if-r0--4)
        - [If %r0 = 9](#if-r0--9)
- [Exercise 6](#exercise-6)
    - [Step by step solution](#step-by-step-solution)
    - [SOLUTION](#solution)

# Exercise 4
We are to translate the following instructions into binary code.
```
0x00 ldi %r2, 1
0x04 ldi %r1, 1
0x08 mul %r2, %r2, %r0
0x0C sub %r0, %r0, %r1
0x10 cmp %r3, %r0, %r1
0x14 jgt %r3, -16
```

We are given one example in the exercise handout:

add %r7, %r8, %r9 translates to
```
00001 00111 01000 01001 XXXX XXXX XXXX
add   r7    r8    r9
```

See page 5 in the handout for state diagram of the machine. (shown below)
![State diagram of the machine](thestateofthings.png)
We can see the opcodes listed as...

| opcode | int | binary |
| ------ | --- | ------ |
| ldi    | 0   | 00000  |
| add    | 1   | 00001  |
| mul    | 2   | 00010  |
| cmp    | 3   | 00011  |
| jgt    | 4   | 00100  |
| sub    | 5   | 00101  |


## SOLUTION, step by step
| pc   | opcode |       |             |                | 
| ---- | ------ | ----- | ----------- | -------------- |
| 0x00 | ldi    | %r2   | 1           |                |
|      | 00000  | 00010 | 00000 00000 | 0000 0000 0001 |
| 0x04 | ldi    | %r1   | 1           |                |
|      | 00000  | 00001 | 00000 00000 | 0000 0000 0001 |
| 0x08 | mul    | %r2   | %r2         | %r0            |
|      | 00010  | 00010 | 00010 00000 | XXXX XXXX XXXX |
| 0x0C | sub    | %r0   | %r0         | %r1            |
|      | 00101  | 00000 | 00000 00001 | XXXX XXXX XXXX |
| 0x10 | cmp    | %r3   | %r0         | %r1            |
|      | 00011  | 00011 | 00000 00001 | XXXX XXXX XXXX |
| 0x14 | jgt    | %r3   | -16         |                |
|      | 00100  | 00011 | 11111 11111 | 1111 1111 0000 |

## Answer
```binary
00000000100000000000000000000001
00000000010000000000000000000001
00010000100001000000XXXXXXXXXXXX
00101000000000000001XXXXXXXXXXXX
00011000110000000001XXXXXXXXXXXX
00100000111111111111111111110000
```


# Exercise 5
Assume that register %r0 contains 2 before the program is executed. What would be the value in register %r2 once the program reaches the instruction at address 0x18, i.e. the branch at address 0x14 is not taken. What would be the value in %r2, if %r0 would contain 3, 4, 9?

| PC   |     |     |     |     | R0  | R1  | R2  | R3  |
| ---- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0x00 | ldi | %r2 | 1   |     |     |     |     |     |
| 0x04 | ldi | %r1 | 1   |     |     |     |     |     |
| 0x08 | mul | %r2 | %r2 | %r0 |     |     |     |     |
| 0x0C | sub | %r0 | %r0 | %r1 |     |     |     |     |
| 0x10 | cmp | %r3 | %r0 | %r1 |     |     |     |     |
| 0x14 | jgt | %r3 |     | -16 |     |     |     |     |

**Submission**

Hand in a plain text file with the corresponding values per line, i.e. the value for 2 on the first line, the value for 3 on the second, etc.

----

## Table of contents
- [TDT4160-2018](#tdt4160-2018)
- [Exercise 4](#exercise-4)
- [Exercise 5](#exercise-5)
    - [Table of contents](#table-of-contents)
    - [Solution for the hasty](#solution-for-the-hasty)
    - [The lazymans Quickstart to the instruction set architecture](#the-lazymans-quickstart-to-the-instruction-set-architecture)
        - [ldi](#ldi)
        - [mul](#mul)
        - [sub](#sub)
        - [cmp](#cmp)
        - [jgt](#jgt)
    - [Step by step Exercise solutions](#step-by-step-exercise-solutions)
        - [If %r0 = 2](#if-r0--2)
        - [If %r0 = 3](#if-r0--3)
        - [If %r0 = 4](#if-r0--4)
        - [If %r0 = 9](#if-r0--9)
- [Exercise 6](#exercise-6)
----
## Solution for the hasty
```
2
6
24
362880
```
----

## The lazymans Quickstart to the instruction set architecture
To do these exercises we have to look at the instruction set architecture. Page 2.
For the lazy, here is a quick Explanation of them:

**NB**. These instructions only apply to the instruction set architecture for *these* exercises. Remember to check the isa that is appended in the exam. A lot of the things should be similar though.

### ldi
``A=B``
Load the integer in B into the register in A

| op  | A   | B   | Explanation                           |
| --- | --- | --- | ------------------------------------- |
| ldi | %r2 | 1   | loads integer 1 into register 2 (%r2) |

### mul
``A=B*C``
Multiply B with C, store in A.

| op  | A   | B   | C   | Explanation                                                      |
| --- | --- | --- | --- | ---------------------------------------------------------------- |
| mul | %r2 | %r2 | %r0 | Multiply the integers in %r2 and %r0 and store the result in %r2 |

### sub
A=B-C
Subtract C from B, store in A.

| op  | A   | B   | C   | Explanation                                            |
| --- | --- | --- | --- | ------------------------------------------------------ |
| sub | %r0 | %r0 | %r1 | Subtract the integers in %r1 from %r0 and store in %r0 |

### cmp
This is a compare operation that returns a binary...

``if (A < B) => 100``

``if (A > B) => 010``

``if (A == B) => 001``

| op  |     | A   | B   | %r0 | %r1 | OUTPUT (%r3) | Explanation                                          |
| --- | --- | --- | --- | --- | --- | ------------ | ---------------------------------------------------- |
| cmp | %r3 | %r0 | %r1 | 0   | 1   | 0b100        | ``A < B`` -> Therefore, store 0b0100 in register %r3 |
| cmp | %r3 | %r0 | %r1 | 1   | 0   | 0b010        | ``A > B`` -> Therefore, store 0b010 in register %r3  |
| cmp | %r3 | %r0 | %r1 | 1   | 1   | 0b001        | ``A == B`` -> Therefore, store 0b001 in register %r3 |

### jgt
Jump-Greater-Than Instruction
Returns the program-counter + the immidiate.


Depending on what the output of the compare function is (see above), we will get different outcome.

If the output of cmp is "0b010" we will jump. Setting the Program-Counter (PC) to the PC + immidiate.

Example

| PC   | op  | A   | B (immidiate) | %r3   | Note                            |
| ---- | --- | --- | ------------- | ----- | -------------------------------------- |
| 0x14 | jgt | %r3 | -16           | 0b010 | We will jump. PC = PC+immidiate = 0x04 |

**Quick Explanation** 
The cmp instruction have stored in register 3 that A > B. Therefore we will jump to PC + immidiate = 0x14 + (-)16 = 0x04

**NB.** Note that the PC-Values are written in hexadecimals. Made clear by "0x" preceeding the number.

For the other two possibilities we will just continue down the program.

| op  | A   | B (immidiate) | %r3   | Explanation                            |
| --- | --- | ------------- | ----- | -------------------------------------- |
| jgt | %r3 | -16           | 0b100 | We will not jump. Continue the Program |
| jgt | %r3 | -16           | 0b001 | We will not jump. Continue the Program |

----

## Step by step Exercise solutions

### If %r0 = 2
Then %r2 = 2

| #            |      |      |      |      | R0   | R1   | R2    | R3    | Comment                     |
| ------------ | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ----- | --------------------------- |
|              |      |      |      |      | 2    |      |       |       | R0 is already set to 2      |
| 0x00         | ldi  | %r2  | 1    |      |      |      | 1     |       |                             |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |       |       |                             |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 2     |       |                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | -1   |      |       |       | r0-r1=>r0                   |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |       | 0b100 |                             |
| 0x14         | jgt  | %r3  |      | -16  |      |      |       |       | If (R3 == 0b010 ) goto 0x04 |
| ----         | ---- | ---- | ---- | ---- | ---- | ---- | ----  | ----  | -----                       |
| **SOLUTION** |      |      |      |      |      |      | **2** |       |                             |

----

### If %r0 = 3
Then %r2 = 6

| #            |      |      |      |      | R0   | R1   | R2    | R3    | Comment                     |
| ------------ | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ----- | --------------------------- |
|              |      |      |      |      | 3    |      |       |       |                             |
| 0x00         | ldi  | %r2  | 1    |      |      |      | 1     |       |                             |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |       |       |                             |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 3     |       |                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 2    |      |       |       | r0-r1=>r0                   |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |       | 0b010 |                             |
| 0x14         | jgt  | %r3  |      | -16  |      |      |       |       | If (R3 == 0b010 ) goto 0x04 |
| ----         | ---- | ---- | ---- | ---- | ---- | ---- | ----  | ----  | -----                       |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |       |       |                             |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 6     |       |                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 1    |      |       |       | r0-r1=>r0                   |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |       | 0b001 |                             |
| 0x14         | jgt  | %r3  |      | -16  |      |      |       |       | If (R3 == 0b010 ) goto 0x04 |
| ----         | ---- | ---- | ---- | ---- | ---- | ---- | ----  | ----  | -----                       |
| **SOLUTION** |      |      |      |      |      |      | **6** |       |                             |

----

### If %r0 = 4
Then %r2 = 24

| #            |      |      |      |      | R0   | R1   | R2     | R3    | Comment                     |
| ------------ | ---- | ---- | ---- | ---- | ---- | ---- | ------ | ----- | --------------------------- |
|              |      |      |      |      | 4    |      |        |       |                             |
| 0x00         | ldi  | %r2  | 1    |      |      |      | 1      |       |                             |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |        |       |                             |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 4      |       |                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 3    |      |        |       |                             |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |        | 0b010 |                             |
| 0x14         | jgt  | %r3  |      | -16  |      |      |        |       | If (R3 == 0b010 ) goto 0x04 |
| ----         | ---- | ---- | ---- | ---- | ---- | ---- | ----   | ----  | -----                       |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |        |       |                             |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 12     |       |                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 2    |      |        |       | r0-r1=>r0                   |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |        | 0b010 |                             |
| 0x14         | jgt  | %r3  |      | -16  |      |      |        |       | If (R3 == 0b010 ) goto 0x04 |
| ----         | ---- | ---- | ---- | ---- | ---- | ---- | ----   | ----  | -----                       |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |        |       |                             |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 24     |       |                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 1    |      |        |       | r0-r1=>r0                   |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |        | 0b001 |                             |
| 0x14         | jgt  | %r3  |      | -16  |      |      |        |       | If (R3 == 0b010 ) goto 0x04 |
| ----         | ---- | ---- | ---- | ---- | ---- | ---- | ----   | ----  | -----                       |
| **SOLUTION** |      |      |      |      |      |      | **24** |       |                             |

----

### If %r0 = 9
Then %r2 = 362880

| #            |      |      | (A)  | (B)  | R0   | R1   | R2          | R3    | Comment                              |
| ------------ | ---- | ---- | ---- | ---- | ---- | ---- | ----------- | ----- | ------------------------------------ |
|              |      |      |      |      | 9    |      |             |       |                                      |
| 0x00         | ldi  | %r2  | 1    |      |      |      | 1           |       |                                      |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 9           |       |                                      |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 8    |      |             |       | 9-1=8                                |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b010 | (A)9 > (B)8 => 0b010, Need to repeat |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       | Jump to 0x04                         |
| --JUMP--     | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 72          |       | 9*8 = 72                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 7    |      |             |       | (A)-(B) = ?                          |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b010 | (A)>(B) =>  0b010                    |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       | If (r3==0b010) => --JUMP-- to 0x04   |
| --JUMP--     | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 504         |       | 72*7 = 504                           |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 6    |      |             |       | 7-1=6                                |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b010 | (A)>(B) =>                           |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       | If (r3==0b010) => Jump to 0x04       |
| --JUMP--     | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 3 024       |       | 6*504                                |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 5    |      |             |       | r0-r1=>r0                            |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b010 |                                      |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       | If (R3 == 0b010 ) goto 0x04          |
| --JUMP--     | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 15 120      |       | 3 024*5                              |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 4    |      |             |       | r0-r1=>r0                            |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b010 |                                      |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       | If (R3 == 0b010 ) goto 0x04          |
| --JUMP--     | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 60 480      |       | 4*15 120                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 3    |      |             |       | r0-r1=>r0                            |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b010 |                                      |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       | If (R3 == 0b010 ) goto 0x04          |
| --JUMP--     | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 181 440     |       | 3*60 480                             |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 2    |      |             |       | r0-r1=>r0                            |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b010 |                                      |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       | If (R3 == 0b010 ) goto 0x04          |
| --JUMP--     | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| 0x04         | ldi  | %r1  | 1    |      |      | 1    |             |       |                                      |
| 0x08         | mul  | %r2  | %r2  | %r0  |      |      | 362 880     |       | 2*181 440                            |
| 0x0C         | sub  | %r0  | %r0  | %r1  | 1    |      |             |       | r0-r1=>r0                            |
| 0x10         | cmp  | %r3  | %r0  | %r1  |      |      |             | 0b001 |                                      |
| 0x14         | jgt  | %r3  |      | -16  |      |      |             |       |                                      |
| ----         | ---- | ---- | ---- | ---- | ---- | ---- | ----        | ----  | -----                                |
| **SOLUTION** |      |      |      |      |      |      | **362 880** |       |                                      |

----


# Exercise 6
Assume that register %r0 contains 1 before the program is executed. Given the microarchitecture in Section 2 and the control unit’s state machine in Section 3, write down the values of the control unit’s output signals for each executed instruction in the following order: imm, alu, regw, branch.

**Submission**
Hand in a plain text file with the values for each executed instruction per line.

- [Exercise 6](#exercise-6)
    - [Step by step solution](#step-by-step-solution)
    - [SOLUTION](#solution)

## Step by step solution
This exercise is as easy as reading off the state machine schema during execution of the program.

The program is still:
```
0x00 ldi %r2, 1
0x04 ldi %r1, 1
0x08 mul %r2, %r2, %r0
0x0C sub %r0, %r0, %r1
0x10 cmp %r3, %r0, %r1
0x14 jgt %r3, -16
```

And we can write it out more clear as a sheet.

| #        |      |      |      |      | R0   | R1   | R2   | R3    | imm | alu | regw | branch |
| -------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | --- | --- | ---- | ------ |
|          |      |      |      |      | 1    |      |      |       |     |     |      |        |
| 0x00     | ldi  | %r2  | 1    |      |      |      | 1    |       |     |     |      |        |
| 0x04     | ldi  | %r1  | 1    |      |      | 1    |      |       |     |     |      |        |
| 0x08     | mul  | %r2  | %r2  | %r0  |      |      | 1    |       |     |     |      |        |
| 0x0C     | sub  | %r0  | %r0  | %r1  | 0    |      |      |       |     |     |      |        |
| 0x10     | cmp  | %r3  | %r0  | %r1  |      |      |      | 0b100 |     |     |      |        |
| 0x14     | jgt  | %r3  |      | -16  |      |      |      |       |     |     |      |        |
| ----     | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----  |     |     |      |        |
| SOLUTION |      |      |      |      |      |      | 1    |       |     |     |      |        |

NB. I have also written down the Register-values just so we can see that the program actually ends with just *"one go"*.

Notice that we are interested in finding the values for imm,alu,regw and branch for each step. Let's feed the state-machine some input and read its outputs for each step.
![State machine](../o4/thestateofthings.png)

| opcode | imm | alu | regw | branch |
| ------ | --- | --- | ---- | ------ |
| ldi    | 1   | 3   | 1    | 0      |
| mul    | 0   | 4   | 1    | 0      |
| sub    | 0   | 5   | 1    | 0      |
| cmp    | 0   | 1   | 1    | 0      |
| jgt    | 0   | 2   | 0    | 1      |


And then it's just a matter of filling out each program-step with the corresponding *"opcode outputs"*.

| #        |      |      |      |      | R0   | R1   | R2    | R3    | imm | alu | regw | branch |
| -------- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ----- | --- | --- | ---- | ------ |
|          |      |      |      |      | 1    |      |       |       |     |     |      |        |
| 0x00     | ldi  | %r2  | 1    |      |      |      | 1     |       | 1   | 3   | 1    | 0      |
| 0x04     | ldi  | %r1  | 1    |      |      | 1    |       |       | 1   | 3   | 1    | 0      |
| 0x08     | mul  | %r2  | %r2  | %r0  |      |      | 1     |       | 0   | 4   | 1    | 0      |
| 0x0C     | sub  | %r0  | %r0  | %r1  | 0    |      |       |       | 0   | 5   | 1    | 0      |
| 0x10     | cmp  | %r3  | %r0  | %r1  |      |      |       | 0b100 | 0   | 1   | 1    | 0      |
| 0x14     | jgt  | %r3  |      | -16  |      |      |       |       | 0   | 2   | 0    | 1      |

## SOLUTION
```
1310
1310
0410
0510
0110
0201
```
