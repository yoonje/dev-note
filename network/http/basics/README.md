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
- HTTP: HyperText Transfer Protocol로 기존에는 하이퍼 텍스트를 전송하기 위한 프로토콜이었지만 현재는 HTML, TEXT, IMAGE, 음성, 영상, 파일, JSON, XML 등 거의 모든 형태의 데이터 전송
- HTTP의 역사
  - HTTP/0.9 1991년: GET 메서드만 지원, HTTP 헤더X
  - HTTP/1.0 1996년: 메서드, 헤더 추가
  - HTTP/1.1 1997년: 가장 많이 사용, 우리에게 가장 중요한 버전, TCP
  - HTTP/2 2015년: 성능 개선, TCP
  - HTTP/3 진행중: TCP 대신에 UDP 사용, 성능 개선, UDP
- HTTP의 특징
  - 클라이언트 서버 구조
  - `무상태 프로토콜(스테이스리스)`, 비연결성 HTTP 메시지
  - 단순하고 확장 가능

#### 클라이언트 서버 구조
- Request Response 구조
- 클라이언트는 서버에 요청을 보내고, 응답을 대기
- 서버가 요청에 대한 결과를 만들어서 응답
- 클라이언트는 UI/UX에 초점을 맞추고 서버는 트래픽 제어와 비지니스 로직에 초점을 맞춤

#### Stateful/Stateless
- 무상태 프로토콜
  - 서버가 클라이언트의 상태를 보존X
  - 장점: 서버 확장성 높음(스케일 아웃)
  - 단점: 클라이언트가 추가 데이터 전송
- Stateful에 비한 Stateless 장점
  - 항상 같은 서버가 유지되지 않아도 됨
  - 중간에 서버가 장애 아무 서버나 호출
  - 스케일 아웃(수평 확장)에 유리
- Stateless 한계
  - 상태 유지가 필요한 서비스(로그인) - 브라우저의 쿠키와 서버의 세션을 통해서 상태 유지


#### 비 연결성
- 비 연결성의 장점
  - HTTP는 기본이 연결을 유지하지 않는 모델
  - 일반적으로 초 단위의 이하의 빠른 속도로 응답
  - 서버 자원을 매우 효율적으로 사용할 수 있음
- 비 연결성의 한계
  - TCP/IP 연결을 새로 맺어야 함 - 3 way handshake 시간 추가
  - 웹 브라우저로 사이트를 요청하면 HTML 뿐만 아니라 자바스크립트, css, 추가 이미지 등
등 수 많은 자원이 함께 다운로드
- 비 연결성의 극복
  - 일정 시간 동안 지속 연결로 유지

#### HTTP 메시지
- HTTP 메시지 구조
  - `시작 라인`
  - `헤더`
  - `공백 라인 (CRLF)`
  - `바디`
- 시작 라인: request-line와 status-line으로 구성
  - request-line = method SP(공백) request-target SP(공백) HTTP-version CRLF(엔터)
  - status-line = HTTP-version SP(공백) status-code SP(공백) reason-phrase CRLF(엔터)
- 헤더: field-name ":" OWS field-value OWS 형태로 구성
- 바디: 실제 전송할 데이터

## HTTP 메서드

#### HTTP API를 만들어보자
- API 설계 시에 가장 중요한 것은 `리소스 식별`
- URI는 리소스만 식별
- 리소스와 해당 리소스를 대상으로 하는 행위을 분리

#### HTTP 메서드 - GET, POST
- HTTP 주요 메서드 종류
  - GET: 리소스 조회
  - POST: 요청 데이터 처리, 주로 등록에 사용 PUT: 리소스를 대체, 해당 리소스가 없으면 생성
  - PATCH: 리소스 부분 변경
  - DELETE: 리소스 삭제
- 기타 메서드
  - HEAD: GET과 동일하지만 메시지 부분을 제외하고, 상태 줄과 헤더만 반환 
  - OPTIONS: 대상 리소스에 대한 통신 가능 옵션(메서드)을 설명(주로 CORS에서 사용) 
  - CONNECT: 대상 자원으로 식별되는 서버에 대한 터널을 설정
  - TRACE: 대상 리소스에 대한 경로를 따라 메시지 루프백 테스트를 수행
