
---

# Setup Guide for PIC Development with VSCode on Linux

This guide will help you set up your environment for PIC16F887 development using the XC8 compiler, VSCode, and a Makefile on a Linux operating system.

## Prerequisites

- Linux operating system (e.g., Ubuntu)
- Internet connection

## Step 1: Install XC8 Compiler

1. Download the XC8 compiler from the [Microchip website](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xc-compilers#tabs).
2. Extract the downloaded file to a location of your choice.
3. Add the XC8 compiler's bin directory to your system's PATH. You can do this by adding the following line to your shell configuration file (e.g., `~/.bashrc`):

   ```sh
   export PATH="/path/to/xc8/bin:$PATH"
   ```

   Replace `/path/to/xc8/bin` with the actual path to the bin directory of the XC8 compiler.
   - Hint : it will be `/opt/microchip/xc8/v2.46/bin`

4. Source your shell configuration file to apply the changes:

   ```sh
   source ~/.bashrc
   ```

## Step 2: Install VSCode

1. Download and install Visual Studio Code from the [official website](https://code.visualstudio.com/).
2. Follow the on-screen instructions to complete the installation.

## Step 3: Install C/C++ Extension for VSCode

1. Open VSCode.
2. Go to the Extensions view by clicking on the square icon on the sidebar or by pressing `Ctrl+Shift+X`.
3. Search for "C/C++" in the Extensions view search box.
4. Click the Install button next to the "C/C++" extension offered by Microsoft.

## Step 4: Install Make

Make should already be installed on most Linux distributions. If it's not, you can install it using your package manager. For example, on Ubuntu, you can install Make with the following command:

```sh
sudo apt-get install make
```

## Step 5: Configure VSCode for PIC Development

1. Open your project in Visual Studio Code.
2. If you don't have a `.vscode` folder in your project, create one.
3. Inside the `.vscode` folder, create a file named `c_cpp_properties.json` if it doesn't already exist.
4. Copy and paste the following configuration into the `c_cpp_properties.json` file:

   ```json
   {
    "configurations": [
        {
            "name": "PIC18F4520",
            "browse": {
                "path": [
                    // Add the following paths to the path array
                    "/opt/microchip/xc8/v2.46/pic/include/*",
                    "${workspaceFolder}"
                ],
                "limitSymbolsToIncludedHeaders": true,
                "databaseFilename": ""
            },
            "includePath": [
                // Add the following paths to the includePath array
                "/opt/microchip/xc8/v2.46/pic/include/*",
                "${workspaceFolder}",
                "/opt/microchip/xc8/v2.46/pic/include/c90",
                "/opt/microchip/xc8/v2.46/pic/include/proc"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE",
                "__XC",
                "__XC8",
                "__XC8_VERSION=2460",
                "__XC8_VERSION_MAJOR=2",
                "__XC8_VERSION_MINOR=46",
                "__XC8_VERSION_PATCH=0",
                "__XC8_VERSION_BUILD=0"
            ],
            // Update the compilerPath to the correct path
            "compilerPath": "/opt/microchip/xc8/v2.46/bin/xc8-cc",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
    }
   ```

   Replace `/path/to/xc8/include` with the actual path to the include directory of the XC8 compiler.

5. Save the file.

## Step 6: Write Makefile for PIC16F887

Create a `Makefile` in your project directory with the following content:

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

## Step 7: Create `main.c` and Simple Program

1. Create a `src` directory in your project directory if you haven't already.
2. Inside the `src` directory, create a file named `main.c`.
3. Add the following simple program to `main.c` to blink an LED connected to pin RB0 on the PIC16F887:

```c
#include <xc.h>
#include <pic16f877a.h>
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

## Step 8: Compile and Run

1. Open a terminal in your project directory.
2. Run `make` to compile your project.
3. If the compilation is successful, you should see the `main.hex` file in the `build` directory.
4. Upload the `main.hex` file to your PIC16F887 to run the program.
5. If you want to clean the project, run `make clean` to remove the object files and the `main.hex` file.
6. You can also use the `make` command to recompile the project after making changes to the source files.

To add the installation of Wine and Proteus for simulating your PIC projects on Linux, you can follow these steps:

## Step 9: Install Wine

1. Wine is a compatibility layer that allows you to run Windows applications on Linux. Install Wine using your package manager. For example, on Ubuntu, you can use the following commands:

   ```sh
   sudo dpkg --add-architecture i386
   sudo apt update
   sudo apt install wine64 wine32
   ```

2. Verify the installation by running `wine --version`. You should see the Wine version number.

## Step 10: Download and Install Proteus

1. Download the Proteus installation package from the [Labcenter Electronics website](https://www.labcenter.com/).
2. Navigate to the directory where you downloaded the Proteus installer.
3. Install Proteus using Wine:

   ```sh
   wine <proteus_installer_file>.exe
   ```

   Replace `<proteus_installer_file>.exe` with the actual name of the Proteus installer file.

4. Follow the on-screen instructions to complete the installation.

## Step 11: Configure Proteus for PIC Simulation

1. Open Proteus using Wine:

   ```sh
   wine "C:\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\BIN\Proteus.exe"
   ```


3. You can now use Proteus to simulate your PIC projects on Linux.


## Conclusion

You should now have a basic setup for PIC16F887 development with VSCode using the XC8 compiler and a Makefile on a Linux operating system. You can expand this setup by adding more source files, libraries, or configurations as needed for your project.

You can find the code [here](https://drive.google.com/drive/folders/1k4-EQZsXhrs8ODOxJA-X8I0NbcBNqGr9?usp=drive_link).

## Credits

This setup guide was adapted for Linux by `Mostafa Hendy`.

---
