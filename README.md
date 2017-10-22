# Table Query

Command line utility for querying large delimiter separated files (CSV, etc)
and DSV streaming library.

## Usage

Count rows:

```bash
$ tq nr file.csv.gz
5
```

Count columns:

```bash
$ tq nc file.csv.gz
3
```

Get column names:

```bash
$ tq cn d\| pipe-separated.csv | sort
A
B
C
```

## Getting

### Download binary

Binaries can be obtained from
[releases page](https://github.com/vlasenkov/tq/releases).

### Build from source

Requires Boost library.

```bash
$ cd tq
$ mkdir build
$ cd build
$ cmake ..
$ make install
```

If you have problems with Boost version it can be explicitly pointed:

```bash
$ cmake -DBOOST_ROOT=/usr/local/Cellar/boost/1.65.1/ ..
```

## License

[MIT](LICENSE)