- GET
  - `리소스 조회`
  - 서버에 전달하고 싶은 데이터는 query(쿼리 파라미터, 쿼리 스트링)를 통해서 전달
  - 메시지 바디를 사용해서 데이터를 전달할 수 있지만, 지원하지 않는 곳이 많아서 권장하지 않음
  ```
  GET /members/100 HTTP/1.1 
  Host: www.google.com
  ```
- POST
  - `리소스에 대한 요청 데이터 처리`
  - 메시지 바디를 통해 서버로 요청 데이터 전달
  - 서버는 요청 데이터를 처리
  - 주로 전달된 데이터로 신규 리소스 등록, 프로세스 처리에 사용
  - URI에 POST 요청이 오면 요청 데이터를 어떻게 처리할지 리소스마다 따로 정해야 함 -> 정해진 것이 없음
  ```
  POST /members HTTP/1.1 
  Content-Type: application/json 

  {
    "username": "hello", "age": 20
  }
  ```


#### HTPP 메서드 - PUT, PATCH, DELETE
- PUT
  - `리소스를 완전히 대체하거나 생성`
  - 클라이언트가 리소스 위치를 알고 URI를 지정해하므로 POST와 다름
  - 리소스가 있는 경우 완전히 대체하고 리소스가 없는 경우 생성
  ```
  PUT /members/100 HTTP/1.1
  Content-Type: application/json

  {
    "username": "hello", 
    "age": 20
  }
  ```
- PATCH
  - `리소스를 부분 변경`
  ```
  PATCH /members/100 HTTP/1.1 
  Content-Type: application/json

  {
    "age": 50
  }
  ```
  
- DELETE
  - `리소스 제거`
  ```
  DELETE /members/100 HTTP/1.1 
  Host: localhost:8080
  ```

#### HTTP 메서드의 속성
- 안전(Safe Methods)
  - `호출해도 리소스를 변경하지 않음`
- 멱등(Idempotent Methods)
  - `여러번 호출해도 결과가 똑같음`
  - POST는 멱등이 아님
- 캐시 가능(Cacheable Methods)
  - GET, HEAD, POST, PATCH 캐시가능 (실제로는 GET 정도만 캐시로 사용)

## HTTP 메서드 활용

#### 클라이언트에서 서버로 데이터 전송
- 클라이언트 -> 서버 데이터 전달 방식
  - `쿼리 파라미터`를 통한 데이터 전송: 주로 GET
  - `메시지 바디`를 통한 데이터 전송: 주로 POST, PUT, PATCH
- 클라이언트 -> 서버 데이터 전달 상황
  - 정적 데이터 조회: 이미지, 정적 텍스트 문서
    - 쿼리 파라미터 미사용
  - 동적 데이터 조회: 주로 검색, 게시판 목록에서 정렬 필터(검색어)
    - 쿼리 파라미터 사용
  - `HTML Form`을 통한 데이터 전송: 회원 가입, 상품 주문, 데이터 변경
    - POST 전송과 Content-Type: application/x-www-form-urlencoded 사용이 기본
    - 바이너리 데이터는 Content-Type: multipart/form-data를 사용
    - GET도 가능
  - `HTTP API`를 통한 데이터 전송: 회원 가입, 상품 주문, 데이터 변경
    - 서버 to 서버, 앱 클라이언트, 웹 클라이언트(Ajax)
    - Content-Type: application/json을 주로 사용
    - POST, PUT, PATCH: 메시지 바디를 통해 데이터 전송
    - GET: 조회, 쿼리 파라미터로 데이터 전달
## HTTP 상태코드

#### HTTP 상태코드 소개
- 상태코드: 클라이언트가 보낸 요청의 처리 상태를 응답에서 알려주는 기능
  - 1xx (Informational): 요청이 수신되어 처리중
  - 2xx (Successful): 요청 정상 처리
  - 3xx (Redirection): 요청을 완료하려면 추가 행동이 필요
  - 4xx (Client Error): 클라이언트 오류, 잘못된 문법등으로 서버가 요청을 수행할 수 없음 5xx (Server Error): 서버 오류, 서버가 정상 요청을 처리하지 못함

