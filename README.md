# sjpp (SJP++)

![Build and tests status](https://img.shields.io/github/actions/workflow/status/raxonpc/sjpp/build_and_test.yml?label=Build%20%2B%20Unit%20Tests)
![Build and docs deploy status](https://img.shields.io/github/actions/workflow/status/raxonpc/sjpp/build_docs.yml?label=Deploy%20Docs)

![Logo](assets/logo.png)

C++ API for [Słownik Języka Polskiego](https://sjp.pl/)

Provides a convenient way to look up words in the SJP Polish dictionary.

## Table of Contents

* [sjpp](#sjpp--sjp-)
    * [Installation](#installation)
    * [Usage](#usage)
    * [License](#license)
    * [Dependencies](#dependencies)

## Installation

sjpp can be built from sources. Before building, make sure you have [libcurl](https://curl.se/download.html)
installed on your machine.

Just run these commands in your shell: 

```sh
cd sjpp
git pull --recurse-submodules # optional, if you want a nice doxygen theme
mkdir build
cd build
cmake ..
cmake --build . --target install doxygen
```

## Usage

Example use of the API can be found in the Examples can be found in the [documentation](https://raxonpc.tech/sjpp/examples.html).

## License

See the [LICENSE](https://github.com/raxonpc/sjpp/blob/main/LICENSE) file.

## Dependencies
 - LibCURL
 - GoogleTest
 - Doxygen

### Installing dependencies

#### Ubuntu/Debian:
```shell
sudo apt install libcurl-dev doxygen
```

#### Windows (Chocolatey):
```cmd
choco install curl doxygen.install
```

#### OSX:
```shell
brew install curl doxygen
```

#### Arch Linux:
```shell
sudo pacman -S curl doxygen
```

#### openSUSE:
```shell
zypper install libcurl doxygen
```



