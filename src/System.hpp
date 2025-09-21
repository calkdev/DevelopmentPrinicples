#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.hpp"
#include "Student.hpp"
#include "Course.hpp"
#include "Assessment.hpp"
#include "FileHandler.hpp"

USING_STD_SYSTEM

namespace PokenoSouth {

/**
 * @class System
 * @brief   Main system controller for
 *          Pokeno South Primary School Student Management System
 *
 *          This class manages all entities (Students, Courses, Assessments) and provides
 *          comprehensive menu-driven interface with CRUD operations, data persistence,
 *          reporting capabilities, and system management functions.
 * 
 * @author  System developed Adam Calkin 270712965, Ben Edwards 270683820, & Allan Werner 270712961.
 * @version 1.0.0
 */
class System {
private:
    // === ENTITY MANAGEMENT ===
    vector<shared_ptr<Student>> students;
    vector<shared_ptr<Course>> courses;
    vector<shared_ptr<Assessment>> assessments;
    
    // === SYSTEM STATE ===
    bool isRunning;
    bool dataLoaded;
    string currentSession;
    
    // === MENU DISPLAY METHODS ===
    void displayMainMenu() const;
    void displayStudentMenu() const;
    void displayCourseMenu() const;
    void displayAssessmentMenu() const;
    void displayReportsMenu() const;
    void displaySystemMenu() const;
    
    // === INPUT HANDLING ===
    int getMenuChoice(int minOption, int maxOption) const;
    string getStringInput(const string& prompt) const;
    int getIntInput(const string& prompt) const;
    double getDoubleInput(const string& prompt) const;
    bool getYesNoInput(const string& prompt) const;
    
    // ENHANCED INPUT VALIDATION ===
    string getValidatedStringInput(const string& prompt,
                                      function<bool(const string&)> validator,
                                      const string& errorMessage) const;
    int getValidatedIntInput(const string& prompt, int minValue, int maxValue) const;
    double getValidatedDoubleInput(const string& prompt, double minValue, double maxValue) const;
    string trimWhitespace(const string& str) const;
    
    // === INPUT VALIDATION ===
    bool isValidDate(const string& date) const;
    bool isValidEmail(const string& email) const;
    bool isValidRollNumber(int rollNumber) const;
    bool isValidCourseId(const string& courseId) const;
    
    // === MENU CONTROLLERS ===
    void handleStudentMenu();
    void handleCourseMenu();
    void handleAssessmentMenu();
    void handleReportsMenu();
    void handleSystemMenu();
    
    // === ENTITY OPERATIONS ===
    void addNewStudent();
    void viewAllStudents() const;
    void editStudent();
    void deleteStudent();
    void findStudent() const;
    
    void addNewCourse();
    void viewAllCourses() const;
    void editCourse();
    void deleteCourse();
    void findCourse() const;
    
    void addNewAssessment();
    void viewAllAssessments() const;
    void editAssessment();
    void deleteAssessment();
    void findAssessment() const;
    
    // === ENROLLMENT MANAGEMENT ===
    void enrollStudentInCourse();
    void withdrawStudentFromCourse();
    void viewStudentEnrollments() const;
    void viewCourseEnrollments() const;
    
    // === REPORTS AND ANALYTICS ===
    void generateStudentReport() const;
    void generateCourseReport() const;
    void generateGradeReport() const;
    void generateEnrollmentReport() const;
    void generateSystemStatistics() const;
    
    // === DATA MANAGEMENT ===
    void loadAllSystemData();
    bool saveAllSystemData();
    void backupSystemData();
    void validateDataIntegrity();
    void resetSystemData();
    
    // === UTILITY FUNCTIONS ===
    void clearScreen() const;
    void pauseForUser() const;
    void displayHeader(const string& title) const;
    void displayFooter() const;
    void showOperationResult(bool success, const string& operation) const;
    
    // === SEARCH OPERATIONS ===
    shared_ptr<Student> findStudentByRollNumber(int rollNumber) const;
    shared_ptr<Course> findCourseById(const string& courseId) const;
    shared_ptr<Assessment> findAssessmentById(const string& assessmentId) const;
    vector<shared_ptr<Student>> getStudentsInCourse(const string& courseId) const;
    vector<shared_ptr<Course>> getCoursesForStudent(int rollNumber) const;
    vector<shared_ptr<Assessment>> getAssessmentsForStudent(int rollNumber) const;
    vector<shared_ptr<Assessment>> getAssessmentsForCourse(const string& courseId) const;

public:
    // === CONSTRUCTOR AND DESTRUCTOR ===
    System();
    ~System();
    
    // === CORE SYSTEM OPERATIONS ===
    bool initialize();
    int run();
    bool shutdown();
    
    // === ENTITY MANAGEMENT ===
    bool addStudent(shared_ptr<Student> student);
    bool addCourse(shared_ptr<Course> course);
    bool addAssessment(shared_ptr<Assessment> assessment);
    bool removeStudent(int rollNumber);
    bool removeCourse(const string& courseId);
    bool removeAssessment(const string& assessmentId);
    
    // === DATA PERSISTENCE INTERFACE ===
    bool loadData();
    bool saveData();
    bool createBackup();
    
    // === SYSTEM STATUS AND STATISTICS ===
    size_t getStudentCount() const;
    size_t getCourseCount() const;
    size_t getAssessmentCount() const;
    size_t getEnrollmentCount() const;
    bool isInitialized() const;
    string getSessionInfo() const;
    
    // === ENROLLMENT MANAGEMENT (Public Interface) ===
    bool enrollStudent(int rollNumber, const string& courseId);
    bool withdrawStudent(int rollNumber, const string& courseId);
    bool isStudentEnrolled(int rollNumber, const string& courseId) const;
    
    // === USER EXPERIENCE IMPROVEMENTS ===
    void showContextualHelp(const string& menuContext) const;
    bool handleMenuNavigation(int choice, int minOption, int maxOption, const string& menuType);
    void displayNavigationTips() const;
    void clearScreenWithHeader(const string& title) const;
    
    // === User-friendly error messages ===
    void displayUserFriendlyError(const string& operation, const string& technicalError) const;
    void displaySuccessMessage(const string& operation, const string& details = "") const;
    void displayWarningMessage(const string& message) const;
    void displayInfoMessage(const string& message) const;
    
    // === Confirmation dialogs for destructive operations ===
    bool confirmDestructiveOperation(const string& operation, const string& itemDescription,
                                   const vector<string>& warnings = {}) const;
    bool confirmDataLoss(const string& operation) const;
    bool confirmSystemExit() const;
    
    // === UTILITY METHODS ===
    string getCurrentTimestamp() const;
    
    // === COPY AND ASSIGNMENT (Deleted for resource management) ===
    System(const System&) = delete;
    System& operator=(const System&) = delete;
    System(System&&) = delete;
    System& operator=(System&&) = delete;
};

} // namespace PokenoSouth

#endif // SYSTEM_H
