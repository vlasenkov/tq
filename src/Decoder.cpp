#include "Decoder.hpp"

using namespace Tq;


Decoder::Decoder(std::istream& stream, const char delimiter)
: m_delimiter(delimiter)
, m_stream(stream) {
}


Decoder::~Decoder() {
}


count_t Decoder::countColumns(const bool verify) {
  if (verify) {
    skipFields();
    count_t n = m_count;
    while (skipFields()) {
      if (m_count != n) {
        throw std::runtime_error("verification");
      }
    }
    return n;
  } else {
    skipFields();
    return m_count;
  }
}


count_t Decoder::countRows() {
  skipRows();
  return m_count;
}


void Decoder::getHeader(std::vector<std::string>& header) {
  header.clear();
  do {
    header.emplace_back();
  } while (readField(header.back()));
  if (m_count == 0) {
    header.pop_back();
  }
}
