#ifndef  g78912f75_ba71_47f6_8cba_b1ca654cc753
#define  g78912f75_ba71_47f6_8cba_b1ca654cc753

#include <algorithm>

namespace hsc { namespace meas {
namespace tansip {

/** 2 dimensional polynomial: f(x,y) = \sum a_{ij} x^i y^j.
    Its degree must be <= Polynomial2D::maxDegree.
*/
class Polynomial2D
{
public:
    static const unsigned maxDegree = 9;
    static const unsigned maxCoeffVectorLength = (maxDegree + 2) * (maxDegree + 1) / 2;

    struct CoeffVector
    {
        double   value[maxCoeffVectorLength];

        typedef double (&reference)[maxCoeffVectorLength];
        typedef double const (&const_reference)[maxCoeffVectorLength];

        operator reference () { return value; }
        operator const_reference () const { return value; }

        unsigned size()   const { return length_; }
        unsigned getDegree() const { return degree_; }

    private:
        friend class Polynomial2D;
        CoeffVector(){}

        unsigned length_;
        unsigned degree_;
    };

    Polynomial2D()
        : degree_(0)
    {
        coeff_[0][0] = 0.0;
    }

    explicit Polynomial2D(unsigned degree)
        : degree_(degree)
    {
        std::fill_n(coeff_[0], (maxDegree+1)*(maxDegree+1), 0.0);
    }

    Polynomial2D(unsigned degree, double const vector[])
        : degree_(degree)
    {
        for(unsigned i = 0; i <= degree; ++i){
            for(unsigned j = 0; j <= degree - i; ++j){
                coeff_[i][j] = *(vector++);
            }
        }
    }

    Polynomial2D(Polynomial2D const& other)
        : degree_(other.getDegree())
    {
        std::copy(other.coeff_[0], other.coeff_[0] + (maxDegree+1)*(maxDegree+1), coeff_[0]);
    }

    Polynomial2D& operator=(Polynomial2D const& other){
        if(this != &other){
            degree_ = other.getDegree();
            std::copy(other.coeff_[0], other.coeff_[0] + (maxDegree+1)*(maxDegree+1), coeff_[0]);
        }
        return *this;
    }

    /** degree
    */
    unsigned getDegree() const { return degree_; }

    /** coefficients
    */
    double coeff(unsigned i, unsigned j) const {
        return coeff_[i][j];
    }
    double& coeff(unsigned i, unsigned j) {
        return coeff_[i][j];
    }

    /** coeff vector
    */
    void setCoeffVector(unsigned degree, double const vector[]){
        this->degree_ = degree;

        for(unsigned i = 0; i <= degree; ++i){
            for(unsigned j = 0; j <= degree - i; ++j){
                coeff_[i][j] = *(vector++);
            }
        }
    }

    void setCoeffVector(CoeffVector const& coeff){
        this->setCoeffVector(coeff.getDegree(), coeff.value);
    }

    void getCoeffVector(double vector[]) const {
        for(unsigned i = 0; i <= degree_; ++i){
            for(unsigned j = 0; j <= degree_ - i; ++j){
                *(vector++) = coeff_[i][j];
            }
        }
    }

    CoeffVector getCoeffVector() const {
        CoeffVector vec;
        this->getCoeffVector(vec);
        vec.length_ = this->getCoeffVectorLength();
        vec.degree_ = this->getDegree();
        return vec;
    }

    unsigned getCoeffVectorLength() const {
        return getCoeffVectorLength(degree_);
    }

    static unsigned getCoeffVectorLength(unsigned degree){
        return (degree + 2) * (degree + 1) / 2;
    }

    /** f(x,y)
    */
    double operator()(double x, double y) const {
        double sumXY = 0;
        for(int i = (int)degree_; i >= 0; --i){
            double sumY = 0;
            for(int j = (int)degree_ - i; j >= 0; --j){
                sumY = coeff_[i][j] + y * sumY;
            }
            sumXY = sumY + x * sumXY;
        }
        return sumXY;
    }

    /** df/dx
    */
    Polynomial2D dx() const {
        Polynomial2D temp = *this;

        if(degree_ > 0){
            for(unsigned i = 1; i <= degree_; ++i){
                for(unsigned j = 0; j <= degree_ - i; ++j){
                    temp.coeff_[i-1][j] = i * temp.coeff_[i][j];
                }
            }

            --temp.degree_;
        }
        else{
            temp.coeff_[0][0] = 0.0;
        }

        return temp;
    }

    /** df/dy
    */
    Polynomial2D dy() const {
        Polynomial2D temp = *this;

        if(degree_ > 0){
            for(unsigned i = 0; i < /* not <= */ degree_; ++i){
                for(unsigned j = 1; j <= degree_ - i; ++j){
                    temp.coeff_[i][j-1] = j * temp.coeff_[i][j];
                }
            }

            --temp.degree_;
        }
        else{
            temp.coeff_[0][0] = 0.0;
        }

        return temp;
    }

private:
    double   coeff_[maxDegree+1][maxDegree+1];
    unsigned degree_;
};

} // namespace tansip
}} // namespace hsc::meas
#endif //g78912f75_ba71_47f6_8cba_b1ca654cc753
