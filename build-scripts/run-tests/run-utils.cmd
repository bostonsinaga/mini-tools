@echo off
"../../build/test/main-files/utils/utils_printer.exe"
"../../build/test/main-files/utils/utils_randomwords.exe"
"../../build/test/main-files/utils/utils_scanner.exe"
"../../build/test/main-files/utils/utils_strtools.exe"
"../../build/test/main-files/utils/utils_timedate.exe"
"../../build/test/main-files/utils/utils_vectools.exe"
echo.
powershell -command "& {Write-Host 'UTILS TEST COMPLETED' -ForegroundColor Blue}"
