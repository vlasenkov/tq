#include "StrictDecoderWithBlanks.hpp"

using namespace Tq;


StrictDecoderWithBlanks::StrictDecoderWithBlanks(std::istream& stream,
                                                 char delimiter)
: Decoder(stream, delimiter) {
}


StrictDecoderWithBlanks& StrictDecoderWithBlanks::skipRows(const count_t n) {
  m_count = 0;
  if (m_stream) {
    m_char = 1;
    m_col = 1;
    while (m_count < n) {
      if (m_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n')) {
        m_line++;
        if (m_stream.gcount() > 1){
          m_count++;
        }
      } else {
        m_line++;
        if (m_stream.gcount() > 1){
          m_count++;
        }
        break;
      }
    }
    m_row += m_count;
  }
  return *this;
}


bool StrictDecoderWithBlanks::readField(std::string& s) {
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
        m_line++;
        if (m_char != 1) {
          m_col = 1;
          m_char = 1;
          m_row++;
          return false;
        }
      } else {
        s += c;
        m_char++;
      }
    } else {
      if (m_char == 1) {
        m_count = 0;
      }
      m_col = 1;
      m_char = 1;
      m_line++;
      m_row++;
      return false;
    }
  }
}


StrictDecoderWithBlanks& StrictDecoderWithBlanks::skipFields(const count_t n) {
  m_count = 0;
  char c;
  while (m_count < n) {
    if (m_stream.get(c)) {
      if (c == m_delimiter) {
        m_col++;
        m_count++;
        m_char++;
      } else if (c == '\n') {
        m_line++;
        if (m_char != 1) {
          m_col = 1;
          m_char = 1;
          m_row++;
          m_count++;
          return *this;
        }
      } else {
        m_char++;
      }
    } else {
      if (m_char != 1) {
        m_count++;
      }
      m_col = 1;
      m_char = 1;
      m_line++;
      m_row++;
      return *this;
    }
  }
  return *this;
}
