@echo off
"../../build/test/main-files/algorithms/algorithms_numbersequence.exe"
"../../build/test/main-files/algorithms/algorithms_roundrobin.exe"
"../../build/test/main-files/algorithms/sorters/algorithms_sorters_bubble.exe"
"../../build/test/main-files/algorithms/sorters/algorithms_sorters_comb.exe"
"../../build/test/main-files/algorithms/sorters/algorithms_sorters_insertion.exe"
"../../build/test/main-files/algorithms/sorters/algorithms_sorters_merge.exe"
"../../build/test/main-files/algorithms/sorters/algorithms_sorters_quick.exe"
"../../build/test/main-files/algorithms/sorters/algorithms_sorters_selection.exe"
echo.
powershell -command "& {Write-Host 'ALGORITHMS TEST COMPLETED' -ForegroundColor Blue}"
