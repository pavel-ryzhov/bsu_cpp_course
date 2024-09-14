./02_assembler/gdb/a.out < 02_assembler/gdb/input.txt
if (( $? != 0 )); then
    echo "Sorry you didn't get OK :("
    exit 0
fi
exit 1
