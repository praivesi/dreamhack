__asm__(
    ".global run_sh\n"
    "run_sh:\n"

    // '/tmp/flag'을 리틀 엔디안으로 스택에 저장 (push 대신 직접 str 사용)
    "sub sp, sp, #16\n"                // 스택 공간 확보
    "mov x0, #0x67\n"                  // x0에 0x67 ('g') 저장
    "str x0, [sp]\n"                   // 스택에 x0 저장

    // '/tmp/flag' 문자열의 나머지 부분을 리틀 엔디안으로 저장
    "ldr x0, =0x67616c662f706d74\n"    // '/tmp/flag' 문자열을 리틀 엔디안으로 로드
    "str x0, [sp, #-8]!\n"             // 스택에 문자열 저장

    // open syscall 호출
    "mov x0, sp\n"                     // x0 = '/tmp/flag' (스택에 저장된 파일 경로)
    "mov x1, #0\n"                     // x1 = O_RDONLY (0)
    "mov x2, #0\n"                     // x2 = 0 (NULL)
    "mov x8, #56\n"                    // syscall 번호 (open) - AArch64에서 56번
    "svc #0\n"                         // 시스템 호출

    // read syscall 호출
    "mov x1, sp\n"                     // x1 = 버퍼 (rsp)
    "sub x1, sp, #0x30\n"              // x1 = rsp - 0x30 (버퍼 위치 설정)
    "mov x2, #0x30\n"                  // x2 = 0x30 (읽을 바이트 수)
    "mov x8, #63\n"                    // syscall 번호 (read) - AArch64에서 63번
    "svc #0\n"                         // 시스템 호출

    // write syscall 호출
    "mov x0, #1\n"                     // x0 = 1 (stdout)
    "mov x8, #64\n"                    // syscall 번호 (write) - AArch64에서 64번
    "svc #0\n"                         // 시스템 호출

    // exit syscall 호출
    "mov x0, #0\n"                     // 종료 상태 = 0
    "mov x8, #93\n"                    // syscall 번호 (exit) - AArch64에서 93번
    "svc #0\n"                         // 시스템 호출
);

void run_sh();

int main() {
    run_sh();
}

