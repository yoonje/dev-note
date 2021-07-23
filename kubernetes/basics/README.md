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
