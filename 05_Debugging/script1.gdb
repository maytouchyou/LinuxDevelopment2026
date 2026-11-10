file range

set pagination off
set confirm off
start 1 12 > /dev/null

watch I.current if I.current % 5 == 0
commands
    silent
    printf "@@@%d, %d, %d, %d\n", main::I.current, main::I.start, main::I.stop, main::I.step
    continue
end

continue

quit
