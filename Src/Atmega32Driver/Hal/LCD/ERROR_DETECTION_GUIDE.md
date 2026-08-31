# LCD Driver Error Detection Guide

## Overview
The LCD driver has been enhanced with comprehensive error detection capabilities. All functions that can fail now return error codes and maintain an internal error state that can be queried.

## Error Types

```c
typedef enum {
    LCD_ERROR_NONE = 0,                    // No error occurred
    LCD_ERROR_INVALID_LINE = 1,            // Invalid line number (not 1 or 2)
    LCD_ERROR_INVALID_DIGIT = 2,           // Invalid digit position (> 15)
    LCD_ERROR_NULL_POINTER = 3,            // NULL pointer passed to function
    LCD_ERROR_INIT_FAILED = 4,             // LCD initialization failed
    LCD_ERROR_INVALID_LOCATION = 5         // Invalid CGRAM location (not 0-7)
} LCD_ErrorStatus_t;
```

## Functions with Error Detection

### 1. LCD_Init()
```c
uint8_t LCD_Init(void);
```
**Returns:** Error status (0 = success)
**Errors:**
- `LCD_ERROR_INIT_FAILED` - Initialization sequence failed
- `LCD_ERROR_NONE` - Success

**Example:**
```c
if(LCD_Init() != LCD_ERROR_NONE) {
    // Handle LCD initialization error
    LOG_Event(LCD_INIT_ERROR);
    // System should still function, but LCD output disabled
}
```

---

### 2. LCD_MoveTo()
```c
uint8_t LCD_MoveTo(uint8_t LineNo, uint8_t DigitNo);
```
**Parameters:**
- `LineNo` - Line number (1 or 2)
- `DigitNo` - Column position (0-15)

**Returns:** Error status (0 = success)
**Errors:**
- `LCD_ERROR_INVALID_LINE` - LineNo not 1 or 2
- `LCD_ERROR_INVALID_DIGIT` - DigitNo > 15
- `LCD_ERROR_NONE` - Success

**Example:**
```c
// Move to Line 2, Position 5
if(LCD_MoveTo(2, 5) != LCD_ERROR_NONE) {
    switch(LCD_GetLastError()) {
        case LCD_ERROR_INVALID_LINE:
            // Invalid line number
            break;
        case LCD_ERROR_INVALID_DIGIT:
            // Invalid digit position
            break;
        default:
            break;
    }
}
```

---

### 3. LCD_WriteString()
```c
uint8_t LCD_WriteString(uint8_t *String);
```
**Parameters:**
- `String` - Pointer to string to write (must not be NULL)

**Returns:** Error status (0 = success)
**Errors:**
- `LCD_ERROR_NULL_POINTER` - String pointer is NULL
- `LCD_ERROR_NONE` - Success

**Example:**
```c
uint8_t* message = "Hello";
if(LCD_WriteString(message) != LCD_ERROR_NONE) {
    if(LCD_GetLastError() == LCD_ERROR_NULL_POINTER) {
        // Handle NULL pointer error
    }
}
```

---

### 4. LCD_StoreSpecialCharacter()
```c
uint8_t LCD_StoreSpecialCharacter(uint8_t *SpecialCharacter, uint8_t Location);
```
**Parameters:**
- `SpecialCharacter` - Pointer to 8-byte character array (must not be NULL)
- `Location` - CGRAM location (0-7, only 8 locations available)

**Returns:** Error status (0 = success)
**Errors:**
- `LCD_ERROR_NULL_POINTER` - Character pointer is NULL
- `LCD_ERROR_INVALID_LOCATION` - Location >= 8
- `LCD_ERROR_NONE` - Success

**Example:**
```c
uint8_t heart[8] = {0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00};

if(LCD_StoreSpecialCharacter(heart, 0) != LCD_ERROR_NONE) {
    switch(LCD_GetLastError()) {
        case LCD_ERROR_NULL_POINTER:
            // NULL character pointer
            break;
        case LCD_ERROR_INVALID_LOCATION:
            // Location out of range (0-7)
            break;
        default:
            break;
    }
}
```

