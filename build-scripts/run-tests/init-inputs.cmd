@echo off
"../../build/test/main-files/utils/utils_randomwords.exe" --init-inputs -amount 1000 -max-number 100 -word-length-start 5 -word-length-end 11
echo.
powershell -command "& {Write-Host 'INPUTS INITIALIZED' -ForegroundColor Blue}"
