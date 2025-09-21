#pragma once

#include "Student.hpp"
#include "Course.hpp"
#include "Assessment.hpp"
#include "common.hpp"
#include "Usings.hpp"

USING_STD_FILEHANDLER

namespace PokenoSouth {
    // Forward declarations
    class Student;
    class Course;
    class Assessment;
    
    /**
     * FileHandler Class for Pokeno South Primary School
     * Static repository pattern for CSV file operations following TalentHub Wellington patterns
     *
     * Key Features:
     * - Static utility design for file operations
     * - Comprehensive CSV parsing and writing
     * - Robust error handling and data validation
     * - Relationship management and referential integrity
     * - Backup and recovery operations
     */
    class FileHandler {
    private:
        // Private constructor - static utility class
        FileHandler() = delete;
        FileHandler(const FileHandler&) = delete;
        FileHandler& operator=(const FileHandler&) = delete;
        
        // Internal helper methods
        static vector<string> parseCSVLine(const string& line);
        static string escapeCSVField(const string& field);
        static bool validateCSVHeaders(const vector<string>& headers,
                                     const vector<string>& expectedHeaders);
        static void createDirectoryIfNotExists(const string& dirPath);
        static string generateBackupFilename(const string& originalPath);
        
        // T041-T043: Enhanced file operations and integrity validation
        static bool validateDataConsistency(const vector<shared_ptr<Student>>& students,
                                           const vector<shared_ptr<Course>>& courses,
                                           const vector<shared_ptr<Assessment>>& assessments);
        static bool validateTempFileIntegrity(const vector<string>& tempFiles);
        static void cleanupTempFiles(const vector<string>& tempFiles);
        static bool validateReferentialIntegrity(const vector<shared_ptr<Student>>& students,
                                                const vector<shared_ptr<Course>>& courses,
                                                const vector<shared_ptr<Assessment>>& assessments);
        static bool repairReferentialIntegrity(vector<shared_ptr<Student>>& students,
                                              vector<shared_ptr<Course>>& courses,
                                              vector<shared_ptr<Assessment>>& assessments);
        static bool createIncrementalBackup();
        static bool restoreFromIncrementalBackup(const string& backupPath);
        static vector<string> listAvailableBackups();
        static bool cleanupOldBackups(int keepCount = 10);
        
    public:
        // === CONSTANTS AND CONFIGURATION ===
        static constexpr const char* STUDENTS_FILE = "data/students.csv";
        static constexpr const char* COURSES_FILE = "data/courses.csv";
        static constexpr const char* ASSESSMENTS_FILE = "data/assessments.csv";
        static constexpr const char* ENROLLMENTS_FILE = "data/enrollments.csv";
        static constexpr const char* DATA_DIRECTORY = "data/";
        static constexpr const char* BACKUP_DIRECTORY = "data/backups/";
        static constexpr char CSV_DELIMITER = ',';
        
        // CSV Headers
        static const vector<string> STUDENT_HEADERS;
        static const vector<string> COURSE_HEADERS;
        static const vector<string> ASSESSMENT_HEADERS;
        static const vector<string> ENROLLMENT_HEADERS;
        
        // === FILE EXISTENCE AND VALIDATION ===
        static bool fileExists(const string& filePath);
        static bool isFileReadable(const string& filePath);
        static bool isFileWritable(const string& filePath);
        static bool isValidCSVFile(const string& filePath);
        static long getFileSize(const string& filePath);
        static string getFileLastModified(const string& filePath);
        
        // === DIRECTORY OPERATIONS ===
        static bool createDataDirectories();
        static bool clearDataDirectory();
        static vector<string> listDataFiles();
        
        // === BACKUP AND RECOVERY ===
        static bool backupDataFiles();
        static bool backupFile(const string& filePath);
        static bool restoreFromBackup(const string& backupPath);
        static vector<string> listBackupFiles();
        
        // === STUDENT OPERATIONS ===
        static bool loadStudentsFromFile(vector<shared_ptr<Student>>& students);
        static bool loadStudentsFromFile(vector<shared_ptr<Student>>& students,
                                       const string& filePath);
        static bool saveStudentsToFile(const vector<shared_ptr<Student>>& students);
        static bool saveStudentsToFile(const vector<shared_ptr<Student>>& students,
                                     const string& filePath);
        static bool appendStudentToFile(const shared_ptr<Student>& student);
        static bool updateStudentInFile(const shared_ptr<Student>& student);
        static bool removeStudentFromFile(int rollNumber);
        
        // === COURSE OPERATIONS ===
        static bool loadCoursesFromFile(vector<shared_ptr<Course>>& courses);
        static bool loadCoursesFromFile(vector<shared_ptr<Course>>& courses,
                                      const string& filePath);
        static bool saveCoursesToFile(const vector<shared_ptr<Course>>& courses);
        static bool saveCoursesToFile(const vector<shared_ptr<Course>>& courses,
                                    const string& filePath);
        static bool appendCourseToFile(const shared_ptr<Course>& course);
        static bool updateCourseInFile(const shared_ptr<Course>& course);
        static bool removeCourseFromFile(const string& courseId);
        
