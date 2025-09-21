# T049 - Sample Data Files for Testing

**Sample Data Documentation Version**: 1.0  
**Created**: September 14, 2025  
**Dependencies**: T041 (data persistence implementation)

## Overview

This document describes the comprehensive sample data files created for testing the Student Management System. These files enable realistic testing scenarios that reflect a typical primary school environment.

---

## Sample Data Files

### 1. sample_students.csv
**Purpose**: Comprehensive student dataset for testing CRUD operations and performance
**Records**: 50 students
**Data Range**: Students aged 10-11 (born 2013-2014)

**Key Features**:
- Realistic names representing diverse backgrounds
- Consistent email format for parent contacts
- Emergency contact information
- Standard enrollment date (2024-09-01)
- Sequential roll numbers for easy identification

**Usage Scenarios**:
- Testing student addition, modification, deletion
- Performance testing with medium-sized datasets
- Batch operation testing
- Data validation testing

### 2. sample_courses.csv
**Purpose**: Comprehensive course catalog for primary school curriculum
**Records**: 20 courses
**Coverage**: Core subjects, languages, arts, and extracurricular activities

**Course Categories**:
- **Core Subjects**: Mathematics, English, Science, Social Studies
- **Arts & Creativity**: Art, Music, Drama
- **Physical Development**: Physical Education, Health & Wellness
- **Technology**: Computer Skills, Digital Literacy
- **Languages**: Spanish, French
- **Special Programs**: Advanced courses, clubs, tutoring

**Key Features**:
- Realistic credit hours (1-4 credits)
- Appropriate class sizes (10-30 students)
- Detailed course descriptions
- Standard academic year scheduling
- Mix of required and elective courses

### 3. sample_assessments.csv
**Purpose**: Diverse assessment data covering multiple evaluation types
**Records**: 50 assessments
**Coverage**: Various assessment types across different courses

**Assessment Types**:
- **Quizzes**: Quick knowledge checks
- **Essays**: Writing and critical thinking
- **Lab Reports**: Scientific methodology
- **Midterms**: Comprehensive evaluations
- **Presentations**: Communication skills
- **Projects**: Creative and practical applications
- **Skills Tests**: Physical and technical abilities
- **Oral Exams**: Language proficiency

**Key Features**:
- Realistic grade distributions (70-97%)
- Detailed teacher comments and feedback
- Various point scales (20, 25, 30, 40, 50, 100 points)
- Complete submission tracking
- Performance across different subjects

---

## Data Quality Standards

### Student Data Standards
- **Names**: Realistic, culturally diverse
- **Emails**: Consistent parent contact format
- **Dates**: Age-appropriate birth dates
- **Contact Info**: Professional emergency contact format
- **IDs**: Sequential, easy to track

### Course Data Standards
- **Course Codes**: Logical department and level coding
- **Credits**: Appropriate for primary school level
- **Descriptions**: Detailed, curriculum-aligned
- **Enrollment**: Realistic class size limits
- **Duration**: Standard academic calendar

### Assessment Data Standards
- **IDs**: Structured course_type_sequence format
- **Grades**: Realistic distribution with proper scaling
- **Comments**: Constructive, professional feedback
- **Dates**: Chronological, academically realistic
- **Types**: Diverse evaluation methods

---

## Testing Scenarios Enabled

### Performance Testing
1. **Startup Performance**: Test with 50 students, 20 courses, 50 assessments
2. **CRUD Performance**: Add, edit, delete operations on realistic datasets
3. **Search Performance**: Find students, courses, assessments efficiently
4. **Report Generation**: Generate meaningful reports and analytics

### Functional Testing
1. **Data Integrity**: Verify relationships between students, courses, assessments
2. **Validation Testing**: Test input validation with realistic edge cases
3. **Error Handling**: Test system behavior with various data scenarios
4. **User Experience**: Test navigation and display with meaningful data

### Stress Testing
1. **Large Datasets**: Scale up for testing with hundreds of records
2. **Rapid Operations**: Quick succession of CRUD operations
3. **File I/O**: Test reading/writing large CSV files efficiently
4. **Memory Usage**: Monitor resource consumption with realistic data

---

## Data Generation Methodology

### Student Generation
- Used popular names from education statistics
- Generated realistic birth dates for age-appropriate students
- Created consistent email patterns for parent contacts
- Ensured diversity in name origins and backgrounds

