#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <cstdlib>

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

typedef std::vector<size_t> DataIndexes;
typedef RawValues Values;

void remove_duplicates(const RawValues& raw, DataIndexes& indexes, Values & values)
{
  int table[raw.size()];
  std::memset(table, -1, sizeof(table));
  std::cout << "size_of: " << sizeof(table) << std::endl;

  for (size_t i = 0; i<raw.size(); ++i) {
    const Value& v = raw[i];

    size_t hash = boost::hash_range(v.begin(), v.end());
  }

}

int main()
{
  RawValues vals = read_raw_values("data");
  std::cout << "lines read: " << vals.size() << std::endl;

  DataIndexes indexes;
  Values values;
  remove_duplicates(vals, indexes, values);

  return 0;
}

