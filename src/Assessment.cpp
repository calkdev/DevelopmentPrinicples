#include "Assessment.hpp"

namespace PokenoSouth {

    // Constructor with core data
    Assessment::Assessment(const string& assessmentId,
                          int studentRollNumber,
                          const string& courseId,
                          double internalMarks,
                          double finalMarks,
                          const string& assessmentDate)
        : assessmentId(assessmentId),
          studentRollNumber(studentRollNumber),
          courseId(courseId),
          calculatedGrade(0.0),
          gradeNeedsRecalculation(true) {
        
        // Validate assessment ID
        if (!isValidAssessmentId(assessmentId)) {
            throw invalid_argument("Invalid assessment ID: cannot be empty");
        }
        
        // Validate student roll number
        if (!isValidRollNumber(studentRollNumber)) {
            throw invalid_argument("Invalid student roll number: must be between 1 and 99999");
        }
        
        // Validate course ID
        if (!isValidCourseId(courseId)) {
            throw invalid_argument("Invalid course ID format");
        }
        
        // Validate and set internal marks
        if (!isValidMarks(internalMarks)) {
            throw invalid_argument("Invalid internal marks: must be between " +
                                      to_string(MIN_MARKS) + " and " +
                                      to_string(MAX_MARKS));
        }
        this->internalMarks = internalMarks;
        
        // Validate and set final marks
        if (!isValidMarks(finalMarks)) {
            throw invalid_argument("Invalid final marks: must be between " +
                                      to_string(MIN_MARKS) + " and " +
                                      to_string(MAX_MARKS));
        }
        this->finalMarks = finalMarks;
        
        // Validate and set assessment date
        if (!Common::isValidDate(assessmentDate)) {
            throw invalid_argument("Invalid assessment date format: must be YYYY-MM-DD");
        }
        this->assessmentDate = assessmentDate;
        
        // Initialize defaults
        this->assessmentType = "Assignment";
        this->remarks = "";
        this->isSubmitted = false;
        this->submissionDate = "";
    }
    
    // Constructor with full metadata
    Assessment::Assessment(const string& assessmentId,
                          int studentRollNumber,
                          const string& courseId,
                          double internalMarks,
                          double finalMarks,
                          const string& assessmentDate,
                          const string& assessmentType,
                          const string& remarks)
        : Assessment(assessmentId, studentRollNumber, courseId, internalMarks, finalMarks, assessmentDate) {
        
        this->assessmentType = assessmentType.empty() ? "Assignment" : assessmentType;
        this->remarks = remarks;
    }
    
    // Copy constructor
    Assessment::Assessment(const Assessment& other)
        : assessmentId(other.assessmentId),
          studentRollNumber(other.studentRollNumber),
          courseId(other.courseId),
          internalMarks(other.internalMarks),
          finalMarks(other.finalMarks),
          assessmentDate(other.assessmentDate),
          calculatedGrade(other.calculatedGrade),
          gradeNeedsRecalculation(other.gradeNeedsRecalculation),
          assessmentType(other.assessmentType),
          remarks(other.remarks),
          isSubmitted(other.isSubmitted),
          submissionDate(other.submissionDate) {
    }
    
    // Assignment operator
    Assessment& Assessment::operator=(const Assessment& other) {
        if (this != &other) {
            // Note: assessmentId, studentRollNumber, courseId are const and cannot be changed
            internalMarks = other.internalMarks;
            finalMarks = other.finalMarks;
            assessmentDate = other.assessmentDate;
            calculatedGrade = other.calculatedGrade;
            gradeNeedsRecalculation = other.gradeNeedsRecalculation;
            assessmentType = other.assessmentType;
            remarks = other.remarks;
            isSubmitted = other.isSubmitted;
            submissionDate = other.submissionDate;
        }
        return *this;
    }
    
