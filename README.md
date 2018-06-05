# EpxertSystem
Backward-chaining inference engine.

Usage:
./expert_system filename
filename - path to input file.

Input file format:
First block:
Lines, that contains rules.
Vocabulary:
XOR - ^
OR - |
AND - +
NOT - !
Implies - =>
If and only if - <=>
Second block:
Single line, starting with '=' - Set of initial facts. All other are false.
Third block:
Single line, startig with '?' - Facts, which values you want to obtain.
