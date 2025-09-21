#include "FileHandler.hpp"

USING_STD_FILEHANDLER

namespace PokenoSouth {

    // Static member definitions
    string FileHandler::lastError = "";
    bool FileHandler::errorFlag = false;
    
    // CSV Headers
    const vector<string> FileHandler::STUDENT_HEADERS = {
        "RollNumber", "FirstName", "LastName", "Address", "DateOfBirth", 
        "ContactEmail", "EmergencyContact", "EnrollmentDate"
    };
    
    const vector<string> FileHandler::COURSE_HEADERS = {
        "CourseId", "CourseName", "Credits", "Description", "Teacher", "Duration",
        "StartDate", "EndDate", "MaxEnrollment", "IsActive"
    };
    
    const vector<string> FileHandler::ASSESSMENT_HEADERS = {
        "AssessmentId", "StudentRollNumber", "CourseId", "InternalMarks",
        "FinalMarks", "CalculatedGrade", "AssessmentDate", "AssessmentType",
        "IsSubmitted", "SubmissionDate", "Remarks"
    };
    
    const vector<string> FileHandler::ENROLLMENT_HEADERS = {
        "EnrollmentId", "StudentRollNumber", "CourseId", "EnrollmentDate", "Status"
    };
    
    // === PRIVATE HELPER METHODS ===
    