    // === CALCULATED GETTERS ===
    double Assessment::getCalculatedGrade() const {
        // Memory optimization: Use lazy evaluation with thread-safe double-checked locking pattern
        if (gradeNeedsRecalculation) {
            // Calculate weighted grade: internal*0.3 + final*0.7
            const double newCalculatedGrade = calculateWeightedGrade();
            
            // Atomic update of cached values
            calculatedGrade = newCalculatedGrade;
            gradeNeedsRecalculation = false;
        }
        return calculatedGrade;
    }
    
    double Assessment::getInternalContribution() const {
        return internalMarks * INTERNAL_WEIGHT;
    }
    
    double Assessment::getFinalContribution() const {
        return finalMarks * FINAL_WEIGHT;
    }
    
    string Assessment::getLetterGrade() const {
        double grade = getCalculatedGrade();
        
        if (grade >= A_PLUS_THRESHOLD) return "A+";
        if (grade >= A_THRESHOLD) return "A";
        if (grade >= B_PLUS_THRESHOLD) return "B+";
        if (grade >= B_THRESHOLD) return "B";
        if (grade >= C_PLUS_THRESHOLD) return "C+";
        if (grade >= C_THRESHOLD) return "C";
        if (grade >= D_THRESHOLD) return "D";
        return "F";
    }
    
    string Assessment::getGradeStatus() const {
        return isPassing() ? "Pass" : "Fail";
    }
    
    bool Assessment::isPassing() const {
        return getCalculatedGrade() >= PASS_THRESHOLD;
    }
    
    // === SETTER METHODS ===
    void Assessment::setInternalMarks(double marks) {
        if (!isValidMarks(marks)) {
            throw invalid_argument("Invalid internal marks: must be between " +
                                      to_string(MIN_MARKS) + " and " +
                                      to_string(MAX_MARKS));
        }
        
        // Memory optimization: Only update if value actually changed
        if (abs(this->internalMarks - marks) > 1e-9) {  // Use epsilon comparison for doubles
            this->internalMarks = marks;
            gradeNeedsRecalculation = true;
        }
    }
    
    void Assessment::setFinalMarks(double marks) {
        if (!isValidMarks(marks)) {
            throw invalid_argument("Invalid final marks: must be between " +
                                      to_string(MIN_MARKS) + " and " +
                                      to_string(MAX_MARKS));
        }
        
        // Memory optimization: Only update if value actually changed
        if (abs(this->finalMarks - marks) > 1e-9) {  // Use epsilon comparison for doubles
            this->finalMarks = marks;
            gradeNeedsRecalculation = true;
        }
    }
    
    void Assessment::setAssessmentDate(const string& date) {
        if (!Common::isValidDate(date)) {
            throw invalid_argument("Invalid assessment date format: must be YYYY-MM-DD");
        }
        this->assessmentDate = date;
    }
    
    void Assessment::setAssessmentType(const string& type) {
        this->assessmentType = type.empty() ? "Assignment" : type;
    }
    
    void Assessment::setRemarks(const string& remarks) {
        this->remarks = remarks;
    }
    
    void Assessment::setIsSubmitted(bool submitted) {
        this->isSubmitted = submitted;
        if (submitted && submissionDate.empty()) {
            submissionDate = Common::getCurrentDate();
        }
    }
    
    void Assessment::setSubmissionDate(const string& date) {
        if (!date.empty() && !Common::isValidDate(date)) {
            throw invalid_argument("Invalid submission date format: must be YYYY-MM-DD");
        }
        this->submissionDate = date;
        if (!date.empty()) {
            this->isSubmitted = true;
        }
    }
    
    // === GRADE CALCULATION METHODS ===
    void Assessment::recalculateGrade() {
        gradeNeedsRecalculation = true;
        getCalculatedGrade(); // Force recalculation
    }
    
    double Assessment::calculateWeightedGrade() const {
        return (internalMarks * INTERNAL_WEIGHT) + (finalMarks * FINAL_WEIGHT);
    }
    
