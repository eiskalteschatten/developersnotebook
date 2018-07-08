# Developer's Notebook

Developer's Notebook is intended to be a cross-platform, open-source application that provides developers a series of organizational tools.

The project is currently in its infancy.


## Libraries

Developer's Notebook relies on a few libraries. To see which are required for your platform, see the "Install Libraries" section of the `Makefile`.

### Install using Makefile targets

- Mac: `make install-libs-mac` (requires Homebrew)
- Ubuntu/Debian: `make install-libs-debian` *(Note: You will need sudo privileges. The command automatically installs the packages withour further prompting.)*


## Building

Developer's Notebook relies on the g++ compiler to build.

- Compile: `make`
- Compile and run: `make build-run`

### macOS-specific commands

- Compile and create an application bundle: `make create-mac-bundle`
- Compile, create and run the application bundle: `make build-run-mac`

All required libraries are automatically bundled in the macOS application bundle.

### Linux-specific commands

- Compile and create a gziped bundle: `make create-linux-bundle`
- Compile and create a .deb package: `make package-deb`

### Windows

See [Windows.md](https://github.com/eiskalteschatten/developersnotebook/blob/master/Windows.md) for more information about the setup. **Note: Windows is not supported yet, but support is on its way.**


## Building with Docker

Another way to build and package Developer's Notebook for Linux is with Docker.

- Compile and create a .deb package within a Debian Docker Container: `make package-deb-docker`


## Running

After building, the binaries can be found in the `build` directory. They can either be run directly there or by using the following command:

    make run


## Roadmap

### 0.1

[Released](https://github.com/eiskalteschatten/developersnotebook/releases) on 8 July 2018.

- Dashboard
- Projects
- License


### 0.2

- Custom UI theme(s)
- Icons in the menu on the left
- Ability to have multiple databases and save them wherever the user wants


### 0.3

- To dos
- Issues
- Updated dashboard


### 0.4

- Tools (color picker/converter, image and file compression, etc)
- Bookmarks
- Notes
- Updated dashboard


### 0.5

- Journal
- Code cache
- Archive
- Updated dashboard


### 1.0

- Preferences
- Check for updates
- Command palette
- Search
- Updated dashboard


### 2.0

- ...

## License

[MIT](https://github.com/eiskalteschatten/developersnotebook/blob/master/LICENSE)

---

Alex Seifert - https://www.alexseifert.com
