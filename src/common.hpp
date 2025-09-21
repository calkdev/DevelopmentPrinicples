#ifndef COMMON_HPP
#define COMMON_HPP

#include "Usings.hpp"

USING_STD_COMMON

namespace Common {
    
    /**
     * Validates email format using regex pattern
     */
    bool isValidEmail(const string& email);

    /**
     * Validates phone number format (basic international patterns)
     */
    bool isValidPhoneNumber(const string& phoneNumber);

    /**
     * Validates date is not in the future
     */
    bool isDateNotFuture(const string& date);
    
    /**
     * Additional validation functions for Student class compatibility
     */
    bool isValidRollNumber(int rollNumber);
    bool isValidName(const string& name);
    bool isValidDateFormat(const string& date);
    bool isValidDate(const string& date);
    
    // === T036: INPUT SANITIZATION AND VALIDATION HELPERS ===
    
    /**
     * Sanitizes input string by removing/escaping dangerous characters
     */
    string sanitizeInput(const string& input);
    
    /**
     * Removes leading and trailing whitespace from string
     */
    string trimString(const string& str);
    
    /**
     * Validates string contains only alphanumeric characters and specified special chars
     */
    bool isValidAlphanumeric(const string& input, const string& allowedSpecialChars = " '-");
    
    /**
     * Validates and sanitizes numeric input from string
     */
    bool parseAndValidateInt(const string& input, int& value, int minValue, int maxValue);
    
    /**
     * Validates and sanitizes double input from string
     */
    bool parseAndValidateDouble(const string& input, double& value, double minValue, double maxValue);
    
    /**
     * Checks if string contains potentially dangerous characters or patterns
     */
    bool isSafeInput(const string& input);
    
    /**
     * Validates string length is within acceptable bounds
     */
    bool isValidLength(const string& input, size_t minLength, size_t maxLength);
    
    /**
     * Escapes special characters in string for safe CSV output
     */
    string escapeCSVField(const string& input);
    
    /**
     * Normalizes text by converting to lowercase and removing extra whitespace
     */
    string normalizeText(const string& input);
    
    /**
     * Validates text contains only printable ASCII characters
     */
    bool isPrintableASCII(const string& input);
    
    /**
     * Checks if input matches common SQL injection patterns
     */
    bool isSafeSQLInput(const string& input);
    
    /**
     * Validates input against a whitelist of allowed characters
     */
    bool matchesWhitelist(const string& input, const string& whitelist);
    
    // === UTILITY FUNCTIONS ===
    
    /**
     * General error handling utility
     */
    void handleError(const string& operation, const string& details, bool critical = false);
    
    /**
     * Success message utility
     */
    void displaySuccess(const string& operation, const string& details = "");
    
    /**
     * Warning message utility
     */
    void displayWarning(const string& message, const string& details = "");
    
    /**
     * Get current date in YYYY-MM-DD format
     */
    string getCurrentDate();
    
    /**
     * Get current timestamp in YYYY-MM-DD HH:MM:SS format
     */
    string getCurrentTimestamp();

} // namespace Common

#endif // COMMON_HPP
