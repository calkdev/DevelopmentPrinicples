#pragma once

#include "common.hpp"
#include "Student.hpp"

USING_STD_COURSE

namespace PokenoSouth {
    // Forward declaration
    class Student;
    
    /**
     * Course Entity for Pokeno South Primary School
     * Represents a course with bidirectional relationship management following TalentHub Wellington patterns
     * 
     * Key Features:
     * - Immutable course ID with uppercase enforcement
     * - Bidirectional relationships with students
     * - Enrollment capacity management
     * - Business rule validation
     * - Comprehensive CRUD operations
     */
    class Course {
    // ...existing code...
    // ...existing code...
    // ...existing code...
    // ...existing code...
    // ...existing code...
    // ...existing code...
    // (Removed duplicate getCourseId and getCourseName from private section)
    private:
    // Core course data (immutable after construction)
    const string courseId;     // Immutable identifier, uppercase format
    string courseName;         // Required, descriptive name
    int credits;                    // 1-6 credits allowed
    string description;        // Course description
    string teacher;            // Teacher assigned to course
    int duration;                   // Duration in weeks (1-52)
        
        // Relationship management (bidirectional with Student)
        vector<shared_ptr<Student>> enrolledStudents;
        
        // Course metadata
        string startDate;          // YYYY-MM-DD format
        string endDate;            // YYYY-MM-DD format, must be after startDate
        int maxEnrollment;              // Maximum students allowed
        bool isActive;                  // Course active status
        
    public:

    // Constructor with core data
    Course(const string& courseId,
        const string& courseName,
        int credits,
        const string& description,
        int duration);

    // Constructor with core data and teacher
    Course(const string& courseId,
        const string& courseName,
        int credits,
        const string& description,
        int duration,
        const string& teacher);

    // Constructor with full metadata (no teacher)
    Course(const string& courseId,
           const string& courseName,
           int credits,
           const string& description,
           int duration,
           const string& startDate,
           const string& endDate,
           int maxEnrollment);

    // Constructor with full metadata (with teacher)
    Course(const string& courseId,
           const string& courseName,
           int credits,
           const string& description,
           int duration,
           const string& teacher,
           const string& startDate,
           const string& endDate,
           int maxEnrollment,
           bool isActive);

    // Teacher accessor/mutator
    const string& getTeacher() const { return teacher; }
    void setTeacher(const string& t) { teacher = t; }
    // CourseId and CourseName getters
    const string& getCourseId() const { return courseId; }
    const string& getCourseName() const { return courseName; }
    // Additional getters
    int getCredits() const { return credits; }
    const string& getDescription() const { return description; }
    int getDuration() const { return duration; }
    const string& getStartDate() const { return startDate; }
    const string& getEndDate() const { return endDate; }
        
        // Destructor
        ~Course() = default;
        
        // Copy constructor and assignment (careful with shared_ptr)
        Course(const Course& other);
        Course& operator=(const Course& other);
        
    // 
        int getMaxEnrollment() const { return maxEnrollment; }
        bool getIsActive() const { return isActive; }
        
        // Derived getters
        int getCurrentEnrollment() const;
        int getAvailableSpots() const;
        double getEnrollmentPercentage() const;
        bool isFull() const;
        
        // === SETTER METHODS (validation enforced) ===
        void setCourseName(const string& name);
        void setCredits(int credits);
        void setDescription(const string& description);
        void setDuration(int duration);
        void setStartDate(const string& startDate);
        void setEndDate(const string& endDate);
        void setMaxEnrollment(int maxEnrollment);
        void setIsActive(bool active);
        // Note: courseId is immutable
        
        // === STUDENT ENROLLMENT MANAGEMENT (bidirectional) ===
        bool enrollStudent(shared_ptr<Student> student);
        bool withdrawStudent(int rollNumber);
        bool isStudentEnrolled(int rollNumber) const;
        shared_ptr<Student> getStudent(int rollNumber) const;
        vector<shared_ptr<Student>> getEnrolledStudents() const;
        
        // === ENROLLMENT QUERIES ===
        vector<int> getEnrolledRollNumbers() const;
        vector<string> getEnrolledStudentNames() const;
        bool hasWaitingList() const;
        
        // === BUSINESS RULE VALIDATION ===
        bool canEnrollMoreStudents() const;
        bool isEnrollmentPeriodActive() const;  // Based on start/end dates
        bool meetsPrerequisites(shared_ptr<Student> student) const;
        
        // === GRADE AND ASSESSMENT SUPPORT ===
        double getCourseAverageGrade() const;
        vector<shared_ptr<Student>> getPassingStudents() const;
        vector<shared_ptr<Student>> getFailingStudents() const;
        int getPassCount() const;
        int getFailCount() const;
        double getPassRate() const;
        
        // === DISPLAY AND FORMATTING ===
        void displayCourseInfo() const;
        void displayEnrollmentList() const;
        void displayCourseStatistics() const;
        string toCSVString() const;  // For file persistence
        
        // === VALIDATION HELPERS ===
        static bool isValidCourseId(const string& courseId);
        static bool isValidCourseName(const string& name);
        static bool isValidCredits(int credits);
        static bool isValidDuration(int duration);
        static string formatCourseId(const string& courseId);  // Convert to uppercase
        
        // === BUSINESS RULES ===
        static constexpr int MIN_CREDITS = 1;
        static constexpr int MAX_CREDITS = 6;
        static constexpr int MIN_DURATION = 1;    // weeks
        static constexpr int MAX_DURATION = 52;   // weeks
        static constexpr int DEFAULT_MAX_ENROLLMENT = 30;
        static constexpr int ABSOLUTE_MAX_ENROLLMENT = 50;
        
        // === COMPARISON OPERATORS ===
        bool operator==(const Course& other) const;
        bool operator!=(const Course& other) const;
        bool operator<(const Course& other) const;  // For sorting by course ID
    };
    
    // Stream operators for easy printing
    ostream& operator<<(ostream& os, const Course& course);
}
