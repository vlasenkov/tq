#ifndef TQ_STRICTDECODER_HPP_
#define TQ_STRICTDECODER_HPP_

#include "Decoder.hpp"

namespace Tq
{
  class StrictDecoder : public Decoder
  {
  public:
    StrictDecoder(std::istream& stream, char delimiter = ',');
    bool readField(std::string& s);
    StrictDecoder& skipRows(const count_t n = MAXCOUNT);
    StrictDecoder& skipFields(const count_t n = MAXCOUNT);
  };
}

#endif // TQ_STRICTDECODER_HPP_