#### 2xx - 성공
- 200 OK: 요청 성공
- 201 Created: 요청 성공해서 새로운 리소스가 생성됨
- 202 Accepted: 요청이 접수되었으나 처리가 완료되지 않았음
- 204 No Content: 서버가 요청을 성공적으로 수행했지만, 응답 페이로드 본문에 보낼 데이터가 없음

#### 3xx - 라디이렉션
- 리다이렉션: 웹 브라우저는 3xx 응답의 결과에 Location 헤더가 있으면, Location 위치로 자동 이동
- 301 Moved Permanently: 영구 리다이렉션 / 리다이렉트 시 요청 메서드가 GET으로 변하고, 본문이 제거될 수도 있음 
- 302 Found: 일시적 리다이렉션 / 리다이렉트 시 요청 메서드가 GET으로 변하고, 본문이 제거될 수도 있음
- 303 See Other: 일시적 리다이렉션 / 리다이렉트 시 요청 메서드가 GET으로 변경
- 304 Not Modified: 캐시를 목적으로 사용, 클라이언트에게 리소스가 수정되지 않았음을 알려줌(메시지 바디를 포함하면 안됨)
- 307 Temporary Redirect: 일시적 리다이렉션 / 리다이렉트시 요청 메서드와 본문 유지(요청 메서드를 변경하면 안됨)
- 308 Permanent Redirect: 영구 리다이렉션 / 리다이렉트 시 요청 메서드와 본문 유지(처음 POST를 보내면 리다이렉트도 POST 유지)
- PRG: Post/Redirect/Get
  - POST로 요청 후에 웹 브라우저를 새로고침하면 다시 요청이 될 수 있음
  - POST로 요청 후에 302를 응답으로 받으면 요청 결과 화면을 GET 메서드로 리다이렉트(새로 고침으로 인한 중복 요청 방지)
- 일시적 리다이렉션인 302, 307, 303 중에서 뭘 써야 하나요?
  - 307, 303을 권장하지만 현실적으로 이미 많은 애플리케이션 라이브러리들이 302를 기본값으로 사용

#### 4xx - 클라이언트 오류
- 클라이언트 오류
  - 클라이언트의 요청에 잘못된 문법 등으로 서버가 요청을 수행할 수 없음
  - 오류의 원인이 클라이언트에 있음
  - 클라이언트가 이미 잘못된 요청, 똑같은 재시도가 실패함
- 400 Bad Request: 클라이언트가 잘못된 요청을 해서 서버가 요청을 처리할 수 없음
- 401 Unauthorized: 클라이언트가 해당 리소스에 대한 인증이 필요함
- 403 Forbidden: 서버가 요청을 이해했지만 승인을 거부함
- 404 Not Found: 요청 리소스를 찾을 수 없음

#### 5xx - 서버 오류
- 서버 오류
  - 서버 문제로 오류 발생
  - 서버에 문제가 있기 때문에 재시도 하면 성공할 수도 있음
- 500 Internal Server Error: 서버 문제로 오류 발생, 애매하면 500 오류
- 503 Service Unavailable: 서비스 이용 불가

## HTTP 헤더1 - 일반 헤더

#### HTTP 헤더 개요
- HTTP 헤더: HTTP 전송에 필요한 모든 부가 정보로, 표준 헤더도 있고 임의의 헤더 추가도 가능
- HTTP 헤더
  - General 헤더: 메시지 전체에 적용되는 정보, 예) Connection: close
  - Request 헤더: 요청 정보, 예) User-Agent: Mozilla/5.0 (Macintosh; ..)
  - Response 헤더: 응답 정보, 예) Server: Apache
  - `Representation 헤더`: 표현 바디 정보, 예) Content-Type: text/html, Content-Length: 3423
- HTTP 바디
  - 메시지 본문 = 페이로드(payload)
  - 표현은 요청이나 응답에서 전달할 실제 데이터
  - 표현 헤더는 표현 데이터를 해석할 수 있는 정보 제공

