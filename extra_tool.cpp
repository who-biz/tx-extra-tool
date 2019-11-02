#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

//https://stackoverflow.com/users/939402/joel-sj%c3%b6gren -- colored text helper
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_CYAN     = 36,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}


std::string bytes_to_string(std::vector<uint8_t> &input)
{
  static const char characters[] = "0123456789abcdef";

  std::string ret(input.size() * 2, 0);

  char *buf = const_cast<char *>(ret.data());
 // int base_plus = stoi(base, nullptr, 16);
  //int base_int = ((base) - 1);

  for (const auto &inputbyte : input)
  {
    *buf++ = characters[inputbyte >> 4];
    *buf++ = characters[inputbyte & 0x0F];
  }
  return ret;
}

std::vector<uint8_t> hex_string_to_bytes(const std::string &input)
{
    size_t len = input.length();
    std::vector<uint8_t> out;
    for(size_t i = 0; i < len; i += 2) {
        std::istringstream strm(input.substr(i, 2));
        uint8_t x;
        strm >> std::hex >> x;
        out.push_back(x);
    }
    return out;
}

int main()
{

  Color::Modifier cyan(Color::FG_CYAN);
  Color::Modifier blue(Color::FG_BLUE);
  Color::Modifier def(Color::FG_DEFAULT);
  Color::Modifier red(Color::FG_RED);

bool result = false;
  std::string in;
/*  std::cout << blue << "Please select formatting for tx_extra: "<< def << std::endl;
  std::cout << blue << "Press:   " << def << cyan << "'0' for hexidecimal (default)" << def << std::endl;
  std::cout << cyan << "         '1' for an array of bytes" << def << std::endl;
  std::cout << "         Selection: "; std::cin >> in;

  uint8_t choice = stoi(in, nullptr, 10);

  bool user = choice;

  if(user) {
    in = "";
    std::cout << red << "Choice not yet supported. " << def << std::endl;
*/
  std::string string;
  std::cout << blue << "Enter tx_extra as hex string: " << def << std::endl;
  std::cin >> string;
  std::vector<uint8_t> bytes = hex_string_to_bytes(string);
//    std::vector<uint8_t> bytes = { };
//    std::cout << blue << "Tx extra (bytes): " << def << std::endl;
//    string = bytes_to_hex_string(bytes);

  int bytesize = bytes.size();
  int byte_term = (bytesize)*(2);
  std:: string hexcount = string.substr(2,2);
  uint8_t hexcount_int = stoi(hexcount, nullptr, 16);
  uint8_t hexcount_dec = stoi(hexcount, nullptr, 10);
  std::string hex_dec_str = std::to_string(hexcount_int);
  std::string fields_total = string.substr((hexcount_int+2)*2, byte_term);
  int char_count = (hexcount_int*2);
  int pubnum = (fields_total.length()/66);
  int excess = string.length() - (byte_term - fields_total.length());
  int x = 1;

  std::cout << cyan << "Tx Extra (double-check this with above): " << std::endl << def << blue << string << def << std::endl;
  std::cout << cyan << "Hex without (extranonce) + (byte-count) + (padding): " << std::endl << def << blue << string.substr(6) << def << std::endl;
  std::cout << cyan << "Count of extra bytes total: " << def << blue << bytesize << def << std::endl;
  std::cout << cyan << "User-specified byte-count (in hex): " << def << blue << hexcount << def << std::endl;
  std::cout << cyan << "User-specified byte-count (in decimal): " << def << blue << hex_dec_str << def << std::endl;
  std::cout << cyan << "Bytes after extranonce cutoff: " << def << blue << fields_total << def << std::endl;

  int pubnum_count = 0;
  for (x=1; x<(pubnum+1);x++) {
    int pubkeyincr = ((x-1)*66);
    int lead_tag = stoi(fields_total.substr(pubkeyincr,2), nullptr, 16);
    if (lead_tag == 1) {
      std::cout << cyan << "Pubkey: " << def << blue << fields_total.substr(pubkeyincr,66) << def << std::endl;
    }
    if (lead_tag == 4) {
      std::cout << cyan << "Pubkey additional: " << def << blue << fields_total.substr(pubkeyincr,66) << def << std::endl;
    }
    pubnum_count = pubkeyincr;
  }
  std::string remainder = fields_total.substr(pubnum_count);
  std::cout << cyan << "Remainder of extra: " << blue <<  remainder << std::endl;
  return 0;
}
