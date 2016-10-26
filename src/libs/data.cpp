#ifndef DEF_DATA
#define DEF_DATA

#include <fstream>
#include <iostream>
#include <vector>

template<class TYPE>
class Data
{
private:
  std::vector<TYPE> m_x;
  std::vector<TYPE> m_y;
  std::vector<TYPE> m_z;
  std::vector<TYPE> m_val;
  std::vector<TYPE> m_weight;
  std::vector<size_t> m_sample;
public:
  // constructors
  Data() {}
  Data(std::string source, size_t dim) {this->load(source,dim);} 
  // getter functions
  std::vector<TYPE> x() const
  {
    return m_x;
  }
  std::vector<TYPE> y() const
  {
    return m_y;
  }
  std::vector<TYPE> z() const
  {
    return m_z;
  }
  std::vector<TYPE> val() const
  {
    return m_val;
  }
  std::vector<TYPE> weight() const
  {
    return m_weight;
  }
  std::vector<size_t> sample() const
  {
    return m_sample;
  }
  // loading data
  void load(std::string source, size_t dim)
  /*
    Load source into class data.
    source must be a 5 columns (dim=2) or 6 columns (dim=3) file.
    First columns are assume to be x,y(,z).
    third to last column assume to be value at x,y(,z) position.
    Second to last column assume to be weight.
    Last column assume to be sample number. Must be an integer!
   */
  {
    if((dim!=2) & (dim!=3))
      {
	throw std::domain_error("Data::load(std::string source, size_t dim): dim must be 2 or 3.");
	return;
      }
    std::ifstream file(source);
    if(!file.is_open())
      {
	throw std::runtime_error("Data::load(std::string source, size_t dim): could not open source file.");
      }
    // checking size of file  
    size_t n_lines = 0;
    std::string line;
    while (std::getline(file, line))
      ++n_lines;
    // going back to beginning of file
    file.clear();
    file.seekg(0, std::ios::beg);
    // setting size of vectors
    m_x.resize(n_lines);
    m_y.resize(n_lines);
    m_z.resize(n_lines);
    m_val.resize(n_lines);
    m_weight.resize(n_lines);
    m_sample.resize(n_lines);
    // loading source to data
    for (int irow=0; irow<n_lines; irow++){
      file >> m_x[irow];
      file >> m_y[irow];
      if(dim == 3) file >> m_z[irow];
      file >> m_val[irow];
      file >> m_weight[irow];
      file >> m_sample[irow];
    }
    return;
  }
};

#endif
