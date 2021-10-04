# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [ {'description': 'Exceed 140kg Balance: A=50, B=50, C=50, Total=150',  # 0000 0000 -> 0000 0100
    'steps': [ {'inputs': [('PINA',50),('PINB',50),('PINC',50)], 'iterations': 5 } ],
    'expected': [('PORTD',0b00100101)]},
    {'description': 'Under 140kg Unbalance: A=100, B=30, C=10, Total=140',  # 0000 0000 -> 0000 0100
    'steps': [ {'inputs': [('PINA',100),('PINB',30),('PINC',10)], 'iterations': 5 } ],
    'expected': [('PORTD',0b00100010)],
    {'description': 'Exceed 140kg Unbalance: A=100, B=50, C=10, Total=160',  # 0000 0000 -> 0000 0100
    'steps': [ {'inputs': [('PINA',100),('PINB',50),('PINC',10)], 'iterations': 5 } ],
    'expected': [('PORTD',0b00101011)],
    {'description': 'Under 140kg Balance: A=40, B=40, C=40, Total=120',  # 0000 0000 -> 0000 0100
    'steps': [ {'inputs': [('PINA',40),('PINB',40),('PINC',40)], 'iterations': 5 } ],
    'expected': [('PORTD',0b00111100)],
    {'description': 'Under 140kg Balance: A=40, B=40, C=40, Total=120',  # 0000 0000 -> 0000 0100
    'steps': [ {'inputs': [('PINA',40),('PINB',40),('PINC',40)], 'iterations': 5 } ],
    'expected': [('PORTD',0b00111100)],
    ]

# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
# watch = ['<function>::<static-var>','PORTB']

