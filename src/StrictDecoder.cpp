#include "StrictDecoder.hpp"

using namespace Tq;


StrictDecoder::StrictDecoder(std::istream& stream, char delimiter)
: Decoder(stream, delimiter) {
}


StrictDecoder& StrictDecoder::skipRows(const count_t n) {
  m_count = 0;
  while (m_count < n &&
         m_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n')) {
    m_count++;
  }
  if (m_count) {
    m_line += m_count;
    m_row += m_count;
    m_char = 1;
  }
  return *this;
}


bool StrictDecoder::readField(std::string& s) {
  if (m_stream) {
    s.clear();
    char c;
    m_count = 1;
    for (;;) {
      if (m_stream.get(c)) {
        if (c == m_delimiter) {
          m_col++;
          m_char++;
          return true;
        } else if (c == '\n') {
          m_col = 1;
          m_char = 1;
          m_row++;
          m_line++;
          return false;
        } else {
          s += c;
          m_char++;
        }
      } else {
        m_col = 1;
        m_char = 1;
        m_line++;
        m_row++;
        return false;
      }
    }
  } else {
    m_count = 0;
    return false;
  }
}


StrictDecoder& StrictDecoder::skipFields(const count_t n) {
  m_count = 0;
  char c;
  while (m_count < n) {
    if (m_stream.get(c)) {
      if (c == m_delimiter) {
        m_col++;
        m_count++;
        m_char++;
      } else if (c == '\n') {
        m_col = 1;
        m_char = 1;
        m_row++;
        m_line++;
        m_count++;
        return *this;
      } else {
        m_char++;
      }
    } else {
      m_count++;
      m_line++;
      m_col = 1;
      m_char = 1;
      m_row++;
      return *this;
    }
  }
  return *this;
}
