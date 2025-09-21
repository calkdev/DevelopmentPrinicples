#pragma once

#include "GradeCalculator.hpp"

namespace PokenoSouth {

                class Grade {
                public:
                        virtual ~Grade() = default;
                        virtual double calculateGrade() const = 0;
                        virtual string getGradeType() const = 0;
                };

} // namespace PokenoSouth