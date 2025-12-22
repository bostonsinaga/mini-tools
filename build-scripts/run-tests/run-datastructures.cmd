set STATUS_PRINTER_FAILED_DATA_STRUCTURES="--message -failed TEST QUEUE STOPPED @ DATA STRUCTURES"

call var-status-printer.cmd
call utils/general-tree.cmd

if (%ERRORLEVEL% EQU 0) (
  call utils/linked-list.cmd

  if (%ERRORLEVEL% EQU 0) (
    %STATUS_PRINTER% --message -completed "DATA STRUCTURES TEST PASSED"

  ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_DATA_STRUCTURES% )
) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_DATA_STRUCTURES% )
