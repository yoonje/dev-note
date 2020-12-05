# Nginx 주요 설정 정리
`CentOS 7`를 기준으로 한 Nginx 주요 설정 정리

### Nginx 관련 설정 파일 목록
* nginx.conf: 기본 환경 설정
* mime.types: 파일 확장명과 MIME 타입 목록
* fastcgi.conf: FastCGI 관련 설정
* proxy.conf: 프록시 관련 설정
* sites.conf: 엔진엑스에 의해 서비스되는 가상 호스트 웹사이트의 설정, 도메인마다 파일을 분리할 것을 권장

### Nginx.conf Default
```conf
server {
    listen       80;
    server_name  localhost;

    #charset koi8-r;
    #access_log  /var/log/nginx/host.access.log  main;

    location / {
        root   /usr/share/nginx/html;
        index  index.html index.htm;
    }

    #error_page  404              /404.html;

    # redirect server error pages to the static page /50x.html
    #
    error_page   500 502 503 504  /50x.html;
    location = /50x.html {
        root   /usr/share/nginx/html;
    }

    # proxy the PHP scripts to Apache listening on 127.0.0.1:80
    #
    #location ~ \.php$ {
    #    proxy_pass   http://127.0.0.1;
    #}

    # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
    #
    #location ~ \.php$ {
    #    root           html;
    #    fastcgi_pass   127.0.0.1:9000;
    #    fastcgi_index  index.php;
    #    fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
    #    include        fastcgi_params;
    #}

    # deny access to .htaccess files, if Apache's document root
    # concurs with nginx's one
    #
    #location ~ /\.ht {
    #    deny  all;
    #}
}
```

### server block 설정 (http)
* listen: nginx가 응답을 받을 포트 번호
* location: 처리할 URI 형식
  * proxy_pass: nginx 뒤에 WAS가 있는 경우 요청을 넘길 WAS
  * allow: 접근 가능한 호스트 지정
  * deny: 무시할 호스트 지정
  * root: / url에서 redirect할 경로
  * index: index 파일 리스트
* log_format: 엑세스 로그의 형식 지정
* access_log: 엑세스 로그를 남길 파일 경로 지정
* error_log: 에러 로그를 남길 파일 경로 지정
* sendfile: sendfile api 를 사용할지 말지 결정
* keepalive_timeout: 접속시 커넥션을 몇 초동안 유지할지에 대한 설정값. 이 값이 높으면 불필요한 커넥션을 유지하기 때문에 낮은값 또는 0을 권장


### 고급 설정
* event block: 비동기 이벤트 처리에 대한 옵션을 설정하는 블록
  * worker_connections: 나의 프로세스가 처리할 수 있는 커넥션의 수를 의미
* upstream block: proxy_pass 지시자를 통해 nginx가 받은 리퀘스트를 넘겨줄 서버들을 정의하는 블록
  * server: upstream 안에서 리퀘스트를 받을 서버
  * keepalive: nginx와 리퀘스트를 넘겨 받을 서버 받을 서버 간의 최대 TCP 커넥션 개수
* user: nginx 프로세스가 실행되는 권한, `user root root`가 디폴트 값인데 보안 상 문제가 될 수 있으므로 수정 필요
* worker_process: nginx 프로세스 실행 개수 수, `worker_processes 1`가 디폴트 값인데 CPU 개수와 서버의 환경에 따라 수정 필요
* worker_connections: 서버가 동시에 수용할 수 있는 전체 접속 수, `worker_connections 1024`가 디폴트 값인데 CPU 개수와 서버의 환경에 따라 수정 필요
* worker_priority: -5(커널의 기본 우선순위)~19까지의 작업자 우선순위, `worker_priority 0`가 디폴트 값인데 엔진엑스 작업자 프로세스에 더 높은 우선순위를 부여
cf) work_process * work_connection = 동시 접속 처리 개수