#### 표현 헤더
- 표현 헤더는 전송, 응답 둘다에서 사용
- Content-Type: 표현 데이터의 형식
  - text/html; charset=utf-8 
  - application/json 
  - image/png
- Content-Encoding: 표현 데이터의 압축 방식
  - gzip
  - deflate
  - identity
- Content-Language: 표현 데이터의 자연 언어
  - ko
  - en
  - en-US
- Content-Length: 표현 데이터의 길이


#### 콘텐츠 협상
- 콘텐츠 협상: 클라이언트가 선호하는 표현 요청
  - Accept: 클라이언트가 선호하는 미디어 타입 전달 
  - Accept-Charset: 클라이언트가 선호하는 문자 인코딩 
  - Accept-Encoding: 클라이언트가 선호하는 압축 인코딩 
  - Accept-Language: 클라이언트가 선호하는 자연 언어
- 협상과 우선순위 1
  - Quality Values(q) 값 사용
  - 0~1, 클수록 높은 우선순위이고 생략하면 1
- 협상과 우선순위 2
  - 구체적인 것이 우선
- 협상과 우선순위 3
  - 구체적인 것을 기준으로 미디어 타입을 맞춤

#### 전송 방식
- 단순 전송: Content-Length 필요
- 압축 전송: Content-Length와 Content-Encoding 필요
- 분할 전송: Transfer-Encoding 필요, Content-Length가 있으면 안됨
- 범위 전송: Content-Range

#### 일반 정보
- From: 유저 에이전트의 이메일 정보
  - 일반적으로 잘 사용되지 않음
  - 검색 엔진 같은 곳에서, 주로 사용
  - 요청에서 사용
- `Referer`: 이전 웹 페이지 주소
  - A -> B로 이동하는 경우 B를 요청할 때 Referer: A 를 포함해서 요청
  - 요청에서 사용
- User-Agent: 유저 에이전트 애플리케이션 정보
  - 어떤 종류의 브라우저에서 장애가 발생하는지 파악 가능
  - 요청에서 사용
- Server: 요청을 처리하는 오리진 서버의 소프트웨어 정보 
- Date: 메시지가 생성된 날짜
  - 응답에서 사용

#### 특별한 정보
- Host: 요청한 호스트 정보(도메인)
  - 필수
  - 하나의 서버가 여러 도메인을 처리해야 할 때
  - 하나의 IP 주소에 여러 도메인이 적용되어 있을 때
- Location: 페이지 리다이렉션
  - 웹 브라우저는 3xx 응답의 결과에 Location 헤더가 있으면, Location 위치로 자동 이동
- Allow: 허용 가능한 HTTP 메서드
  - 405 (Method Not Allowed) 에서 응답에 포함해야함
- Retry-After: 유저 에이전트가 다음 요청을 하기까지 기다려야 하는 시간
  - 503 (Service Unavailable)에서 서비스가 언제까지 불능인지 알려줄 수 있음

#### 인증
- Authorization: 클라이언트 인증 정보를 서버에 전달
- WWW-Authenticate: 리소스 접근시 필요한 인증 방법 정의
  - 401 Unauthorized 응답과 함께 사용

#### 쿠키
- Set-Cookie: 서버에서 클라이언트로 쿠키 전달(응답)
- Cookie: 클라이언트가 서버에서 받은 쿠키를 브라우저에 저장하고, HTTP 요청시 서버로 전달(요청)
  - 모든 요청에 쿠키 정보 자동 포함
  - 서버에 전송하지 않고, 웹 브라우저 내부에 데이터를 저장하고 싶으면 웹 스토리지 참고
- 쿠키 - 생명 주기(expire)
  - 세션 쿠키: 만료 날짜를 생략하면 브라우저 종료시까지만 유지
  - 영속 쿠키: 만료 날짜를 입력하면 해당 날짜까지 유지
- 쿠키 - 도메인(domain)
  - 명시한 문서 기준 도메인 + 서브 도메인 포함하면 서브 도메인도 쿠키가 적용
  - 현재 문서 기준 도메인만 적용하면 현재 도메인만 쿠키가 적용
- 쿠키 - 경로(path)
  - 이 경로를 포함한 하위 경로 페이지만 쿠키 접근
  - 일반적으로 path=/ 루트로 지정
