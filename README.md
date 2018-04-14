# Developer's Notebook

Developer's Notebook is intended to be a cross-platform, open-source application that provides developers a series of organizational tools.

The project is currently in its infancy.


## Libraries

Developer's Notebook relies on a few libraries. To see which are required for your platform, see the "Install Libraries" section of the `Makefile`.

### Install using Makefile targets

- Mac: `make install-libs-mac` (requires Homebrew)
- Ubuntu/Debian: `make install-libs-debian`


## Building

Developer's Notebook relies on the g++ compiler to build. Currently only macOS and Linux are supported, but support for Windows will come at some point in the future.

- Compile: `make`
- Compile and run: `make build-run`

### macOS-specific commands

- Compile and create an application bundle: `create-mac-bundle`

**Note:** The libraries are not bundled within the macOS application bundle yet and are thus still required to be installed separatly to run it. This will change when Developer's Notebook gets closer to completion.


## Running

After building, the binaries can be found in the `build` directory. They can either be run directly there or by using the following command:

    make run


---

Alex Seifert - https://www.alexseifert.com
