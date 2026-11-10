file range

set pagination off
set confirm off
start -100 100 3 > /dev/null

set $a=1

break range_get
commands
    silent
    if $a >= 28 && $a <= 35
        printf "@@@%d, %d, %d, %d\n", main::I.current, main::I.start, main::I.stop, main::I.step
    end
    set $a=$a+1
    continue
end

continue

quit
