#ifndef DEF_LUT
#define DEF_LUT

template <int LBound, int UBound, class TYPE_RESULT, class TYPE_ARG>
    class LUT{
 private:
    TYPE_RESULT m_lut[UBound - LBound + 1];
    double m_coeff;
 public:
    explicit LUT (TYPE_RESULT (*f) (TYPE_ARG), double coeff = 1){
        m_coeff = coeff;
        for (int i = LBound; i <= UBound; ++i){
            m_lut[i - LBound] = f(coeff * i);
        }
    }
    const TYPE_RESULT & operator() (TYPE_ARG val) const{
        int i = int(val/m_coeff) - LBound;
        if(i < 0){
            throw std::out_of_range("LUT::const TYPE_RESULT & operator() (TYPE_ARG val) const: val is lower than 0");
            return 0;
        }
        if(i >= UBound - LBound + 1){
            throw std::out_of_range("LUT::const TYPE_RESULT & operator() (TYPE_ARG val) const: val is greater than UBound - LBound");
            return 0;
        }
        return m_lut[i];
    }
};

#endif DEF_LUT
