# Calculator-GUI
This project is a graphical scientific calculator built using C++ and the wxWidgets GUI framework. It includes basic arithmetic operations and a variety of scientific functions such as square root, power, trigonometric functions, logarithms, and factorials. The goal was to apply Object-Oriented Programming (OOP) principles while learning how to create cross-platform desktop applications with graphical user interfaces.
------------------------------------------------------------------------------------------
Technologies & Tools Used:
    Language: C++
    
    GUI Framework: wxWidgets 3.0.5
    
    IDE/Text Editor: Visual Studio Code

    Compiler: g++ via MinGW64

    Build Environment: MSYS2 on Windows
------------------------------------------------------------------------------------------
Process of Writing the Code:

    Class Design (OOP):
        Created a Calculator class encapsulating all calculator functionalities.

        Each scientific operation was implemented as a method (squareRoot(), logarithm(), etc.).

         A basic expression evaluator was written to process simple operations in string format.

    GUI Setup (wxWidgets):

        Designed the calculator window with wxFrame and added buttons using wxButton.

        Used wxGridSizer to neatly arrange the buttons in a 4x4 grid.

        Set up event handling for button clicks to update the display and perform calculations.

    Input and Evaluation:

        On pressing =, the app captures the string expression, parses it, evaluates the result using the Calculator class, and shows it on the screen.
        Commands Used to Compile the Code:
------------------------------------------------------------------------------------------
To compile the project using g++ in the MSYS2 MinGW64 shell, I used the following command:

g++ oop_calculator.cpp -o oop_calculator.exe -std=c++17 \
-IC:/msys64/mingw64/include/wx-3.0 \
-IC:/msys64/mingw64/lib/wx/include/msw-unicode-3.0 \
-LC:/msys64/mingw64/lib \
-lwx_baseu-3.0 -lwx_mswu_core-3.0 -mwindows

    Note: You can also write this all in a single line if needed.
------------------------------------------------------------------------------------------
