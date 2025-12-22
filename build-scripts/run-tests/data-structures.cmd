@echo off
set STATUS_MESSAGE="QUEUE STOPPED @ DATA STRUCTURES"

call var-status-printer.cmd
call data-structures/general-tree.cmd

if %ERRORLEVEL% EQU 0 (
  call data-structures/linked-list.cmd

  if %ERRORLEVEL% EQU 0 (
    %STATUS_PRINTER% --message -completed "TESTS PASSED @ DATA STRUCTURES"

  ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