- 쿠키 - 보안(Secure)
  - 쿠키는 http, https를 구분하지 않고 전송하는데 Secure를 적용하면 https인 경우에만 전송


## HTTP 헤더2 - 캐시와 조건부 요청

#### 캐시 기본 동작
- 캐시를 사용하는 이유
  - 데이터가 변경되지 않아도 계속 네트워크를 통해서 데이터를 다운로드 받아야 한다.
  - 인터넷 네트워크는 매우 느리고 비싸다.
  - 브라우저 로딩 속도가 느리다.
- 동작 과정
  - 클라이언트가 서버에 데이터를 요청
  - 서버가 헤더에 cache-control를 통해 캐시 유효 시간을 설정하고 Last-Modified 설정하고 클라이언트에 응답
  - 클라이언트는 브라우저 캐시에 응답 결과를 저장
  - 클라이언트는 캐시 시간이 초과하기 전까지 캐시에서 데이터를 읽음
  - 캐시 시간이 초과된 경우 if-modified-since의 Last-Modified 값을 넣고 조건부 요청으로 304와 바디가 없는 헤더 메타 정보를 리턴 받거나 새로운 데이터를 리턴 받음

#### 검증 헤더와 조건부 요청
- 일반적인 캐시
  - If-Modified-Since와 Last-Modified를 같이 사용
  - 304 Not Modified + 헤더 메타 정보만 응답(바디X)
- 개선된 캐시
  - If-None-Match와 ETag를 같이 사용
  - 캐시용 데이터에 임의의 고유한 버전 이름을 달아두어 ETag만 보내서 같으면 유지, 다르면 다시 받기
  - 캐시 제어 로직을 서버에서 완전히 관리

#### 캐시와 조건부 요청 헤더
- 캐시 제어 헤더
  - Cache-Control: 캐시 제어 
  - Pragma: 캐시 제어, 하위 호환으로 거의 사용하지 않음
  - Expires: 캐시 유효 기간, 하위 호환으로 거의 사용하지 않음
- Cache-Control 캐시 지시어(directives)
  - Cache-Control: `max-age`, 캐시 유효 시간, 초 단위, 권장
  - Cache-Control: no-cache, 데이터는 캐시해도 되지만, 항상 `원(origin) 서버`에 검증하고 사용 
  - Cache-Control: no-store, 데이터에 민감한 정보가 있으므로 저장하면 안됨 (메모리에서 사용하고 최대한 빨리 삭제)
  - Cache-Control: public, 응답이 public 캐시에 저장되어도 됨 
  - Cache-Control: private, 응답이 해당 사용자만을 위한 것임, private 캐시에 저장해야 함(기본값) 
  - Cache-Control: s-maxage, 프록시 캐시에만 적용되는 max-age
- 검증 헤더 (Validator)
  - ETag: "v1.0", ETag: "asid93jkrh2l"
  - Last-Modified: Thu, 04 Jun 2020 07:19:24 GMT 
- 조건부 요청 헤더
  - If-Match, If-None-Match: ETag 값 사용
  - If-Modified-Since, If-Unmodified-Since: Last-Modified 값 사용

#### 프록시 캐시
- 원 서버
  - 클라이언트가 실제 비즈니스 로직을 처리하는 서버에 요청함
- 프록시 캐시 서버(CDN)
  - 클라이언트와 가까운 원 서버의 데이터를 캐싱한 프록시 캐시 서버에 요청함

#### 캐시 무효화
- 확실한 캐시 무효화가 필요한 이유
  - 캐시를 안해도 웹 브라우저에서 자동으로 캐싱하는 경우가 많음
- 확실한 캐시 무효화 응답
  - Cache-Control: no-cache, no-store, must-revalidate
  - Pragma: no-cache (하위 호환)
- no-cache와 must-revalidate
  - no-cache는 원 서버에 접근할 수 없는 경우 캐시 서버 설정에 따라서 오류를 반환하거나 캐시된 데이터를 반환할 수 있음
  - must-revalidate는 원 서버에 접근할 수 없는 경우, 항상 오류를 반환