        // === ASSESSMENT OPERATIONS ===
        static bool loadAssessmentsFromFile(vector<shared_ptr<Assessment>>& assessments);
        static bool loadAssessmentsFromFile(vector<shared_ptr<Assessment>>& assessments,
                                          const string& filePath);
        static bool saveAssessmentsToFile(const vector<shared_ptr<Assessment>>& assessments);
        static bool saveAssessmentsToFile(const vector<shared_ptr<Assessment>>& assessments,
                                        const string& filePath);
        static bool appendAssessmentToFile(const shared_ptr<Assessment>& assessment);
        static bool updateAssessmentInFile(const shared_ptr<Assessment>& assessment);
        static bool removeAssessmentFromFile(const string& assessmentId);
        
        // === ENROLLMENT RELATIONSHIP OPERATIONS ===
        static bool loadEnrollments(vector<shared_ptr<Student>>& students,
                                  vector<shared_ptr<Course>>& courses);
        static bool saveEnrollments(const vector<shared_ptr<Student>>& students,
                                  const vector<shared_ptr<Course>>& courses);
        static bool saveEnrollments(const vector<shared_ptr<Student>>& students,
                                  const vector<shared_ptr<Course>>& courses,
                                  const string& filePath);
        static bool enrollStudentInCourse(int rollNumber, const string& courseId);
        static bool withdrawStudentFromCourse(int rollNumber, const string& courseId);
        static bool isStudentEnrolledInCourse(int rollNumber, const string& courseId);
        
        // === COMPREHENSIVE DATA OPERATIONS ===
        static bool loadAllData(vector<shared_ptr<Student>>& students,
                              vector<shared_ptr<Course>>& courses,
                              vector<shared_ptr<Assessment>>& assessments);
        static bool saveAllData(const vector<shared_ptr<Student>>& students,
                              const vector<shared_ptr<Course>>& courses,
                              const vector<shared_ptr<Assessment>>& assessments);
        static bool initializeDataFiles();
        static bool validateDataIntegrity(const vector<shared_ptr<Student>>& students,
                                        const vector<shared_ptr<Course>>& courses,
                                        const vector<shared_ptr<Assessment>>& assessments);
        
        // === ERROR HANDLING AND LOGGING ===
        static string getLastError();
        static void clearLastError();
        static bool hasError();
        static void logOperation(const string& operation, bool success,
                               const string& details = "");
        
        // === T035: ENHANCED ERROR HANDLING ===
        static bool validateFilePermissions(const string& filePath);
        static bool validateDiskSpace(const string& filePath, size_t requiredSpace = 0);
        static bool createFileBackupWithRetry(const string& filePath, int maxRetries = 3);
        static bool recoverFromFileCorruption(const string& filePath);
        static string getDetailedErrorInfo();
        static void logErrorWithContext(const string& operation, const string& filePath,
                                      const exception& e, int lineNumber = -1);
        static bool isFileRecoverable(const string& filePath);
        static bool attemptFileRecovery(const string& filePath, const string& backupDir);
        static bool createEmptyFileWithHeaders(const string& filePath);
        
        // === DATA STATISTICS AND REPORTING ===
        static int countRecordsInFile(const string& filePath);
        static vector<string> validateFileFormat(const string& filePath,
                                                          const vector<string>& expectedHeaders);
        static bool repairCorruptedFile(const string& filePath);
        
        // === IMPORT/EXPORT UTILITIES ===
        static bool exportToCSV(const string& filePath,
                               const vector<vector<string>>& data,
                               const vector<string>& headers);
        static bool importFromCSV(const string& filePath,
                                vector<vector<string>>& data,
                                vector<string>& headers);
        
        // === SEARCH AND FILTER OPERATIONS ===
        static shared_ptr<Student> findStudentByRollNumber(int rollNumber,
                                                               const vector<shared_ptr<Student>>& students);
        static shared_ptr<Course> findCourseById(const string& courseId,
                                                     const vector<shared_ptr<Course>>& courses);
        static shared_ptr<Assessment> findAssessmentById(const string& assessmentId,
                                                             const vector<shared_ptr<Assessment>>& assessments);
        static vector<shared_ptr<Student>> findStudentsByName(const string& name,
                                                                       const vector<shared_ptr<Student>>& students);
        static vector<shared_ptr<Assessment>> findAssessmentsByStudent(int rollNumber,
                                                                                const vector<shared_ptr<Assessment>>& assessments);
        static vector<shared_ptr<Assessment>> findAssessmentsByCourse(const string& courseId,
                                                                               const vector<shared_ptr<Assessment>>& assessments);

    private:
        // Error tracking
        static  string lastError;
        static bool errorFlag;

        // Operation logging
        static void setError(const string& error);
    };
}