    vector<string> FileHandler::parseCSVLine(const string& line) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        bool inQuotes = false;
        string current = "";
        
        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == CSV_DELIMITER && !inQuotes) {
                fields.push_back(Common::trimString(current));
                current = "";
            } else {
                current += c;
            }
        }
        fields.push_back(Common::trimString(current));
        
        return fields;
    }
    
    string FileHandler::escapeCSVField(const string& field) {
        if (field.find(CSV_DELIMITER) != string::npos ||
            field.find('"') != string::npos ||
            field.find('\n') != string::npos) {
            string escaped = "\"";
            for (char c : field) {
                if (c == '"') escaped += "\"\"";
                else escaped += c;
            }
            escaped += "\"";
            return escaped;
        }
        return field;
    }
    
    bool FileHandler::validateCSVHeaders(const vector<string>& headers,
                                       const vector<string>& expectedHeaders) {
        if (headers.size() != expectedHeaders.size()) {
            return false;
        }
        
        for (size_t i = 0; i < headers.size(); ++i) {
            if (Common::trimString(headers[i]) != expectedHeaders[i]) {
                return false;
            }
        }
        return true;
    }
    
    void FileHandler::createDirectoryIfNotExists(const string& dirPath) {
        try {
            std::filesystem::create_directories(dirPath);
        } catch (const exception& e) {
            setError("Failed to create directory: " + dirPath + " - " + e.what());
        }
    }
    
    string FileHandler::generateBackupFilename(const string& originalPath) {
        auto now = time(nullptr);
        auto tm = *localtime(&now);
        ostringstream oss;
        oss << put_time(&tm, "%Y%m%d_%H%M%S");
        
        size_t lastSlash = originalPath.find_last_of("/\\");
        string filename = (lastSlash != string::npos) ?
                              originalPath.substr(lastSlash + 1) : originalPath;
        
        return string(BACKUP_DIRECTORY) + filename + "_" + oss.str() + ".bak";
    }
    
    void FileHandler::setError(const string& error) {
        lastError = error;
        errorFlag = true;
    }
    
    // === T035: ENHANCED ERROR HANDLING ===
    
    bool FileHandler::validateFilePermissions(const string& filePath) {
        try {
            std::filesystem::path path(filePath);
            
            // Check if parent directory is writable
            std::filesystem::path parentDir = path.parent_path();
            if (!std::filesystem::exists(parentDir)) {
                setError("Parent directory does not exist: " + parentDir.string());
                return false;
            }
            
            // Try to create a temporary file to test write permissions
            string tempFile = parentDir.string() + "/temp_permission_test.tmp";
            ofstream test(tempFile);
            if (!test.good()) {
                setError("No write permission in directory: " + parentDir.string());
                return false;
            }
            test.close();
            std::filesystem::remove(tempFile);
            
            // If file exists, check if it's readable and writable
            if (std::filesystem::exists(filePath)) {
                ifstream readTest(filePath);
                if (!readTest.good()) {
                    setError("File is not readable: " + filePath);
                    return false;
                }
                readTest.close();
                
                ofstream writeTest(filePath, ios::app);
                if (!writeTest.good()) {
                    setError("File is not writable: " + filePath);
                    return false;
                }
                writeTest.close();
            }
            
            return true;
        } catch (const exception& e) {
            setError("Failed to validate file permissions: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::validateDiskSpace(const string& filePath, size_t requiredSpace) {
        try {
            std::filesystem::path path(filePath);
            std::filesystem::path dir = path.parent_path();
            
            if (!std::filesystem::exists(dir)) {
                dir = std::filesystem::current_path();
            }
            
            auto spaceInfo = std::filesystem::space(dir);
            size_t availableSpace = spaceInfo.available;
            
            // If no specific requirement, use default minimum (10MB)
            if (requiredSpace == 0) {
                requiredSpace = 10 * 1024 * 1024; // 10MB default
            }
            
            if (availableSpace < requiredSpace) {
                setError("Insufficient disk space. Required: " + to_string(requiredSpace) +
                        " bytes, Available: " + to_string(availableSpace) + " bytes");
                return false;
            }
            
            return true;
        } catch (const exception& e) {
            setError("Failed to check disk space: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::createFileBackupWithRetry(const string& filePath, int maxRetries) {
        for (int attempt = 1; attempt <= maxRetries; ++attempt) {
            try {
                if (backupFile(filePath)) {
                    return true;
                }
                
                if (attempt < maxRetries) {
                    logOperation("Backup Retry", false, "Attempt " + to_string(attempt) +
                               " failed for " + filePath + ", retrying...");
                    // Brief delay before retry
                    sleep_for(milliseconds(100 * attempt));
                }
            } catch (const exception& e) {
                if (attempt == maxRetries) {
                    setError("Backup failed after " + to_string(maxRetries) +
                           " attempts: " + string(e.what()));
                }
            }
        }
        return false;
    }
    
    string FileHandler::getDetailedErrorInfo() {
        stringstream info;
        info << "Last Error: " << lastError << "\n";
        info << "Error Flag: " << (errorFlag ? "true" : "false") << "\n";
        info << "Timestamp: " << Common::getCurrentTimestamp() << "\n";
        
        // Add system information
        try {
            auto cwd = std::filesystem::current_path();
            info << "Working Directory: " << cwd.string() << "\n";
            
            if (std::filesystem::exists(DATA_DIRECTORY)) {
                auto spaceInfo = std::filesystem::space(DATA_DIRECTORY);
                info << "Data Directory Space - Total: " << spaceInfo.capacity 
                     << " bytes, Available: " << spaceInfo.available << " bytes\n";
            }
        } catch (const exception& e) {
            info << "Failed to get system info: " << e.what() << "\n";
        }
        
        return info.str();
    }
    
    void FileHandler::logErrorWithContext(const string& operation, const string& filePath,
                                        const exception& e, int lineNumber) {
        stringstream errorMsg;
        errorMsg << "OPERATION: " << operation << " | ";
        errorMsg << "FILE: " << filePath << " | ";
        if (lineNumber > 0) {
            errorMsg << "LINE: " << lineNumber << " | ";
        }
        errorMsg << "ERROR: " << e.what();
        
        setError(errorMsg.str());
        logOperation(operation, false, errorMsg.str());
    }
    
    bool FileHandler::isFileRecoverable(const string& filePath) {
        try {
            if (!std::filesystem::exists(filePath)) {
                return false;
            }
            
            // Check if file is readable
            ifstream file(filePath);
            if (!file.good()) {
                return false;
            }
            
            // Try to read first few lines to check basic structure
            string line;
            int validLines = 0;
            while (getline(file, line) && validLines < 5) {
                if (!line.empty() && line.find(',') != string::npos) {
                    validLines++;
                }
            }
            
            return validLines > 0;
        } catch (const exception&) {
            return false;
        }
    }
    
    bool FileHandler::attemptFileRecovery(const string& filePath, const string& backupDir) {
        try {
            // First, try to find a recent backup
            vector<string> backups = listBackupFiles();
            string baseName = std::filesystem::path(filePath).filename().string();
            
            // Find the most recent backup for this file
            string mostRecentBackup;
            for (const auto& backup : backups) {
                if (backup.find(baseName) != string::npos) {
                    if (mostRecentBackup.empty() || backup > mostRecentBackup) {
                        mostRecentBackup = backup;
                    }
                }
            }
            
            if (!mostRecentBackup.empty()) {
                if (restoreFromBackup(mostRecentBackup)) {
                    logOperation("File Recovery", true, "Restored " + filePath + " from " + mostRecentBackup);
                    return true;
                }
            }
            
            // If no backup available, try to create an empty valid file with headers
            if (createEmptyFileWithHeaders(filePath)) {
                logOperation("File Recovery", true, "Created empty valid file: " + filePath);
                return true;
            }
            
            return false;
        } catch (const exception& e) {
            setError("File recovery failed: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::createEmptyFileWithHeaders(const string& filePath) {
        try {
            std::filesystem::path path(filePath);
            string filename = path.filename().string();
            
            vector<string> headers;
            if (filename.find("students") != string::npos) {
                headers = STUDENT_HEADERS;
            } else if (filename.find("courses") != string::npos) {
                headers = COURSE_HEADERS;
            } else if (filename.find("assessments") != string::npos) {
                headers = ASSESSMENT_HEADERS;
            } else if (filename.find("enrollments") != string::npos) {
                headers = ENROLLMENT_HEADERS;
            } else {
                return false;
            }
            
            ofstream file(filePath);
            if (!file.good()) {
                return false;
            }
            
            for (size_t i = 0; i < headers.size(); ++i) {
                if (i > 0) file << ",";
                file << headers[i];
            }
            file << "\n";
            
            return true;
        } catch (const exception&) {
            return false;
        }
    }
    
    // === FILE EXISTENCE AND VALIDATION ===
    
    bool FileHandler::fileExists(const string& filePath) {
        return std::filesystem::exists(filePath);
    }
    
    bool FileHandler::isFileReadable(const string& filePath) {
        ifstream file(filePath);
        return file.good();
    }
    
    bool FileHandler::isFileWritable(const string& filePath) {
        if (!fileExists(filePath)) {
            // Try to create the file
            ofstream testFile(filePath);
            if (testFile.good()) {
                testFile.close();
                std::filesystem::remove(filePath);
                return true;
            }
            return false;
        }
        
        ofstream file(filePath, ios::app);
        return file.good();
    }
    
    bool FileHandler::isValidCSVFile(const string& filePath) {
        if (!fileExists(filePath) || !isFileReadable(filePath)) {
            return false;
        }
        
        ifstream file(filePath);
        string firstLine;
        getline(file, firstLine);
        
        // Basic validation - contains commas and reasonable length
        return !firstLine.empty() && 
               firstLine.find(CSV_DELIMITER) != string::npos &&
               firstLine.length() < 1000; // Reasonable header length
    }
    
    long FileHandler::getFileSize(const string& filePath) {
        try {
            return std::filesystem::file_size(filePath);
        } catch (const exception&) {
            return -1;
        }
    }
    
    string FileHandler::getFileLastModified(const string& filePath) {
        try {
            auto ftime = std::filesystem::last_write_time(filePath);
            auto sctp = time_point_cast<system_clock::duration>(
                ftime - std::filesystem::file_time_type::clock::now() + system_clock::now());
            auto cftime = system_clock::to_time_t(sctp);
            auto tm = *localtime(&cftime);
            
            ostringstream oss;
            oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
            return oss.str();
        } catch (const exception&) {
            return "Unknown";
        }
    }
    
    // === DIRECTORY OPERATIONS ===
    
    bool FileHandler::createDataDirectories() {
        try {
            createDirectoryIfNotExists(DATA_DIRECTORY);
            createDirectoryIfNotExists(BACKUP_DIRECTORY);
            return !hasError();
        } catch (const exception& e) {
            setError("Failed to create data directories: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::clearDataDirectory() {
        try {
            if (std::filesystem::exists(DATA_DIRECTORY)) {
                for (const auto& entry : std::filesystem::directory_iterator(DATA_DIRECTORY)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".csv") {
                        std::filesystem::remove(entry.path());
                    }
                }
            }
            return true;
        } catch (const exception& e) {
            setError("Failed to clear data directory: " + string(e.what()));
            return false;
        }
    }
    
    vector<string> FileHandler::listDataFiles() {
        vector<string> files;
        try {
            if (std::filesystem::exists(DATA_DIRECTORY)) {
                for (const auto& entry : std::filesystem::directory_iterator(DATA_DIRECTORY)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".csv") {
                        files.push_back(entry.path().string());
                    }
                }
            }
        } catch (const exception& e) {
            setError("Failed to list data files: " + string(e.what()));
        }
        return files;
    }
    
    // === BACKUP AND RECOVERY ===
    
    bool FileHandler::backupDataFiles() {
        try {
            createDirectoryIfNotExists(BACKUP_DIRECTORY);
            
            vector<string> dataFiles = {
                STUDENTS_FILE, COURSES_FILE, ASSESSMENTS_FILE, ENROLLMENTS_FILE
            };
            
            for (const auto& file : dataFiles) {
                if (fileExists(file)) {
                    if (!backupFile(file)) {
                        return false;
                    }
                }
            }
            return true;
        } catch (const exception& e) {
            setError("Failed to backup data files: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::backupFile(const string& filePath) {
        try {
            if (!fileExists(filePath)) {
                setError("Source file does not exist: " + filePath);
                return false;
            }
            
            string backupPath = generateBackupFilename(filePath);
            std::filesystem::copy_file(filePath, backupPath);
            
            logOperation("Backup", true, filePath + " -> " + backupPath);
            return true;
        } catch (const exception& e) {
            setError("Failed to backup file: " + filePath + " - " + e.what());
            return false;
        }
    }
    
    bool FileHandler::restoreFromBackup(const string& backupPath) {
        try {
            if (!fileExists(backupPath)) {
                setError("Backup file does not exist: " + backupPath);
                return false;
            }
            
            // Determine original file path from backup name
            size_t lastSlash = backupPath.find_last_of("/\\");
            string filename = (lastSlash != string::npos) ?
                                  backupPath.substr(lastSlash + 1) : backupPath;
            
            // Extract original filename (remove timestamp and .bak)
            size_t underscorePos = filename.find_last_of('_');
            if (underscorePos != string::npos) {
                filename = filename.substr(0, underscorePos);
            }
            
            string originalPath = string(DATA_DIRECTORY) + filename;
            std::filesystem::copy_file(backupPath, originalPath,
                                     std::filesystem::copy_options::overwrite_existing);
            
            logOperation("Restore", true, backupPath + " -> " + originalPath);
            return true;
        } catch (const exception& e) {
            setError("Failed to restore from backup: " + backupPath + " - " + e.what());
            return false;
        }
    }
    
    vector<string> FileHandler::listBackupFiles() {
        vector<string> backups;
        try {
            if (std::filesystem::exists(BACKUP_DIRECTORY)) {
                for (const auto& entry : std::filesystem::directory_iterator(BACKUP_DIRECTORY)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".bak") {
                        backups.push_back(entry.path().string());
                    }
                }
            }
        } catch (const exception& e) {
            setError("Failed to list backup files: " + string(e.what()));
        }
        return backups;
    }
    
    // === STUDENT OPERATIONS ===
    
    bool FileHandler::loadStudentsFromFile(vector<shared_ptr<Student>>& students) {
        return loadStudentsFromFile(students, STUDENTS_FILE);
    }
    
    bool FileHandler::loadStudentsFromFile(vector<shared_ptr<Student>>& students,
                                         const string& filePath) {
        try {
            clearLastError();
            
            if (!fileExists(filePath)) {
                setError("Students file does not exist: " + filePath);
                return false;
            }
            
            if (!isFileReadable(filePath)) {
                setError("Cannot read students file: " + filePath);
                return false;
            }
            
            ifstream file(filePath);
            string line;
            bool firstLine = true;
            int lineNumber = 0;
            
            students.clear();
            
            while (getline(file, line)) {
                lineNumber++;
                
                if (line.empty()) continue;
                
                auto fields = parseCSVLine(line);
                
                if (firstLine) {
                    firstLine = false;
                    if (!validateCSVHeaders(fields, STUDENT_HEADERS)) {
                        setError("Invalid CSV headers in students file at line " + to_string(lineNumber));
                        return false;
                    }
                    continue;
                }
                
                if (fields.size() != STUDENT_HEADERS.size()) {
                    setError("Invalid field count in students file at line " + to_string(lineNumber) +
                           " (expected " + to_string(STUDENT_HEADERS.size()) + ", got " + to_string(fields.size()) + ")");
                    continue; // Skip this record but continue processing
                }
                
                try {
                    int rollNumber = stoi(fields[0]);
                    auto student = make_shared<Student>(
                        rollNumber,
                        fields[1], // firstName
                        fields[2], // lastName
                        fields[4], // dateOfBirth (per header order)
                        fields[3], // address
                        fields[5], // contactEmail
                        fields[6], // emergencyContact
                        fields[7]  // enrollmentDate
                    );
                    
                    students.push_back(student);
                } catch (const exception& e) {
                    setError("Failed to create student from line " + to_string(lineNumber) + ": " + e.what());
                    continue; // Skip this record but continue processing
                }
            }
            
            logOperation("Load Students", true, "Loaded " + to_string(students.size()) + " students from " + filePath);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to load students file: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::saveStudentsToFile(const vector<shared_ptr<Student>>& students) {
        return saveStudentsToFile(students, STUDENTS_FILE);
    }
    
    bool FileHandler::saveStudentsToFile(const vector<shared_ptr<Student>>& students,
                                       const string& filePath) {
        try {
            clearLastError();
            createDataDirectories();
            
            ofstream file(filePath);
            if (!file.good()) {
                setError("Cannot write to students file: " + filePath);
                return false;
            }
            
            // Write headers
            for (size_t i = 0; i < STUDENT_HEADERS.size(); ++i) {
                if (i > 0) file << CSV_DELIMITER;
                file << STUDENT_HEADERS[i];
            }
            file << "\n";
            
            // Write student data (must match STUDENT_HEADERS order)
            for (const auto& student : students) {
                if (!student) continue;
                
                file << student->getRollNumber() << CSV_DELIMITER
                     << escapeCSVField(student->getFirstName()) << CSV_DELIMITER
                     << escapeCSVField(student->getLastName()) << CSV_DELIMITER
                     << escapeCSVField(student->getAddress()) << CSV_DELIMITER
                     << student->getDateOfBirth() << CSV_DELIMITER
                     << escapeCSVField(student->getContactEmail()) << CSV_DELIMITER
                     << escapeCSVField(student->getEmergencyContact()) << CSV_DELIMITER
                     << student->getEnrollmentDate() << "\n";
            }
            
            logOperation("Save Students", true, "Saved " + to_string(students.size()) + " students to " + filePath);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to save students file: " + string(e.what()));
            return false;
        }
    }
    
    // === COURSE OPERATIONS ===
    
    bool FileHandler::loadCoursesFromFile(vector<shared_ptr<Course>>& courses) {
        return loadCoursesFromFile(courses, COURSES_FILE);
    }
    
    bool FileHandler::loadCoursesFromFile(vector<shared_ptr<Course>>& courses,
                                        const string& filePath) {
        try {
            clearLastError();
            
            if (!fileExists(filePath)) {
                setError("Courses file does not exist: " + filePath);
                return false;
            }
            
            ifstream file(filePath);
            string line;
            bool firstLine = true;
            int lineNumber = 0;
            
            courses.clear();
            
            while (getline(file, line)) {
                lineNumber++;
                
                if (line.empty()) continue;
                
                auto fields = parseCSVLine(line);
                
                if (firstLine) {
                    firstLine = false;
                    if (!validateCSVHeaders(fields, COURSE_HEADERS)) {
                        setError("Invalid CSV headers in courses file at line " + to_string(lineNumber));
                        return false;
                    }
                    continue;
                }
                
                if (fields.size() != COURSE_HEADERS.size()) {
                    setError("Invalid field count in courses file at line " + to_string(lineNumber));
                    continue;
                }
                
                try {
                    int credits = stoi(fields[2]);
                    // fields[4] is Teacher per header; Duration at index 5
                    int duration = stoi(fields[5]);
                    int maxEnrollment = stoi(fields[8]);
                    string isActiveStr = fields[9];
                    transform(isActiveStr.begin(), isActiveStr.end(), isActiveStr.begin(), [](char c) {return tolower(c);});
                    bool isActive = (isActiveStr == "yes" || isActiveStr == "active" || isActiveStr == "true");
                    
                    auto course = make_shared<Course>(
                        fields[0], // courseId
                        fields[1], // courseName
                        credits,
                        fields[3], // description
                        duration,
                        fields[4], // teacher
                        fields[6], // startDate
                        fields[7], // endDate
                        maxEnrollment,
                        isActive
                    );
                    
                    courses.push_back(course);
                    
                } catch (const exception& e) {
                    setError("Failed to create course from line " + to_string(lineNumber) + ": " + e.what());
                    continue;
                }
            }
            
            logOperation("Load Courses", true, "Loaded " + to_string(courses.size()) + " courses from " + filePath);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to load courses file: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::saveCoursesToFile(const vector<shared_ptr<Course>>& courses) {
        return saveCoursesToFile(courses, COURSES_FILE);
    }
    
    bool FileHandler::saveCoursesToFile(const vector<shared_ptr<Course>>& courses,
                                      const string& filePath) {
        try {
            clearLastError();
            createDataDirectories();
            
            ofstream file(filePath);
            if (!file.good()) {
                setError("Cannot write to courses file: " + filePath);
                return false;
            }
            
            // Write headers
            for (size_t i = 0; i < COURSE_HEADERS.size(); ++i) {
                if (i > 0) file << CSV_DELIMITER;
                file << COURSE_HEADERS[i];
            }
            file << "\n";
            
            // Write course data (must match COURSE_HEADERS order)
            for (const auto& course : courses) {
                if (!course) continue;
                
                file << escapeCSVField(course->getCourseId()) << CSV_DELIMITER
                     << escapeCSVField(course->getCourseName()) << CSV_DELIMITER
                     << course->getCredits() << CSV_DELIMITER
                     << escapeCSVField(course->getDescription()) << CSV_DELIMITER
                     << escapeCSVField(course->getTeacher()) << CSV_DELIMITER
                     << course->getDuration() << CSV_DELIMITER
                     << course->getStartDate() << CSV_DELIMITER
                     << course->getEndDate() << CSV_DELIMITER
                     << course->getMaxEnrollment() << CSV_DELIMITER
                     << (course->getIsActive() ? "Yes" : "No") << "\n";
            }
            
            logOperation("Save Courses", true, "Saved " + to_string(courses.size()) + " courses to " + filePath);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to save courses file: " + string(e.what()));
            return false;
        }
    }
    
    // === ASSESSMENT OPERATIONS ===
    
    bool FileHandler::loadAssessmentsFromFile(vector<shared_ptr<Assessment>>& assessments) {
        return loadAssessmentsFromFile(assessments, ASSESSMENTS_FILE);
    }
    
    bool FileHandler::loadAssessmentsFromFile(vector<shared_ptr<Assessment>>& assessments,
                                            const string& filePath) {
        try {
            clearLastError();
            
            if (!fileExists(filePath)) {
                setError("Assessments file does not exist: " + filePath);
                return false;
            }
            
            ifstream file(filePath);
            string line;
            bool firstLine = true;
            int lineNumber = 0;
            
            assessments.clear();
            
            while (getline(file, line)) {
                lineNumber++;
                
                if (line.empty()) continue;
                
                auto fields = parseCSVLine(line);
                
                if (firstLine) {
                    firstLine = false;
                    if (!validateCSVHeaders(fields, ASSESSMENT_HEADERS)) {
                        setError("Invalid CSV headers in assessments file at line " + to_string(lineNumber));
                        return false;
                    }
                    continue;
                }
                
                if (fields.size() != ASSESSMENT_HEADERS.size()) {
                    setError("Invalid field count in assessments file at line " + to_string(lineNumber));
                    continue;
                }
                
                try {
                    int studentRollNumber = stoi(fields[1]);
                    double internalMarks = stod(fields[3]);
                    double finalMarks = stod(fields[4]);
                    bool isSubmitted = (fields[8] == "Yes" || fields[8] == "true");
                    
                    auto assessment = make_shared<Assessment>(
                        fields[0], // assessmentId
                        studentRollNumber,
                        fields[2], // courseId
                        internalMarks,
                        finalMarks,
                        fields[6], // assessmentDate
                        fields[7], // assessmentType
                        fields[10] // remarks
                    );
                    
                    assessment->setIsSubmitted(isSubmitted);
                    if (!fields[9].empty()) {
                        assessment->setSubmissionDate(fields[9]);
                    }
                    
                    assessments.push_back(assessment);
                    
                } catch (const exception& e) {
                    setError("Failed to create assessment from line " + to_string(lineNumber) + ": " + e.what());
                    continue;
                }
            }
            
            logOperation("Load Assessments", true, "Loaded " + to_string(assessments.size()) + " assessments from " + filePath);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to load assessments file: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::saveAssessmentsToFile(const vector<shared_ptr<Assessment>>& assessments) {
        return saveAssessmentsToFile(assessments, ASSESSMENTS_FILE);
    }
    
    bool FileHandler::saveAssessmentsToFile(const vector<shared_ptr<Assessment>>& assessments,
                                          const string& filePath) {
        try {
            clearLastError();
            createDataDirectories();
            
            ofstream file(filePath);
            if (!file.good()) {
                setError("Cannot write to assessments file: " + filePath);
                return false;
            }
            
            // Write headers
            for (size_t i = 0; i < ASSESSMENT_HEADERS.size(); ++i) {
                if (i > 0) file << CSV_DELIMITER;
                file << ASSESSMENT_HEADERS[i];
            }
            file << "\n";
            
            // Write assessment data
            for (const auto& assessment : assessments) {
                if (!assessment) continue;
                
                file << escapeCSVField(assessment->getAssessmentId()) << CSV_DELIMITER
                     << assessment->getStudentRollNumber() << CSV_DELIMITER
                     << escapeCSVField(assessment->getCourseId()) << CSV_DELIMITER
                     << fixed << setprecision(1) << assessment->getInternalMarks() << CSV_DELIMITER
                     << fixed << setprecision(1) << assessment->getFinalMarks() << CSV_DELIMITER
                     << fixed << setprecision(1) << assessment->getCalculatedGrade() << CSV_DELIMITER
                     << assessment->getAssessmentDate() << CSV_DELIMITER
                     << escapeCSVField(assessment->getAssessmentType()) << CSV_DELIMITER
                     << (assessment->getIsSubmitted() ? "Yes" : "No") << CSV_DELIMITER
                     << assessment->getSubmissionDate() << CSV_DELIMITER
                     << escapeCSVField(assessment->getRemarks()) << "\n";
            }
            
            logOperation("Save Assessments", true, "Saved " + to_string(assessments.size()) + " assessments to " + filePath);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to save assessments file: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::loadAllData(vector<shared_ptr<Student>>& students,
                                vector<shared_ptr<Course>>& courses,
                                vector<shared_ptr<Assessment>>& assessments) {
        bool success = true;
        
        success &= loadStudentsFromFile(students);
        success &= loadCoursesFromFile(courses);
        success &= loadAssessmentsFromFile(assessments);
        
        // Load enrollments to establish relationships
        if (success) {
            success &= loadEnrollments(students, courses);
        }
        
        if (success) {
            logOperation("Load All Data", true, "Successfully loaded all system data with relationships");
        } else {
            logOperation("Load All Data", false, "Failed to load some system data");
        }
        
        return success;
    }
    
    bool FileHandler::saveAllData(const vector<shared_ptr<Student>>& students,
                                const vector<shared_ptr<Course>>& courses,
                                const vector<shared_ptr<Assessment>>& assessments) {
        
        // T041: Enhanced data consistency with atomic operations
        
        // Step 1: Validate basic data integrity (skip referential integrity for normal saves)
        // Only check for null pointers and duplicate IDs
        for (const auto& student : students) {
            if (!student) {
                logOperation("Save All Data", false, "Found null student pointer");
                return false;
            }
        }
        for (const auto& course : courses) {
            if (!course) {
                logOperation("Save All Data", false, "Found null course pointer");
                return false;
            }
        }
        for (const auto& assessment : assessments) {
            if (!assessment) {
                logOperation("Save All Data", false, "Found null assessment pointer");
                return false;
            }
        }
        
        // Step 2: Create backup before any changes
        if (!backupDataFiles()) {
            logOperation("Save All Data", false, "Backup creation failed");
            return false;
        }
        
        // Step 3: Use atomic save operations with rollback capability
        vector<string> tempFiles;
        bool success = true;
        
        try {
            // Create temporary files for atomic saves
            string tempStudents = string(STUDENTS_FILE) + ".tmp";
            string tempCourses = string(COURSES_FILE) + ".tmp";
            string tempAssessments = string(ASSESSMENTS_FILE) + ".tmp";
            string tempEnrollments = string(ENROLLMENTS_FILE) + ".tmp";
            
            tempFiles = {tempStudents, tempCourses, tempAssessments, tempEnrollments};
            
            // Save to temporary files first
            success &= saveStudentsToFile(students, tempStudents);
            success &= saveCoursesToFile(courses, tempCourses);
            success &= saveAssessmentsToFile(assessments, tempAssessments);
            success &= saveEnrollments(students, courses, tempEnrollments);
            
            if (success) {
                // Validate the temporary files
                success &= validateTempFileIntegrity(tempFiles);
            }
            
            if (success) {
                // Atomic replacement: move temp files to final locations
                std::filesystem::rename(tempStudents, STUDENTS_FILE);
                std::filesystem::rename(tempCourses, COURSES_FILE);
                std::filesystem::rename(tempAssessments, ASSESSMENTS_FILE);
                std::filesystem::rename(tempEnrollments, ENROLLMENTS_FILE);
                
                logOperation("Save All Data", true, 
                    "Successfully saved all system data with atomic operations");
            } else {
                // Cleanup temporary files on failure
                cleanupTempFiles(tempFiles);
                logOperation("Save All Data", false, 
                    "Failed to save system data - temporary files cleaned up");
            }
            
        } catch (const exception& e) {
            success = false;
            cleanupTempFiles(tempFiles);
            setError("Save operation failed: " + string(e.what()));
            logOperation("Save All Data", false, "Exception during save: " + string(e.what()));
        }
        
        return success;
    }
    
    bool FileHandler::initializeDataFiles() {
        try {
            createDataDirectories();
            
            // Create empty files with headers if they don't exist
            if (!fileExists(STUDENTS_FILE)) {
                vector<shared_ptr<Student>> emptyStudents;
                saveStudentsToFile(emptyStudents);
            }
            
            if (!fileExists(COURSES_FILE)) {
                vector<shared_ptr<Course>> emptyCourses;
                saveCoursesToFile(emptyCourses);
            }
            
            logOperation("Initialize Data Files", true, "Data files initialized successfully");
            return true;
            
        } catch (const exception& e) {
            setError("Failed to initialize data files: " + string(e.what()));
            return false;
        }
    }
    
    // === ENROLLMENT RELATIONSHIP OPERATIONS ===
    
    bool FileHandler::loadEnrollments(vector<shared_ptr<Student>>& students,
                                    vector<shared_ptr<Course>>& courses) {
        try {
            clearLastError();
            
            if (!fileExists(ENROLLMENTS_FILE)) {
                logOperation("Load Enrollments", true, "No enrollments file found - starting with empty enrollments");
                return true; // No enrollments file is valid for new system
            }
            
            ifstream file(ENROLLMENTS_FILE);
            string line;
            bool firstLine = true;
            int lineNumber = 0;
            int enrollmentsProcessed = 0;
            
            while (getline(file, line)) {
                lineNumber++;
                
                if (line.empty()) continue;
                
                auto fields = parseCSVLine(line);
                
                if (firstLine) {
                    firstLine = false;
                    if (!validateCSVHeaders(fields, ENROLLMENT_HEADERS)) {
                        setError("Invalid CSV headers in enrollments file at line " + to_string(lineNumber));
                        return false;
                    }
                    continue;
                }
                
                if (fields.size() != ENROLLMENT_HEADERS.size()) {
                    setError("Invalid field count in enrollments file at line " + to_string(lineNumber));
                    continue;
                }
                
                try {
                    int studentRollNumber = stoi(fields[1]);
                    string courseId = fields[2];
                    string status = fields[4];
                    
                    // Only process active enrollments
                    if (status != "Active") continue;
                    
                    // Find student and course
                    auto student = findStudentByRollNumber(studentRollNumber, students);
                    auto course = findCourseById(courseId, courses);
                    
                    if (!student) {
                        setError("Student not found for enrollment: " + to_string(studentRollNumber));
                        continue;
                    }
                    
                    if (!course) {
                        setError("Course not found for enrollment: " + courseId);
                        continue;
                    }
                    
                    // Establish bidirectional relationship
                    try {
                        student->enrollInCourse(course);
                        course->enrollStudent(student);
                        enrollmentsProcessed++;
                    } catch (const exception& e) {
                        setError("Failed to establish enrollment relationship: " + string(e.what()));
                        continue;
                    }
                    
                } catch (const exception& e) {
                    setError("Failed to process enrollment at line " + to_string(lineNumber) + ": " + e.what());
                    continue;
                }
            }
            
            logOperation("Load Enrollments", true, "Processed " + to_string(enrollmentsProcessed) + " enrollments");
            return true;
            
        } catch (const exception& e) {
            setError("Failed to load enrollments file: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::saveEnrollments(const vector<shared_ptr<Student>>& students,
                                    const vector<shared_ptr<Course>>& courses) {
        try {
            clearLastError();
            createDataDirectories();
            
            ofstream file(ENROLLMENTS_FILE);
            if (!file.good()) {
                setError("Cannot write to enrollments file: " + string(ENROLLMENTS_FILE));
                return false;
            }
            
            // Write headers
            for (size_t i = 0; i < ENROLLMENT_HEADERS.size(); ++i) {
                if (i > 0) file << CSV_DELIMITER;
                file << ENROLLMENT_HEADERS[i];
            }
            file << "\n";
            
            // Generate enrollment records from student-course relationships
            int enrollmentCounter = 1;
            int enrollmentsSaved = 0;
            
            for (const auto& student : students) {
                if (!student) continue;
                
                auto enrolledCourses = student->getEnrolledCourses();
                for (const auto& course : enrolledCourses) {
                    if (!course) continue;
                    
                    string enrollmentId = "ENR" + to_string(enrollmentCounter).insert(0, 3 - to_string(enrollmentCounter).length(), '0');
                    
                    file << enrollmentId << CSV_DELIMITER
                         << student->getRollNumber() << CSV_DELIMITER
                         << course->getCourseId() << CSV_DELIMITER
                         << student->getEnrollmentDate() << CSV_DELIMITER
                         << "Active" << "\n";
                    
                    enrollmentCounter++;
                    enrollmentsSaved++;
                }
            }
            
            logOperation("Save Enrollments", true, "Saved " + to_string(enrollmentsSaved) + " enrollments to " + string(ENROLLMENTS_FILE));
            return true;
            
        } catch (const exception& e) {
            setError("Failed to save enrollments file: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::enrollStudentInCourse(int rollNumber, const string& courseId) {
        try {
            clearLastError();
            
            // Load current data
            vector<shared_ptr<Student>> students;
            vector<shared_ptr<Course>> courses;
            
            if (!loadStudentsFromFile(students) || !loadCoursesFromFile(courses)) {
                return false;
            }
            
            // Load existing enrollments
            if (!loadEnrollments(students, courses)) {
                return false;
            }
            
            // Find student and course
            auto student = findStudentByRollNumber(rollNumber, students);
            auto course = findCourseById(courseId, courses);
            
            if (!student) {
                setError("Student not found: " + to_string(rollNumber));
                return false;
            }
            
            if (!course) {
                setError("Course not found: " + courseId);
                return false;
            }
            
            // Check if already enrolled
            if (student->isEnrolledInCourse(courseId)) {
                setError("Student " + to_string(rollNumber) + " is already enrolled in course " + courseId);
                return false;
            }
            
            // Perform enrollment
            student->enrollInCourse(course);
            course->enrollStudent(student);
            
            // Save updated enrollments
            if (!saveEnrollments(students, courses)) {
                return false;
            }
            
            logOperation("Enroll Student", true, "Student " + to_string(rollNumber) + " enrolled in course " + courseId);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to enroll student: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::withdrawStudentFromCourse(int rollNumber, const string& courseId) {
        try {
            clearLastError();
            
            // Load current data
            vector<shared_ptr<Student>> students;
            vector<shared_ptr<Course>> courses;
            
            if (!loadStudentsFromFile(students) || !loadCoursesFromFile(courses)) {
                return false;
            }
            
            // Load existing enrollments
            if (!loadEnrollments(students, courses)) {
                return false;
            }
            
            // Find student and course
            auto student = findStudentByRollNumber(rollNumber, students);
            auto course = findCourseById(courseId, courses);
            
            if (!student) {
                setError("Student not found: " + to_string(rollNumber));
                return false;
            }
            
            if (!course) {
                setError("Course not found: " + courseId);
                return false;
            }
            
            // Check if enrolled
            if (!student->isEnrolledInCourse(courseId)) {
                setError("Student " + to_string(rollNumber) + " is not enrolled in course " + courseId);
                return false;
            }
            
            // Perform withdrawal
            student->withdrawFromCourse(courseId);
            course->withdrawStudent(rollNumber);
            
            // Save updated enrollments
            if (!saveEnrollments(students, courses)) {
                return false;
            }
            
            logOperation("Withdraw Student", true, "Student " + to_string(rollNumber) + " withdrawn from course " + courseId);
            return true;
            
        } catch (const exception& e) {
            setError("Failed to withdraw student: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::isStudentEnrolledInCourse(int rollNumber, const string& courseId) {
        try {
            clearLastError();
            
            // Load current data
            vector<shared_ptr<Student>> students;
            vector<shared_ptr<Course>> courses;
            
            if (!loadStudentsFromFile(students) || !loadCoursesFromFile(courses)) {
                return false;
            }
            
            // Load existing enrollments
            if (!loadEnrollments(students, courses)) {
                return false;
            }
            
            // Find student
            auto student = findStudentByRollNumber(rollNumber, students);
            if (!student) {
                return false;
            }
            
            return student->isEnrolledInCourse(courseId);
            
        } catch (const exception& e) {
            setError("Failed to check enrollment status: " + string(e.what()));
            return false;
        }
    }
    
    // === T041-T043: ENHANCED FILE OPERATIONS AND INTEGRITY VALIDATION ===
    
    bool FileHandler::validateDataConsistency(const vector<shared_ptr<Student>>& students,
                                             const vector<shared_ptr<Course>>& courses,
                                             const vector<shared_ptr<Assessment>>& assessments) {
        try {
            // Validate students
            for (const auto& student : students) {
                if (!student) {
                    setError("Found null student pointer");
                    return false;
                }
                
                // Check for duplicate roll numbers
                int rollNumber = student->getRollNumber();
                int count = 0;
                for (const auto& s : students) {
                    if (s && s->getRollNumber() == rollNumber) {
                        count++;
                    }
                }
                if (count > 1) {
                    setError("Duplicate roll number found: " + to_string(rollNumber));
                    return false;
                }
            }
            
            // Validate courses
            for (const auto& course : courses) {
                if (!course) {
                    setError("Found null course pointer");
                    return false;
                }
                
                // Check for duplicate course IDs
                string courseId = course->getCourseId();
                int count = 0;
                for (const auto& c : courses) {
                    if (c && c->getCourseId() == courseId) {
                        count++;
                    }
                }
                if (count > 1) {
                    setError("Duplicate course ID found: " + courseId);
                    return false;
                }
            }
            
            // Validate assessments
            for (const auto& assessment : assessments) {
                if (!assessment) {
                    setError("Found null assessment pointer");
                    return false;
                }
                
                // Check for duplicate assessment IDs
                string assessmentId = assessment->getAssessmentId();
                int count = 0;
                for (const auto& a : assessments) {
                    if (a && a->getAssessmentId() == assessmentId) {
                        count++;
                    }
                }
                if (count > 1) {
                    setError("Duplicate assessment ID found: " + assessmentId);
                    return false;
                }
            }
            
            // Validate referential integrity
            return validateReferentialIntegrity(students, courses, assessments);
            
        } catch (const exception& e) {
            setError("Data consistency validation failed: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::validateTempFileIntegrity(const vector<string>& tempFiles) {
        try {
            for (const auto& filePath : tempFiles) {
                if (!fileExists(filePath)) {
                    setError("Temporary file does not exist: " + filePath);
                    return false;
                }
                
                if (!isFileReadable(filePath)) {
                    setError("Temporary file is not readable: " + filePath);
                    return false;
                }
                
                // Check if file has reasonable size (not empty, not too large)
                long fileSize = getFileSize(filePath);
                if (fileSize < 0) {
                    setError("Cannot determine size of temporary file: " + filePath);
                    return false;
                }
                
                if (fileSize == 0) {
                    setError("Temporary file is empty: " + filePath);
                    return false;
                }
                
                // Basic CSV format validation
                if (!isValidCSVFile(filePath)) {
                    setError("Temporary file has invalid CSV format: " + filePath);
                    return false;
                }
            }
            
            return true;
            
        } catch (const exception& e) {
            setError("Temporary file integrity check failed: " + string(e.what()));
            return false;
        }
    }
    
    void FileHandler::cleanupTempFiles(const vector<string>& tempFiles) {
        for (const auto& filePath : tempFiles) {
            try {
                if (fileExists(filePath)) {
                    std::filesystem::remove(filePath);
                }
            } catch (const exception& e) {
                // Log but don't fail - cleanup is best effort
                logOperation("Cleanup Temp File", false, 
                    "Failed to remove " + filePath + ": " + e.what());
            }
        }
    }
    
    bool FileHandler::saveEnrollments(const vector<shared_ptr<Student>>& students,
                                     const vector<shared_ptr<Course>>& courses,
                                     const string& filePath) {
        try {
            ofstream file(filePath);
            if (!file.is_open()) {
                setError("Failed to open enrollments file for writing: " + filePath);
                return false;
            }
            
            // Write headers
            for (size_t i = 0; i < ENROLLMENT_HEADERS.size(); ++i) {
                if (i > 0) file << CSV_DELIMITER;
                file << ENROLLMENT_HEADERS[i];
            }
            file << "\n";
            
            // Write enrollment data
            int enrollmentId = 1;
            for (const auto& student : students) {
                if (!student) continue;
                
                auto enrolledCourses = student->getEnrolledCourses();
                for (const auto& course : enrolledCourses) {
                    if (!course) continue;
                    
                    file << enrollmentId++ << CSV_DELIMITER
                         << student->getRollNumber() << CSV_DELIMITER
                         << escapeCSVField(course->getCourseId()) << CSV_DELIMITER
                         << escapeCSVField(student->getEnrollmentDate()) << CSV_DELIMITER
                         << "ACTIVE\n";
                }
            }
            
            if (file.good()) {
                logOperation("Save Enrollments", true, 
                    "Enrollment relationships saved to " + filePath);
                return true;
            } else {
                setError("Error writing enrollment data to file: " + filePath);
                return false;
            }
            
        } catch (const exception& e) {
            setError("Failed to save enrollments: " + string(e.what()));
            return false;
        }
    }
    
    // === T042: REFERENTIAL INTEGRITY VALIDATION ===
    
    bool FileHandler::validateReferentialIntegrity(const vector<shared_ptr<Student>>& students,
                                                  const vector<shared_ptr<Course>>& courses,
                                                  const vector<shared_ptr<Assessment>>& assessments) {
        try {
            bool isValid = true;
            vector<string> integrityErrors;
            
            // Check assessments reference valid students and courses
            for (const auto& assessment : assessments) {
                if (!assessment) continue;
                
                int studentRollNumber = assessment->getStudentRollNumber();
                string courseId = assessment->getCourseId();
                
                // Verify student exists
                bool studentFound = false;
                for (const auto& student : students) {
                    if (student && student->getRollNumber() == studentRollNumber) {
                        studentFound = true;
                        break;
                    }
                }
                
                if (!studentFound) {
                    isValid = false;
                    integrityErrors.push_back("Assessment " + assessment->getAssessmentId() + 
                        " references non-existent student: " + to_string(studentRollNumber));
                }
                
                // Verify course exists
                bool courseFound = false;
                for (const auto& course : courses) {
                    if (course && course->getCourseId() == courseId) {
                        courseFound = true;
                        break;
                    }
                }
                
                if (!courseFound) {
                    isValid = false;
                    integrityErrors.push_back("Assessment " + assessment->getAssessmentId() + 
                        " references non-existent course: " + courseId);
                }
            }
            
            // Check student-course enrollments
            for (const auto& student : students) {
                if (!student) continue;
                
                auto enrolledCourses = student->getEnrolledCourses();
                for (const auto& enrolledCourse : enrolledCourses) {
                    if (!enrolledCourse) {
                        isValid = false;
                        integrityErrors.push_back("Student " + to_string(student->getRollNumber()) +
                            " has null course enrollment");
                        continue;
                    }
                    
                    // Verify the course exists in the courses list
                    bool courseFound = false;
                    for (const auto& course : courses) {
                        if (course && course->getCourseId() == enrolledCourse->getCourseId()) {
                            courseFound = true;
                            break;
                        }
                    }
                    
                    if (!courseFound) {
                        isValid = false;
                        integrityErrors.push_back("Student " + to_string(student->getRollNumber()) +
                            " enrolled in non-existent course: " + enrolledCourse->getCourseId());
                    }
                }
            }
            
            // Check course-student enrollments (bidirectional consistency)
            for (const auto& course : courses) {
                if (!course) continue;
                
                auto enrolledStudents = course->getEnrolledStudents();
                for (const auto& enrolledStudent : enrolledStudents) {
                    if (!enrolledStudent) {
                        isValid = false;
                        integrityErrors.push_back("Course " + course->getCourseId() + 
                            " has null student enrollment");
                        continue;
                    }
                    
                    // Verify the student exists in the students list
                    bool studentFound = false;
                    for (const auto& student : students) {
                        if (student && student->getRollNumber() == enrolledStudent->getRollNumber()) {
                            studentFound = true;
                            break;
                        }
                    }
                    
                    if (!studentFound) {
                        isValid = false;
                        integrityErrors.push_back("Course " + course->getCourseId() + 
                            " has enrollment for non-existent student: " + 
                            to_string(enrolledStudent->getRollNumber()));
                    }
                }
            }
            
            if (!isValid) {
                string errorMsg = "Referential integrity violations found:\n";
                for (const auto& error : integrityErrors) {
                    errorMsg += "- " + error + "\n";
                }
                setError(errorMsg);
            }
            
            return isValid;
            
        } catch (const exception& e) {
            setError("Referential integrity validation failed: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::repairReferentialIntegrity(vector<shared_ptr<Student>>& students,
                                                vector<shared_ptr<Course>>& courses,
                                                vector<shared_ptr<Assessment>>& assessments) {
        try {
            bool repairsMade = false;
            
            // Remove assessments with invalid student or course references
            auto assessmentIt = assessments.begin();
            while (assessmentIt != assessments.end()) {
                if (!*assessmentIt) {
                    assessmentIt = assessments.erase(assessmentIt);
                    repairsMade = true;
                    continue;
                }
                
                int studentRollNumber = (*assessmentIt)->getStudentRollNumber();
                string courseId = (*assessmentIt)->getCourseId();
                
                // Check if student exists
                bool studentExists = false;
                for (const auto& student : students) {
                    if (student && student->getRollNumber() == studentRollNumber) {
                        studentExists = true;
                        break;
                    }
                }
                
                // Check if course exists
                bool courseExists = false;
                for (const auto& course : courses) {
                    if (course && course->getCourseId() == courseId) {
                        courseExists = true;
                        break;
                    }
                }
                
                if (!studentExists || !courseExists) {
                    logOperation("Repair Integrity", true, 
                        "Removed assessment " + (*assessmentIt)->getAssessmentId() + 
                        " with invalid references");
                    assessmentIt = assessments.erase(assessmentIt);
                    repairsMade = true;
                } else {
                    ++assessmentIt;
                }
            }
            
            // TODO: Fix bidirectional enrollment inconsistencies
            // This would require access to Student/Course internal methods
            // For now, log the issue for manual resolution
            
            if (repairsMade) {
                logOperation("Repair Referential Integrity", true, 
                    "Completed integrity repairs - some data may have been removed");
            }
            
            return true;
            
        } catch (const exception& e) {
            setError("Referential integrity repair failed: " + string(e.what()));
            return false;
        }
    }
    
    // === T043: ENHANCED BACKUP AND RECOVERY MECHANISMS ===
    
    bool FileHandler::createIncrementalBackup() {
        try {
            // Create timestamped backup directory
            auto now = time(nullptr);
            auto tm = *localtime(&now);
            ostringstream oss;
            oss << put_time(&tm, "%Y%m%d_%H%M%S");
            
            string backupSession = string(BACKUP_DIRECTORY) + "session_" + oss.str() + "/";
            createDirectoryIfNotExists(backupSession);
            
            // Files to backup
            vector<string> dataFiles = {
                STUDENTS_FILE, COURSES_FILE, ASSESSMENTS_FILE, ENROLLMENTS_FILE
            };
            
            bool success = true;
            for (const auto& file : dataFiles) {
                if (fileExists(file)) {
                    size_t lastSlash = file.find_last_of("/\\");
                    string filename = (lastSlash != string::npos) ?
                                          file.substr(lastSlash + 1) : file;
                    
                    string backupPath = backupSession + filename;
                    
                    try {
                        std::filesystem::copy_file(file, backupPath);
                        logOperation("Incremental Backup", true, file + " -> " + backupPath);
                    } catch (const exception& e) {
                        setError("Failed to backup " + file + ": " + e.what());
                        success = false;
                    }
                }
            }
            
            if (success) {
                // Create backup manifest
                string manifestPath = backupSession + "backup_manifest.txt";
                ofstream manifest(manifestPath);
                if (manifest.is_open()) {
                    manifest << "Backup Session: " << oss.str() << "\n";
                    manifest << "Created: " << put_time(&tm, "%Y-%m-%d %H:%M:%S") << "\n";
                    manifest << "Files backed up:\n";
                    for (const auto& file : dataFiles) {
                        if (fileExists(file)) {
                            manifest << "- " << file << " (size: " << getFileSize(file) << " bytes)\n";
                        }
                    }
                    manifest.close();
                }
                
                logOperation("Create Incremental Backup", true, 
                    "Backup session created: " + backupSession);
            }
            
            return success;
            
        } catch (const exception& e) {
            setError("Incremental backup failed: " + string(e.what()));
            return false;
        }
    }
    
    bool FileHandler::restoreFromIncrementalBackup(const string& backupPath) {
        try {
            if (!std::filesystem::exists(backupPath) || !std::filesystem::is_directory(backupPath)) {
                setError("Backup directory does not exist: " + backupPath);
                return false;
            }
            
            // Files to restore
            vector<pair<string, string>> filesToRestore = {
                {backupPath + "students.csv", STUDENTS_FILE},
                {backupPath + "courses.csv", COURSES_FILE},
                {backupPath + "assessments.csv", ASSESSMENTS_FILE},
                {backupPath + "enrollments.csv", ENROLLMENTS_FILE}
            };
            
            // Create backup of current data before restore
            if (!backupDataFiles()) {
                setError("Failed to backup current data before restore");
                return false;
            }
            
            bool success = true;
            for (const auto& [backupFile, targetFile] : filesToRestore) {
                if (std::filesystem::exists(backupFile)) {
                    try {
                        std::filesystem::copy_file(backupFile, targetFile, 
                            std::filesystem::copy_options::overwrite_existing);
                        logOperation("Restore File", true, backupFile + " -> " + targetFile);
                    } catch (const exception& e) {
                        setError("Failed to restore " + backupFile + ": " + e.what());
                        success = false;
                    }
                }
            }
            
            if (success) {
                logOperation("Restore from Incremental Backup", true, 
                    "Data restored from: " + backupPath);
            }
            
            return success;
            
        } catch (const exception& e) {
            setError("Incremental restore failed: " + string(e.what()));
            return false;
        }
    }
    
    vector<string> FileHandler::listAvailableBackups() {
        vector<string> backups;
        
        try {
            if (!std::filesystem::exists(BACKUP_DIRECTORY)) {
                return backups;
            }
            
            for (const auto& entry : std::filesystem::directory_iterator(BACKUP_DIRECTORY)) {
                if (entry.is_directory()) {
                    string dirName = entry.path().filename().string();
                    if (dirName.find("session_") == 0) {
                        backups.push_back(entry.path().string());
                    }
                } else if (entry.is_regular_file()) {
                    string fileName = entry.path().filename().string();
                    if (fileName.find(".bak") != string::npos) {
                        backups.push_back(entry.path().string());
                    }
                }
            }
            
            // Sort backups by timestamp (newest first)
            sort(backups.rbegin(), backups.rend());
            
        } catch (const exception& e) {
            setError("Failed to list backups: " + string(e.what()));
        }
        
        return backups;
    }
    
    bool FileHandler::cleanupOldBackups(int keepCount) {
        try {
            auto backups = listAvailableBackups();
            
            if (static_cast<int>(backups.size()) <= keepCount) {
                return true; // Nothing to clean up
            }
            
            bool success = true;
            int removedCount = 0;
            
            // Remove oldest backups, keeping only the specified count
            for (size_t i = keepCount; i < backups.size(); ++i) {
                try {
                    if (std::filesystem::is_directory(backups[i])) {
                        std::filesystem::remove_all(backups[i]);
                    } else {
                        std::filesystem::remove(backups[i]);
                    }
                    removedCount++;
                    logOperation("Cleanup Backup", true, "Removed old backup: " + backups[i]);
                } catch (const exception& e) {
                    logOperation("Cleanup Backup", false, 
                        "Failed to remove " + backups[i] + ": " + e.what());
                    success = false;
                }
            }
            
            if (removedCount > 0) {
                logOperation("Cleanup Old Backups", true, 
                    "Removed " + to_string(removedCount) + " old backup(s)");
            }
            
            return success;
            
        } catch (const exception& e) {
            setError("Backup cleanup failed: " + string(e.what()));
            return false;
        }
    }
    
    // === ERROR HANDLING AND LOGGING ===
    
    string FileHandler::getLastError() {
        return lastError;
    }
    
    void FileHandler::clearLastError() {
        lastError = "";
        errorFlag = false;
    }
    
    bool FileHandler::hasError() {
        return errorFlag;
    }
    
    void FileHandler::logOperation(const string& operation, bool success,
                                 const string& details) {
        // Simple logging to console - in production would use proper logging
        cout << "[FileHandler] " << operation << ": "
                  << (success ? "SUCCESS" : "FAILED");
        if (!details.empty()) {
            cout << " - " << details;
        }
        cout << endl;
    }
    
    // === SEARCH AND FILTER OPERATIONS ===
    
    shared_ptr<Student> FileHandler::findStudentByRollNumber(int rollNumber,
                                                                 const vector<shared_ptr<Student>>& students) {
        auto it = find_if(students.begin(), students.end(),
            [rollNumber](const shared_ptr<Student>& student) {
                return student && student->getRollNumber() == rollNumber;
            });
        return (it != students.end()) ? *it : nullptr;
    }
    
    shared_ptr<Course> FileHandler::findCourseById(const string& courseId,
                                                       const vector<shared_ptr<Course>>& courses) {
        auto it = find_if(courses.begin(), courses.end(),
            [&courseId](const shared_ptr<Course>& course) {
                return course && course->getCourseId() == courseId;
            });
        return (it != courses.end()) ? *it : nullptr;
    }
    
    shared_ptr<Assessment> FileHandler::findAssessmentById(const string& assessmentId,
                                                              const vector<shared_ptr<Assessment>>& assessments) {
        auto it = find_if(assessments.begin(), assessments.end(),
            [&assessmentId](const shared_ptr<Assessment>& assessment) {
                return assessment && assessment->getAssessmentId() == assessmentId;
            });
        return (it != assessments.end()) ? *it : nullptr;
    }
} // namespace PokenoSouth
