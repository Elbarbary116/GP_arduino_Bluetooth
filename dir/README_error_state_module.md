# Error State Module Documentation (error_state.h)

## Overview
This module defines a simple error state enumeration for use throughout the robot project. It provides a standard way to indicate success or failure in function return values.

---

## error_state.h
### Purpose
- Defines the `ES_t` enum for error and status reporting.

### Enum: ES_t
- `ES_OK`: Indicates successful operation.
- `ES_NOT_OK`: Indicates an error or unsuccessful operation.

### Usage
- Used as a return type for initialization and other functions to indicate success or failure.
- Promotes consistent error handling across modules.

---

## Integration
- Included by all modules that need to report status or error codes.
- Used in `voice_module.cpp`, `main.ino`, and other files.

## Notes
- The enum can be extended with additional error codes as needed for more complex projects. 