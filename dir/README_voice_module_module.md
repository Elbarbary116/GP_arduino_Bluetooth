# Voice Module Documentation (voice_module.cpp & voice_module.h)

## Overview
This module manages the integration of the voice recognition hardware with the robot. It provides initialization, command loading, and recognition functions, as well as command code definitions.

---

## voice_module.cpp
### Purpose
- Implements the logic for initializing and using the voice recognition module.
- Loads supported voice commands and provides a function to recognize commands during operation.

### Key Functions
- `voice_module_init()`: Initializes the voice recognition module, loads command records, and returns a status code.
- `voice_module_recognize()`: Listens for and returns the recognized command as an integer code.

### Integration
- Used by `main.ino` to enable voice-controlled operation of the robot.
- Relies on the `VoiceRecognitionV3` library for hardware interaction.

---

## voice_module.h
### Purpose
- Defines command codes and function prototypes for the voice module.

### Key Definitions
- **Command Codes**: Integer codes for each supported voice command: `FORWARD`, `BACKWARD`, `STOP`, `LEFT`, `RIGHT`.
- **Function Prototypes**:
  - `ES_t voice_module_init(void)`
  - `int voice_module_recognize(void)`

### Integration
- Used throughout the codebase for consistent command handling.

---

## Notes
- The module is designed to be easily extended with new commands or error handling.
- Command codes are used for consistent control logic across the project. 