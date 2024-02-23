# GNL - getline() but in C

The goal of this project is to develop a function in C that reads lines ending with a newline character ('\n') from a file descriptor without prior knowledge of their size. Through this project, we aim to explore the concept of static variables in C programming and gain insight into memory allocations, buffer manipulation, and the lifecycle of buffers.

|    Project Name    |                                                                       get_next_line                                                                      |
| :----------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------: |
|    Description     |                                             My implementation of a function written in C that reads a lines from a file descriptor function                                             |
|    Technologies    | <a href="#"><img alt="C" src="https://custom-icon-badges.demolab.com/badge/C-03599C.svg?logo=c-in-hexagon&logoColor=white&style=for-the-badge"></a> |
| External libraries |     malloc(), free(), read()      |

## Usage

```bash
  gcl https://github.com/trobert42/get_next_line.git
  cd get_next_line
```

You can use it by compiling the main.c. Here's how :
```bash
gcc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c 
./a.out text1.text
```
