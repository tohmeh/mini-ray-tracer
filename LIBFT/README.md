# Libft

Libft is a comprehensive library of C functions that I developed as part of my studies at 42. This project brings together three separate projects into one, covering a wide range of essential C functions that serve as a foundational toolkit for any C programmer. The functions implemented include string manipulation, memory management, file handling, and various utility functions, all crafted to enhance efficiency and ease in coding.

## Table of Contents

- [Introduction](#introduction)
- [Functions Implemented](#functions-implemented)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Libft is a custom C library that mimics the functionality of many standard C library functions, while also introducing additional utility functions. The goal of this project was to deepen my understanding of C by implementing these functions from scratch, without relying on the standard library.

This project is divided into three parts:
1. **Part 1:** Reimplementation of standard C library functions.
2. **Part 2:** Additional utility functions for memory and string management.
3. **Part 3:** Bonus functions, including file handling functions like `get_next_line`.

## Functions Implemented

### Part 1: Standard C Library Functions

- `ft_strlen` - Calculate the length of a string.
- `ft_strdup` - Duplicate a string.
- `ft_strjoin` - Concatenate two strings.
- `ft_split` - Split a string into an array based on a delimiter.
- `ft_memcpy` - Copy memory area.
- `ft_memset` - Fill memory with a constant byte.
- `ft_strchr` - Locate a character in a string.
- `ft_strrchr` - Locate the last occurrence of a character in a string.
- `ft_strncmp` - Compare two strings up to a specified length.
-.....
### Part 2: Utility Functions

- `ft_itoa` - Convert an integer to a string.
- `ft_strtrim` - Trim whitespace from the beginning and end of a string.
- `ft_substr` - Extract a substring from a string.
- `ft_strmapi` - Apply a function to each character of a string.
- `ft_striteri` - Apply a function to each character of a string with its index.
- `ft_putchar_fd` - Write a character to a file descriptor.
- `ft_putstr_fd` - Write a string to a file descriptor.
- `ft_putendl_fd` - Write a string to a file descriptor, followed by a newline.
- `ft_putnbr_fd` - Write an integer to a file descriptor.
-.....
### Part 3: Bonus Functions

- `get_next_line` - Read a line from a file descriptor.
- `ft_printf` - printf function . 
- `ft_lstnew` - Create a new list element.
- `ft_lstadd_front` - Add a new element at the beginning of a list.
- `ft_lstadd_back` - Add a new element at the end of a list.
- `ft_lstsize` - Count the number of elements in a list.
- `ft_lstlast` - Return the last element of a list.
- `ft_lstdelone` - Delete an element of a list.
- `ft_lstclear` - Clear a list.

## Installation

To use the Libft library in your project, clone the repository and compile the library using `make`:

```bash
git clone https://github.com/tohmeh/libft.git
cd libft
make
