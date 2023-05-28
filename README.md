# PEHeaderParser
Inspired by the blog writeup by 0xRick (https://github.com/0xRick)

Just some class organization and stuff done.
PE32 and PE32+ (PE64) support added

To Do:
-> Overall managing class for both PE32 and PE64:
-> Which:
  -> Checks to make sure the file is actually a PE
  -> Works out which type (32 vs 64) it is
  -> Intefaces calls through there
  -> Proper logging support

-> ImGui Menu for easier use and exploring the PE

-> PE from a current running active process
  -> Injects and communicates with a .dll running in the target process
  -> Gathers runtime PE infomation
