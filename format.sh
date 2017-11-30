# format.sh
# formats all of the source and header files in the project using clang-format
# will print an error if the clang-format executable is not found

if [ -x "$(command -v clang-format)" ]; then 
    clang-format -i -style=LLVM **/*.[ch]
else
    echo >&2 "clang-format binary not found, could not format files" 
fi
