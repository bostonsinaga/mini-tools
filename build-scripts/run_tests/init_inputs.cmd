@echo off
"../build/test/main-files/utils/utils_randomwords.exe --init-inputs"
powershell -command "& {Write-Host 'INPUTS INITIALIZED' -ForegroundColor Green}"