### Course Generation
- Based on standard primary school curriculum
- Included core subjects and enrichment activities
- Realistic credit hours and enrollment limits
- Comprehensive course descriptions

### Assessment Generation
- Distributed across different courses and students
- Various assessment types and difficulty levels
- Realistic grade distributions (bell curve)
- Professional teacher feedback and comments

---

## Usage Instructions

### Loading Sample Data
```bash
# Replace current data with sample data for testing
cp data/sample_students.csv data/students.csv
cp data/sample_courses.csv data/courses.csv
cp data/sample_assessments.csv data/assessments.csv

# Run system with sample data
./build/PokenoSouthPrimary
```

### Backup Current Data
```bash
# Create backup before loading sample data
mkdir -p data/backup_$(date +%Y%m%d)
cp data/*.csv data/backup_$(date +%Y%m%d)/
```

### Reset to Sample Data
```bash
# Script to quickly reset to sample data
#!/bin/bash
echo "Resetting to sample data..."
cp data/sample_students.csv data/students.csv
cp data/sample_courses.csv data/courses.csv  
cp data/sample_assessments.csv data/assessments.csv
echo "Sample data loaded successfully!"
```

---

## Data Scaling for Performance Testing

### Small Dataset (Baseline)
- Students: 10
- Courses: 5  
- Assessments: 25

### Medium Dataset (Provided)
- Students: 50
- Courses: 20
- Assessments: 50

### Large Dataset (Generated)
- Students: 200
- Courses: 30
- Assessments: 500

### Extra Large Dataset (Stress Testing)
- Students: 500
- Courses: 50
- Assessments: 1000+

---

## Data Validation Rules

### Student Validation
- Roll numbers must be unique and positive
- Names must be non-empty and printable ASCII
- Email addresses must follow valid format
- Birth dates must be age-appropriate for primary school
- Enrollment dates must be valid calendar dates

### Course Validation
- Course IDs must be unique and follow naming convention
- Course names must be descriptive and non-empty
- Credits must be between 1-10 for primary school level
- Enrollment limits must be reasonable (5-50 students)
- Dates must form valid academic periods

### Assessment Validation
- Assessment IDs must be unique per course
- Student roll numbers must exist in student database
- Course IDs must exist in course database
- Grades must be within valid ranges (0-100%)
- Dates must be realistic for academic calendar

---

## Sample Data Statistics

### Student Demographics
- **Age Range**: 10-11 years old
- **Gender Distribution**: Balanced representation
- **Name Diversity**: Multiple cultural backgrounds
- **Enrollment**: Full academic year students

### Course Distribution
- **Core Subjects**: 40% (8/20 courses)
- **Arts & Enrichment**: 35% (7/20 courses)
- **Languages**: 10% (2/20 courses)
- **Special Programs**: 15% (3/20 courses)

### Assessment Distribution
- **Quizzes**: 25% (quick assessments)
- **Projects**: 25% (creative work)
- **Exams**: 20% (comprehensive testing)
- **Presentations**: 15% (communication skills)
- **Other**: 15% (skills tests, oral exams)

### Grade Distribution
- **A Range (90-100%)**: 30% of assessments
- **B Range (80-89%)**: 40% of assessments
- **C Range (70-79%)**: 25% of assessments
- **Below 70%**: 5% of assessments

---

## Maintenance and Updates

### Regular Updates
- Refresh student names for current trends
- Update course descriptions for curriculum changes
- Adjust assessment types for modern evaluation methods
- Maintain realistic grade distributions

### Seasonal Adjustments
- Update enrollment dates for new academic years
- Adjust course schedules for calendar changes
- Refresh assessment dates for current terms
- Update emergency contact information

### Quality Assurance
- Regular validation of data integrity
- Consistency checks across all files
- Performance impact assessment
- User feedback integration

---

## Integration with Testing Framework

### Automated Testing Support
```bash
# Test data validation
./validate_sample_data.sh

# Performance benchmarking with sample data
./benchmark_with_samples.sh

# Load testing with scaled datasets
./load_test_scaled.sh small|medium|large|xlarge
```

### Manual Testing Support
- Pre-populated data for immediate testing
- Realistic scenarios for user experience testing
- Edge cases built into dataset
- Clear documentation for test case creation

---

*Sample data files prepared for T049 implementation*  
*Comprehensive testing datasets ready for production validation*  
*Supporting realistic primary school environment simulation*
