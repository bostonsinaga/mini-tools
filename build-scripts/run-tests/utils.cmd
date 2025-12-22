@echo off
set STATUS_MESSAGE="QUEUE STOPPED @ UTILS"

call var-status-printer.cmd
call utils/cli-parser.cmd

if %ERRORLEVEL% EQU 0 (
  call utils/printer.cmd

  if %ERRORLEVEL% EQU 0 (
    call utils/random-words.cmd

    if %ERRORLEVEL% EQU 0 (
      call utils/scanner.cmd

      if %ERRORLEVEL% EQU 0 (
        call utils/str-tools.cmd

        if %ERRORLEVEL% EQU 0 (
          call utils/time-date.cmd

          if %ERRORLEVEL% EQU 0 (
            call utils/vec-tools.cmd

            if %ERRORLEVEL% EQU 0 (
              %STATUS_PRINTER% --message -completed "TESTS PASSED @ UTILS"

            ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
          ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
        ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
      ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
    ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
  ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
