#pragma once

#include "common.hpp"
#include "Student.hpp"
#include "Course.hpp"
#include "Grade.hpp"

USING_STD_ASSESSMENT

namespace PokenoSouth {
    // Forward declarations
    class Student;
    class Course;
    
    /**
     * Assessment Entity for Pokeno South Primary School
     * Represents a weighted assessment with automatic grade calculation following TalentHub Wellington patterns
     * 
     * Key Features:
     * - Weighted grade calculation (Internal 30%, Final 70%)
     * - Immutable assessment ID and relationships
     * - Comprehensive validation for marks (0-100 range)
     * - Grade classification and pass/fail determination
     * - Integration with Student and Course entities
     */
    class Assessment : public Grade {
    private:
        // Core assessment data (immutable after construction)
        const string assessmentId;    // Immutable identifier
        const int studentRollNumber;       // Reference to student (immutable)
        const string courseId;        // Reference to course (immutable)
        
        // Marks data (mutable for corrections)
        double internalMarks;              // 0-100, weighted 30%
        double finalMarks;                 // 0-100, weighted 70%
        string assessmentDate;        // YYYY-MM-DD format
        
        // Calculated fields (auto-computed)
        mutable double calculatedGrade;    // Cache for weighted calculation
        mutable bool gradeNeedsRecalculation;  // Flag for lazy evaluation
        
        // Assessment metadata
        string assessmentType;        // e.g., "Assignment", "Test", "Exam"
        string remarks;               // Optional teacher comments
        bool isSubmitted;                  // Submission status
        string submissionDate;        // When student submitted
        
    public:
    // Constructor with core data
    Assessment(const string& assessmentId,
           int studentRollNumber,
           const string& courseId,
           double internalMarks,
           double finalMarks,
           const string& assessmentDate);
    // Polymorphic grade calculation
    double calculateGrade() const override;
    string getGradeType() const override { return "Assessment"; }
        // Constructor with full metadata
        Assessment(const string& assessmentId,
                   int studentRollNumber,
                   const string& courseId,
                   double internalMarks,
                   double finalMarks,
                   const string& assessmentDate,
                   const string& assessmentType,
                   const string& remarks);
        
        // Destructor
        ~Assessment() = default;
        
        // Copy constructor and assignment
        Assessment(const Assessment& other);
        Assessment& operator=(const Assessment& other);
        
        // Move constructor and assignment
        Assessment(Assessment&& other) noexcept = default;
        Assessment& operator=(Assessment&& other) noexcept = delete;  // Cannot move due to const members
        
        // === GETTER METHODS (const correctness) ===
        const string& getAssessmentId() const { return assessmentId; }
        int getStudentRollNumber() const { return studentRollNumber; }
        const string& getCourseId() const { return courseId; }
        double getInternalMarks() const { return internalMarks; }
        double getFinalMarks() const { return finalMarks; }
        const string& getAssessmentDate() const { return assessmentDate; }
        const string& getAssessmentType() const { return assessmentType; }
        const string& getRemarks() const { return remarks; }
        bool getIsSubmitted() const { return isSubmitted; }
        const string& getSubmissionDate() const { return submissionDate; }
        
        // === CALCULATED GETTERS ===
        double getCalculatedGrade() const;     // Weighted: internal*0.3 + final*0.7
        double getInternalContribution() const; // Internal marks * 0.3
        double getFinalContribution() const;    // Final marks * 0.7
        string getLetterGrade() const;     // A+, A, B+, B, C+, C, D, F
        string getGradeStatus() const;     // "Pass" or "Fail"
        bool isPassing() const;                 // Grade >= 50%
        
        // === SETTER METHODS (validation enforced) ===
        void setInternalMarks(double marks);
        void setFinalMarks(double marks);
        void setAssessmentDate(const string& date);
        void setAssessmentType(const string& type);
        void setRemarks(const string& remarks);
        void setIsSubmitted(bool submitted);
        void setSubmissionDate(const string& date);
        // Note: assessmentId, studentRollNumber, courseId are immutable
        
        // === GRADE CALCULATION METHODS ===
        void recalculateGrade();               // Force recalculation
        double calculateWeightedGrade() const; // Pure calculation method
        void updateMarks(double internal, double final); // Update both marks atomically
        
        // === COMPARISON AND ANALYSIS ===
        double getMarksDifference() const;     // Difference between internal and final
        double getImprovementRate() const;     // (final - internal) / internal * 100
        bool showsImprovement() const;         // final > internal
        bool showsDecline() const;             // final < internal
        
        // === VALIDATION AND BUSINESS RULES ===
        bool isLateSubmission() const;         // submission > assessment date
        int getDaysLate() const;               // Days between assessment and submission
        bool requiresResubmission() const;     // Grade < pass threshold and is submitted
        bool isEligibleForSupplemental() const; // Grade between 40-49%
        
        // === DISPLAY AND FORMATTING ===
        void displayAssessmentInfo() const;
        void displayGradeBreakdown() const;
        void displayDetailedReport() const;
        string toCSVString() const;       // For file persistence
        
        // === VALIDATION HELPERS ===
        static bool isValidAssessmentId(const string& assessmentId);
        static bool isValidMarks(double marks);
        static bool isValidRollNumber(int rollNumber);
        static bool isValidCourseId(const string& courseId);
        static string generateAssessmentId(int studentRoll, const string& courseId);
        
        // === BUSINESS RULES AND CONSTANTS ===
        static constexpr double MIN_MARKS = 0.0;
        static constexpr double MAX_MARKS = 100.0;
        static constexpr double INTERNAL_WEIGHT = 0.3;   // 30% weighting
        static constexpr double FINAL_WEIGHT = 0.7;      // 70% weighting
        static constexpr double PASS_THRESHOLD = 50.0;   // 50% to pass
        static constexpr double SUPPLEMENTAL_MIN = 40.0; // Minimum for supplemental
        static constexpr double SUPPLEMENTAL_MAX = 49.9; // Maximum for supplemental
        
        // Grade boundaries for letter grades
        static constexpr double A_PLUS_THRESHOLD = 95.0;
        static constexpr double A_THRESHOLD = 85.0;
        static constexpr double B_PLUS_THRESHOLD = 75.0;
        static constexpr double B_THRESHOLD = 65.0;
        static constexpr double C_PLUS_THRESHOLD = 55.0;
        static constexpr double C_THRESHOLD = 50.0;
        static constexpr double D_THRESHOLD = 40.0;
        // Below 40 = F
        
        // === COMPARISON OPERATORS ===
        bool operator==(const Assessment& other) const;
        bool operator!=(const Assessment& other) const;
        bool operator<(const Assessment& other) const;  // For sorting by grade
        bool operator>(const Assessment& other) const;
    };
    
    // Stream operators for easy printing
    ostream& operator<<(ostream& os, const Assessment& assessment);
}
