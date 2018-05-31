#include "Bohr.h"

class AhoCorasick {

public:
       AhoCorasick();
      ~AhoCorasick();

      void init(const std::string&, const std::vector<std::string>&, const unsigned int&);
      std::vector<result> solve();
      void reset();
      static bool sortComparator(const result&, const result&);

private:

      std::string text;
      std::vector<std::string> patterns;

      Bohr* bohr;

};
