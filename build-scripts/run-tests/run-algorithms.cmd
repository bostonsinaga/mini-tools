set STATUS_PRINTER_FAILED_ALGORITHMS="--message -failed TEST QUEUE STOPPED @ ALGORITHMS"

call var-status-printer.cmd
call ALGORITHMS/number-sequence.cmd

if (%ERRORLEVEL% EQU 0) (
  call ALGORITHMS/round-robin.cmd

  if (%ERRORLEVEL% EQU 0) (
    call ALGORITHMS/bubble.cmd

    if (%ERRORLEVEL% EQU 0) (
      call ALGORITHMS/comb.cmd

      if (%ERRORLEVEL% EQU 0) (
        call ALGORITHMS/insertion.cmd

        if (%ERRORLEVEL% EQU 0) (
          call ALGORITHMS/merge.cmd

          if (%ERRORLEVEL% EQU 0) (
            call ALGORITHMS/quick.cmd

            if (%ERRORLEVEL% EQU 0) (
              call ALGORITHMS/selection.cmd

              if (%ERRORLEVEL% EQU 0) (
                %STATUS_PRINTER% --message -completed "ALGORITHMS TEST PASSED"

              ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
            ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
          ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
        ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
      ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
    ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
  ) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
) else ( %STATUS_PRINTER% %STATUS_PRINTER_FAILED_ALGORITHMS% )
