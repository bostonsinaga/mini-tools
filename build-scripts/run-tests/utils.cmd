set STATUS_PRINTER_FAILED_UTILS="--message -failed TEST QUEUE STOPPED @ UTILS"

call var-status-printer.cmd
call utils/cli-parser.cmd

if (%ERRORLEVEL% EQU 0) (
  call utils/printer.cmd

  if (%ERRORLEVEL% EQU 0) (
    call utils/random-words.cmd

    if (%ERRORLEVEL% EQU 0) (
      call utils/scanner.cmd

      if (%ERRORLEVEL% EQU 0) (
        call utils/strtools.cmd

        if (%ERRORLEVEL% EQU 0) (
          call utils/time-date.cmd

          if (%ERRORLEVEL% EQU 0) (
            call utils/vec-tools.cmd

            if (%ERRORLEVEL% EQU 0) (
              %STATUS_PRINTER% --message -completed "UTILS TEST PASSED"

            ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_UTILS% )
          ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_UTILS% )
        ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_UTILS% )
      ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_UTILS% )
    ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_UTILS% )
  ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_UTILS% )
) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_UTILS% )
