#ifndef DEF_PROFILE
#define DEF_PROFILE

#include <stdexcept>
#include <vector>

#include "axis.h"
#include "matrix.h"

template<class TYPE_MATRIX, class TYPE_AXES=TYPE_MATRIX>
    class Profile{
    private:
    Axis<TYPE_AXES> m_axis1, m_axis2;
    Matrix<TYPE_MATRIX> m_data, m_data2, m_entries, m_weight;
    public:
    // constructor
    Profile() {}
    // 1D profile
    Profile(Axis<TYPE_AXES> axis1): m_axis1(axis1){
        Axis<TYPE_AXES> axis2;
        axis2.push_back(0);
        m_axis2 = axis2;
        m_data = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
        m_data2 = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
        m_entries = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
        m_weight = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
    }
    // 2D profile
    Profile(Axis<TYPE_AXES> axis1, Axis<TYPE_AXES> axis2): m_axis1(axis1), m_axis2(axis2){
        m_data = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
        m_data2 = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
        m_entries = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
        m_weight = Matrix<TYPE_MATRIX>(axis1.size(),axis2.size());
    }
    // const element accessor
    /*
    const TYPE_MATRIX& operator()(size_t axis1, size_t axis2)
    {
        if (m_weight(axis1,axis2) > 0)
            return m_data(axis1,axis2) / m_weight(axis1,axis2);
        return m_data(axis1,axis2);
    }
    */
    // getter functions
    const Axis<TYPE_AXES> & getAxis1(){
        return m_axis1;
    }
    const Axis<TYPE_AXES> & getAxis2(){
        return m_axis2;
    }
    Matrix<TYPE_MATRIX> getData(){
        return m_data/m_weight;
    }
    Matrix<TYPE_MATRIX> getData2(){
        return m_data2/m_weight;
    }
    Matrix<TYPE_MATRIX> getEntries(){
        return m_entries;
    }
    Matrix<TYPE_MATRIX> getWeight(){
        return m_weight;
    }
    Matrix<TYPE_MATRIX> getVariance(){
        return this->getData2() - (this->getData()*this->getData());
    }
    // filler 1D
    void fill(TYPE_AXES val1, TYPE_MATRIX data, TYPE_MATRIX weight){
        size_t bin1;
        try{
            bin1 = m_axis1.getBin(val1);
        }catch(std::exception &err){
            std::cout << "Warning: " << err.what() << "\n";
            return;
        }
        m_data(bin1,0)+=data*weight;
        m_data2(bin1,0)+=data*data*weight;
        m_entries(bin1,0)+=1;
        m_weight(bin1,0)+=weight;
        return;
    }
    // filler 2D
    void fill(TYPE_AXES val1, TYPE_AXES val2, TYPE_MATRIX data, TYPE_MATRIX weight){
        size_t bin1;
        try{
            bin1 = m_axis1.getBin(val1);
        }catch(std::exception &err){
            std::cout << "Warning: " << err.what() << "\n";
            return;
        }
        size_t bin2;
        try{
            bin2 = m_axis2.getBin(val2);
        }catch(std::exception &err){
            std::cout << "Warning: " << err.what() << "\n";
            return;
        }
        m_data(bin1,bin2)+=data*weight;
        m_data2(bin1,bin2)+=data*data*weight;
        m_entries(bin1,bin2)+=1;
        m_weight(bin1,bin2)+=weight;
        return;
    }
    };

#endif