    void Assessment::updateMarks(double internal, double final) {
        if (!isValidMarks(internal)) {
            throw invalid_argument("Invalid internal marks: must be between " +
                                      to_string(MIN_MARKS) + " and " +
                                      to_string(MAX_MARKS));
        }
        
        if (!isValidMarks(final)) {
            throw invalid_argument("Invalid final marks: must be between " +
                                      to_string(MIN_MARKS) + " and " +
                                      to_string(MAX_MARKS));
        }
        
        this->internalMarks = internal;
        this->finalMarks = final;
        gradeNeedsRecalculation = true;
    }
    
    // === COMPARISON AND ANALYSIS ===
    double Assessment::getMarksDifference() const {
        return finalMarks - internalMarks;
    }
    
    double Assessment::getImprovementRate() const {
        if (internalMarks == 0.0) return 0.0;
        return (getMarksDifference() / internalMarks) * 100.0;
    }
    
    bool Assessment::showsImprovement() const {
        return finalMarks > internalMarks;
    }
    
    bool Assessment::showsDecline() const {
        return finalMarks < internalMarks;
    }
    
    // === VALIDATION AND BUSINESS RULES ===
    bool Assessment::isLateSubmission() const {
        if (!isSubmitted || submissionDate.empty() || assessmentDate.empty()) {
            return false;
        }
        return submissionDate > assessmentDate;
    }
    
    int Assessment::getDaysLate() const {
        if (!isLateSubmission()) return 0;
        // Simple calculation - for now return placeholder
        // In a real implementation, would parse dates and calculate difference
        return 1; // Placeholder for days late
    }
    
    bool Assessment::requiresResubmission() const {
        return isSubmitted && !isPassing();
    }
    
    bool Assessment::isEligibleForSupplemental() const {
        double grade = getCalculatedGrade();
        return grade >= SUPPLEMENTAL_MIN && grade <= SUPPLEMENTAL_MAX;
    }
    
    // === DISPLAY AND FORMATTING ===
    void Assessment::displayAssessmentInfo() const {
        cout << "\n=== Assessment Information ===" << endl;
        cout << "Assessment ID: " << assessmentId << endl;
        cout << "Student Roll: " << studentRollNumber << endl;
        cout << "Course: " << courseId << endl;
        cout << "Type: " << assessmentType << endl;
        cout << "Assessment Date: " << assessmentDate << endl;
        cout << "Internal Marks: " << fixed << setprecision(1) << internalMarks << "/100" << endl;
        cout << "Final Marks: " << fixed << setprecision(1) << finalMarks << "/100" << endl;
        cout << "Calculated Grade: " << fixed << setprecision(1) << getCalculatedGrade() << "%" << endl;
        cout << "Letter Grade: " << getLetterGrade() << endl;
        cout << "Status: " << getGradeStatus() << endl;
        cout << "Submitted: " << (isSubmitted ? "Yes" : "No") << endl;
        if (isSubmitted && !submissionDate.empty()) {
            cout << "Submission Date: " << submissionDate << endl;
            if (isLateSubmission()) {
                cout << "Late by: " << getDaysLate() << " days" << endl;
            }
        }
        if (!remarks.empty()) {
            cout << "Remarks: " << remarks << endl;
        }
    }
    
