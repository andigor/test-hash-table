#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/functional/hash.hpp>
#include <boost/array.hpp>


typedef boost::array<int, 3> Value;
typedef std::vector<Value> RawValues;

RawValues read_raw_values(char const * const name)
{
  std::ifstream infile(name);
  std::string line;
  RawValues ret;
  while (std::getline(infile, line)) {
    Value v;
    std::stringstream str(line);
    str >> v[0];
    str >> v[1];
    str >> v[2];
    ret.push_back(v);
  }
  infile.close();
  return ret;
}


int main()
{
  RawValues vals = read_raw_values("data");
  std::cout << "lines read: " << vals.size() << std::endl;
  return 0;
}
