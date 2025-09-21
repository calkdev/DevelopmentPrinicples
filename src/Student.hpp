#pragma once

#include "common.hpp"
#include "Course.hpp"
#include "Assessment.hpp"

USING_STD_STUDENT

namespace PokenoSouth {
    // Forward declarations
    class Course;
    class Assessment;
    
    /**
     * Student Entity for Pokeno South Primary School
     * Represents a student with immutable ID and composition patterns following TalentHub Wellington patterns
     * 
     * Key Features:
     * - Immutable roll number (ID pattern)
     * - Comprehensive validation for all fields
     * - Bidirectional relationships with courses
     * - Assessment tracking and grade management
     * - CRUD operations with proper encapsulation
     */
    class Student {
    private:
        // Core student data (immutable after construction)
        const int rollNumber;           // Unique identifier, immutable
        string firstName;          // Alphabetic only, required
        string lastName;           // Alphabetic only, required
        string dateOfBirth;        // YYYY-MM-DD format, past date only
        string address;            // Non-empty, max length 100
        string contactEmail;       // Valid email format required
        string emergencyContact;   // Valid email format required
        string enrollmentDate;     // YYYY-MM-DD format, not future
        
        // Relationship management (composition pattern)
        vector<shared_ptr<Course>> enrolledCourses;
        vector<shared_ptr<Assessment>> assessments;
        
    public:
        // Constructor with comprehensive validation
        Student(int rollNumber, 
                const string& firstName,
                const string& lastName,
                const string& dateOfBirth,
                const string& address,
                const string& contactEmail,
                const string& emergencyContact,
                const string& enrollmentDate);
        
        // Destructor
        ~Student() = default;
        
        // Copy constructor and assignment (careful with shared_ptr)
        Student(const Student& other);
        Student& operator=(const Student& other);
        
        // Move constructor and assignment
        Student(Student&& other) noexcept = default;
        Student& operator=(Student&& other) noexcept = delete;  // Cannot move due to const members
        
        // === GETTER METHODS (const correctness) ===
        int getRollNumber() const { return rollNumber; }
        const string& getFirstName() const { return firstName; }
        const string& getLastName() const { return lastName; }
        const string& getDateOfBirth() const { return dateOfBirth; }
        const string& getAddress() const { return address; }
        const string& getContactEmail() const { return contactEmail; }
        const string& getEmergencyContact() const { return emergencyContact; }
        const string& getEnrollmentDate() const { return enrollmentDate; }
        
        // Derived getters
        string getFullName() const;
        int getAge() const;  // Calculate from dateOfBirth
        
        // === SETTER METHODS (validation enforced) ===
        void setFirstName(const string& firstName);
        void setLastName(const string& lastName);
        void setContactEmail(const string& email);
        void setEmergencyContact(const string& phoneNumber);
        // Note: rollNumber, dateOfBirth, enrollmentDate are immutable
        
        // === COURSE ENROLLMENT MANAGEMENT ===
        void enrollInCourse(shared_ptr<Course> course);
        void withdrawFromCourse(const string& courseId);
        bool isEnrolledInCourse(const string& courseId) const;
        vector<shared_ptr<Course>> getEnrolledCourses() const;
        int getEnrollmentCount() const;
        
        // === ASSESSMENT MANAGEMENT ===
        void addAssessment(shared_ptr<Assessment> assessment);
        void removeAssessment(const string& assessmentId);
        vector<shared_ptr<Assessment>> getAssessments() const;
        vector<shared_ptr<Assessment>> getAssessmentsForCourse(const string& courseId) const;
        
        // === GRADE CALCULATION AND REPORTING ===
        double getOverallGrade() const;  // Average across all assessments
        double getCourseGrade(const string& courseId) const;  // Average for specific course
        string getGradeStatus() const;  // Pass/Fail based on 50% threshold
        
        // === DISPLAY AND FORMATTING ===
        void displayStudentInfo() const;
        void displayEnrollmentSummary() const;
        void displayGradeSummary() const;
        string toCSVString() const;  // For file persistence
        
        // === BUSINESS RULES ===
        static constexpr int MIN_ROLL_NUMBER = 1;
        static constexpr int MAX_ROLL_NUMBER = 99999;
        static constexpr int MAX_ENROLLMENTS = 8;  // Maximum courses per student
        static constexpr double PASS_THRESHOLD = 50.0;  // Minimum grade to pass
        
        // === COMPARISON OPERATORS ===
        bool operator==(const Student& other) const;
        bool operator!=(const Student& other) const;
        bool operator<(const Student& other) const;  // For sorting by roll number
    };
    
    // Stream operators for easy printing
    ostream& operator<<(ostream& os, const Student& student);
}
