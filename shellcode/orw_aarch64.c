__asm__(
    ".global run_sh\n"
    "run_sh:\n"

    // 스택에 0x67 추가 (AArch64에서는 push 대신 str 명령 사용)
    // "sub sp, sp, #16\n"             // 스택 공간 확보
    "mov w0, #0x67\n"               // w0에 0x67을 로드
    "str w0, [sp]\n"                // 스택에 w0 저장

    // '/tmp/flag' 문자열 설정
    "mov x0, 0x616c662f706d742f\n" // 
    "mov x1, sp\n"                  // x1 = 스택 포인터
    "mov x2, #0\n"                  // x2 = O_RDONLY (0)

    // open syscall (AArch64 syscall 번호: 56)
    "mov x8, #56\n"                 // x8 = syscall 번호 (open)
    "svc #0\n"                      // syscall 호출

    // 파일 디스크립터를 x0에 저장
    "mov x1, sp\n"                  // 버퍼 설정
    "sub x1, sp, #0x30\n"           // 스택 포인터에서 0x30만큼 뺌
    "mov x2, #0x30\n"               // 읽을 길이 설정

    // read syscall (AArch64 syscall 번호: 63)
    "mov x8, #63\n"                 // x8 = syscall 번호 (read)
    "svc #0\n"                      // syscall 호출

    // write syscall (AArch64 syscall 번호: 64)
    "mov x0, #1\n"                  // 파일 디스크립터 1 (stdout)
    "mov x8, #64\n"                 // x8 = syscall 번호 (write)
    "svc #0\n"                      // syscall 호출

    // exit syscall (AArch64 syscall 번호: 93)
    "mov x0, #0\n"                  // 종료 상태 설정
    "mov x8, #93\n"                 // x8 = syscall 번호 (exit)
    "svc #0\n"                      // syscall 호출
);

void run_sh();

int main() { run_sh(); }
