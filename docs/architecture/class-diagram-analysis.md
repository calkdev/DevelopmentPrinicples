# Architecture Documentation: Pokeno South Primary School Student Management System

**Generated**: September 18, 2025  
**Version**: 1.0.0  
**Codebase Analysis**: Complete class structure with PlantUML documentation

## Executive Summary

This document provides a comprehensive architectural analysis of the Pokeno South Primary School Student Management System, a C++ application that demonstrates enterprise-grade object-oriented design patterns following TalentHub Wellington methodologies. The system implements a layered architecture with clear separation of concerns, utilizing modern C++17/20 features and proven design patterns.

## System Overview

The Student Management System is organized into five distinct architectural layers:

1. **Entity Layer**: Core business objects (Student, Course, Assessment, Grade)
2. **Strategy Layer**: Pluggable grade calculation algorithms (GradeCalculator implementations)
3. **Controller Layer**: System orchestration and business logic (System class)
4. **Repository Layer**: Data persistence and file operations (FileHandler)
5. **Utility Layer**: Shared validation and helper functions (Common namespace)

## Class Architecture Analysis

### Entity Layer Classes

#### Student Class
**Responsibility**: Represents a student entity with immutable identification and comprehensive relationship management.

**Key Design Patterns**:
- **Immutable ID Pattern**: `const int rollNumber` ensures identity consistency
- **Composition Pattern**: Owns `vector<shared_ptr<Assessment>>` lifecycle
- **Bidirectional Association**: Maintains references to enrolled courses

**TalentHub Patterns Implemented**:
- Immutable primary key (rollNumber)
- Comprehensive validation on all setters
- RAII with smart pointer management
- Const correctness throughout public interface

**Critical Relationships**:
- **Many-to-Many with Course**: `vector<shared_ptr<Course>> enrolledCourses`
- **One-to-Many Composition with Assessment**: Owns assessment lifecycle
- **Dependency on Common**: Uses validation utilities

#### Course Class
**Responsibility**: Manages course information and student enrollment with capacity constraints.

**Key Design Patterns**:
- **Bidirectional Association**: Maintains two-way relationship with Student
- **Business Rules Enforcement**: Enrollment capacity, prerequisites validation
- **Immutable ID Pattern**: `const string courseId` for consistency

**Business Logic**:
- Enrollment capacity management with configurable limits
- Grade aggregation and pass/fail analytics
- Date-based enrollment period validation

**Critical Features**:
- Automatic bidirectional relationship maintenance
- Thread-safe enrollment operations with shared_ptr
- CSV serialization for persistence

#### Assessment Class
**Responsibility**: Implements weighted grade calculation with inheritance from Grade abstract base.

**Key Design Patterns**:
- **Strategy Pattern**: Inherits from Grade for polymorphic calculation
- **Lazy Evaluation**: Cached `calculatedGrade` with `gradeNeedsRecalculation` flag
- **Immutable References**: Student and Course IDs cannot change after creation

**Grade Calculation Algorithm**:
```cpp
calculatedGrade = (internalMarks * 0.3) + (finalMarks * 0.7)
```

**Validation Rules**:
- Marks range: 0.0 - 100.0
- Date validation: Assessment date cannot be future
- Referential integrity: Student must exist and be enrolled in course

#### Grade Abstract Base Class
**Responsibility**: Provides polymorphic interface for grade calculation strategies.

**Design Purpose**:
- Enables multiple grade calculation implementations
- Supports future extensibility (different grade types)
- Clean abstraction for calculation logic

### Strategy Pattern Implementation

#### GradeCalculator Hierarchy
**Responsibility**: Implements multiple grade calculation strategies using the Strategy pattern.

**Concrete Implementations**:
1. **WeightedAverageCalculator**: Standard weighted average across all assessments
2. **BestNOutOfMCalculator**: Takes best N scores from M total assessments

**Benefits**:
- Runtime algorithm selection
- Easy addition of new calculation methods
- Separation of calculation logic from entity classes

### Controller Layer

#### System Class
**Responsibility**: Main system orchestrator implementing facade pattern for all operations.

**Key Design Patterns**:
- **Facade Pattern**: Simplifies complex subsystem interactions
- **Composition Pattern**: Manages entity collections as member variables
- **Command Pattern**: Menu-driven operations with consistent interface

**Entity Management**:
- Centralized CRUD operations for all entities
- Relationship management between Students and Courses
- Data persistence coordination with FileHandler

**User Interface**:
- Menu-driven console interface
- Input validation and error handling
- Context-sensitive help and navigation

### Repository Layer

#### FileHandler Class
**Responsibility**: Implements repository pattern for CSV-based data persistence.

**Key Design Patterns**:
- **Repository Pattern**: Abstracts data access from business logic
- **Static Utility Pattern**: No instance state, purely functional
- **Factory Pattern**: Creates entity objects from CSV data

**Data Management Features**:
- CSV parsing and writing with proper escaping
- Referential integrity validation
- Backup and recovery operations
- Incremental data updates

**Error Handling**:
- Comprehensive validation before file operations
- Automatic backup creation before destructive operations
- Graceful degradation with detailed error reporting

### Utility Layer

