# Building on Windows

## Setup MinGW and MSYS2

1. Download MinGW from http://www.mingw.org and install it.
2. Download the 64-bit version of MSYS2 from http://www.msys2.org and install it.
3. Download Node.js from https://www.nodejs.org and install it.

4. Open MSYS2 and add MinGW's "bin" directory to the PATH variable:
    ```
    export PATH=/c/MinGW/bin:"/c/Program Files/nodejs":$PATH
    ```

5. Update pacman: `pacman -Syu`

6. Install the following packages in MSYS2 using the following command:
    ```
     pacman -S base-devel mingw-w64-x86_64-gcc-libs mingw-w64-i686-gtk3 mingw-w64-x86_64-pkg-config mingw-w64-i686-sqlite3 mingw-w64-i686-boost
    ```

7. Navigate to Developer's Notebook root folder and run `npm install`.

8. Run `make`.
