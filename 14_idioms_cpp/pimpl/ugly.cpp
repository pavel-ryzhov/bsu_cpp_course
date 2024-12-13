#include "ugly.h"

#include "bad.h"

#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

class Spline::SplineImpl {
   public:
    SplineImpl(std::vector<double>&& x, std::vector<double>&& y, double a, double b)
        : x_(std::move(x)), y_(std::move(y)) {
        y2_.resize(x_.size(), 0);
        switch (mySplineSnd(x_.data(), y_.data(), x_.size(), a, b, y2_.data())) {
            case -1:
                throw std::bad_alloc();
            case -2:
                throw std::invalid_argument("");
            default: {
            }
        }
    }

    [[nodiscard]] double Interpolate(double x) const {
        double result = 0;
        switch (mySplintCube(x_.data(), y_.data(), y2_.data(), x_.size(), x, &result)) {
            case -1:
                throw std::runtime_error("Interpolate exception");
            default:
                return result;
        }
    }

   private:
    std::vector<double> x_;
    std::vector<double> y_;
    std::vector<double> y2_;
    double* buffer_ = new double[4](2);
};

Spline::Spline(std::vector<double> x, std::vector<double> y, double a, double b)
    : impl_(std::make_unique<SplineImpl>(std::move(x), std::move(y), a, b)) {
}

Spline::~Spline() = default;

double Spline::Interpolate(double x) const {
    return impl_->Interpolate(x);
}
