#ifndef TQ_DECODER_HPP_
#define TQ_DECODER_HPP_

#include <vector>
#include <string>
#include <istream>

#include "Common.hpp"

namespace Tq
{
  class Decoder
  {
  public:
    Decoder(std::istream& stream, const char delimiter);
    virtual ~Decoder();

    // compute some metrics and perform checks
    count_t countColumns(const bool verify = false);
    count_t countRows();
    void    getHeader(std::vector<std::string>& header);

    // transform table somehow
    // ...

    // give information about position in table
    count_t line()      const { return m_line; }
    count_t character() const { return m_char; }
    count_t row()       const { return m_row; }
    count_t column()    const { return m_col; }
    count_t count()     const { return m_count; }

    // used as stopper in while cycle
    explicit operator bool() const { return bool(m_stream); }

    // format specific routines for movements in table

    // returns true if the field read is not last
    // if the field read is last returns false
    // returns false if there was no field, in this case count = 0
    virtual bool readField(std::string& s) = 0;
    virtual Decoder& skipFields(const count_t n = MAXCOUNT) = 0;
    virtual Decoder& skipRows(const count_t n = MAXCOUNT) = 0;

  protected:
    const char m_delimiter;
    std::istream& m_stream;
    count_t m_line = 1;
    count_t m_char = 1;
    count_t m_row = 1;
    count_t m_col = 1;
    count_t m_count = 0;
  };
}

#endif  // TQ_DECODER_HPP_