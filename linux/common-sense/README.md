# 리눅스 토막 상식 그때 그때 정리 자료

### Table of Contents
<!--ts-->
  * [Permission](#Permission)
  * [RAID](#RAID)
  * [Systemd](#Systemd)
  * [FQDN](#FQDN) 
  * [Kernel Setting](#Kernel-Setting)
  * [top](#top)
  * [free](#free)
  * [ps](#ps)
  * [Memory Cache](#Memory-cache)
  * [Linux Directory](#Linux-Directory)
  * [IP](#IP)
<!--te-->

### Permission
* 파일 별로 접근 권한을 줄 수 있는데 10개의 알파벳으로 구성
  * r : 4 (2진수로 100) read
  * w : 2 (2진수로 10) write
  * x : 1 (2진수로 1) execute
  
  ex) drwxr-xr-x -> 755, -rw-r--r-- -> 644

|파일의 종류|파일의 User|파일의 Group|관계없는자들(Other)|
|:--------|:-------------|:----------|:----------|
|d        |rwx           |r-x        |r-x        |
|디렉토리   |읽기/쓰기/실행 가능|읽기/실행 가능|읽기/실행 가능|


### RAID
RAID는 여러 개의 디스크를 묶어 `하나의 디스크 처럼 사용하는 기술`로 다음과 같은 효과를 같음
- 대용량의 단일 볼륨을 사용하는 효과
- 디스크 I/O 병렬화로 인한 성능 향상 
- 데이터 복제로 인한 안정성 향상

### Systemd
* systemd는 부팅 중 시작하는 `서비스(혹 데몬)들을 관리하는 프로그램으로 init의 업그레이드 버전
* 서비스 파일 등록하는 법
  * 부팅 시 서비스가 실행(재부팅 시 적용)
  * /lib/system/systemd 폴더와 /etc/systemd/system 폴더 안에 관련 파일을 확인하고 각 시스템 폴더에 링크파일을 생성해 주는 역할을 한다. 
  ```bash
  $ systemctl enable [serviceName|serviceName.service]
  ```
  ```bash
  $ systemctl enable XX
  ```
  ```bash
  $ systemctl enable XX.service
  ```

* 서비스 파일 해제하는 법
  * 서비스가 등록된 링크파일을 삭제(재부팅 시 적용)
  ```bash
  $ systemctl disable [serviceName|serviceName.service]
  ```
  ```bash
  $ systemctl disable XX  
  ```
  ```bash
  $ systemctl disable XX.service
  ```

* 서비스 start
  * 관련된 시스템을 실행
  ```bash
  $ systemctl start XX
  ````

* 서비스 stop
  * 관련된 시스템을 중지
  ```bash
  $ systemctl stop XX
  ```

### FQDN
* `호스트와 도메인을 함께 명시`하여 전체 경로를 모두 표기하는 것
  1. 도메인 - www.tistory.com  
  2. FQDN(Fully Qualified Domain Name) - onlywis.tistory.com

### Kernel Setting
* 커널 설정을 변경하는 방법
  * `/etc/sysctl.conf` 파일 수정 이후 `$sysctl -p` 명령으로 설정
  * `sysctl -w` 명령으로 설정
* 커널 설정 파라미터 종류
```
### 시스템 관리 개선 ###

# 커널의 시스템 요구 디버깅 기능을 제어 / 시스템에서 매직키 활성화 여부 결정
# 매직키란 시스템을 Lock 하지 않은 상태에서 시스템이 어떤 작업을 하는 중이라도 커널이 반응하는 키
kernel.sysrq = 0

# 코어 덤프가 코어 파일 이름에 PID 를 추가할지 여부를 제어
kernel.core_uses_pid = 1

# PID 의 최대값 설정
kernel.pid_max = 65535

# /proc/<pid>/maps, smaps 의 내용을 단지 관리자만 볼수 있으며 ptrace() 과정을 허용
kernel.maps_protect = 1

# kernel.exec-shield 설정은 NX(Not eXecutable) 기법과 관련된 설정
kernel.exec-shield = 0 ---> ExecShield 보호 비활성화
kernel.exec-shield = 1 ---> ExecShield 보호 활성화

# kernel.randomize_va_space 설정은 ASLR 기법과 관련된 설정
# ASLR(Address Space Layout Randomization) 이란 메모리상의 공격을 어렵게 하기 위해 스택이나 힙, 라이브러리 등의 주소를 랜덤으로 프로세스 주소 공간에 배치함으로써 실행할 때 마다 데이터의 주소가 바뀌게 하는 기법
kernel.randomize_va_space = 0 ---> ASLR 해제
kernel.randomize_va_space = 1 ---> 랜덤 스택 & 라이브러리 활성화
kernel.randomize_va_space = 2 ---> 랜덤 스택 & 라이브러리 & 힙 활성화

# 메시지의 최대 크기 (바이트 단위)
kernel.msgmnb = 65535

# 하나의 프로세스에서 다른 프로세스로 보내질 수 있는 메시지 큐의 최대 크기 (바이트 단위)
kernel.msgmax = 65535

# 코어 덤프 제한
fs.suid_dumpable = 0

# 커널 포인트 숨기기
# non-root 유저가 kallsyms 등을 통해서 커널영역 포인터값을 보지 못하게 하는 설정임
kernel.kptr_restrict = 1



### 메모리 관리 개선 ###

# 파일 핸들과 inode 캐시의 크기를 늘림
fs.file-max = 209708

# swapping 비율 설정
vm.swappiness = 30
# 전체 시스템 메모리에서 Dirty Page 비율로 Process가 Dirty Page를 쓰기 시작하는 기준값
vm.dirty_ratio = 30
# 전체 시스템 메모리에서 dirty page 비율로 pdflush 데몬이 dirty page 를 쓰기 시작하는 기준값
vm.dirty_background_ratio =5

# 프로세스가 mmap이 허용되는 가상 주소를 최소로 지정
# mmap 이란 프로세스 간의 데이터 공유 메커니즘임
vm.mmap_min_addr = 4096

# vm.overcommit_ratio = 50 - overcommit_memory 가 2 로 설정되어 있는 경우 고려해야 할 물리적 RAM의 백분율을 지정함 (기본값은 50)

# 대량 메모리 요청을 수락 또는 거부할 지에 대해 결정하는 조건 설정
vm.overcommit_memory = 0 ---> 기본 설정으로 커널은 사용 가능한 메모리 양을 추정하고 잘못된 요청을 실패시켜 휴리스틱 메모리 오버커밋 처리를 수행하는데 불행히도 메모리는 정확한 알고리즘이 아닌 휴리스틱 알고리즘을 사용하여 할당되므로 이러한 설정은 시스템에서 사용가능한 메모리가 오버로드가 가능
vm.overcommit_memory = 1 ---> 커널은 메모리 오버커밋 처리를 수행하지 않으므로 이러한 설정에서 메모리 오버로드 가능성은 증가하므로 메모리 집약적 작업을 위한 성능
vm.overcommit_memory = 2 ---> 커널은 총 사용 가능한 스왑의 합계와 overcommit_ratio에 지정된 물리적 RAM의 백분율 보다 메모리가 크거나 동일한 경우 요청을 거부하므로 메모리 오버커밋의 위험을 줄이고자 할 경우 이 설정이 가장 적합

# shm 에 할당된 최대 메모리 양을 256 MB 로 설정
# shmmax - 공유 메모리 세그먼트 최대 크기를 설정
# shmall - 특정 시점에서 시스템에서 사용 가능한 공유 메모리의 최대 크기를 설정
kernel.shmmax = 268435456
kernel.shmall = 268435456

# 시스템 전체에 걸쳐 빈 공간으로 두는 최소 크기 설정값임(단위 KB)
vm.min_free_kbytes = 65535



### 일반 네트워크 보안 옵션 ###

# SYN 공격을 막고 SYNcookies를 활성화(max_syn_backlog에 도달하면 시작)
net.ipv4.tcp_syncookies = 1
net.ipv4.tcp_syn_retries = 2
net.ipv4.tcp_synack_retries = 2
net.ipv4.tcp_max_syn_backlog = 4096

# 패킷 포워딩 비활성화
net.ipv4.ip_forward = 0
net.ipv4.conf.all.forwarding = 0
net.ipv4.conf.default.forwarding = 0
net.ipv6.conf.all.forwarding = 0
net.ipv6.conf.default.forwarding = 0

# IP 소스 라우팅 비활성화
net.ipv4.conf.all.send_redirects = 0
net.ipv4.conf.default.send_redirects = 0
net.ipv4.conf.all.accept_source_route = 0
net.ipv4.conf.default.accept_source_route = 0
net.ipv6.conf.all.accept_source_route = 0
net.ipv6.conf.default.accept_source_route = 0

# IP 스푸핑 방지 활성화시키고 소스 경로 확인 켜기
net.ipv4.conf.all.rp_filter = 1
net.ipv4.conf.default.rp_filter = 1

# ICMP 리다이렉션 허용 비활성화
net.ipv4.conf.all.accept_redirects = 0
net.ipv4.conf.default.accept_redirects = 0
net.ipv4.conf.all.secure_redirects = 0
net.ipv4.conf.default.secure_redirects = 0
net.ipv6.conf.all.accept_redirects = 0
net.ipv6.conf.default.accept_redirects = 0

# 스푸핑 패킷, 소스 라우팅 패킷, 리다이렉션 패킷의 로그 활성화
net.ipv4.conf.all.log_martians = 1
net.ipv4.conf.default.log_martians = 1

# tcp_fin_timeout 연결의 시간 기본값을 줄임
net.ipv4.tcp_fin_timeout = 7

# 연결을 유지하는 데 걸리는 시간을 줄임
# TCP/IP가 대기 연결이 계속 원래 상태를 유지하는지 확인을 시도하는 빈도값 (성능향상을 위해서 감소)
net.ipv4.tcp_keepalive_time = 300

# TCP/IP가 기존 연결에 대한 수신확인되지 않은 활성화 상태 지속 메시지를 재전송하는 횟수를 결정하는 값 (성능향상을 위해서 감소)
net.ipv4.tcp_keepalive_probes = 5

# 상대로부터 활성화 상태 지속 응답이 수신되지 않을 경우 TCP/IP에서 활성화 상태 지속 전송을 반복하는 빈도를 결정하는 값 (성능향상을 위해서 감소)
net.ipv4.tcp_keepalive_intvl = 15


# bootp 릴레이 비활성화
net.ipv4.conf.all.bootp_relay = 0

# proxy arp 실행 비활성화
net.ipv4.conf.all.proxy_arp = 0

# tcp_timestamps 기능 활성화
net.ipv4.tcp_timestamps = 1

# ping 응답 비활성화
net.ipv4.icmp_echo_ignore_all = 0

# 브로드캐스트 요청 무시 활성화
net.ipv4.icmp_echo_ignore_broadcasts = 1

# 잘못된 오류 메시지 보호 활성화
net.ipv4.icmp_ignore_bogus_error_responses = 1

# 로컬 포트 범위 설정
net.ipv4.ip_local_port_range = 16384 65535

# 세팅되면 TCP 스택은 RFC1337을 따름
net.ipv4.tcp_rfc1337 = 1

# 자동 구성 IPv6 비활성화
net.ipv6.conf.all.autoconf=0
net.ipv6.conf.all.accept_ra=0
net.ipv6.conf.default.autoconf=0
net.ipv6.conf.default.accept_ra=0
net.ipv6.conf.eth0.autoconf=0
net.ipv6.conf.eth0.accept_ra=0



### 네트워크 성능 튜닝 ###

# BBR TCP 혼잡 제어를 사용하고 tcp_notsent_lowat을 16384로 설정하여 HTTP/2 버전이 우선 순위가 최적으로 작동하도록 함
# mmodprobe tcp_bbr 먼저 수행하며(커널 4.9 버전 이상) bbr을 사용할 수 없는 경우 htcp로 폴백
net.ipv4.tcp_congestion_control = htcp
net.ipv4.tcp_congestion_control = bbr
net.ipv4.tcp_notsent_lowat = 16384
    
# tcp-heavy 작업 부하가있는 서버의 경우 FQ 큐 관리 스케줄러를 활성화함 (커널 3.12 버전 이상)
net.core.default_qdisc = fq

# tcp_window_scaling 기능 활성화
net.ipv4.tcp_window_scaling = 1

# TCP 수신 버퍼
net.ipv4.tcp_rmem = 8192 87380 16777216

# UDP 수신 버퍼 최소량
net.ipv4.udp_rmem_min = 16384

# 모든 프로토콜 수신 버퍼
net.core.rmem_default = 262144

# 모든 프로토콜 수신 버퍼 최대량
net.core.rmem_max = 16777216

# TCP 송신 버퍼
net.ipv4.tcp_wmem = 8192 65536 16777216
# UDP 수신 버퍼 최소량
net.ipv4.udp_wmem_min = 16384
# 모든 프로토콜 송신 버퍼
net.core.wmem_default = 262144
# 모든 프로토콜 송신 버퍼 최대량
net.core.wmem_max = 16777216

# 수신 연결 갯수 증가
net.core.somaxconn = 32768

# 수신 연결 로그수 증가
net.core.netdev_max_backlog = 16384
net.core.dev_weight = 64

# 옵션 메모리 버퍼의 최대 크기 증가
net.core.optmem_max = 65535

# TIME_WAIT 상태 소켓 최대 설정값으로 간단한 DoS 공격을 방어하기 위해 해당 값 증가
net.ipv4.tcp_max_tw_buckets = 1440000

# TCP TIME_WAIT 소켓 재활용 여부 결정
net.ipv4.tcp_tw_recycle = 0
# CP TIME_WAIT 소켓 재사용 여부 결정
net.ipv4.tcp_tw_reuse = 1

# 사용자 파일 핸들에 연결되어 있지 않아서 시스템이 가지고 있는 TCP 소켓의 최대 개수
net.ipv4.tcp_max_orphans = 16384

# 닫은 TCP 연결을 죽이기 전까지 몇 번이나 재시도를 할 것인가 여부
net.ipv4.tcp_orphan_retries = 0

# IP 조각 재조립에 쓰이는 최대 메모리 제한
# IP 조각 재조립에 쓰이는 최소 메모리 제한
net.ipv4.ipfrag_low_thresh = 196608
net.ipv4.ipfrag_high_thresh = 262144
net.ipv6.ip6frag_low_thresh = 196608
net.ipv6.ip6frag_high_thresh = 262144


# 이전 연결에서 ssthresh 캐시를 하지 않음
net.ipv4.tcp_no_metrics_save = 1
net.ipv4.tcp_moderate_rcvbuf = 1

# RPC 데이터그램 큐 길이 크기 증가
net.unix.max_dgram_qlen = 50

# ARP 캐시에 유지되는 최대 항목 수(2028 보더 더 혀용하지 않는 것이 좋음)
net.ipv4.neigh.default.gc_thresh3 = 2048

# ARP 캐시에 유지되는 최대 항목 수
# LAN 크기에 따라 조정해야 하며 1024는 /24 네트워크에 적합함
net.ipv4.neigh.default.gc_thresh2 = 1024

# ARP 캐시에 유지되는 최소 항목 수
net.ipv4.neigh.default.gc_thresh1 = 32

# ARP 캐시에 GC(Garbage Collector)가 실행하는 시간 간격
net.ipv4.neigh.default.gc_interval = 30

# TCP 큐 길이 증가
net.ipv4.neigh.default.proxy_qlen = 96
net.ipv4.neigh.default.unres_qlen = 6

# 명백한 혼합 공지(Explicit Congestion Notification) 활성화
net.ipv4.tcp_ecn = 1

# TCP 스트림에 패킷들의 최대 재요청 설정값
net.ipv4.tcp_reordering = 3

# 무언가 문제가 있을 때 연결을 위해 재시도할 횟수 (최소 값과 기본 값은 3)
net.ipv4.tcp_retries1 = 3

# TCP 연결을 끊기 전에 재시도할 횟수
net.ipv4.tcp_retries2 = 15

# keep alive 연결로 혼잡 윈도우 크기(cwnd)를 크게 유지함 (커널 3.6 버전 이상)
net.ipv4.tcp_slow_start_after_idle = 0

# TCP fastopen flag 기능 활성화 (커널 3.7 버전 이상) - TCP 3-Hand Negotiation 과정을 몇 단계 생략하여 접속을 빠르게 하는 기능
net.ipv4.tcp_fastopen = 3

# 라우팅 캐시 청소 기능 활성화
net.ipv4.route.flush = 1
net.ipv6.route.flush = 1
```
* 주요 커널 파라미터 튜닝 후

```
# Kernel core
kernel.sysrq = 1
kernel.core_uses_pid = 1

# Controls IP packet forwarding
net.ipv4.ip_forward = 0

# number of open file
fs.file-max = 655360

# for Swap
vm.swappiness = 1

# for Network core tuning
net.core.somaxconn = 65000
net.core.netdev_max_backlog = 20000
net.core.rmem_max = 33554432
net.core.wmem_max = 33554432
net.core.rmem_default = 16777216
net.core.wmem_default = 16777216
net.core.optmem_max = 16777216

# for IPv4 tuning
net.ipv4.conf.default.accept_source_route = 0
net.ipv4.conf.all.rp_filter = 2
net.ipv4.conf.default.rp_filter = 0
net.ipv4.tcp_tw_recycle = 0
net.ipv4.tcp_tw_reuse = 1
net.ipv4.tcp_max_syn_backlog = 20000
net.ipv4.tcp_syncookies = 1
net.ipv4.tcp_mem = 16777216 16777216 16777216
net.ipv4.tcp_rmem = 4096 87380 16777216
net.ipv4.tcp_wmem = 4096 65536 16777216
net.ipv4.tcp_fin_timeout = 10
net.ipv4.tcp_max_orphans = 262144
net.ipv4.tcp_synack_retries = 5
net.ipv4.tcp_syn_retries = 5
net.ipv4.tcp_keepalive_time = 60
net.ipv4.tcp_keepalive_probes = 3
net.ipv4.tcp_keepalive_intvl = 10
net.ipv4.tcp_sack = 1
net.ipv4.tcp_timestamps = 1
net.ipv4.tcp_window_scaling = 1
net.ipv4.tcp_slow_start_after_idle = 0
net.ipv4.udp_rmem_min = 65536
net.ipv4.udp_wmem_min = 65536
net.unix.max_dgram_qlen = 100
vm.dirty_ratio = 40
vm.dirty_background_ratio = 10
vm.max_map_count = 262144
net.ipv4.tcp_fack = 1
kernel.msgmnb = 65536
kernel.msgmax = 65536
net.ipv6.conf.all.disable_ipv6 = 1
net.ipv6.conf.default.disable_ipv6 = 1
```

### top
* top: 시스템의 상태를 전반적으로 가장 빠르게 파악 가능(CPU, Memory, Process)
* 특징: 옵션없이 입력하면 interval 간격(기본 3초)으로 proc에서 검색한 시스템 상태 화면을 갱신하며 정보를 보여주는 주기적인 출력을 보여준다는 면에서 `ps`와 다름
* top 옵션
  * -b: 순간의 정보를 확인
  * -n: top 실행 횟수 지정
* top 실행 이후 명령 옵션
  * shift + p: CPU 사용률 내림차순
  * shit + m: 메모리 사용률 내림차순
  * shift + t: 프로세스가 돌아가고 있는 시간 순
  * k: kill(k 입력 후 PID 번호 작성. signal은 9)
  * f: sort field 선택 화면 -> q 누르면 RES순으로 정렬
  * a: 메모리 사용량에 따라 정렬
  * b: Batch 모드로 작동
  * 1: CPU Core별로 사용량 보여줌
* top 플래그
  * CPU
    1. %us: 유저 레벨에서 사용하고 있는 CPU의 비중
    2. %sy: 시스템 레벨에서 사용하고 있는 CPU비중
    3. %id: 유휴 상태의 CPU 비중
    4. %wa: 시스템이 I/O 요청을 처리하지 못한 상태에서의 CPU idle 상태인 비중
  * 메모리
    1. %total: 전체 물리적인 메모리
    2. %used: 시용 중인 메모리
    3. %free: 사용되지 않은 여유 메모리
    4. %buffers: 버퍼된 메모리
  * Swap
    1. %total: 전체 스왑 메모리
    2. %used: 사용중인 스왑 메모리
    3. %free: 남아있는 스왑메모리
    4. %cached: 캐싱메모리
  * 프로세스 상태
    1. PID: 프로세스 ID (PID)
    1. USER: 프로세스를 실행시킨 사용자 ID
    1. PRI: 프로세스의 우선순위 (priority)
    1. NI: NICE 값. 일의 nice value값이다. 마이너스를 가지는 nice value는 우선순위가 높음.
    1. VIRT: 가상 메모리의 사용량(SWAP+RES)
    1. RES: 현재 페이지가 상주하고 있는 크기(Resident Size)
    1. SHR: 분할된 페이지, 프로세스에 의해 사용된 메모리를 나눈 메모리의 총합.
    1. S: 프로세스의 상태 [ S(sleeping), R(running), W(swapped out process), Z(zombies) ]
    1. %CPU: 프로세스가 사용하는 CPU의 사용율
    1. %MEM: 프로세스가 사용하는 메모리의 사용율
    1. COMMAND: 실행된 명령어

### free
* free: 시스템 전체의 메모리의 상태를 확인하는 명력어
* free 옵션
  * -m: 메가바이트 단위로 출력
  * -g: 기가바이트 단위로 출력
  * -k: 킬로바이트 단위로 출력
* free 플래
  * total: 설치된 총 메모리 크기 / 설정된 스왑 총 크기
  * used: total에서 free, buff/cache를 뺀 사용중인 메모리. / 사용중인 스왑 크기
  * free: total에서 used와 buff/cahce를 뺀 실제 사용 가능한 여유 있는 메모리량 / 사용되지 않은 스왑 크기
  * shared: tmpfs(메모리 파일 시스템), ramfs 등으로 사용되는 메모리. 여러 프로세스에서 사용할 수 있는 공유 메모리
  * buffers: 커널 버퍼로 사용중인 메모리
  * cache: 페이지 캐시와 slab으로 사용중인 메모리
  * buff/cache: 버퍼와 캐시를 더한 사용중인 메모리
  * available: swapping 없이 새로운 프로세스에서 할당 가능한 메모리의 예상 크기. (예전의 -/+ buffers/cache이 사라지고 새로 생긴 컬럼)

### ps
* top: 현재 시점의 시스템의 프로세스의 상태를 파악하는 명령어
* 특징: 현시점의 상태만을 출력한다는 점에서 `top`과 다름
* ps 옵션
  * e: 모든 프로세스를 표시
  * f: 전체 경로로 프로세스를 표시
  * l: 긴 포맷으로 출력
  * u: 실행한 유저 및 실행 시간을 표시
  * a: 다른 유저의 프로세스도 표시
  * x: 터미널 제어 없이 프로세스 현황 보기
* ps 플래그
  * PID(process ID): 프로세스마다 주어지는 번호
  * TTY(Tele Typewriter): 명령어가 실행되는 터미널의 번호
  * STAT: 실행되고 있는 프로세스 상태(R, S, D, T, Z, W, N)
  * START: 프로세스가 시작된 시간
  * TIME: CPU가 사용한 시간
  * USER: 사용자의 이름
  * COMMAND: 사용자가 실행한 명령어
  * UID(User ID): 사용자의 ID
  * PGID(Parent Group ID): 사용자 부모 프로세스의 그룹 ID
  * SID(Seesion ID): 세션 ID
  * PRI(PRIority): 실행하는 우선순위에 따른 프로세스
  * NI(NIce): nice에 의한 우선순위에 따른 프로세스
  * RSS(Resident Set Size): 프로세스가 사용하는 메모리 크기
  * SZ(Size): 프로세스가 사용하는 자료와 스택의 크기
  * SHRD(SHaRD): 프로세스가 사용하는 공유메모리
  * %CPU: 프로세스가 사용하는 CPU 정유율
  * WCHAN: 프로세스가 실행하고 있는 메모리 점유율
  * VSZ: KiB 단위(1024 바이트 단위)의 프로세스의 비주얼 메모리 크기


### Memory Cache
* 페이지 캐시: 디스크 접근을 최소화 하여 파일 I/O성능을 향상시키기 위해 사용되는 메모리 영역으로 한 번 읽은 파일의 내용을 이 페이지 캐시 영역에 저장하고 같은 파일의 접근이 일어나면 디스크에서 읽어오는 것이 아니라 페이지 캐시에서 읽음
* 버퍼 캐시: 디스크의 블록 단위로 데이터를 전송하는 블록 디바이스가 가지고 있는 블록 자체에 대한 캐시로 커널이 특정 블록에 접근하면 블록의 내용을 버퍼 캐시 영역에 저장하고 동일한 블록에 접근할 시에 버퍼 캐시에서 읽음(현재는 페이지 캐시가 버퍼 캐시 내에 포함되어 있음)


### Linux Directory
* /bin
  - binarise의 약어
  - 리눅스의 `기본 명령어(binary)`들이 들어있는 디렉토리
  - 시스템을 운영하는데 기본적인 명령어들이 모여있는 디렉토리
  - 부팅에 필요한 명령어들이 들이 위치하며 부팅 후 시스템의 사용자들이 사용할 수 있는 일반적인 명령어들도 위치하고 있음
  
* /sbin
  - `시스템 관리에 관련된 실행 명령어`들이 들어있는 디렉토리
  - 시스템 점검 및 복구 명령, 시스템 초기 및 종료 명령 등 시스템 관리에 관련된 실행파일들 존재
  
* /lib
  - 프로그램들이 의존하고 있는 `라이브러리` 파일들 존재
  - /lib/modules: 커널 모듈 파일들 존재
  - 대부분의 라이브러리들은 링크로 연결되어 있음
  
* /proc
  - `시스템의 각종 프로세서, 프로그램 정보, 하드웨어적인 정보`들이 저장됨
  - 가상 파일시스템으로 /dev 디렉토리와 마찬가지로 하드디스크 상에 물리적인 용량을 갖지 않음(실제로 존재하지 않음)
  - 실제 하드 디스크에 저장되지 않고 커널에 의해서 메모리에 저장됨
  - 현재 시스템의 설정을 보여줌
  - 커널의 어떤 기능을 제어할 수 있는 역할을 가지고 있음
  - 대부분 읽기 전용이나, 일부 파일중에는 쓰기가 가능한 파일이 존재 하는데 이러한 파일들에 특정 값을 지정하면 커널 기능이 변하게 됨
  - 이 디렉토리 내에 있는 파일을 cat 명령을 이용하여 보면 시스템 정보를 확인 할 수 있음

* /etc
  - 시스템 `환경 설정 파일`이 있는 디렉토리
  - 네트워크 관련 설정파일, 사용자 정보 및 암호정보, 파일 시스템 정보, 보안파일, 시스템 초기화 파일등 중요 설정 파일들의 위치한 디렉토리
  - /etc/CORBA : Common Object Request Broker Architecture (COBRA)에 관한 파일이 들어있음
  - /etc/X11 : 엑스 윈도우 설정에 관련된 파일들이 있음
  - /etc/cron.d : crontab 명령의 설정파일이 있음
  - /etc/cron.daily : 매일 작동하게 하는 crontab 스크립트 파일이 존재
  - /etc/gnome : GTK+ 정의파일들이 있음
  - /etc/httpd : 아파치 웹 서버의 설정 및 로그파일이 있음
  - /etc/logrotate.d : logrotate 설정 파일들이 있음
  - /etc/mail : 센드메일과 관련된 파일이 있음
  - /etc/ppp : ppp 설정에 관련된 파일들이 있음
  - /etc/profile.d : 쉘 로그인 하여 프로파일의 실행되는 스크립트에 대한 정의가 있음
  - /etc/rc.d : 시스템 초기화와 관련된 스크립트가 존재
  - /etc/samba : 삼바에 관련된 파일들이 있음
  - /etc/security : 터미널 보안에 관련된 설정이 있음
  - /etc/skel : 새로운 사용자를 추가할 때 자동적으로 생성되는 디렉토리와 파일이 있음
  - /etc/squid : squid 프록시 서버에 관련된 파일이 있음
  - /etc/ssh : secure shell 설정 파일이 있음
  - /etc/sysconfig : 시스템과 네트워크 설정을 담고 있음
  - /etc/xinetd.d : 슈퍼데몬 xinetd.d의 서비스 영역을 설정하는 디렉토리

* /var
  - 시스템에서 사용되는 `동적인 파일`들이 저장됨(가변 자료 저장 디렉토리)
  - 시스템 운영중에 시스템 자료 데이터가 변경될 때 변경된 자료들이 저장되는 곳
  - 주로 시스템 작동기록(`log`)들을 저장
  - 각종 시스템 로그파일, 사용자 로그인에 대한 보안기록, 그리고 메일서버를 운영한다면 전송되는 메일들을 임시로 저장
  - 레드헷 7.0에서부터는 /home 디렉토리에 저장되던 /home/httpd 디렉토리가 /var/www로 변경되어 저장됨, /home/ftp는 /var/ftp로 변경
  - /var/log : 시스템에 발생된 일들에 대한 기록 파일이 있음
  - /var/named : 네임서버 설정 파일들 존재
  - /var/spool/mail : 수신 메일을 사용자 명으로 기록하는 디렉토리

* /usr
  - 일반 사용자들을 위한 `대부분의 프로그램` 라이브러리 파일들이 위치
  - `/usr/bin` : 응용 프로그램의 실행 파일이 위치
  - /usr/sbin : 주로 네트워크 관련 실행 명령어와 실행 데몬들을 많이 포함하고 있음
  - /usr/X11R6 : X-window 시스템에 관련된 파일 존재
  - /usr/include : 기본 C 라이브러리 헤더 파일과 각종 라이브러리 헤더파일들이 있음
  - /usr/lib : /usr/bin과 /usr/sbin에 있는 실행 바이너리를 실행하기 위한 라이브러리 존재
  - /usr/src : 프로그램소스 및 커널 소스들이 보관되어 있는 곳
  - /usr/man : 매뉴얼 페이지가 담겨있는곳
  - /usr/local : 새로운 프로그램들이 설치되는 곳 (windows의 Program Files와 유사)

* /mnt
  - 다른 장치들을 마운트 할때 일반적으로 사용하는 디렉토리
  - 다른 디렉토리를 사용하여도 됨

* /home
  - 일반 사용자의 홈 디렉토리가 만들어 지는 디렉토리
  - 사용자 계정을 만들면 게정과 같은 이름으로 새로운 사용자 디렉토리가 /home 디렉토리의 하위 디렉토리로 생성됨

* /boot
  - 부팅에 핵심적인 커널 이미지와 부팅 정보 파일을 담고 있는 디렉토리
  - /etc/lilo.conf에서 지정한 커널 부팅 이미지 파일이 들어 있으며 부팅시 매우 중요한 디렉토리

* /root
  - 슈퍼유저(root) 사용자의 홈 디렉토리
  - / 와 /root 디렉토리는 부르는 이름은 같지만 서로 다름

### IP
* IP 주소는 네트워크 주소 + 호스트 주소를 모두 갖고 있는 개념
  - 127.0.0.1은 루프백으로 즉 자기 스스로를 가리키는 특별한 IP를 의미
  - 0.0.0.0은 보통 서브넷 마스크 0.0.0.0과 같이 사용되며 모든 IP를 의미
* IP 네트워크 클래스
  - 현재는 서브넷이라는 기술을 통해 네트워크 비트를 8, 16, 24 비트로 정량적으로 구분하지 않고 서브넷 마스크 만큼을 네트워크 비트로 설정하는 유동적인 방식으로 변경되었으나 클래스 개념와 연동하여 사용

|클래스   |최상위 비트 |범위                     |사설IP 범위                   |네트워크 비트 |호스트 비트   |네트워크 수   |호스트 수    |
|:------|:---------|:----------------------|:---------------------------|:----------|:----------|:----------|:----------|
|A      |0         |0.0.0.0~127.0.0.0      |10.0.0.0~10.255.255.255     |8          |24         |128        |16,777,214 |
|B      |10        |128.0.0.0~191.255.0.0  |172.16.0.0~172.31.255.255   |16         |16         |16,384     |65,534     |
|C      |11        |192.0.0.0~223.255.255.0|192.168.0.0~192.168.255.255 |24         |8          |2,097,152  |254        |