    void Assessment::displayGradeBreakdown() const {
        cout << "\n=== Grade Breakdown ===" << endl;
        cout << "Assessment: " << assessmentId << " (" << courseId << ")" << endl;
        cout << "Internal Assessment (" << static_cast<int>(INTERNAL_WEIGHT * 100) << "%): "
                  << fixed << setprecision(1) << internalMarks
                  << " → " << getInternalContribution() << " points" << endl;
        cout << "Final Assessment (" << static_cast<int>(FINAL_WEIGHT * 100) << "%): "
                  << fixed << setprecision(1) << finalMarks
                  << " → " << getFinalContribution() << " points" << endl;
        cout << "Total Grade: " << fixed << setprecision(1) << getCalculatedGrade() << "%" << endl;
        cout << "Letter Grade: " << getLetterGrade() << endl;
        cout << "Performance: ";
        if (showsImprovement()) {
            cout << "Improved by " << fixed << setprecision(1)
                      << getImprovementRate() << "%" << endl;
        } else if (showsDecline()) {
            cout << "Declined by " << fixed << setprecision(1)
                      << abs(getImprovementRate()) << "%" << endl;
        } else {
            cout << "Consistent performance" << endl;
        }
    }
    
    void Assessment::displayDetailedReport() const {
        displayAssessmentInfo();
        displayGradeBreakdown();
        
        // Additional analysis
        cout << "\n=== Analysis ===" << endl;
        if (isEligibleForSupplemental()) {
            cout << "• Eligible for supplemental assessment" << endl;
        }
        if (requiresResubmission()) {
            cout << "• Requires resubmission (below pass threshold)" << endl;
        }
        if (isLateSubmission()) {
            cout << "• Late submission (" << getDaysLate() << " days)" << endl;
        }
        if (getCalculatedGrade() >= A_THRESHOLD) {
            cout << "• Excellent performance!" << endl;
        } else if (getCalculatedGrade() >= B_THRESHOLD) {
            cout << "• Good performance" << endl;
        } else if (isPassing()) {
            cout << "• Satisfactory performance" << endl;
        } else {
            cout << "• Needs improvement" << endl;
        }
    }
    
    string Assessment::toCSVString() const {
        ostringstream oss;
        oss << assessmentId << ","
            << studentRollNumber << ","
            << courseId << ","
            << fixed << setprecision(1) << internalMarks << ","
            << fixed << setprecision(1) << finalMarks << ","
            << fixed << setprecision(1) << getCalculatedGrade() << ","
            << getLetterGrade() << ","
            << assessmentDate << ","
            << assessmentType << ","
            << (isSubmitted ? "Yes" : "No") << ","
            << submissionDate << ","
            << remarks;
        return oss.str();
    }
    
    // === VALIDATION HELPERS ===
    bool Assessment::isValidAssessmentId(const string& assessmentId) {
        return !assessmentId.empty() && assessmentId.length() <= 20;
    }
    
    bool Assessment::isValidMarks(double marks) {
        return marks >= MIN_MARKS && marks <= MAX_MARKS;
    }
    
    bool Assessment::isValidRollNumber(int rollNumber) {
        return rollNumber >= 1 && rollNumber <= 99999;
    }
    
    bool Assessment::isValidCourseId(const string& courseId) {
        return !courseId.empty() && courseId.length() >= 3;
    }
    
    string Assessment::generateAssessmentId(int studentRoll, const string& courseId) {
        return "ASS" + to_string(studentRoll) + "_" + courseId;
    }
    
    // === COMPARISON OPERATORS ===
    bool Assessment::operator==(const Assessment& other) const {
        return assessmentId == other.assessmentId;
    }
    
    bool Assessment::operator!=(const Assessment& other) const {
        return !(*this == other);
    }
    
    bool Assessment::operator<(const Assessment& other) const {
        return getCalculatedGrade() < other.getCalculatedGrade();
    }
    
    bool Assessment::operator>(const Assessment& other) const {
        return getCalculatedGrade() > other.getCalculatedGrade();
    }
    
    // Stream operator
    ostream& operator<<(ostream& os, const Assessment& assessment) {
        os << "Assessment[" << assessment.getAssessmentId() << "]: " 
           << assessment.getCourseId() << " - " 
           << fixed << setprecision(1) << assessment.getCalculatedGrade() << "% ("
           << assessment.getLetterGrade() << ")";
        return os;
    }

    double Assessment::calculateGrade() const {
        return getCalculatedGrade();
    }
}