#### Common Namespace
**Responsibility**: Provides shared validation and utility functions across the system.

**Validation Functions**:
- Email format validation with regex
- Date format and range validation
- Input sanitization for security
- String manipulation utilities

**Security Features**:
- Input sanitization against injection attacks
- Safe CSV field escaping
- Alphanumeric validation with whitelisting

## Relationship Analysis

### Primary Relationships

#### Student ↔ Course (Many-to-Many Bidirectional)
- **Implementation**: Both classes maintain vectors of shared_ptr to each other
- **Consistency**: Enrollment operations update both sides automatically
- **Persistence**: Separate enrollments.csv file maintains relationship data
- **Business Rules**: Maximum enrollment limits, prerequisite validation

#### Student → Assessment (One-to-Many Composition)
- **Ownership**: Student owns Assessment lifecycle completely
- **Implementation**: `vector<shared_ptr<Assessment>> assessments` in Student class
- **Referential Integrity**: Assessment destruction automatic when Student deleted
- **Validation**: Assessment creation requires valid Student-Course enrollment

#### Course → Assessment (One-to-Many Reference)
- **Implementation**: Assessment holds `const string courseId` reference
- **Aggregation**: Course can calculate statistics from related Assessments
- **Validation**: Course existence validated before Assessment creation

### Design Pattern Relationships

#### Composition Patterns
- **System → Entities**: System class composes Student, Course, Assessment collections
- **Student → Assessment**: Student owns Assessment lifecycle
- **FileHandler → CSV Operations**: Encapsulates all file operation complexity

#### Association Patterns
- **Student ↔ Course**: Bidirectional many-to-many with shared_ptr management
- **Assessment → Student/Course**: References through immutable IDs

## Design Patterns Catalog

### Creational Patterns
1. **Factory Pattern** (FileHandler): Creates entities from CSV data
2. **Builder Pattern** (Entity constructors): Multi-parameter construction with validation

### Structural Patterns
1. **Facade Pattern** (System class): Simplifies complex subsystem interactions
2. **Composition Pattern**: Entity ownership and lifecycle management
3. **Repository Pattern** (FileHandler): Data access abstraction

### Behavioral Patterns
1. **Strategy Pattern** (GradeCalculator): Pluggable calculation algorithms
2. **Template Method** (Grade inheritance): Common calculation interface
3. **Command Pattern** (Menu operations): Encapsulated user actions

### TalentHub Enterprise Patterns
1. **Immutable ID Pattern**: const primary keys in all entities
2. **Bidirectional Association Management**: Automatic consistency maintenance
3. **Comprehensive Validation**: Input validation at all entry points
4. **RAII Resource Management**: Smart pointer usage throughout

## Architectural Decisions

### Technology Choices
- **C++17/20**: Modern features (auto, range-based loops, constexpr)
- **Smart Pointers**: Automatic memory management with shared_ptr
- **CSV Persistence**: Simple, portable data format
- **Static Linking**: Self-contained executable deployment

### Design Principles Applied
1. **Single Responsibility**: Each class has one clear purpose
2. **Open/Closed**: Strategy pattern enables extension without modification
3. **Dependency Inversion**: Abstractions (Grade) not dependent on details
4. **Interface Segregation**: Small, focused interfaces
5. **SOLID Principles**: Consistently applied throughout codebase

### Error Handling Strategy
- **Exception Safety**: RAII ensures resource cleanup
- **Input Validation**: Comprehensive validation at all boundaries
- **Graceful Degradation**: System continues operation after non-critical errors
- **User-Friendly Messages**: Technical errors translated to user language

## Quality Attributes

### Maintainability
- Clear separation of concerns across layers
- Consistent naming conventions and code style
- Comprehensive documentation and comments
- Modular design enabling independent changes

### Extensibility
- Strategy pattern allows new calculation methods
- Abstract Grade class supports new assessment types
- Repository pattern abstracts storage implementation
- Menu system easily accommodates new operations

### Performance
- Lazy evaluation in grade calculations
- Smart pointer efficiency for object sharing
- Minimal object copying with move semantics
- Efficient CSV parsing with streaming

### Reliability
- Comprehensive input validation
- Automatic backup before destructive operations
- Referential integrity enforcement
- Exception-safe operations throughout

## Integration Points

### File System Integration
- CSV files for data persistence
- Backup directory for data safety
- Log files for operation tracking
- Configuration through file paths

### Future Extension Points
- Database persistence (replace FileHandler)
- Web interface (extend System class)
- Additional grade calculation strategies
- Import/export to other formats

## Conclusion

The Pokeno South Primary School Student Management System demonstrates a well-architected C++ application that successfully implements multiple enterprise design patterns while maintaining simplicity and usability. The clear separation of concerns, comprehensive validation, and extensible design make it an excellent example of modern C++ application development following TalentHub Wellington enterprise standards.

The architecture supports current requirements while providing a solid foundation for future enhancements through its strategic use of design patterns and adherence to SOLID principles.

---
**PlantUML Diagram**: [class-diagram.puml](./class-diagram.puml)  
**Generated by**: Architecture Documentation System  
**Last Updated**: September 18, 2025
