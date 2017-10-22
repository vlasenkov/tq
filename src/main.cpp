#include <iostream>
#include <cstdlib>
#include <fstream>

#include "Utilities.hpp"
#include "Config.hpp"


char const help[] = R"HELP(
Table query utility.

Syntax:
  tq COMMAND [PARAMETERS] FILE

Parameters:
  d - delimiter [any character]
  b - ignore blank lines [T or F]

Commands:
  nr      - get number of rows (including header)
  nc      - get number of columns
  ncv     - get number of columns and verify that each row has the same length
  cn      - get columns names
  help    - print this help message
  version - print version

Example:
  Count number of rows for pipe-separated values fiel:
    $ tq nr d\| data.csv
)HELP";


int main (int argc, char *argv[]) {
  std::string cmd;
  if (argc < 2) {
    std::cerr << "At least command must be supplied" << std::endl;
    return EXIT_FAILURE;
  } else {
    cmd.assign(argv[1]);
  }

  if (cmd == "help") {
    std::cout << help << std::endl;
    return EXIT_SUCCESS;

  } else if (cmd == "version") {
    std::cout << TQ_VERSION_MAJOR << '.' << TQ_VERSION_MINOR << '.' <<
      TQ_VERSION_PATCH << std::endl;
    return EXIT_SUCCESS;

  } else if (argc > 4) {
    std::cerr << "Too many arguments" << std::endl;
    return EXIT_FAILURE;

  } else {

    Tq::Compression cmp = Tq::inferCompression(argv[argc - 1]);
    boost::iostreams::
      filtering_stream<boost::iostreams::input> stream;
    Tq::decompressFile(stream, argv[argc - 1], cmp);

    Tq::Decoder *decoder;
    if (argc == 4) {
      decoder = Tq::makeDecoder(stream, argv[2]);
    } else {
      decoder = Tq::makeDecoder(stream, "");
    }

    if (cmd == "nr") {

      std::cout << decoder->countRows() << std::endl;
      return EXIT_SUCCESS;

    } else if (cmd == "nc") {

      std::cout << decoder->countColumns() << std::endl;
      return EXIT_SUCCESS;

    } else if (cmd == "ncv") {

      std::cout << decoder->countColumns(true) << std::endl;
      return EXIT_SUCCESS;

    } else if (cmd == "cn") {

      std::vector<std::string> header;
      decoder->getHeader(header);
      for (auto field: header)
        std::cout << field << std::endl;
      return EXIT_SUCCESS;

    } else {

      std::cout << "Uknown command: " << cmd << std::endl;
      return EXIT_FAILURE;

    }
  }

  return EXIT_SUCCESS;
}