---

## Error Management Functions

### LCD_GetLastError()
```c
LCD_ErrorStatus_t LCD_GetLastError(void);
```
**Returns:** The error status from the last LCD operation

**Usage:**
```c
if(LCD_MoveTo(3, 0) == LCD_ERROR_INVALID_LINE) {
    LCD_ErrorStatus_t error = LCD_GetLastError();
    if(error == LCD_ERROR_INVALID_LINE) {
        // Take appropriate action
    }
}
```

---

### LCD_ClearError()
```c
void LCD_ClearError(void);
```
**Purpose:** Reset the error flag to LCD_ERROR_NONE

**Usage:**
```c
// Clear any previous errors
LCD_ClearError();

// Perform new LCD operations
if(LCD_MoveTo(1, 0) == LCD_ERROR_NONE) {
    LCD_WriteString((uint8_t*)"System Ready");
}
```

---

## Best Practices

### 1. Check Return Values Immediately
```c
// GOOD
if(LCD_MoveTo(1, 0) != LCD_ERROR_NONE) {
    // Handle error immediately
}

// AVOID
LCD_MoveTo(1, 0);
// ... other code ...
if(LCD_GetLastError() != LCD_ERROR_NONE) {  // Error may have been overwritten
    // Handle error
}
```

### 2. Clear Errors Before New Operations
```c
// Clear any previous error state
LCD_ClearError();

// Now perform operations
if(LCD_WriteString((uint8_t*)"Starting up") == LCD_ERROR_NONE) {
    // Operation successful
}
```

### 3. Validate Input Data
```c
// Validate position before calling LCD_MoveTo()
uint8_t line = get_line_from_config();
uint8_t pos = get_position_from_config();

if(line < 1 || line > 2) {
    // Handle invalid line
}
if(pos > 15) {
    // Handle invalid position
}

// Now safe to call
LCD_MoveTo(line, pos);
```

### 4. Handle Errors Gracefully
```c
// Check LCD initialization
if(LCD_Init() != LCD_ERROR_NONE) {
    // LCD module failed - system should continue if possible
    // You can still log events or use other output methods
    UART_SendString("LCD initialization failed\r\n");
} else {
    // LCD is ready for use
    LCD_MoveTo(1, 0);
    LCD_WriteString((uint8_t*)"System Ready");
}
```

### 5. Recovery Strategies
```c
uint8_t display_message(uint8_t *msg) {
    // Try to display message
    if(LCD_WriteString(msg) != LCD_ERROR_NONE) {
        // First retry with reinitialize
        if(LCD_Init() != LCD_ERROR_NONE) {
            return LCD_ERROR_INIT_FAILED;
        }
        
        // Retry the write
        if(LCD_WriteString(msg) != LCD_ERROR_NONE) {
            return LCD_GetLastError();
        }
    }
    
    return LCD_ERROR_NONE;
}
```

---

## Common Error Scenarios

### Scenario 1: Invalid Line Number
```c
// This will fail
LCD_MoveTo(3, 0);  // Line 3 doesn't exist
// Error: LCD_ERROR_INVALID_LINE
```
**Solution:** Only use line 1 or 2
```c
LCD_MoveTo(2, 0);  // Correct
```

### Scenario 2: Column Out of Range
```c
// This will fail
LCD_MoveTo(1, 20);  // Column 20 doesn't exist (max 15)
// Error: LCD_ERROR_INVALID_DIGIT
```
**Solution:** Use positions 0-15
```c
LCD_MoveTo(1, 15);  // Last valid position
```

### Scenario 3: NULL String Pointer
```c
uint8_t *str = NULL;
// This will fail
LCD_WriteString(str);
// Error: LCD_ERROR_NULL_POINTER
```
**Solution:** Always validate pointers
```c
uint8_t *str = get_message();
if(str != NULL) {
    LCD_WriteString(str);
}
```

