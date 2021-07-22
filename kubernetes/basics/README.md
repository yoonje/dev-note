# Kubernetes 정리 자료
[쿠버네티스 안내서](https://subicura.com/k8s/guide/#%E1%84%80%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%83%E1%85%B3)과 도커/쿠버네티스를 활용한 컨테이너 개발 실전 입문(야마다 아키노리)를 정리하여 만들었습니다.

Table of contents
=================
<!--ts-->
   * [Container Orchestration](#Container-Orchestration)
   * [Kubernetes](#Kubernetes)
   * [Kubernetes Architecture](#Kubernetes-Architecture)
   * [Installation](#Installation)
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

