# HTTP 기초 
김영한 강사님 모든 개발자를 위한 HTTP 웹 기본 지식 강의 정리

## 인터넷 네트워크

#### 인터넷 통신
- 인터넷에서 컴퓨터 둘은 어떻게 통신할까?
  - 내가(클라이언트) 던진 데이터가 인터넷을 거쳐 다른 컴퓨터(서버)로 전달

#### IP
- IP
  - 지정한 `IP 주소(IP Address)`에 데이터 전달
  - `패킷(Packet)`이라는 통신 단위로 데이터 전달
- IP 프로토콜의 한계
  - 비연결성: 패킷을 받을 대상이 없거나 서비스 불능 상태여도 패킷 전송
  - 비신뢰성: 중간에 패킷이 사라지거나 패킷이 순서대로 안오는 상황
  - 프로그램 구분: 같은 IP를 사용하는 서버에서 통신하는 애플리케이션이 여러 개인 상황

#### TCP/UDP
- 인터넷 프로토콜 스택의 5계층
  - 애플리케이션 계층 - HTTP, FTP
  - 전송 계층 - TCP, UDP
  - 인터넷 계층 - IP
  - 네트워크 인터페이스 계층 - Ethernet frame
  - 물리 계층
- IP 패킷 정보
  - 출발지 IP, 목적지 IP + 데이터
- TCP 패킷 정보
  - 출발지 PORT, 목적지 PORT 전송 제어, 순서, 검증 정보 + IP 패킷 정보
- TCP(Transmission Control Protocol) 특징
  - 연결지향 - `TCP 3 way handshake (가상 연결)` 
  - 데이터 전달 보증
  - 순서 보장
- 3 way handshake
  - 클라이언트 -> 서버 SYN
  - 서버 -> 클라이언트 SYN + ACK
  - 클라이언트 -> 서버 ACK(데이터도 같이 전송 가능)
- UDP(User Datagram Protocol) 특징
  - 연결지향 X
  - 데이터 전달 보증 X
  - 순서 보장 X
  - 단순하고 빠름
  - PORT와 체크섬 정도만 추가

#### PORT
- PORT: 한번에 여러 개의 프로세스를 연결하기 위한 구분자
- PORT의 특징
  - 0 ~ 65535 할당 가능
  - 0 ~ 1023: 잘 알려진 포트
  - HTTP - 80 / HTTPS - 443


#### DNS
- IP의 한계
  - IP는 기억하기 어려움
  - IP는 변경될 수 있음
- DNS: 도메인 명을 IP 주소로 변환하는 시스템

## URI와 웹 브라우저 요청 흐름

#### URI
- URI(Uniform Resource Identifier): URL(Locator) + URN(Name)
  - Uniform: 리소스 식별하는 통일된 방식
  - Resource: 자원, URI로 식별할 수 있는 모든 것(제한 없음) 
  - Identifier: 다른 항목과 구분하는데 필요한 정보
  - URN 이름만으로 실제 리소스를 찾을 수 있는 방법이 보편화 되지 않아 URL만 대부분 사용
- URL 문법: scheme://[userinfo@]host[:port][/path][?query][#fragment]
  - 예시 -> https://www.google.com:443/search?q=hello&hl=ko
  - 프로토콜(https) 
  - 호스트명(www.google.com): 도메인 명 또는 IP 주소를 직접 사용 가능
  - 포트 번호(443): 일반적으로 생략, 생략 시 http는 80, https는 443
  - 패스(/search): 리소스 경로(path), 계층적 구조인 형태
  - 쿼리 파라미터(q=hello&hl=ko): key=value 형태, ?로 시작하며 &로 추가 가능

#### 웹 브라우저 요청 흐름
1. HTTP 요청 메시지 생성: HTTP 메소드 + path와 쿼리 스트링 + HTTP 버전 + 호스트 등등
2. TCP/IP 패킷을 HTTP 메시지에 추가
3. DNS 조회
4. 서버에 전송
5. HTPP 응답 메시지 생성: HTTP 버전 + 상태 코드 + Content-Type + Content-Length 등등
6. 클라이언트에 전송

## HTTP 기본

#### 모든 것이 HTTP

#### 클라이언트 서버 구조

#### Stateful/Stateless

#### 비 연결성

#### HTTP 메시지



## HTTP 메서드

## HTTP 메서드 활용

## HTTP 헤더1 - 일반 헤더

## HTTP 헤더2 - 캐시와 조건부 요청