### Scenario 4: Too Many Custom Characters
```c
// Define 9 custom characters
uint8_t char0[8] = {...};
// ...
uint8_t char8[8] = {...};

// Only locations 0-7 available!
LCD_StoreSpecialCharacter(char8, 8);  // FAILS
// Error: LCD_ERROR_INVALID_LOCATION
```
**Solution:** Use only 8 locations (0-7)
```c
for(uint8_t i = 0; i < 8; i++) {
    LCD_StoreSpecialCharacter(custom_chars[i], i);
}
```

---

## Testing Error Detection

### Unit Test Example
```c
void test_lcd_error_detection() {
    // Test invalid line
    assert(LCD_MoveTo(3, 0) == LCD_ERROR_INVALID_LINE);
    assert(LCD_GetLastError() == LCD_ERROR_INVALID_LINE);
    
    // Test invalid digit
    LCD_ClearError();
    assert(LCD_MoveTo(1, 20) == LCD_ERROR_INVALID_DIGIT);
    assert(LCD_GetLastError() == LCD_ERROR_INVALID_DIGIT);
    
    // Test NULL pointer
    LCD_ClearError();
    assert(LCD_WriteString(NULL) == LCD_ERROR_NULL_POINTER);
    assert(LCD_GetLastError() == LCD_ERROR_NULL_POINTER);
    
    // Test invalid CGRAM location
    LCD_ClearError();
    uint8_t dummy[8] = {0};
    assert(LCD_StoreSpecialCharacter(dummy, 8) == LCD_ERROR_INVALID_LOCATION);
    assert(LCD_GetLastError() == LCD_ERROR_INVALID_LOCATION);
}
```

---

## Integration with Event Logging

The LCD error detection can be integrated with the event logging system:

```c
#include "Hal/LCD/LCD_Interface.h"
#include "App/EventLogging/EventLogging_Interface.h"

void LCD_Init_Safe(void) {
    if(LCD_Init() != LCD_ERROR_NONE) {
        LOG_Event(EVENT_LCD_INIT_FAILED);
    }
}

void LCD_Display_Safe(uint8_t line, uint8_t pos, uint8_t *msg) {
    if(LCD_MoveTo(line, pos) != LCD_ERROR_NONE) {
        LOG_Event(EVENT_LCD_INVALID_POSITION);
        return;
    }
    
    if(LCD_WriteString(msg) != LCD_ERROR_NONE) {
        LOG_Event(EVENT_LCD_WRITE_FAILED);
    }
}
```

---

## Migration Guide (For Existing Code)

### Before (No Error Checking)
```c
LCD_MoveTo(1, 0);
LCD_WriteString((uint8_t*)"Hello");
```

### After (With Error Checking)
```c
if(LCD_MoveTo(1, 0) == LCD_ERROR_NONE) {
    if(LCD_WriteString((uint8_t*)"Hello") != LCD_ERROR_NONE) {
        // Handle write error
    }
} else {
    // Handle position error
}
```

---

## Troubleshooting

### LCD Functions Always Return Errors
- **Cause:** LCD not properly initialized
- **Solution:** Call `LCD_Init()` first, check for errors

### LCD Appears Unresponsive
- **Cause:** util/delay.h not available (compilation error)
- **Solution:** Ensure AVR-libc is properly installed in toolchain

### Error Codes Not Matching Expected Values
- **Cause:** LCD_GetLastError() called after another function
- **Solution:** Check return values immediately, don't rely on global error state

---

## Summary

The LCD error detection system provides:
- ✓ Robust input validation
- ✓ Immediate error feedback via return codes
- ✓ Error state queries for detailed diagnostics
- ✓ Graceful degradation when LCD fails
- ✓ Integration points for event logging
- ✓ Backward compatibility with error-free operation
