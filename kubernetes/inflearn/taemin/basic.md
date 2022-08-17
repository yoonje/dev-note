# Kubernetes 정리 자료
대세는 쿠버네티스 강의를 정리하여 만들었습니다.

##### k8s version: 1.15 / docker version: 18.06.2 / dashboard version: 1.10.1

##### k8s Cluster Information: Master: 1, Node: 2

Table of Contents
=================
<!--ts-->
   * [Kubernetes Basis](#Kubernetes-Basis)
   * [Installation](#Installation)
   * [Object](#Object) 
   * [Controller](#Controller)
<!--te-->

Kubernetes Basis
=======
* `쿠버네티스`: 쿠버네티스는 컨테이너를 쉽고 빠르게 배포/확장하고 관리를 자동화해주는 컨테이너 오케스트레이션 오픈소스 플랫폼로 노드의 리소스 사용 현황 및 배치 전략을 근거로 컨테이너를 적절히 배치한다.
* `대시보드`: 쿠버네티스에 배포된 컨테이너 등에 대한 정보를 한눈에 보여주는 웹 기반의 관리 도구
* `쿠버네티스 클러스터`: 쿠버네티스의 리소스를 관리하기 위한 집합체
* `노드`: 쿠버네티스 클러스터의 관리 대상으로 등록된 도커 호스트로 컨테이너가 배치되는 대상
* 쿠버네티스의 특징
  * Ecosystem: 구글 기반으로 여러 회사들이 참여하여 만든 프로젝트로 생태계가 탄탄하다.
  * `Auto Scaling`: 트래픽 양의 따라 서비스 자원 양을 조절하여 배치하는 기능이 있어 효율적이다.
  * `Auto Healing`: 장애가 난 서비스를 다른 서버로 자동으로 배치하여 운영하는 기능이 있어 안정적이다.
  * 다양한 배포방식: 컨테이너 업데이트 시 `Deployment` 객체를 통해 배포를 자동적으로 처리하여 효율적으로 운영이 가능하고 `StatefulSets` 객체를 통해 실행 순서를 보장하고 호스트 이름과 볼륨을 일정하게 사용이 가능하다. 로그나 모니터링 등 모든 노드에 설치가 필요한 경우엔 `DaemonSet`을 이용하고 배치성 작업은 `Job`이나 `CronJob`을 이용한다.
  * 클라우드 자원과의 연동: 쿠버네티스는 Cloud Controller를 이용하여 클라우드와의 연동을 손쉽게 확장가능 하다.
  * RBAC(Role-based Access Control): 접근 권한 시스템으로 각각의 리소스에 대해 유저별로 CRUD스런 권한을 손쉽게 지정할 수 있다.
  * Federation, Multi Cluster: 클라우드에 설치한 쿠버네티스 클러스터와 자체 서버에 설치한 쿠버네티스를 묶어서 하나로 사용이 가능하다.
  * CRD (Custom Resource Definition): 쿠버네티스가 제공하지 않는 기능을 기본 기능과 동일한 방식으로 적용하고 사용할 수 있다.
* `쿠버네티스 오브젝트`
  * `Pod`: 쿠버네티스에서 `배포할 수 있는 컨테이너 집합 단위` 중의 가장 작은 단위로 한 개 이상의 컨테이너와 스토리지, 네트워크 속성을 가진다.
  * `ReplicaSet`: `Pod을 여러 개`(한 개 이상) 복제하여 관리하는 오브젝트이다. Pod을 생성하고 개수를 유지하려면 반드시 ReplicaSet을 사용한다.
  * `Service`: 네트워크와 관련된 오브젝트이다. Pod을 외부 네트워크와 연결해주고 여러 개의 Pod을 바라보는 `내부 로드 밸런서`를 생성할 때 사용한다.
  * `Volume`: 저장소와 관련된 오브젝트이다. 호스트 디렉토리를 그대로 사용할 수도 있고 EBS 같은 스토리지를 동적으로 생성하여 사용할 수도 있다.
* `쿠버네티스 컨트롤러`
  * `Auto Healing`: 파드나 노드가 다운되었을 때 컨트롤러에 의해 다른 노드에 파드를 만들어주는 기능
  * `Auto Scaling`: 파드에 리소스에 임계치에 도달했을 때 파드를 더 만들어줘서 부하 분산처리를 하는 기능
  * `Software Update`: 여러 파드에 대한 버전을 업그레이드 해야할 경우 업그레이드 버전을 만들고 스왑하여 한번에 업그레이드할 수 있는 기능
  * `Job`: 일시적인 작업을 해야할 경우 컨트롤러가 필요한 순간에만 파드를 만들고 작업하고 삭제하여 효율적으로 자원을 사용하는 기능
* `쿠버네티스 아키텍처`
  * 마스터 - 노드 구조: 쿠버네티스는 전체 클러스터를 관리하는 마스터와 컨테이너가 배포되는 노드로 구성되어 있다. 모든 명령은 마스터의 API 서버를 호출하고 노드는 마스터와 통신하면서 필요한 작업을 수행하고 마스터가 노드에 접속하여 결과를 응답한다.
  * `Master`: 마스터 서버는 다양한 모듈이 확장성을 고려하여 기능별로 쪼개져 있는 것이 특징이고 마스터가 죽으면 클러스터를 관리할 수 없다.
  * `Node`: 노드 서버는 마스터 서버와 통신하면서 필요한 Pod을 생성하고 네트워크와 볼륨을 설정한다.
  * kubectl: API 서버는 json 또는 protobuf 형식을 이용한 http 통신을 지원하지만 방식을 그대로 쓰면 불편하므로 보통 kubectl이라는 `명령행 도구`를 사용한다.
* Master의 구성 요소
  * `스케줄러(kube-scheduler)`: 스케줄러는 할당되지 않은 Pod을 여러 가지 조건(필요한 자원, 라벨)에 따라 적절한 노드 서버에 할당해주는 모듈
  * `큐브 컨트롤러(kube-controller-manager)`: 쿠버네티스에 있는 거의 모든 오브젝트의 상태를 관리하는 모듈
  * `클라우드 컨트롤러(cloud-controller-manager)`: 클라우드 컨트롤러는 AWS, GCE, Azure 등 클라우드에 특화된 모듈
* Node의 구성 요소
  * `큐블릿(kubelet)`: 노드에 할당된 Pod의 생명주기를 관리하고 Pod을 생성하고 Pod 안의 컨테이너에 이상이 없는지 확인하면서 주기적으로 마스터에 상태를 전달하는 모듈
  * `프록시(kube-proxy)`: 큐블릿이 Pod을 관리한다면 프록시는 Pod으로 연결되는 네트워크를 관리하는 모듈

Installation
=======
* 설치 방법
  * 클라우드 플랫폼을 이용하는 방법: GCP-GKE, AWS-EKS, Azure-AKS
  * On-premise에서 구축하는 방법: Ansible or Yum
* 선행 작업
  * 필수 패키지 설치
  ```sh
  $ yum install -y yum-utils device-mapper-persistent-data lvm2
  ```
  * 호스트 이름 설정
  ```sh
  $ hostnamectl set-hostname ${호스트이름}
  ```
* Docker 설치하기
  * 도커 설치를 위한 저장소 설정하기
  ```sh
  $ yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
  ```
  * 도커 설치
  ```sh
  $ yum update && yum install docker-ce-18.06.2.ce
  ```
* 도커 데몬 등록하기
  * 도커
  ```sh
  $ mkdir /etc/docker
  ```
  * 도커
  ```sh
  $ vi /etc/docker/daemon.json
  ```
  ```json
  {
    "exec-opts": ["native.cgroupdriver=systemd"],
    "log-driver": "json-file",
    "log-opts": {
      "max-size": "100m"
    },
    "storage-driver": "overlay2",
    "storage-opts": [
      "overlay2.override_kernel_check=true"
    ]
  }
  ```
  * 도커
  ```sh
  $ mkdir -p /etc/systemd/system/docker.service.d
  ```
* k8s 설치하기
  * 쿠버네티스 설치를 위한 저장소 설정하기
  ```sh
  $ vi /etc/yum.repos.d/kubernetes.repo
  ```
  ```yml
  [kubernetes]
  name=Kubernetes
  baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
  enabled=1
  gpgcheck=1
  repo_gpgcheck=1
  gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
  ```
  * 호스트 등록하기
  ```sh
  $ vi /etc/hosts
  ```
  ```yml
  # IP주소와 호스트 이름
  192.168.0.30 k8s-master
  192.168.0.31 k8s-node1
  192.168.0.32 k8s-node2
  ```
  * 쿠버네티스 설치하기
  ```sh
  $ yum install -y --disableexcludes=kubernetes kubeadm-1.15.5-0.x86_64 kubectl-1.15.5-0.x86_64 kubelet-1.15.5-0.x86_64
  ```
* 도커 & 쿠버네티스 실행 및 셋팅
  * 데몬 리로드
  ```sh
  $ systemctl daemon-reload
  ```
  * 도커 실행
  ```sh
  $ systemctl enable --now docker
  ```
  * 컨테이너 실행
  ```sh
  $ docker run ${컨테이너}
  ```
  * 쿠버네티스 실행
  ```sh
  $ systemctl enable --now kubelet
  ```
  * 쿠버네티스 초기화 명령
  ```sh
  $ kubeadm init --pod-network-cidr=20.96.0.0/12
  ```
  * 환경변수 설정
  ```sh
  $ mkdir -p $HOME/.kube
  ``` 
  ```sh
  $ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  ```
  ```sh
  $ sudo chown $(id -u):$(id -g) $HOME/.kube/config
  ```
  * Kubectl 자동완성 기능 설치
  ```sh
  $ yum install bash-completion -y
  ```
  ```sh
  $ source <(kubectl completion bash)
  ```
  ```sh
  $ echo "source <(kubectl completion bash)" >> ~/.bashrc
  ```
* Node 설정하기
  * 도커 실행
  ```sh
  $ systemctl daemon-reload
  ```
  ```sh
  $ systemctl enable --now docker
  ```
  * 쿠버네티스 실행
  ```sh
  $ systemctl enable --now kubelet
  ```
  * Master Init 후 복사 했었던 내용으로 Node 연결
  ```sh
  $ kubeadm join 192.168.0.30:6443 --token 7xd747.bfouwf64kz437sqs --discovery-token-ca-cert-hash sha256:ec75641cd258f2930a7f73abfe540bb484eb295ad4500ccdaa166208f97c5117
  ```
  * Node 연결 확인
  ```sh
  $ kubectl get nodes
  ```



Object
=======
* `Pod`
  * Pod: 파드는 하나의 독립적인 서비스를 구동할 수 있는 컨테이너 집합을 의미는데 한 파드 안의 컨테이너는 모두 같은 노드에 배치해야한다.
  * Pod 생성 및 활용: 파드는 .yaml 파일을 정의하여 생성하는 것이 일반적이고 kubectl 명령으로 생성 및 배포하고 삭제한다.
    1. yaml 파일 정의하기
    ```yaml
    apiVersion: v1  
    # 파일에서 정의하는 쿠버네티스 오브젝트 유형
    kind: Pod  
    # 메타데이터 정보
    metadata:  
      name: pod-1  
    # 쿠버네티스 오브젝트 유형에 대한 정보를 정의
    spec:  
      containers:
      # 컨테이너 이름  
      - name: container1
        # 도커 허브에 등록된 이미지 태그값  
        image: kubetm/p8000  
        # 컨테이너가 노출시킬 포트
        ports:  
        - containerPort: 8000  
      # 컨테이너 이름
      - name: container2  
        # 도커 허브에 등록된 이미지 태그값  
        image: kubetm/p8080  
        # 컨테이너가 노출시킬 포트
        ports:  
        - containerPort: 8080
    ```
    2. 파드 생성 및 배포하기  
    `$ kubectl apply -f {파드 이름}.yaml`
    3. 파드 상태 확인  
    `$ kubectl get pod`  
    4.  파드 안의 컨테이너에 접근  
    `$ kubectl exec -it {파드 이름} sh -c {컨테이너 이름}`
    5.  파드 삭제  
    `$ kubectl delete -f {파드 이름}.yaml`
  * Label: Pod 뿐만 아니라 여러 오브젝트에서 사용할 수 있는 개념으로 목적에 따라 오브젝트에 `key:value`방식으로 라벨을 달고 분리하여 이후 연결하기 위해서 사용한다. {오브젝트 이름}.yaml 파일 안에 `spec의 selector와 labels 옵션`을 통해 정의가 가능하다.
  * Node Schedule: 노드에 라벨을 달고 파드를 만들 때 노드를 지정할 때 사용한다. {오브젝트 이름}.yaml 파일 안에 `spec의 NodeSelector와 requests 옵션`을 통해 정의가 가능하다.
* `Service`
  * Service: 파드의 IP는 재생성 시에 동적으로 변경되기 때문에 고정적으로 파드에 접근하기 위한 경로를 정의하기 위해 Service를 정의한다.
  * Service 생성 및 활용:파드는 .yaml 파일을 정의하여 생성하는 것이 일반적이고 kubectl 명령으로 생성 및 배포하고 삭제한다.
    1. yaml 파일 정의하기
    ```yaml
    apiVersion: v1  
    # 파일에서 정의하는 쿠버네티스 오브젝트 유형
    kind: Service
    # 메타데이터 정보
    metadata:  
      name: svc-1  
    # 쿠버네티스 오브젝트 유형에 대한 정보를 정의
    spec:  
      selector:
        # 분산할 오브젝트의 이름 
        app: pod
        # 서비스의 포트  
        - port: 8000
          # 파드의 포트
          tartgetPort: 8080
        type: ClusterIP
    ```
    2. 서비스 생성 및 배포하기  
   `$ kubectl apply -f {서비스 이름}.yaml`
    4. 서비스 상태 확인  
    `$ kubectl get svc {서비스 이름}`
   * ClusterIP: 서비스의 종류 중 하나로 쿠버네티스 클러스터 내의 IP에서만 접근할 수 있는 IP로 여러 개의 파드를 연결하여 트래픽을 분산할 수 있다. Cluster 내에서 서비스로 접속하는 구조이다.
   * NodePort: 서비스의 종류 중 하나로 ClusterIP처럼 Cluster IP를 만들고 서비스가 파드로 트래픽을 분산하는 기능을 갖지만, NodePort는 쿠버네티스 클러스터 외부로 서비스를 공개할 수 있다. 외부에서 어떤 노드로 접근하든지 하나의 서비스로 접속되는 구조이다.
   * Load Balancer: 클라우드 플랫폼에서 제공하는 로드 밸랜서와 연동하귀 위해 사용되는 서비스 유형이다.
* `Volume`
  * Volume: 파드가 사용할 공유 저장소와 관련된 오브젝트로 파드의 yaml 파일에서 설정할 수 있다. 호스트 디렉토리를 그대로 사용할 수도 있고 EBS 같은 스토리지를 동적으로 생성하여 사용할 수 있다.
  * emptyDir: 최초 볼륨이 생성됐을 때 비어 있는 상태를 의미한다. Pod 생성시 만들어지고 삭제시 없어진다.
  * hostPath: 각각의 파드들이 사전 정의된 호스트 경로를 마운트하여 경로를 공유하기 때문에 파드가 죽어도 삭제되지 않는다. 호스트 패스이기 때문에 하나의 노드 안에서만 공유된다.
  * 퍼시스턴트 볼륨(PV): 파드가 사용할 스토리지의 크기 및 종류를 정의한다. 클러스터 운영자 영역에 해당한다.
  * 퍼시스턴트 볼륨 클레임(PVC): 퍼시스턴트 볼륨을 동적으로 확보하기 위해 사용한다. 클러스터 사용자 영역에 해당한다.
* `ReplicaSet`
  * ReplicaSet: 같은 스펙을 갖는 파드를 여러 개 생성하고 관리하는 역할을 한다.
  * ReplicaSet 생성 및 활용: 파드와 동일하게 .yaml 파일을 정의하여 생성하는 것이 일반적이고 kubectl 명령으로 생성 및 배포하고 삭제한다.
    1. yaml 파일 정의하기
    ```yaml
    apiVersion: v1  
    # 파일에서 정의하는 쿠버네티스 오브젝트 유형
    kind: ReplicaSet
    # 메타데이터 정보
    metadata:  
      name: replicaset-1  
    # 쿠버네티스 오브젝트 유형에 대한 정보를 정의
    spec:
      # 레플리카세트엣 만들 파드의 복제본의 수
      replicas: 3  
        # 파드에 대한 정의
        template:  
          metadata:  
            name: pod1  
            labels:  
              type: web  
          spec:  
            containers:  
            - name: container  
              image: kubetm/app:v1
            terminationGracePeriodSeconds: 0
    ```
    2. 레플리카세트 생성 및 배포하기  
   `$ kubectl apply -f {레플리카세트 이름}.yaml`
    3. 레플리카세트 상태 확인  
   `$ kubectl get pod`
  * Selector: Label을 통해서 Pod를 선택할 때 사용한다. {오브젝트 이름}.yaml 파일 안에 `spec의 selector 옵션과 Label 옵션`을 통해 정의가 가능하다.

Controller
=======
* `Deployment`
  * Deployment: 레프리카 세트의 리비전을 관리한다.
  * Deployment 생성 및 활용
    1. yaml 파일 정의하기
    ```yaml
    apiVersion: apps/v1
    # 파일에서 정의하는 쿠버네티스 컨트롤러 유형
    kind: Deployment
    # 메타데이터 정보
    metadata: 
      name: deployment-1  
    # 쿠버네티스 컨트롤러 유형에 대한 정보를 정의
    spec:  
      selector:  
        matchLabels:  
        type: app  
      # 레플리카 개수
      replicas: 2 
      # 파드 설정
      template:  
        metadata:  
          labels:  
            type: app  
        spec:  
          containers:  
          - name: container  
            image: kubetm/app:v1
          terminationGracePeriodSeconds: 10
    ```
    2. 클러스터에 반영하기  
    `$ kubectl apply -f {디플로이먼트 이름}.yaml`
    3. 상태 확인하기  
    `$ kubectl get pod,replicaset,deployment ==selector app={앱 이름}`
  * Recreate: Deployment 업그레이드 방식 중 하나로 Pod v1을 만들고 recreate를 하면 Pod v1를 삭제하고 Pod v2를 만든 이후 업그레이드를 한다. Downtime 존재하는 단점이 있다. {디플로이먼트 이름}.yaml 파일 안에 `spec의 strategy 옵션`을 통해 정의가 가능하다.
  * Rolling Update: Deployment 업그레이드 방식 중 하나로 Pod v1을 만들고 rolling update를 하면 Pod v2를 1개씩 만들고 하나씩 옮기는 방식이다. Downtime 존재하지 않는다. {디플로이먼트 이름}.yaml 파일 안에 `spec의 strategy 옵션`을 통해 정의가 가능하다.
* `Job`
  * Job: 상주 실행을 목적으로 하지 않는 파드를 여러 개 생성하고 정상적인 종료를 보장한다.
  * Job 생성 및 활용
    1. yaml 파일 정의하기
    ```yaml
    apiVersion: batch/v1  
    # 파일에서 정의하는 쿠버네티스 컨트롤러 유형
    kind: Job  
    # 메타데이터 정보
    metadata: 
      name: job-1
    # 쿠버네티스 컨트롤러 유형에 대한 정보를 정의
    spec:
      # 파드에 대한 정의
      template:  
        spec:  
          # 파드의 status 정책 설정
          restartPolicy: Never  
          containers:  
          - name: container  
            image: kubetm/init  
            command: ["sh",  "-c",  "echo 'job start';sleep 20; echo 'job end'"] 
            terminationGracePeriodSeconds: 0
    ```
    2. Job을 통해 파드 실행하기  
    `$ kubectl apply -f {Job 이름}.yaml`
    3. Job의 로그 확인하기  
    `$ kubectl logs -l app={앱 이름}`
    4. 종료된 파드 확인하기  
    `$ kubectl get pod -l app={앱 이름} --show-all`
* `CronJob`
  * CronJob: 크론 문법으로 스케줄링되는 잡이다.
  * CronJob 생성 및 활용
    1. yaml 파일 정의하기
    ```yaml
    apiVersion: batch/v1beta1  
    # 파일에서 정의하는 쿠버네티스 컨트롤러 유형
    kind: CronJob
    # 메타데이터 정보
    metadata:  
      name: cron-job
    # 쿠버네티스 컨트롤러 유형에 대한 정보를 정의
    spec:
      # 크론 포맷으로 정의한 스케줄 옵션
      schedule: "*/1 * * * *"  
      # 잡에 대한 상세한 정의
      jobTemplate:  
        spec:
          # 파드에 대한 정의
          template:  
            spec:
            # 파드의 status 정책 설정
            restartPolicy: Never  
            containers:  
            - name: container  
              image: kubetm/init  
              command: ["sh",  "-c",  "echo 'job start';sleep 20; echo 'job end'"]  
              terminationGracePeriodSeconds: 0
    ```
    2. CronJob을 통해 파드 실행하기  
    `$ kubectl apply -f {CronJob 이름}.yaml`
    3. CronJob의 상태 확인하기  
    `$ kubectl get job -l app={CronJob 이름}`
    4. CronJob의 로그 확인하기  
    `$ kubectl logs -l app={CronJob 이름}`
