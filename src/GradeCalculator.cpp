#include "GradeCalculator.hpp"

namespace PokenoSouth {

        double WeightedAverageCalculator::calculateGrade(const vector<AssessmentScore>& scores) const {
                double wsum = 0.0, sum = 0.0;
                for (const auto& s : scores) {
                    sum  += s.score * s.weight;
                    wsum += s.weight;
                }
                return (wsum > 0.0) ? (sum / wsum) : 0.0;
        }

        double BestNOutOfMCalculator::calculateGrade(const vector<AssessmentScore>& scores) const {
                if (scores.empty()) return 0.0;
                vector<double> weighted;
                weighted.reserve(scores.size());
                for (const auto& s : scores) weighted.push_back(s.score); // simple “best N raw scores”
                nth_element(weighted.begin(),
                                 weighted.begin() + min(bestN_, weighted.size()),
                                 weighted.end(),
                                 greater<double>());
                size_t take = min(bestN_, weighted.size());
                double sum = accumulate(weighted.begin(), weighted.begin() + take, 0.0);
                return sum / static_cast<double>(take);
        }
} // namespace PokenoSouth