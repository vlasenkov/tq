#include "Utilities.hpp"

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <cstring>

#include "StrictDecoder.hpp"
#include "StrictDecoderWithBlanks.hpp"

namespace Tq {

  bool endsWith(const std::string &str, const std::string &ending) {
    return str.size() >= ending.size() &&
           str.compare(str.size() - ending.size(), ending.size(), ending) == 0;
  }


  Compression inferCompression(const std::string &filename) {
    if (endsWith(filename, ".gz") || endsWith(filename, ".gzip")) {
      return Compression::Gzip;
    } else if (endsWith(filename, ".zlib")) {
      return Compression::Zlib;
    } else {
      return Compression::None;
    }
  }


  void decompressFile(boost::iostreams::
                        filtering_stream<boost::iostreams::input>& stream,
                      const std::string& filename,
                      Compression compression) {
    stream.reset();
    switch (compression) {
      case Compression::Gzip:
        stream.push(boost::iostreams::gzip_decompressor());
        break;
      case Compression::Zlib:
        stream.push(boost::iostreams::zlib_decompressor());
        break;
      case Compression::None:
        break;
    }
    stream.push(
      boost::iostreams::file_source(
        filename, std::ios_base::in | std::ios_base::binary));
  }


  Decoder * makeDecoder(std::istream& stream, const char *fmt) {
    char delimiter = ',';
    bool ignore_blank_lines = false;
    int n = strlen(fmt);
    for (int i = 0; i < n - n % 2; i += 2) {
      switch (fmt[i]) {
        case 'd':
          delimiter = fmt[i + 1];
          break;
        case 'b':
          switch (fmt[i + 1]) {
            case 'T':
              ignore_blank_lines = true;
              break;
            case 'F':
              ignore_blank_lines = false;
              break;
            default:
              throw std::invalid_argument( "invalid format" );
          }
          break;
        default:
          throw std::invalid_argument( "invalid format" );
      }
    }

    if (ignore_blank_lines) {
      return new StrictDecoderWithBlanks(stream, delimiter);
    } else {
      return new StrictDecoder(stream, delimiter);
    }
  }
}
