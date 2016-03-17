//----------------------------------------------------------------------------------------------
/// \class AsQuotedString
/// \brief A helper class for reading quoted strings from a stream.
///
/// Usage: _stream >> AsQuotedString(_string, '"') >> ...
//----------------------------------------------------------------------------------------------

#ifndef AS_QUOTED_STRING
#define AS_QUOTED_STRING

class AsQuotedString
{
public:

  AsQuotedString(std::string& string, std::string::value_type delim) : m_string(string), m_delim(delim) {}

  friend std::ostream& operator<<(std::ostream& stream, const AsQuotedString& option) {
      stream << option.m_delim << option.m_string << option.m_delim;
      return stream;
  };
  friend std::istream& operator>>(std::istream& stream, AsQuotedString& option) {
      stream >> std::ws;    // Eat whitespace.
      auto first = stream.peek();

      if (first == option.m_delim)
      {
          stream.get();   // Eat delimiter.
          std::getline(stream, option.m_string, option.m_delim);
      }
      else
      {
          stream >> option.m_string;
      }

      return stream;
  };
  friend std::istream& operator>>(std::istream& stream, AsQuotedString&& option) {
      return stream >> option;
  };

private:

  std::string&                    m_string;
  const std::string::value_type   m_delim;
};

#endif //AS_QUOTED_STRING