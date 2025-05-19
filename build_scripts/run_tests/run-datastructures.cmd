@echo off
"../../build/test/main-files/data-structures/linked-lists/datastructures_linkedlists_circular.exe"
"../../build/test/main-files/data-structures/linked-lists/datastructures_linkedlists_circulardoubly.exe"
"../../build/test/main-files/data-structures/linked-lists/datastructures_linkedlists_doubly.exe"
"../../build/test/main-files/data-structures/linked-lists/datastructures_linkedlists_singly.exe"
"../../build/test/main-files/data-structures/trees/datastructures_trees_binarytree.exe"
"../../build/test/main-files/data-structures/trees/datastructures_trees_binary.exe"
"../../build/test/main-files/data-structures/trees/datastructures_trees_general.exe"
echo.
powershell -command "& {Write-Host 'DATA_STRUCTURES TESTS COMPLETED' -ForegroundColor Green}"
