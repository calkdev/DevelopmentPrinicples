# Data Model: Student Management System Entities

## Entity Definitions

### Student Entity
**Purpose**: Represents a primary school pupil with unique identification and academic progress tracking

**Attributes**:
- `const int rollNumber` - Immutable unique identifier (TalentHub immutable ID pattern)
- `string firstName` - Student's first name (required, max 50 chars)
- `string lastName` - Student's last name (required, max 50 chars)
- `string dateOfBirth` - Birth date in YYYY-MM-DD format (validation required)
- `string contactEmail` - Parent/guardian email (email format validation)
- `string emergencyContact` - Emergency contact information (required)
- `string enrollmentDate` - School enrollment date (YYYY-MM-DD format)
- `vector<Course*> enrolledCourses` - Non-owning pointers to enrolled courses
- `vector<Assessment> assessments` - Owned assessment records (composition)

**Validation Rules**:
- Roll number must be unique across all students
- Name fields cannot be empty and must contain only alphabetic characters
- Date fields must follow YYYY-MM-DD format and be valid dates
- Email must follow standard email format pattern
- Student must be enrolled in at least one course after initial setup

**Business Rules**:
- Roll number assigned once and never changed (immutability principle)
- Student can enroll in multiple courses simultaneously
- Assessment records are owned by student (composition relationship)
- Enrollment date cannot be in the future

### Course Entity
**Purpose**: Represents academic subjects offered by the school

**Attributes**:
- `string courseId` - Unique course identifier (e.g., "MATH101", "ENG201")
- `string courseName` - Descriptive course name (required, max 100 chars)
- `int credits` - Credit hours for the course (1-6 range)
- `string description` - Course description (optional, max 500 chars)
- `int duration` - Course duration in weeks (1-52 range)
- `vector<Student*> enrolledStudents` - Non-owning pointers to enrolled students

**Validation Rules**:
- Course ID must be unique and follow pattern: 3-4 letters + 3 digits
- Course name cannot be empty
- Credits must be in range 1-6
- Duration must be positive and reasonable (1-52 weeks)
- At least one student must be enrolled for course to be active

**Business Rules**:
- Course maintains bidirectional relationship with students
- Course can have multiple students enrolled
- Course information can be updated except for courseId
- Course deletion requires all students to be unenrolled first

### Assessment Entity  
**Purpose**: Represents evaluation records linking students to courses with weighted scoring

**Attributes**:
- `string assessmentId` - Unique assessment identifier (auto-generated)
- `int studentRollNumber` - Reference to student (foreign key)
- `string courseId` - Reference to course (foreign key)
- `double internalMarks` - Internal assessment score (0-100, 30% weight)
- `double finalMarks` - Final assessment score (0-100, 70% weight)
- `string assessmentDate` - Date of assessment completion (YYYY-MM-DD)
- `double calculatedGrade` - Computed final grade (read-only)

**Validation Rules**:
- Assessment ID must be unique across all assessments
- Student roll number must reference existing student
- Course ID must reference existing course
- Internal and final marks must be in range 0-100
- Assessment date cannot be in the future
- Student must be enrolled in the course for assessment

**Business Rules**:
- Final grade calculated as: (internalMarks * 0.3) + (finalMarks * 0.7)
- Each student can have only one assessment per course
- Assessment records are immutable once created (academic integrity)
- Grade calculation automatically triggers on mark entry

**Grade Calculation Formula**:
```
calculatedGrade = (internalMarks * 0.3) + (finalMarks * 0.7)
```

## Entity Relationships

### Student ↔ Course (Many-to-Many)
- **Student Side**: `vector<Course*> enrolledCourses` (non-owning)
- **Course Side**: `vector<Student*> enrolledStudents` (non-owning)
- **Link Table**: Enrollments.csv for persistence
- **Constraints**: Student must be enrolled before assessment creation

### Student → Assessment (One-to-Many Composition)
- **Student Side**: `vector<Assessment> assessments` (owning)
- **Assessment Side**: `int studentRollNumber` (reference)
- **Relationship**: Composition - Student owns Assessment lifecycle
- **Constraints**: Assessment destroyed when Student is deleted

### Course → Assessment (One-to-Many Reference)
- **Course Side**: No direct collection (accessed through students)
- **Assessment Side**: `string courseId` (reference)
- **Relationship**: Reference - Course referenced by Assessment
- **Constraints**: Course cannot be deleted while assessments exist

## Data State Transitions

### Student Lifecycle
1. **Created** → Student registered with basic information
2. **Enrolled** → Student enrolled in one or more courses
3. **Assessed** → Student has assessment records for courses
4. **Graduated** → Student completed all required assessments
5. **Archived** → Student record preserved but inactive

### Course Lifecycle
1. **Defined** → Course created with basic information
2. **Active** → Course has enrolled students
3. **In Progress** → Assessments being conducted
4. **Completed** → All students assessed
5. **Archived** → Course completed and preserved

### Assessment Lifecycle
1. **Planned** → Assessment scheduled for student-course pair
2. **In Progress** → Internal marks entered
3. **Completed** → Final marks entered, grade calculated
4. **Verified** → Assessment verified and finalized
5. **Archived** → Assessment preserved in academic record

## Data Integrity Constraints

### Referential Integrity
- Assessment.studentRollNumber must reference existing Student.rollNumber
- Assessment.courseId must reference existing Course.courseId
- Student enrollment in Course required before Assessment creation

### Business Constraints
- Roll numbers must be unique across all students
- Course IDs must be unique across all courses
- Assessment IDs must be unique across all assessments
- Students cannot have duplicate assessments for the same course

### Data Validation
- All date fields must be valid dates in YYYY-MM-DD format
- Email fields must match email format pattern
- Numeric scores must be within valid ranges (0-100 for marks, 1-6 for credits)
- Text fields must not exceed maximum length constraints

## CSV File Mapping

### Students.csv
```
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
```

### Courses.csv
```
CourseId,CourseName,Credits,Description,Duration
```

### Assessments.csv
```
AssessmentId,StudentRollNumber,CourseId,InternalMarks,FinalMarks,AssessmentDate,CalculatedGrade
```

### Enrollments.csv
```
EnrollmentId,StudentRollNumber,CourseId,EnrollmentDate,Status
```

## Memory Management Strategy

### Ownership Model
- **System Class**: Owns all Student and Course objects (strong ownership)
- **Student Class**: Owns Assessment objects (composition relationship)
- **Course Class**: Holds non-owning pointers to Student objects
- **Student Class**: Holds non-owning pointers to Course objects

### Lifetime Management
- Student and Course objects persist for application lifetime
- Assessment objects tied to Student lifetime (automatic cleanup)
- Pointers validated before use (null pointer checks)
- RAII principles ensure automatic resource cleanup
