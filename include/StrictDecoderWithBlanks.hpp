#ifndef TQ_STRICTDECODERWITHBLANKS_HPP_
#define TQ_STRICTDECODERWITHBLANKS_HPP_

#include "Decoder.hpp"

namespace Tq
{
  class StrictDecoderWithBlanks : public Decoder
  {
  public:
    StrictDecoderWithBlanks(std::istream& stream, char delimiter = ',');
    bool readField(std::string& s);
    StrictDecoderWithBlanks& skipRows(const count_t n = MAXCOUNT);
    StrictDecoderWithBlanks& skipFields(const count_t n = MAXCOUNT);
  };
}

#endif // TQ_STRICTDECODERWITHBLANKS_HPP_