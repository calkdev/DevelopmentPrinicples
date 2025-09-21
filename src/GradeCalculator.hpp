#pragma once

#include "common.hpp"

USING_STD_GRADECALCULATOR

namespace PokenoSouth {
        struct AssessmentScore {
                int rollNumber;
                string courseCode;
                string assessmentId;
                double score;      // 0..100
                double weight;     // 0..1 (per-course definition)
        };

        class GradeCalculator {
            public:
                virtual ~GradeCalculator() = default;
                virtual double calculateGrade(const vector<AssessmentScore>& scores) const = 0;
        };

        class WeightedAverageCalculator final : public GradeCalculator {
            public:
                double calculateGrade(const vector<AssessmentScore>& scores) const override;
        };

        class BestNOutOfMCalculator final : public GradeCalculator {
            public:
                explicit BestNOutOfMCalculator(size_t bestN) : bestN_(bestN) {}
                double calculateGrade(const vector<AssessmentScore>& scores) const override;
            private:
                size_t bestN_;
        };
} // namespace PokenoSouth