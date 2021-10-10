# Test file for "Lab3_BitManip"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests...\n\n

test "More than 70kg: PIND: 0x0010 1000 PB0:0 -> PORTB: 0x02"
# Set inputs
setPIND 0x28
setPINB 0x00
# Continue for several ticks
continue 2
# Set expect values
expectPORTB 0x02
# Check pass/fail
checkResult

test "Less than 70kg, More than 5kg: PIND: 0x0001 1001 PB0:0 -> PORTB: 0x04"
# Set inputs
setPIND 0x19
setPINB 0x00
# Continue for several ticks
continue 2
# Set expect values
expectPORTB 0x04
# Check pass/fail
checkResult

test "Less than 5kg: PIND: 0x0000 0000 PB0:1 -> PORTB: 0x01"
# Set inputs
setPIND 0x00
setPINB 0x01
# Continue for several ticks
continue 2
# Set expect values
expectPORTB 0x01
# Check pass/fail
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
