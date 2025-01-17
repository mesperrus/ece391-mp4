#define ASM     1
    # file sys offset
    # passing in garbage
    # filesys checks

# linkage to IDT
.globl sys_call
.extern sys_call

# search for these guys
.extern halt, execute, read, write, open, close, getargs, vidmap, set_handler, sigreturn

# jumptable for system calls
    # needs the null for the 0th element
syscall_jumptable:
    .long 0x0, halt, execute, read, write, open, close, getargs, vidmap, set_handler, sigreturn

sys_call:
    sti
    pushl %ebx
    pushl %ecx
    pushl %edx
    pushl %esi
    pushl %edi
    pushl %ebp
    pushl %esp
    pushfl
# pushing args onto stack
    pushl %edx            # Arg 3
    pushl %ecx            # Arg 2
    pushl %ebx            # Arg 1
# check for valid syscall number
    cmpl $1, %eax
    jb  invalid_syscall
    cmpl $10, %eax
    ja  invalid_syscall
#syscall_jumptable call
    call    *syscall_jumptable(, %eax, 4)
    # cmpl    $0xFFFFF001, %eax             # -1 to -4095 errors
    jmp      done                          # No errors
    xorl    %ecx, %ecx
    subl    %eax, %ecx                    # negate the error number
    pushl   %ecx
    call    __errno_location              # get ptr to errno
    popl    %ecx                          # put error into ecx
    movl    %ecx, (%eax)                  # move number into errno

# place holder
invalid_syscall:
    movl $-1, %eax        # return -1
done:
    popl %ebx                   # restore stack
    popl %ecx
    popl %edx
    popfl
    popl %esp
    popl %ebp
    popl %edi
    popl %esi
    popl %edx
    popl %ecx
    popl %ebx

    iret

__errno_location:
    call    getIP                   # eax <- raddr
raddr:
    addl    $errno - raddr, %eax    # adjust return value
    ret


getIP:
    movl    (%esp), %eax            # read return address
    ret
errno:
    .long 0x0
