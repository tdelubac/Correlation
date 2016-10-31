#ifndef DEF_DATA
#define DEF_DATA

#include <fstream>
#include <iostream>
#include <math.h> 
#include <vector>

template<class TYPE>
class Data
{
 private:
    size_t m_dim;
    std::vector<TYPE> m_ind;
    std::vector<TYPE> m_x;
    std::vector<TYPE> m_y;
    std::vector<TYPE> m_z;
    std::vector<TYPE> m_val;
    std::vector<TYPE> m_weight;
    std::vector<size_t> m_sample;
 public:
    // constructors
    Data() {}
    Data(std::string source, size_t dim) {m_dim = dim; this->load(source,dim);} 
    // getter functions returning constant reference to member functions
    size_t dim(){
        return m_dim;
    }
    size_t size(){
        return m_x.size();
    }
    const std::vector<TYPE>  & ind()
    {
        return m_ind;
    }
    const std::vector<TYPE>  & x()
    {
        return m_x;
    }
    const std::vector<TYPE> & y()
    {
        return m_y;
    }
    const std::vector<TYPE> & z()
    {
        return m_z;
    }
    const std::vector<TYPE> & val()
    {
        return m_val;
    }
    const std::vector<TYPE> & weight()
    {
        return m_weight;
    }
    const std::vector<size_t> & sample()
    {
        return m_sample;
    }
    // loading data
    void load(std::string source, size_t dim){
    /*
      Load source into class data.
      source must be a 5 columns (dim=2) or 6 columns (dim=3) file.
      First columns are assume to be x,y(,z).
      third to last column assume to be value at x,y(,z) position.
      Second to last column assume to be weight.
      Last column assume to be sample number. Must be an integer!
    */
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
        m_ind.resize(n_lines);
        m_x.resize(n_lines);
        m_y.resize(n_lines);
        m_z.resize(n_lines);
        m_val.resize(n_lines);
        m_weight.resize(n_lines);
        m_sample.resize(n_lines);
        // loading source to data
        for (int irow=0; irow<n_lines; irow++){
            m_ind[irow] = irow;
            file >> m_x[irow];
            file >> m_y[irow];
            if(dim == 3) file >> m_z[irow];
            file >> m_val[irow];
            file >> m_weight[irow];
            file >> m_sample[irow];
        }
        return;
    }
    void spherical2euclidean(double R=1){
        // Convert spherical coordinates (2D) to euclidian coordinates (3D)
        m_dim = 3;
        double ra, dec;
        for(int i=0; i<m_x.size(); ++i){
            ra = m_x[i];
            dec = m_y[i];
            m_x[i] = R*cos(dec) * cos(ra);
            m_y[i] = R*cos(dec) * sin(ra);
            m_z[i] = R*sin(dec);
        }
        return;
    }
};

#endif
