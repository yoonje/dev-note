# Kubernetes 정리 자료
[쿠버네티스 안내서](https://subicura.com/k8s/guide/#%E1%84%80%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%83%E1%85%B3)과 도커/쿠버네티스를 활용한 컨테이너 개발 실전 입문(야마다 아키노리)를 정리하여 만들었습니다.

Table of contents
=================
<!--ts-->
   * [Container Orchestration](#Container-Orchestration)
   * [Kubernetes](#Kubernetes)
   * [Kubernetes Architecture](#Kubernetes-Architecture)
   * [Kubernetes Object](#Kubernetes-Object)
   * [Command](#Command)
   * [Pod](#Pod)
   * [ReplicaSet](#ReplicaSet)
   * [Deployment](#Deployment)
   * [Service](#Service)
   * [Ingress](#Ingress)
   * [Volume](#Volume)
   * [ConfigMap](#ConfigMap)
   * [Secret](#Secret)
<!--te-->

Container Orchestration
=======
- 배경: 도커와 컨테이너의 장점으로 인해 유행을 하게 되어 모든 프로그램을 컨테이로 개발을 하게 되니, 컨테이너와 컨테이너를 동작시키는 서버가 너무 많아지게 되어 컨테이너를 관리하는 기술이 필요
- 컨테이너 오케스트레이션 툴의 역할
  - `중앙에서` 용량을 적게 먹고 있는 서버 검색
  - `중앙에서` 배포를 하여 배포 및 롤백을 편하게 함
  - `중앙에서` 컨테이너의 이상 및 부하 모니터링
- 컨테이너 오케스트레이션 툴의 특징
  - 컨테이너 중앙 제어(클러스터)
  - 컨테이너 네트워킹(클러스터)
  - 노드 스테일(클러스터)
  - 컨테이너 상태 관리(상태)
  - 컨테이너 배포 관리(스케줄링)
  - 컨테이너 배포 버전 관리(롤 아웃, 롤백)
  - 서비스 등록 및 조회(서비스 디스커버리)
  - 볼륨 스토리지

Kubernetes
=======
- 쿠버네티스: 컨테이너화된 애플리케이션을 자동으로 배포, 스케일링 및 관리하기 위해서 컨테이너를 쉽게 관리하고 연결하기 위해 논리적인 단위로 그룹화하는 오픈소스
- 쿠버네티스 용어
  - master: 쿠버
  - node: 마스터 서버와 통신하면서 필요한 Pod을 생성하고 네트워크와 볼륨을 설정하는 서버
  - kubectl: 쿠버네티스 API 서버에 명령을 전달하는 명령행 도구
  - etcd: 모든 상태와 데이터를 저장하는 곳
  - pod: 쿠버네티스에서 `배포할 수 있는 컨테이너 집합 단위` 중의 가장 작은 단위
  - istio: API 등을 사용하여 마이크로 서비스 간 통신을 안전하고 빠르고 신뢰할 수 있게 만들기 위해 설계된 전용 인프라 계층인 서비스 메쉬(Service Mesh)를 구현할 수 있는 오픈소스
  - helm: 
  - kubelet: 노드에 할당된 Pod의 생명주기를 관리하고 Pod을 생성하고 Pod 안의 컨테이너에 이상이 없는지 확인하면서 주기적으로 마스터에 상태를 전달하는 모듈
  - kube-proxy: 큐블릿이 Pod을 관리한다면 프록시는 Pod으로 연결되는 네트워크를 관리하는 모듈
- kubernetes를 통해 Wordpress 컨테이너 만들기
  - yml 파일 정의
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
  name: wordpress-mysql
    labels:
      app: wordpress
  spec:
    selector:
      matchLabels:
        app: wordpress
        tier: mysql
    template:
      metadata:
        labels:
          app: wordpress
          tier: mysql
      spec:
        containers:
          - image: mysql:5.6
            name: mysql
            env:
              - name: MYSQL_ROOT_PASSWORD
                value: password
            ports:
              - containerPort: 3306
                name: mysql

  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: wordpress-mysql
    labels:
      app: wordpress
  spec:
    ports:
      - port: 3306
    selector:
      app: wordpress
      tier: mysql

  ---
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: wordpress
    labels:
      app: wordpress
  spec:
    reaplicas : 2
    selector:
      matchLabels:
        app: wordpress
        tier: frontend
    template:
      metadata:
        labels:
          app: wordpress
          tier: frontend
      spec:
        containers:
          - image: wordpress:5.5.3-apache
            name: wordpress
            env:
              - name: WORDPRESS_DB_HOST
                value: wordpress-mysql
              - name: WORDPRESS_DB_PASSWORD
                value: password
            ports:
              - containerPort: 80
                name: wordpress

  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: wordpress
    labels:
      app: wordpress
  spec:
    type: NodePort
    ports:
      - port: 80
    selector:
      app: wordpress
      tier: frontend
  ```
  - 실행하기
  ```sh
  $ kubectl apply -f wordpress-k8s.yml
  ```
  - 상태 확인하기
  ```sh
  $ kubectl get all
  ```
  - 접속하기 위한 IP 얻기
  ```sh
  $ minikube ip
  ```
  - 강제로 컨테이너를 죽여서 오토 힐링 확인하기
  ```sh
  $ kubectl delete pod/wordpress-{해쉬 값}
  ```
  - 상태 확인하기
  ```sh
  $ kubectl get all
  ```
  - 컨테이너 스케일 아웃하기 위해 yml 파일에 reaplicas 추가
  ```yml
    spec:
      reaplicas : 2  # 추가
      selector:
  ```
  - 실행하기
  ```sh
  $ kubectl apply -f wordpress-k8s.yml
  ```
  - 상태 확인하기
  ```sh
  $ kubectl get all
  ```

Kubernetes Architecture
=======
- Desired State
  - 쿠버네티스는 현재 상태와 원하는 상태를 비교하여 원하는 상태를 유지하는 오픈소스로써 `상태 체크` -> `차이점 발견` -> `조치`
- 구조
  - 마스터
    - etcd: 모든 상태와 데이터를 저장하는 곳
      - 분산 시스템으로 구성하여 안전성을 높임 (고가용성)
      - 가볍고 빠르면서 정확하게 설계 (일관성) 
      - Key(directory)-Value 형태로 데이터 저장 
      - TTL(time to live), watch같은 부가 기능 제공
    - API server: 상태를 바꾸거나 조회 모듈로 etcd와 유일하게 통신함
      - REST API 형태로 제공
      - 권한을 체크하여 적절한 권한이 없을 경우 요청을 차단
      - 관리자 요청 뿐 아니라 다양한 내부 모듈과 통신
      - 수평으로 확장되도록 디자인
    - Scheduler: 새로 생성된 Pod을 감지하고 실행할 노드를 선택
      - 노드의 현재 상태와 Pod의 요구사항을 체크
    - Controller: 끊임 없이 상태를 체크하고 원하는 상태를 유지
      - 논리적으로 다양한 종류의 컨트롤러가 존재
  - 노드
    - kubelet: 노드에서 실행되는 프로그램으로 Pod을 실행/중지하고 상태를 체크
    - proxy: 네트워크 프록시와 부하 분산 역할을 하는데 프록시 프로그램 대신 iptables 또는 IPVS를 사용
- 파드 생성으로 보는 흐름
  - 1. 사용자 -> API Server에 Pod 요청
  - 2. API Server etcd에 Pod 생성
  - 3. API Server와 Controller 새 Pod 확인 및 할당
  - 4. API Server etcd에 Pod 할당
  - 5. API Server Scheduler에 새 Pod 할당 확인 및 노드 확인
  - 6. API Server etcd에 노드 할당
  - 7. API Server 노드의 Kublet에 미실행 Pod 확인
  - 8. API Server 노드에 파드 생성
  - 9. API Server etcd에 노드 생성

Kubernetes Object
=======
- Pod: 가장 작은 배포 단위
  - 전체 클러스터에서 고유한 IP를 할당
  - 여러개의 컨테이너가 하나의 Pod에 속할 수 있음
- ReplicaSet
  - 여러개의 Pod을 관리
  - 새로운 Pod은 Template을 참고하여 생성
  - 신규 Pod을 생성하거나 기존 Pod을 제거하여 원하는 수(Replicas)를 유지
- Deployment
  - 배포 버전을 관리
  - 내부적으로 ReplicaSet을 이용
- Service - ClusterIP
  - 클러스터 내부에서 사용하는 프록시
  - Pod은 동적이지만 서비스는 고유 IP를 가짐
  - 클러스터 내부에서 서비스 연결은 DNS를 이용
- Service - NodePort
  - 노드(host)에 노출되어 외부에서 접근 가능한 서비스
  - 모든 노드에 동일한 포트로 생성
- Service - LoadBalancer
  - 하나의 IP주소를 외부에 노출
- Ingress
  - 도메인 또는 경로별 라우팅
- Volume 
  - Storage
- Namespace: 논리적인 리소스 구분
- ConfigMap/Secret 
  - 설정
- ServiceAccount 
  - 권한 계정
- Role/ClusterRole 
  - 권한 설정
- 오브젝트 스팩: 오브젝트의 특성 (설정정보)을 기술
  - apiVersion
    - apps/v1, v1, batch/v1, networking.k8s.io/v1, ...
  - kind
    - Pod, Deployment, Service, Ingress, ...
  - metadata
    - name, label, namespace, ...
  - spec
    - 각종 설정 (https://kubernetes.io/docs/reference/generated/kubernetes-api/v1.18)
  - status(read-only)
   - 시스템에서 관리하는 최신 상태

- 필수 요소

| 정의 | 설명| 예 |
|------|-----|-----|
|version|오브젝트 버전| v1, app/v1 |
|kind|종류|Pod, ReplicaSet, Deployment, Service|
|metadata|메타데이터|name과 label, annotation(주석)으로 구성|
|spec| 상세, 명세|리소스 종류마다 다름|

Command
=======
- kubectl 명령어 Overview

|명령어 | 설명|
|------|-----|
|apply|원하는 상태를 적용합니다. 보통 -f 옵션으로 파일과 함께 사용합니다.|
|get|리소스 목록을 보여줍니다.|
|describe|리소스의 상태를 자세하게 보여줍니다.|
|delete|리소스를 제거합니다.|
|logs|컨테이너의 로그를 봅니다.|
|exec|컨테이너에 명령어를 전달합니다. 컨테이너에 접근할 때 주로 사용합니다.|
|config|kubectl 설정을 관리합니다.|

- apply
  - `$ kubectl apply -f [파일명 또는 URL]`
  - -f 옵션에 파일명뿐 아니라 URL도 입력이 가능
- get
  - `$ kubectl get [TYPE]`
  - 탑인은 pod, service 등등이 들어갈 수 있음
  - `-o`는 출력 형태를 변경할 수 있고 `--show-labels`는 레이블을 확인할 수 있음
- describe
  - `$ kubectl describe [TYPE]/[NAME] 또는 [TYPE] [NAME]`
  - 특정 리소스의 상태가 궁금하거나 생성이 실패한 이유를 확인할 때 주로 사용
- delete
  - `$ kubectl delete [TYPE]/[NAME] 또는 [TYPE] [NAME]` 
  - 쿠버네티스에 선언된 리소스를 제거
- logs
  - `$ kubectl logs [POD_NAME]`
  - 실시간 로그를 보고 싶다면 -f 옵션을 이용하고 하나의 Pod에 여러 개의 컨테이너가 있는 경우는 -c 옵션으로 컨테이너를 지정
- exec
  - `$ kubectl exec [-it] [POD_NAME] -- [COMMAND]`
  - 쉘로 접속하여 컨테이너 상태를 확인하는 경우에 -it 옵션을 사용하고 여러 개의 컨테이너가 있는 경우엔 -c 옵션으로 컨테이너를 지정
- config
  - `$ kubectl config current-context`: 현재 컨텍스트 확인
  - `$ kubectl config use-context minikube`: 컨텍스트 설정
- 이 외
  - `$ kubectl api-resources`: 전체 오브젝트 종류 확인
  - `$ kubectl explain pod`: 오브젝트 설명 보기

Pod
=======
- Pod: Pod은 쿠버네티스에서 관리하는 가장 작은 배포 단위로 쿠버네티스는 컨테이너가 들어있는 Pod을 통해서 컨테이너들을 관리
- 빠르게 Pod 만들기
  - Pod 만들고 실행: `$ kubectl run echo --image ghcr.io/subicura/echo:v1`
  - Pod 목록 조회: `$ kubectl get pod`
  - 단일 Pod 상세 확인: `$ kubectl describe pod/echo`
  - Pod 로그 확인: `$ kubectl logs echo`
  - Pod 로그 계속 확인: `$ kubectl logs -f echo`
  - Pod 컨테이너 접속: `$ kubectl exec -it echo -- sh`
  - 단일 Pod 제거: `$ kubectl delete pod/echo`
- yml 파일로 Pod 만들기
  - 설정 파일(echo-pod.yml)
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: echo
    labels:
      app: echo
  spec:
    containers:
      - name: app
        image: ghcr.io/subicura/echo:v1
  ```
  - Pod 만들고 실행: `$ kubectl apply -f echo-pod.yml`
  - Pod 목록 조회: `$ kubectl get pod`
  - Pod 제거: `$ kubectl delete -f echo-pod.yml`
- Pod 생성 및 실행 분석
  - Scheduler는 API서버를 감시하면서 할당되지 않은 unassigned Pod이 있는지 체크
  - Scheduler는 할당되지 않은 Pod을 감지하고 적절한 노드 node에 할당 (minikube는 단일 노드)
  - 노드에 설치된 kubelet은 자신의 노드에 할당된 Pod이 있는지 체크
  - kubelet은 Scheduler에 의해 자신에게 할당된 Pod의 정보를 확인하고 컨테이너 생성
  - kubelet은 자신에게 할당된 Pod의 상태를 API 서버에 전달
- `컨테이너 상태 모니터링`
  - livenessProbe: 헬스체크를 계속 진행하고, 동작하지 않으면 컨테이너를 재시작
    - 설정 파일
    ```yml
    apiVersion: v1
    kind: Pod
    metadata:
      name: echo-lp
      labels:
        app: echo
    spec:
      containers:
        - name: app
          image: ghcr.io/subicura/echo:v1
          livenessProbe:
            httpGet: # 특정 경로와 포트로 http get 요청을 보내 확인하는 방법 사용
              path: /not/exist
              port: 8080
            initialDelaySeconds: 5
            timeoutSeconds: 2 # Default 1
            periodSeconds: 5 # Defaults 10
            failureThreshold: 1 # Defaults 3
    ```
  - readinessProbe: 헬스체크를 계속 진행하고, 동작하지 않으면 Pod으로 들어오는 요청을 제외
    - 설정 파일
    ```yml
    apiVersion: v1
    kind: Pod
    metadata:
      name: echo-rp
      labels:
        app: echo
    spec:
      containers:
        - name: app
          image: ghcr.io/subicura/echo:v1
          readinessProbe:
            httpGet:
              path: /not/exist
              port: 8080
            initialDelaySeconds: 5
            timeoutSeconds: 2 # Default 1
            periodSeconds: 5 # Defaults 10
            failureThreshold: 1 # Defaults 3
    ```
    - livenessProbe와 readinessProbe를 같이 적용
      - 설정 파일
      ```yml
      apiVersion: v1
      kind: Pod
      metadata:
        name: echo-health
        labels:
          app: echo
      spec:
        containers:
          - name: app
            image: ghcr.io/subicura/echo:v1
            livenessProbe:
              httpGet:
                path: /
                port: 3000
            readinessProbe:
              httpGet:
                path: /
                port: 3000
      ```
- `다중 컨테이너`
  - 대부분 1 Pod = 1 컨테이너지만 여러 개의 컨테이너를 띄워서 Pod에 속한 컨테이너는 서로 네트워크 localhost로 공유시키고 동일한 디렉토리를 공유 시킬 수 있음
  - 설정 파일
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: counter
    labels:
      app: counter
  spec:
    containers:
      - name: app
        image: ghcr.io/subicura/counter:latest
        env: # 환경 변수 추가
          - name: REDIS_HOST
            value: "localhost"
      - name: db
        image: redis
  ```

ReplicaSet
=======
- ReplicaSet: label을 체크해서 원하는 수의 Pod이 없으면 새로운 Pod을 생성
- ReplicaSet 만들기
  - 설정 파일(echo-rs.yml)
  ```yml
  apiVersion: apps/v1
  kind: ReplicaSet
  metadata:
    name: echo-rs
  spec:
    replicas: 1 # 원하는 Pod 개수
    selector: # label 체크 조건
      matchLabels:
        app: echo
        tier: app
    template: # 없으면 생성할 Pod의 명세
      metadata:
        labels:
          app: echo
          tier: app
      spec:
        containers:
          - name: echo
            image: ghcr.io/subicura/echo:v1
  ```
  - ReplicaSet 생성: `$ kubectl apply -f echo-rs.yml`
  - Pod 확인: `$ kubectl get po,rs`
  - 레이블 확인: `$ kubectl get pod --show-labels`
  - app label을 제거: `$ kubectl label pod/echo-rs-tcdwj app-`
  - 레이블을 포함하여 Pod 확인: `$ kubectl get pod --show-labels`
- ReplicaSet 생성 및 실행 분석
  - ReplicaSet Controller는 ReplicaSet 조건을 감시하면서 현재 상태와 원하는 상태가 다른 것을 체크
  - ReplicaSet Controller가 원하는 상태가 되도록 Pod을 생성하거나 제거
  - Scheduler는 API서버를 감시하면서 할당되지 않은 Pod이 있는지 체크
  - Scheduler는 할당되지 않은 새로운 Pod을 감지하고 적절한 노드에 배치
  - 이후 노드는 기존대로 동작
- 스케일 아웃
  - replicas 개수를 늘려서 Pod을 여러개로 복제할 수 있음 (보통 ReplicaSet을 직접 사용하기 보단 Deployment를 이용해서 사용)
  - 설정 파일
  ```yml
  apiVersion: apps/v1
  kind: ReplicaSet
  metadata:
    name: echo-rs
  spec:
    replicas: 4 # 원하는 Pod 개수
    selector:
      matchLabels:
        app: echo
        tier: app
    template:
      metadata:
        labels:
          app: echo
          tier: app
      spec:
        containers:
          - name: echo
            image: ghcr.io/subicura/echo:v1
  ```

Deployment
=======
- Deployment: ReplicaSet을 이용하여 Pod을 업데이트하고 이력을 관리하여 롤백하거나 특정 버전으로 돌아갈 때 사용하며 Deployment는 `Deployment Controller`가 관리하고 ReplicaSet과 Pod은 기존 `Controller와 Scheduler`가 관리(replicas에 엤는 pod를 하나씩 버전업)
- Deployment 만들기(echo-deployment.yml)
  - 설정 파일
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: echo-deploy
  spec:
    replicas: 4
    selector:
      matchLabels:
        app: echo
        tier: app
    template:
      metadata:
        labels:
          app: echo
          tier: app
      spec:
        containers:
          - name: echo
            image: ghcr.io/subicura/echo:v1
  ```
  - Deployment 생성 및 실행: `$ kubectl apply -f echo-deployment.yml`
  - 리소스 확인: `$ kubectl get po,rs,deploy`
  - 컨테이너 버전 수정하고 재실행: `$ kubectl apply -f echo-deployment.yml`
  - 리소스 확인: `$ kubectl get po,rs,deploy`
- Deployment 실행 및 분석
  - Deployment Controller는 Deployment 조건을 감시하면서 현재 상태와 원하는 상태가 다른 것을 체크
  - Deployment Controller가 원하는 상태가 되도록 ReplicaSet 설정
  - ReplicaSet Controller는 ReplicaSet 조건을 감시하면서 현재 상태와 원하는 상태가 다른 것을 체크
  - ReplicaSet Controller가 원하는 상태가 되도록 Pod을 생성하거나 제거
  - Scheduler는 API 서버를 감시하면서 할당되지 않은 Pod이 있는지 체크
  - Scheduler는 할당되지 않은 새로운 Pod을 감지하고 적절한 노드에 배치
  - 이후 노드는 기존대로 동작
- 버전 관리
  - 히스토리 확인: `$ kubectl rollout history deploy/echo-deploy`
  - revision 1 히스토리 상세 확인: `$ kubectl rollout history deploy/echo-deploy --revision=1`
  - 바로 전으로 롤백: `$ kubectl rollout undo deploy/echo-deploy`
  - 특정 버전으로 롤백: `$ kubectl rollout undo deploy/echo-deploy --to-revision=2`
- 배포 전력 설정
  - 설정 파일(echo-strategy.yml)
  ```yml
  apiVersion: apps/v1
  kind: Deployment  
  metadata:
    name: echo-deploy-st
  spec:
    replicas: 4
    selector:
      matchLabels:
        app: echo
        tier: app
    minReadySeconds: 5
    strategy: # 배포 전략
      type: RollingUpdate
      rollingUpdate:
        maxSurge: 3
        maxUnavailable: 3
    template:
      metadata:
        labels:
          app: echo
          tier: app
      spec:
        containers:
          - name: echo
            image: ghcr.io/subicura/echo:v2
            livenessProbe:
              httpGet:
                path: /
                port: 3000
  ```
  - Watch 옵션으로 리플리카셋 변화 확인: `$ kubectl get rs -w`
  - Deployment 생성 및 실행: `$ kubectl apply -f echo-strategy.yml`

Service
=======
- `ClusterIP(Service)`: Pod은 자체 IP를 가지고 다른 Pod과 통신할 수 있지만, 쉽게 사라지고 생성되는 특징 때문에 직접 통신하는 방법은 권장되지 않아서 k8s는 Pod과 직접 통신하는 방법 대신에 `별도의 고정된 IP를 가진 서비스를 만들고 그 서비스를 통해 Pod 안에서 다른 Pod들과 접근하는 방식 사용`
- ClusterIP(Service) 만들기
  - 설정 파일(counter-redis-svc.yml, counter-app.yml)
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: redis
  spec:
    selector:
      matchLabels:
        app: counter
        tier: db
    template:
      metadata:
        labels:
          app: counter
          tier: db
      spec:
        containers:
          - name: redis
            image: redis
            ports:
              - containerPort: 6379
                protocol: TCP

  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: redis
  spec:
    ports:
      - port: 6379 # 서비스가 생성할 Port
        targetPort: 6379 # 서비스가 접근할 Pod의 Port
        protocol: TCP
    selector: # 서비스가 접근할 Pod의 label 조건
      app: counter
      tier: db
  ```
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: counter
  spec:
    selector:
      matchLabels:
        app: counter
        tier: app
    template:
      metadata:
        labels:
          app: counter
          tier: app
      spec:
        containers:
          - name: counter
            image: ghcr.io/subicura/counter:latest
            env:
              - name: REDIS_HOST
                value: "redis"
              - name: REDIS_PORT
                value: "6379"
  ```
  - 서비스 생성 및 실행: `$ kubectl apply -f counter-redis-svc.yml`
  - counter app Deployment 생성 및 실행: `$ kubectl apply -f counter-app.yml`
  - Pod, ReplicaSet, Deployment, Service 상태 확인: `$ kubectl get all`
  - counter app에 접근: `$ kubectl exec -it counter-<xxxxx> -- sh`
  - counter app Pod에서 redis Pod으로 접근이 되는지 테스트
- Service(ClusterIP) 생성 흐름
  - Endpoint Controller는 Service와 Pod을 감시하면서 조건에 맞는 Pod의 IP를 수집
  - Endpoint Controller가 수집한 IP를 가지고 Endpoint 생성
  - Kube-Proxy는 Endpoint 변화를 감시하고 노드의 iptables을 설정
  - CoreDNS는 Service를 감시하고 서비스 이름과 IP를 CoreDNS에 추가
- `NodePort(Service)`: CluterIP는 클러스터 내부에서만 접근할 수 있어서 클러스터 외부(노드)에서 접근할 수 있도록 NodePort 서비스가 존재
- NodePort(Service) 만들기
  - ClusterIP(Service) 및 앱 실행
    - `$ kubectl apply -f counter-redis-svc.yml`
    - `$ kubectl apply -f counter-app.yml`
  - 설정 파일
  ```yml
  apiVersion: v1
  kind: Service
  metadata:
    name: counter-np
  spec:
    type: NodePort # 서비스의 타입 NodePort으로 지정
    ports:
      - port: 3000
        protocol: TCP
        nodePort: 31000 # 노드에 오픈할 Port
    selector: # 서비스가 접근할 Pod의 label 조건
      app: counter
      tier: app
  ```
  - 서비스 생성 및 실행: `$ kubectl apply -f counter-nodeport.yml`
  - 서비스 상태 확인: `$ kubectl get svc`
- Service(LoadBalancer): NodePort의 단점은 노드가 사라졌을 때 자동으로 다른 노드를 통해 접근이 불가능하므로 자동으로 살아 있는 노드에 접근하기 위해 모든 노드를 바라보는 Load Balancer를 사용하여 NodePort에 직접 요청을 보내는 것이 아니라 Load Balancer에 위임하여 Pod에 접근
- Service(LoadBalancer) 만들기
  - ClusterIP(Service) 및 앱 실행
    - `$ kubectl apply -f counter-redis-svc.yml`
    - `$ kubectl apply -f counter-app.yml`
  - 설정 파일(counter-lb.yml)
  ```yml
  apiVersion: v1
  kind: Service
  metadata:
    name: counter-lb
  spec:
    type: LoadBalancer
    ports:
      - port: 30000
        targetPort: 3000
        protocol: TCP
    selector:
      app: counter
      tier: app
  ```
  - 서비스 생성 및 실행: `$ kubectl apply -f counter-lb.yml`


Ingress
=======
- Ingress: 하나의 클러스터에서 여러 가지 서비스를 운영한다면 외부 연결을 할 때 NodePort를 이용하면 서비스 개수만큼 포트를 오픈하고 사용자에게 어떤 포트인지 알려줘야하므로 Ingress를 통해서 포트를 하나만 Open하고 도메인이나 경로를 통해서 서비스를 분기
- Ingress 만들기
  - 설정 파일(echo-v1.yml, echo-v2.yml)
  ```yml
  apiVersion: networking.k8s.io/v1
  kind: Ingress
  metadata:
    name: echo-v1
  spec:
    rules:
      - host: v1.echo.{쿠버네티스 주소}.sslip.io # 도메인
        http:
          paths:
            - path: /
              pathType: Prefix
              backend:
                service:
                  name: echo-v1 # 서비스 지정
                  port:
                    number: 3000

  ---
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: echo-v1
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: echo
        tier: app
        version: v1
    template:
      metadata:
        labels:
          app: echo
          tier: app
          version: v1
      spec:
        containers:
          - name: echo 
            image: ghcr.io/subicura/echo:v1
            livenessProbe:
              httpGet:
                path: /
                port: 3000

  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: echo-v1
  spec:
    ports:
      - port: 3000
        protocol: TCP
    selector:
      app: echo
      tier: app
      version: v1
  ```
  ```yml
  apiVersion: networking.k8s.io/v1
  kind: Ingress
  metadata:
    name: echo-v2
  spec:
    rules:
      - host: v2.echo.{쿠버네티스 주소}.sslip.io # 도메인 지정
        http:
          paths:
            - path: /
              pathType: Prefix
              backend:
                service:
                  name: echo-v2 # 서비스 지정
                  port:
                    number: 3000

  ---
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: echo-v2
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: echo
        tier: app
        version: v2
    template:
      metadata:
        labels:
          app: echo
          tier: app
          version: v2
      spec:
        containers:
          - name: echo
            image: ghcr.io/subicura/echo:v2
            livenessProbe:
              httpGet:
                path: /
                port: 3000

  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: echo-v2
  spec:
    ports:
      - port: 3000
        protocol: TCP
    selector:
      app: echo
      tier: app
      version: v2
  ```
  - Ingree 생성 및 실행: `$ kubectl apply -f echo-v1.yml,echo-v2.yml`
- Ingree 생성 흐름
  - Ingress Controller는 Ingress 변화를 체크
  - Ingress Controller는 변경된 내용을 Nginx에 설정하고 프로세스 재시작



Volume
=======
- Volume: 컨테이너는 Pod을 제거하면 컨테이너 내부에 저장했던 데이터도 모두 사라지므로 별도의 저장소에 데이터를 저장하고 컨테이너를 새로 만들 때 이전 데이터를 가져와야해서 Volume을 이용하여 컨테이너의 디렉토리를 다른 저장소와 연결
- 가상 디렉토리를 통한 Volume 만들기
  - 설정 파일(empty-dir.yml)
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: sidecar
  spec:
    containers:
      - name: app # 컨테이너 1
        image: busybox
        args:
          - /bin/sh
          - -c
          - >
            while true;
            do
              echo "$(date)\n" >> /var/log/example.log;
              sleep 1;
            done
        volumeMounts:
          - name: varlog
            mountPath: /var/log
      - name: sidecar # 컨테이너 2
        image: busybox
        args: [/bin/sh, -c, "tail -f /var/log/example.log"]
        volumeMounts: # 볼륨 마운트
          - name: varlog
            mountPath: /var/log # 컨테이너들이 공유하는 가상의 경로
    volumes:
      - name: varlog
        emptyDir: {}
  ```
  - Volume 생성 및 실행: `$ kubectl apply -f empty-dir.yml`
- hostpath Volume 만들기
  - 설정 파일(hostpath.yml)
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: host-log
  spec:
    containers:
      - name: log
        image: busybox
        args: ["/bin/sh", "-c", "sleep infinity"]
        volumeMounts:
          - name: varlog
            mountPath: /host/var/log
    volumes:
      - name: varlog
        hostPath:
          path: /var/log
  ```
  - Volume 생성 및 실행: `$ kubectl apply -f hostpath.yml`
  - 컨테이너 접속: `$ kubectl exec -it host-log -- sh`
  - (접속된 상태에서) /host/var/log 디렉토리를 확인: `$ ls -al /host/var/log`

ConfigMap
=======
- ConfigMap: 쿠버네티스에서 설정 파일과 환경 변수 관리하는 오브젝트
- ConfigMap 만들기1 - 설정 파일 자체를 마운트 하기
  - 설정 파일(config-file.yml, alphine.yml)
  ```yml
  global:
    scrape_interval: 15s

  scrape_configs:
    - job_name: prometheus
      metrics_path: /prometheus/metrics
      static_configs:
        - targets:
            - localhost:9090
  ```
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: alpine
  spec:
    containers:
      - name: alpine
        image: alpine
        command: ["sleep"]
        args: ["100000"]
        volumeMounts:
          - name: config-vol # 볼륨 이룸
            mountPath: /etc/config
    volumes:
      - name: config-vol
        configMap: # ConfigMap으로부터 볼륨 생성
          name: my-config # ConfigMap 이름
  ```
  - ConfigMap 생성: `$ kubectl create cm my-config --from-file=config-file.yml`
  - ConfigMap을 적용할 Pod 실행: `$ kubectl apply -f alphine.yml`
  - Pod 접속 후 설정 파일 확인: `$ kubectl exec -it alpine -- cat /etc/config/config-file.yml`

- ConfigMap 만들기2 - ConfigMap 내용을 마운트 하기
  - 설정 파일(config-map.yml, alphine.yml)
  ```yml
  apiVersion: v1
  kind: ConfigMap
  metadata:
    name: my-config
  data:
    hello: world
    kuber: netes
    multiline: |-
      first
      second
      third
  ```
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: alpine
  spec:
    containers:
      - name: alpine
        image: alpine
        command: ["sleep"]
        args: ["100000"]
        volumeMounts:
          - name: config-vol # 볼륨 이룸
            mountPath: /etc/config
    volumes:
      - name: config-vol
        configMap: # ConfigMap으로부터 볼륨 생성
          name: my-config
  ```
  - ConfigMap 생성: `$ kubectl apply -f config-map.yml`
  - ConfigMap을 적용할 Pod 실행: `$ kubectl apply -f alphine.yml`
  - Pod 접속 후 적용 내용 확인: `$ kubectl exec -it alpine -- cat /etc/config/multiline`
