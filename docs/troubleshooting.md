# Troubleshooting Guide - Pokeno South Student Management System

**Version**: 1.0 Production Prototype  
**Last Updated**: September 14, 2025  
**System**: Student Management System Troubleshooting

---

## Table of Contents

1. [Quick Problem Resolution](#quick-problem-resolution)
2. [System Startup Issues](#system-startup-issues)
3. [Data Loading Problems](#data-loading-problems)
4. [User Interface Issues](#user-interface-issues)
5. [Data Entry Problems](#data-entry-problems)
6. [File and Data Issues](#file-and-data-issues)
7. [Performance Problems](#performance-problems)
8. [Error Message Reference](#error-message-reference)
9. [Recovery Procedures](#recovery-procedures)
10. [Advanced Troubleshooting](#advanced-troubleshooting)

---

## Quick Problem Resolution

### Most Common Issues and Quick Fixes

| **Problem** | **Quick Solution** | **Time to Fix** |
|-------------|-------------------|-----------------|
| System won't start | Check if built: `cmake --build build` | 2 minutes |
| Blank menu display | Resize terminal window | 30 seconds |
| Data not saving | Check file permissions in data/ folder | 1 minute |
| Slow performance | Restart application | 30 seconds |
| Menu navigation stuck | Press Ctrl+C, restart system | 1 minute |

### Emergency Recovery Steps

1. **System Unresponsive**: Press `Ctrl+C` to force exit
2. **Data Corruption**: Restore from backup in `data/backups/`
3. **Build Issues**: Clean build with `rm -rf build && cmake -B build -S . && cmake --build build`
4. **Complete Reset**: Use sample data: `./test_sample_data.sh load`

---

## System Startup Issues

### Problem: System Fails to Start

**Symptoms**:
- No output when running `./build/PokenoSouthPrimary`
- "Command not found" error
- Application immediately exits

**Diagnosis Steps**:
1. **Check if system is built**:
   ```bash
   ls -la build/PokenoSouthPrimary
   ```
   Expected: Executable file with recent timestamp

2. **Verify build status**:
   ```bash
   cmake --build build
   ```
   Expected: "Build succeeded" or no errors

3. **Check file permissions**:
   ```bash
   chmod +x build/PokenoSouthPrimary
   ```

**Solutions**:

| **Cause** | **Solution** | **Commands** |
|-----------|--------------|--------------|
| Not built | Build system | `cmake -B build -S . && cmake --build build` |
| No permissions | Add execute permission | `chmod +x build/PokenoSouthPrimary` |
| Build errors | Clean and rebuild | `rm -rf build && cmake -B build -S . && cmake --build build` |
| Wrong directory | Navigate to project root | `cd 105-Development-Principles2` |

### Problem: Compilation Errors

**Common Compilation Issues**:

1. **C++17 Standard Not Supported**:
   ```
   Error: 'std::string_view' is not a member of 'std'
   ```
   **Solution**: Ensure C++17 compatible compiler
   ```bash
   # Check compiler version
   g++ --version
   clang++ --version
   
   # Use specific C++ standard
   cmake -DCMAKE_CXX_STANDARD=17 -B build -S .
   ```

2. **Missing Dependencies**:
   ```
   Error: CMake could not find required packages
   ```
   **Solution**: Install required development tools
   ```bash
   # macOS
   xcode-select --install
   
   # Linux (Ubuntu/Debian)
   sudo apt-get install build-essential cmake
   ```

3. **Header File Not Found**:
   ```
   Error: 'iostream' file not found
   ```
   **Solution**: Verify compiler installation and try different compiler

---

## Data Loading Problems

### Problem: Data Files Not Found

**Symptoms**:
- "Failed to load students.csv" error
- System starts with 0 students/courses/assessments
- Warning messages about missing data files

**Diagnosis**:
```bash
# Check data directory structure
ls -la data/
```

**Expected Structure**:
```
data/
├── students.csv
├── courses.csv
├── assessments.csv
├── enrollments.csv
└── backups/
```

**Solutions**:

1. **Missing Data Directory**:
   ```bash
   mkdir -p data
   ```

2. **Missing CSV Files** (System will create empty files):
   - Start system normally - it will create default files
   - Or load sample data: `./test_sample_data.sh load`

3. **Corrupted Data Files**:
   ```bash
   # Backup current files
   mv data/students.csv data/students.csv.backup
   
   # Restore from backup
   cp data/backups/latest/students.csv data/
   ```

### Problem: Data Loading Errors

**Symptoms**:
- "Error parsing CSV file" messages
- Partial data loading (some records missing)
- System crashes during data loading

**Common Causes and Solutions**:

1. **CSV Format Issues**:
   - **Problem**: Extra commas, missing quotes, special characters
   - **Solution**: Validate CSV format
   ```bash
   # Check file format
   head -5 data/students.csv
   
   # Look for format issues
   grep -n ',,,' data/students.csv  # Extra commas
   grep -n '"' data/students.csv    # Quote issues
   ```

2. **Encoding Problems**:
   - **Problem**: Non-ASCII characters causing parsing errors
   - **Solution**: Convert to UTF-8 encoding
   ```bash
   # Check file encoding
   file data/students.csv
   
   # Convert if needed (macOS)
   iconv -f ISO-8859-1 -t UTF-8 data/students.csv > data/students_utf8.csv
   ```

3. **File Permissions**:
   - **Problem**: Cannot read data files
   - **Solution**: Fix permissions
   ```bash
   chmod 644 data/*.csv
   chmod 755 data/
   ```

---

## User Interface Issues

### Problem: Menu Display Problems

**Symptoms**:
- Menus appear corrupted or misaligned
- Text overlapping or cut off
- Box drawing characters not displaying correctly

**Solutions**:

1. **Terminal Size Issues**:
   ```bash
   # Check terminal size
   echo $COLUMNS x $LINES
   ```
   **Minimum Requirements**: 80x24 characters
   **Recommended**: 120x30 characters

2. **Character Encoding**:
   - Ensure terminal supports UTF-8
   - Try different terminal applications
   - Check terminal settings for character encoding

3. **Terminal Compatibility**:
   - Use modern terminal applications
   - Avoid very old terminal emulators
   - Test in different terminal environments

### Problem: Input Not Working

**Symptoms**:
- Cannot enter text in prompts
- Enter key not working
- Menu selections not responding

**Diagnosis Steps**:
1. Test basic input: `read -p "Test: " test && echo $test`
2. Check terminal input mode
3. Verify no background processes interfering

**Solutions**:
- Reset terminal: `reset` command
- Try different terminal application
- Check for keyboard layout issues
- Restart terminal session

---

## Data Entry Problems

### Problem: Validation Errors

**Common Validation Issues**:

1. **Student Name Validation**:
   ```
   ✗ Invalid name format detected
   ```
   **Valid Format**: Letters, spaces, hyphens, apostrophes only
   **Examples**: 
   - ✅ "Emma Johnson"
   - ✅ "Mary-Jane O'Connor"
   - ✗ "John123" (numbers not allowed)
   - ✗ "Ann@Student" (symbols not allowed)

2. **Email Validation**:
   ```
   ✗ Invalid email format
   ```
   **Valid Format**: standard email format
   **Examples**:
   - ✅ "parent@email.com"
   - ✅ "contact@school.edu"
   - ✗ "invalid.email" (missing @domain)
   - ✗ "@domain.com" (missing username)

3. **Date Validation**:
   ```
   ✗ Invalid date format
   ```
   **Required Format**: YYYY-MM-DD
   **Examples**:
   - ✅ "2013-05-15"
   - ✅ "2014-12-25"
   - ✗ "15/05/2013" (wrong format)
   - ✗ "2013-13-01" (invalid month)

4. **Course Code Validation**:
   ```
   ✗ Invalid course code format
   ```
   **Valid Format**: SUBJECT + NUMBER (e.g., MATH101)
   **Examples**:
   - ✅ "MATH101", "ENG201", "SCI101"
   - ✗ "math101" (lowercase not allowed)
   - ✗ "MATHEMATICS" (no number)

### Problem: Data Not Saving

**Symptoms**:
- Changes appear in session but don't persist
- "Save failed" error messages
- Data reverts after restart

**Diagnosis**:
```bash
# Check file permissions
ls -la data/
# Should show rw-r--r-- permissions

# Check disk space
df -h .
# Ensure sufficient space available

# Test file writing
echo "test" > data/test.txt && rm data/test.txt
# Should complete without errors
```

**Solutions**:
1. **Permission Issues**: `chmod 644 data/*.csv`
2. **Disk Space**: Free up disk space
3. **File Locks**: Close other applications using the files
4. **Directory Permissions**: `chmod 755 data/`

---

## File and Data Issues

### Problem: Corrupted Data Files

**Symptoms**:
- System crashes when loading data
- Partial data loading
- Error messages about file format

**Recovery Steps**:

1. **Identify Corrupted File**:
   ```bash
   # Test each file individually
   head data/students.csv    # Check first few lines
   tail data/students.csv    # Check last few lines
   wc -l data/students.csv   # Count lines
   ```

2. **Backup Current State**:
   ```bash
   mkdir -p data/recovery_$(date +%Y%m%d_%H%M%S)
   cp data/*.csv data/recovery_$(date +%Y%m%d_%H%M%S)/
   ```

3. **Restore from Backup**:
   ```bash
   # List available backups
   ls -la data/backups/
   
   # Restore from specific backup
   cp data/backups/backup_YYYYMMDD_HHMMSS/*.csv data/
   ```

4. **Manual Data Recovery**:
   ```bash
   # Remove problematic lines
   head -n 50 data/students.csv > data/students_clean.csv
   
   # Validate cleaned file
   ./build/PokenoSouthPrimary  # Test if loads correctly
   ```

### Problem: Missing or Empty Files

**Symptoms**:
- "File not found" errors
- 0 records loaded messages
- System starts with empty database

**Quick Fix**:
```bash
# Load sample data
./test_sample_data.sh load
```

**Manual Fix**:
```bash
# Create empty files with headers
echo "RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate" > data/students.csv
echo "CourseId,CourseName,Credits,Description,Duration,StartDate,EndDate,MaxEnrollment,IsActive" > data/courses.csv
echo "AssessmentId,StudentRollNumber,CourseId,InternalMarks,FinalMarks,CalculatedGrade,AssessmentDate,AssessmentType,IsSubmitted,SubmissionDate,Remarks" > data/assessments.csv
```

---

## Performance Problems

### Problem: Slow System Performance

**Symptoms**:
- Long startup times (>5 seconds)
- Slow menu navigation
- Delayed response to inputs

**Diagnosis**:
```bash
# Check system resources
top -pid $(pgrep PokenoSouthPrimary)

# Check file sizes
du -sh data/*.csv

# Memory usage
ps aux | grep PokenoSouthPrimary
```

**Solutions**:

1. **Large Dataset Issues**:
   - **Problem**: Too many records causing slowdown
   - **Solution**: Archive old data
   ```bash
   # Archive old records
   mkdir -p data/archive/$(date +%Y)
   # Move old assessment records to archive
   ```

2. **Memory Issues**:
   - **Problem**: Insufficient system memory
   - **Solution**: 
     - Close other applications
     - Restart the system
     - Consider system upgrade

3. **File I/O Performance**:
   - **Problem**: Slow disk access
   - **Solution**:
     - Check disk space: `df -h`
     - Run disk cleanup
     - Consider SSD upgrade

### Problem: System Hangs or Freezes

**Symptoms**:
- System becomes unresponsive
- Cannot navigate menus
- No response to input

**Immediate Response**:
1. **Force Exit**: Press `Ctrl+C`
2. **Wait 10 seconds** for graceful shutdown
3. **Kill Process** if necessary: `killall PokenoSouthPrimary`

**Prevention**:
- Regular restarts during heavy use
- Monitor system resources
- Avoid rapid, repeated operations

---

## Error Message Reference

### System Error Messages

**"FileHandler Initialize Data Files: FAILED"**
- **Cause**: Cannot create or access data directory
- **Solution**: Check permissions, create data directory manually

**"Load Students: FAILED"**
- **Cause**: CSV file format error or corruption
- **Solution**: Validate CSV format, restore from backup

**"Memory allocation failed"**
- **Cause**: Insufficient system memory
- **Solution**: Close other applications, restart system

### User Input Error Messages

**"Invalid input format detected"**
- **Cause**: Input doesn't match expected format
- **Solution**: Follow the format guidance displayed

**"Validation failed for field: [fieldname]"**
- **Cause**: Data doesn't meet business rules
- **Solution**: Check field requirements and retry

**"Operation cancelled by user"**
- **Cause**: User cancelled operation
- **Solution**: Normal operation, restart task if needed

### Data Integrity Error Messages

**"Relationship constraint violation"**
- **Cause**: Trying to delete referenced data
- **Solution**: Remove references first, then delete

**"Duplicate key detected"**
- **Cause**: Trying to add record with existing ID
- **Solution**: Use different ID or update existing record

**"Data consistency check failed"**
- **Cause**: Data relationships are inconsistent
- **Solution**: Run data integrity check and repair

---

## Recovery Procedures

### Complete System Recovery

**When to Use**: System completely non-functional

**Steps**:
1. **Backup Current State**:
   ```bash
   mkdir -p recovery/$(date +%Y%m%d_%H%M%S)
   cp -r data/ recovery/$(date +%Y%m%d_%H%M%S)/
   cp -r build/ recovery/$(date +%Y%m%d_%H%M%S)/ 2>/dev/null || true
   ```

2. **Clean Rebuild**:
   ```bash
   rm -rf build
   cmake -B build -S .
   cmake --build build
   ```

3. **Reset Data**:
   ```bash
   ./test_sample_data.sh load
   ```

4. **Test System**:
   ```bash
   echo "0" | ./build/PokenoSouthPrimary
   ```

### Data Recovery from Backup

**Automatic Backup Restoration**:
```bash
# List available backups
ls -la data/backups/

# Restore latest backup
latest_backup=$(ls -t data/backups/ | head -1)
cp data/backups/$latest_backup/*.csv data/
```

**Manual Data Recovery**:
```bash
# Extract valid records from corrupted file
grep -v "^$" data/students.csv | head -50 > data/students_recovered.csv
mv data/students_recovered.csv data/students.csv
```

### Emergency Contact Procedure

1. **Document the Problem**:
   - Screenshot error messages
   - Note exact steps that caused the issue
   - Record system environment details

2. **Gather System Information**:
   ```bash
   # System details
   uname -a
   cmake --version
   ls -la build/
   ls -la data/
   ```

3. **Temporary Workaround**:
   - Use sample data for immediate needs
   - Manual data entry if required
   - Alternative tools if available

---

## Advanced Troubleshooting

### Debug Mode Operation

**Enable Verbose Logging**:
```bash
# Run with detailed output
./build/PokenoSouthPrimary 2>&1 | tee debug.log
```

**Memory Debugging** (if available):
```bash
# Check for memory leaks
valgrind --leak-check=full ./build/PokenoSouthPrimary
```

### System Monitoring

**Performance Monitoring**:
```bash
# Monitor resource usage
top -pid $(pgrep PokenoSouthPrimary)

# File system monitoring
lsof +p $(pgrep PokenoSouthPrimary)
```

**Network Debugging** (if applicable):
```bash
# Check file locks
lsof data/
```

### Custom Solutions

**Creating Test Environment**:
```bash
# Create isolated test environment
mkdir test_environment
cd test_environment
cp -r ../105-Development-Principles2/* .
./test_sample_data.sh load
```

**Data Migration**:
```bash
# Export current data
cp data/*.csv backup_for_migration/

# Transform data format if needed
# (custom scripts based on specific requirements)
```

---

## Prevention and Maintenance

### Regular Maintenance Tasks

**Daily** (if used heavily):
- Monitor system performance
- Check for error messages
- Verify data saving properly

**Weekly**:
- Create manual backup
- Review data integrity
- Monitor file sizes

**Monthly**:
- Clean old backup files
- Review system performance
- Update documentation if needed

### Best Practices to Avoid Issues

1. **Data Management**:
   - Regular backups before major operations
   - Validate data before import
   - Monitor file sizes and growth

2. **System Usage**:
   - Avoid rapid, repeated operations
   - Use proper exit procedures
   - Monitor system resources during use

3. **Environment**:
   - Maintain adequate system resources
   - Use supported terminal applications
   - Keep system updated

---

*Troubleshooting Guide Version 1.0 - Production Prototype*  
*For additional support, refer to the User Manual and System Documentation*  
*Last Updated: September 14, 2025*
