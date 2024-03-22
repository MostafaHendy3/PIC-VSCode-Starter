
---

# Setup Guide for PIC Development with VSCode

This guide will help you set up your environment for PIC16F887 development using the XC8 compiler, VSCode, and a Makefile.

## Prerequisites

- Windows operating system
- Internet connection
- Administrative privileges (for some installations)

## Step 1: Install XC8 Compiler

1. Download the XC8 compiler from the [Microchip website](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xc-compilers#tabs).
2. Run the installer and follow the on-screen instructions.
3. Make sure to note down the installation directory, as you will need it later.

## Step 2: Install VSCode

1. Download and install Visual Studio Code from the [official website](https://code.visualstudio.com/).
2. Follow the on-screen instructions to complete the installation.

## Step 3: Install C/C++ Extension for VSCode

1. Open VSCode.
2. Go to the Extensions view by clicking on the square icon on the sidebar or by pressing `Ctrl+Shift+X`.
3. Search for "C/C++" in the Extensions view search box.
4. Click the Install button next to the "C/C++" extension offered by Microsoft.

## Step 4: Install Makefile

1. Download and install Make for Windows from the [GNU Make website](http://gnuwin32.sourceforge.net/packages/make.htm).
2. Follow these [click me](https://leangaurav.medium.com/how-to-setup-install-gnu-make-on-windows-324480f1da69) instructions to complete the installation.

## Step 5: Use Default Git Bash for VSCode

1. Open VSCode.
2. Open the Command Palette by pressing `Ctrl+Shift+P`.
3. Search for "Terminal:Select Default Profile" and choose "Git Bash" from the list.

## Step 6: Configure VSCode for PIC Development

1. Open your project in Visual Studio Code.
2. If you don't have a `.vscode` folder in your project, create one.
3. Inside the `.vscode` folder, create a file named `c_cpp_properties.json` if it doesn't already exist.
4. Copy and paste the configuration you provided into this file.
5. Change the compilerPath to your installation directory of the XC8 compiler with its version number.
6. Save the file.

Your `c_cpp_properties.json` file should look something like this:

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                // Change the compilerPath to your installation directory
                "C:/Program Files/Microchip/xc8/v2.46/pic/include/**"
            ],
            // Change the compilerPath to your installation directory
            "compilerPath": "C:\\Program Files\\Microchip\\xc8\\v2.46\\bin\\xc8-cc.exe",
            "cStandard": "c99",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "windows-gcc-x64",
            "configurationProvider": "ms-vscode.makefile-tools"
        }
    ],
    "version": 4
}
```

After adding this configuration, Visual Studio Code should use it for IntelliSense when working with your project.


## Step 7: Write Makefile for PIC16F887

1. Create a file named `Makefile` in your project directory.
2. Add the following content to the `Makefile`:

```makefile
# XC8 compiler and options
CC = xc8-cc
CFLAGS = -mcpu=16F877A -O0 -std=C99

# Project name
TARGET = application

# Source files
SRCS = $(wildcard *.c) $(wildcard */*.c)

# Object files directory
OBJDIR = build

# Object files
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.p1))

# Default target
all: $(TARGET).hex

# Rule to compile C files
$(OBJDIR)/%.p1: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate hex file
$(TARGET).hex: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET).hex

# Clean
clean:
	rm -f $(OBJS) $(TARGET).hex

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(dir $(OBJS)))
.PHONY: clean

```

## Step 8: Create `main.c` and Simple Program

1. Create a `src` directory in your project directory if you haven't already.
2. Inside the `src` directory, create a file named `main.c`.
3. Add the following simple program to `main.c` to blink an LED connected to pin RB0 on the PIC16F887:

```c
#include <xc.h>
// Configuration bits
#pragma config FOSC = HS        // HS oscillator (HS mode)
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = ON       // Power-up Timer enabled
#pragma config BOREN = OFF      // Brown-out Reset disabled
#pragma config LVP = OFF        // Low-Voltage Programming disabled
#pragma config CPD = OFF        // Data memory code protection off
#pragma config WRT = OFF        // Flash Program Memory Write protection off
#pragma config CP = OFF         // Flash Program Memory Code Protection off

#define _XTAL_FREQ 8000000     // 8 MHz crystal oscillator frequency

int main() {
    int x =0;
    int y = 5;
    
    TRISB0 = 0;                 // RB0 as output
    while(1) {
        RB0 = 1;                // LED ON
        __delay_ms(500);        // Delay 500ms
        RB0 = 0;                // LED OFF
        __delay_ms(500);        // Delay 500ms
    }
    return 0;
}

```

## Step 9: Compile and Run

1. Open a terminal in your project directory.
2. Run `make` to compile your project.
3. If the compilation is successful, you should see the `main.hex` file in the `build` directory.
4. Upload the `main.hex` file to your PIC16F887 to run the program.
5. If you want to clean the project, run `make clean` to remove the object files and the `main.hex` file.
6. You can also use the `make` command to recompile the project after making changes to the source files.

## Step 10 : For New Projects
    
* For new Projects
    * Create a new directory for your project
    * Copy the `Makefile` to the new project directory
    * Create a `.vscode` directory and add the `c_cpp_properties.json` file.
    * Create a `src` directory and create your source files
    * Open the project in VSCode and start coding


## Conclusion

You should now have a basic setup for PIC16F887 development with VSCode using the XC8 compiler and a Makefile. You can expand this setup by adding more source files, libraries, or configurations as needed for your project.

You can find the code [here](https://drive.google.com/drive/folders/1k4-EQZsXhrs8ODOxJA-X8I0NbcBNqGr9?usp=drive_link)

## Credits

This setup guide was created by Mostafa Hendy.
