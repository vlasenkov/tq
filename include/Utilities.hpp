#ifndef TQ_UTILITIES_HPP_
#define TQ_UTILITIES_HPP_

#include <istream>
#include <string>
#include <boost/iostreams/filtering_stream.hpp>
#include "Decoder.hpp"

namespace Tq
{
  enum class Compression { Gzip, Zlib, None };

  bool endsWith(const std::string &str, const std::string &ending);

  Compression inferCompression(const std::string &filename);

  void decompressFile(boost::iostreams::
                        filtering_stream<boost::iostreams::input>& stream,
                      const std::string& filename,
                      Compression compression);

  Decoder * makeDecoder(std::istream& stream, const char *fmt);
}

#endif // TQ_UTILITIES_HPP_