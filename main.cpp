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

void remove_duplicates(const RawValues& raw, DataIndexes& indexes, Values & values, size_t & collisions)
{
  const size_t size = raw.size() * 2;
  int table[size];
  std::memset(table, -1, sizeof(table));

  for (size_t i = 0; i<raw.size(); ++i) {
    const Value& v = raw[i];

    size_t hash = boost::hash_range(v.begin(), v.end()) % size;
    
    for (size_t j = 0; ; ++j) {
      size_t idx = (hash + j) % size;
      if (table[idx] == -1) {
        values.push_back(v);
        indexes.push_back(values.size() - 1);
        table[idx] = values.size() - 1;
        break;
      }
      else if (values[table[idx]] == raw[i]) {
    //    std::cout << "found duplicate!" << std::endl;
        indexes.push_back(table[idx]);
        break;
      }
      else {
    //    std::cout << "found collison" << std::endl;
        ++collisions;
      }
      assert(j < raw.size());
    }
  }

}

int main()
{
  RawValues vals = read_raw_values("data");
  std::cout << "lines read: " << vals.size() << std::endl;

  DataIndexes indexes;
  Values values;
  size_t collisions = 0;
  remove_duplicates(vals, indexes, values, collisions);

  std::cout << "unque_size: " << values.size() << " collisions: " << collisions << std::endl;

  std::cout << "unque_size: " << values.size() << std::endl;

  return 0;
}

