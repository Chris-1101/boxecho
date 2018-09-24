# boxecho [![License](https://img.shields.io/github/license/Chris-1101/boxecho.svg)](https://github.com/Chris-1101/boxecho/blob/master/LICENSE.md)

Takes input from arguments or stdin and centres it within a frame in the terminal.

### Preview
![Screenshot](https://user-images.githubusercontent.com/28808441/45932374-60294480-bf7b-11e8-8378-91205a0d97a3.png)
<sub>Example output, piped to `lolcat` (spectrum colours)</sub>

### Installation
* Dependencies: `make`, `gcc`
* Only tested on Linux x86_64, there might be portability issues.
* The makefile uses gcc, if you have a different preference you already know what you're doing!

```
$ git clone https://github.com/Chris-1101/boxecho.git
$ cd boxecho
$ make
$ make install
```

### Usage
Straightforward, just call the name of the executable `boxecho` from the terminal followed by your desired input. Some of the possible forms of input, depending on the shell in use, might be:
```
$ boxecho [args]
$ boxecho < FILE
$ boxecho < <(command)
$ boxecho <<< $(command)
$ command | boxecho
```

### To Do
* Configure Script
* PKGBUILD / AUR Package
