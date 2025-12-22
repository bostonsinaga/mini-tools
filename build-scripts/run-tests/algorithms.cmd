@echo off
set STATUS_MESSAGE="QUEUE STOPPED @ ALGORITHMS"

call var-status-printer.cmd
call algorithms/number-sequence.cmd

if %ERRORLEVEL% EQU 0 (
  call algorithms/round-robin.cmd

  if %ERRORLEVEL% EQU 0 (
    call algorithms/sorters/bubble.cmd

    if %ERRORLEVEL% EQU 0 (
      call algorithms/sorters/comb.cmd

      if %ERRORLEVEL% EQU 0 (
        call algorithms/sorters/insertion.cmd

        if %ERRORLEVEL% EQU 0 (
          call algorithms/sorters/merge.cmd

          if %ERRORLEVEL% EQU 0 (
            call algorithms/sorters/quick.cmd

            if %ERRORLEVEL% EQU 0 (
              call algorithms/sorters/selection.cmd

              if %ERRORLEVEL% EQU 0 (
                %STATUS_PRINTER% --message -completed "TESTS PASSED @ ALGORITHMS"

              ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
            ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
          ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
        ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
      ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
    ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
  ) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
) else ( %STATUS_PRINTER% --message -failed %STATUS_MESSAGE% )
