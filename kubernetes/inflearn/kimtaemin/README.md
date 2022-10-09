# Kubernetes 정리 자료
대세는 쿠버네티스 강의를 정리하여 만들었습니다.

Table of Contents
=================
<!--ts-->
   - [Kubernetes Basis](#Kubernetes-Basis)
   - [Basic Object](#Basic-Object) 
   - [Controller](#Controller)
   - [Pod](#Pod)
   - [Service](#Service)
   - [Ingress](#Ingress)
   - [Autoscaler](#Autoscaler)
<!--te-->

Kubernetes Basis
=======
- `쿠버네티스`: 쿠버네티스는 컨테이너를 쉽고 빠르게 배포/확장하고 관리를 자동화해주는 컨테이너 오케스트레이션 오픈소스 플랫폼로 노드의 리소스 사용 현황 및 배치 전략을 근거로 컨테이너를 적절히 배치한다.
- `대시보드`: 쿠버네티스에 배포된 컨테이너 등에 대한 정보를 한눈에 보여주는 웹 기반의 관리 도구
- `쿠버네티스 클러스터`: 쿠버네티스의 리소스를 관리하기 위한 집합체
- `노드`: 쿠버네티스 클러스터의 관리 대상으로 등록된 도커 호스트로 컨테이너가 배치되는 대상
- Virtual Machine vs Container
  - Virtual Machine은 호스트 OS 위에 VirtualBox나 VMWare 같은 하이퍼 바이저를 위에 두고 이를 통해 가상화하여 게스트 OS 위에서 라이브러리 및 환경을 셋팅하여 서비스를 구동 -> window와 mac 등 활용 가능
  - Container는 호스트 OS 위에 Docker 같은 컨테이너 가상화 툴을 두고 컨테이너에서 이미지를 서비스로 구동 -> 모듈화된 이미지로 쉽게 서비스 구동이 가능하며 호스트 서버의 자원과 OS를 공유해서 사용하여 자원을 효율적으로 사용 가능

- 쿠버네티스의 특징
  - Ecosystem: 구글 기반으로 여러 회사들이 참여하여 만든 프로젝트로 생태계가 탄탄하다.
  - `Auto Scaling`: 파드에 리소스에 임계치에 도달했을 때 파드를 더 만들어줘서 부하 분산처리를 하는 기능으로 트래픽 양의 따라 서비스 자원 양을 조절하여 배치하는 기능이 있어 효율적이다.
  - `Auto Healing`: 파드나 노드가 다운되었을 때 컨트롤러에 의해 다른 노드에 파드를 만들어주는 기능으로 장애가 난 서비스를 다른 서버로 자동으로 배치하여 운영하는 기능이 있어 안정적이다.
  - `Software Update`: 여러 파드에 대한 버전을 업그레이드 해야할 경우 업그레이드 버전을 만들고 스왑하여 한번에 업그레이드할 수 있는 기능이다.
  - 다양한 배포방식: 컨테이너 업데이트 시 `Deployment` 객체를 통해 배포를 자동적으로 처리하여 효율적으로 운영이 가능하고 `StatefulSets` 객체를 통해 실행 순서를 보장하고 호스트 이름과 볼륨을 일정하게 사용이 가능하다. 로그나 모니터링 등 모든 노드에 설치가 필요한 경우엔 `DaemonSet`을 이용하고 배치성 작업은 `Job`이나 `CronJob`을 이용한다.
  - 클라우드 자원과의 연동: 쿠버네티스는 Cloud Controller를 이용하여 클라우드와의 연동을 손쉽게 확장가능 하다.
  - RBAC(Role-based Access Control): 접근 권한 시스템으로 각각의 리소스에 대해 유저별로 CRUD스런 권한을 손쉽게 지정할 수 있다.
  - Federation, Multi Cluster: 클라우드에 설치한 쿠버네티스 클러스터와 자체 서버에 설치한 쿠버네티스를 묶어서 하나로 사용이 가능하다.
  - CRD (Custom Resource Definition): 쿠버네티스가 제공하지 않는 기능을 기본 기능과 동일한 방식으로 적용하고 사용할 수 있다.

- `쿠버네티스 아키텍처`
  - 마스터 - 노드 구조: 쿠버네티스는 전체 클러스터를 관리하는 마스터와 컨테이너가 배포되는 노드로 구성되어 있다. 모든 명령은 마스터의 API 서버를 호출하고 노드는 마스터와 통신하면서 필요한 작업을 수행하고 마스터가 노드에 접속하여 결과를 응답한다.
  - `Master`: 마스터 서버는 다양한 모듈이 확장성을 고려하여 기능별로 쪼개져 있는 것이 특징이고 마스터가 죽으면 클러스터를 관리할 수 없다.
  - `Node`: 노드 서버는 마스터 서버와 통신하면서 필요한 Pod을 생성하고 네트워크와 볼륨을 설정한다.
  - kubectl: API 서버는 json 또는 protobuf 형식을 이용한 http 통신을 지원하지만 방식을 그대로 쓰면 불편하므로 보통 kubectl이라는 `명령행 도구`를 사용한다.

- Master의 구성 요소
  - `스케줄러(kube-scheduler)`: 스케줄러는 할당되지 않은 Pod를 여러 가지 조건(필요한 자원, 라벨)에 따라 적절한 노드 서버에 할당해주는 모듈
  - `큐브 컨트롤러 매니저(kube-controller-manager)`: 쿠버네티스에 있는 대부분의 오브젝트의 상태를 관리하는 모듈
  - `큐브 API서버(kube-apiserver)`: 쿠버네티스의 모든 기능들을 REST API로 제공하고 그에 대한 명령을 처리하는 서버
  - `etcd`: 쿠버네티스의 모든 상태와 데이터를 저장하는 곳

- Node의 구성 요소
  - `큐블릿(kubelet)`: 노드에 할당된 Pod의 생명주기를 관리하고 Pod을 생성하고 Pod 안의 컨테이너에 이상이 없는지 확인하면서 주기적으로 마스터에 상태를 전달하는 모듈
  - `프록시(kube-proxy)`: 큐블릿이 Pod을 관리한다면 프록시는 Pod으로 연결되는 네트워크를 관리하는 모듈

- 쿠버네티스 용어
  - `리소스`: 쿠버네티스 오브젝트를 생성할 때 사용하는 틀
  - `오브젝트`: 쿠버네티스 시스템에서 영속성을 가지는 대상로 `기본 오브젝트와 컨트롤러로 구성`됨
  - `기본 오브젝트`: 오브젝트 중에서 컨테이너화되어 배포되는 애플리케이션의 워크로드를 기술하는 오브젝트
  - `컨트롤러`: 오브젝트 중에서 오브젝트를 생성하고 관리

- `쿠버네티스 yaml 파일의 기본 필드`
  - apiVersion - 이 스크립트를 실행하기 위한 쿠버네티스 API 버전
  - kind - 리소스의 종류를 정의
  - metadata - 이름, 문자열, UID, 그리고 선택적인 네임스페이스를 포함하여 오브젝트를 유일하게 구분지어 줄 데이터
  - spec - 리소스에 대한 상세한 스펙을 정의

Basic Object
=======
- `쿠버네티스 기본 오브젝트`
  - Pod
  - Service
  - Volume
  - Namespace
- `Pod`: 쿠버네티스에서 `배포할 수 있는 컨테이너 집합 단위`로 한 개 이상의 컨테이너와 스토리지, 네트워크 속성을 가지며 한 파드 안의 컨테이너는 모두 같은 노드에 배치해야한다. 파드 생성 시에 쿠버네티스 클러스터 내에서 접속할 수 있는 IP가 자동 할당된다.
  - 파드 예시
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
  - Label: Pod 뿐만 아니라 여러 오브젝트에서 사용할 수 있는 메타정보로 목적에 따라 오브젝트에 `key:value`방식으로 라벨을 달고 분리하여 이후 연결하기 위해서 사용한다. {오브젝트 이름}.yaml 파일 안에 `spec의 selector와 labels 옵션`을 통해 선택이 가능하다.
  - Selector: Label을 이용해 쿠버네티스 파드를 선택하는 방법이다.
  - Node Schedule: 파드를 만들 때 노드에 라벨을 달고 노드를 직접 지정할 때 사용한다. {오브젝트 이름}.yaml 파일 안에 `spec의 NodeSelector 옵션`을 통해 정의가 가능하다. 일반적인 경우엔 쿠버네티스 스케줄러가 판단해서 컨테이너 리소스 설정에 따라 분배한다.

- `Service`: 네트워크와 관련된 오브젝트로 Pod을 외부 네트워크와 연결하는 기능을 하며 파드의 IP는 재생성 시에 동적으로 변경되기 때문에 고정적인 IP를 Service에 할당하고 파드에 접근하기 위한 경로를 정의한다.
  - `ClusterIP`: 서비스의 종류 중 하나로 쿠버네티스 클러스터 내의 IP에서만 접근할 수 있는 IP로 여러 개의 파드와 연결하여 트래픽을 분산할 수 있다. Cluster 내에서만 접근 가능한 서비스이다.
  - ClusterIP 예시
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
        # 연결할 파드의 이름
        app: pod
        # 서비스의 포트
        - port: 9000
          # 파드의 포트
          tartgetPort: 8080
        # 서비스의 타입 (생략하면 기본 값이 ClusterIP)
        type: ClusterIP
    ```
  - `NodePort`: 서비스의 종류 중 하나로 ClusterIP처럼 클러스터 내 IP를 만들고 서비스가 파드로 트래픽을 분산하는 기능을 갖는다. 클러스터 내 모든 노드에 설정된 Port를 할당하고 서비스로 요청이 올 경우 연결된 파드로 전송한다. NodePort는 물리 IP와 포트(nodePort)를 직접 노출해 쿠버네티스 클러스터 외부로 서비스를 공개한다. 보안 상의 이슈로 내부망에서만 사용해야한다.
  - NodePort 예시
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
      name: svc-2
    spec:
      selector:
        # 연결할 파드의 이름
        app: pod
      ports:
      # 서비스의 포트
      - port: 9000
        # 파드의 포트
        targetPort: 8080
        # 외부에 노출할 노드의 포트 30000 ~ 32767만 설정 가능하고 설정하지 않으면 쿠버네티스가 지정
        nodePort: 30000
      type: NodePort
      # 특정 노드 IP로 접근한 트래픽은 해당 노드의 파드에만 연결되도록 설정
      externalTrafficPolicy: Local
    ```
  - `LoadBalancer`: 서비스의 종류 중 하나로 외부로 서비스를 노출시킬 수 있는 안전한 방법을 제공한다. EXTERNAL IP를 할당하면 이를 통해 외부에 노출시킬 수 있다.
  - LoadBalancer 예시
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
      name: svc-3
    spec:
      selector:
        # 연결할 파드의 이름
        app: pod
      ports:
        # 서비스의 포트
      - port: 9000
        # 파드의 포트
        targetPort: 8080
        type: LoadBalancer
    ```

- `Volume`: 저장소와 관련된 오브젝트, 파드가 사용할 공유 저장소와 관련된 오브젝트로 파드의 yaml 파일에서 설정할 수 있다. 호스트 디렉토리를 그대로 사용할 수도 있고 EBS 같은 스토리지를 동적으로 생성하여 사용할 수 있다.
  - `emptyDir`: 파드 안의 컨테이너들끼리 데이터를 공유하기 위해서 사용한다. 최초 볼륨이 생성됐을 때 비어 있는 상태이다. 파드 생성 시 만들어지고 삭제 시 없어진다.
  - emptyDir 예시
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: pod-volume-1
  spec:
    containers:
    - name: container1
      image: kubetm/init
      volumeMounts:
      - name: empty-dir
        mountPath: /mount1 # 볼륨 연결 컨테이너 내 마운트 경로가 달라도 됨
    - name: container2
      image: kubetm/init
      volumeMounts:
      - name: empty-dir
        mountPath: /mount2 # 볼륨 연결 컨테이너 내 마운트 경로가 달라도 됨
    volumes:
    - name : empty-dir # 볼륨
      emptyDir: {}
  ```
  - `hostPath`: 각각의 파드들이 사전 정의된 호스트 경로를 마운트하여 경로를 공유하기 때문에 파드가 죽어도 삭제되지 않는다. 호스트 패스이기 때문에 하나의 노드 안에서만 공유된다.
  - hostPath 예시
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: pod-volume-3
  spec:
    nodeSelector:
      kubernetes.io/hostname: k8s-node1
    containers:
    - name: container
      image: kubetm/init
      volumeMounts:
      - name: host-path
        mountPath: /mount1 # 파드 내 
    volumes:
    - name : host-path
      hostPath:
        path: /node-v # 노드 내의 마운트할 경로
        type: DirectoryOrCreate # 사전에 해당 노드의 경로가 없으면 생성시키는 용도
  ```
  - 퍼시스턴트 볼륨(PV)과 퍼시스턴트 볼륨 클레임(PVC): 퍼시스턴트 볼륨은 파드가 사용할 스토리지의 크기 및 종류를 정의한다. 클러스터 운영자 영역에 해당한다. 퍼시스턴트 볼륨 클레임은 파드가 퍼시스턴트 볼륨을 동적으로 확보하기 위해 요청할 때 사용한다. 클러스터 사용자 영역에 해당한다.
  - 퍼시스턴트 볼륨과 퍼시스턴트 볼륨 클레임 예시
  ```yml
  apiVersion: v1
  kind: PersistentVolume
  metadata:
    name: pv-03
  spec:
    capacity:
      storage: 2G
    accessModes:
    - ReadWriteOnce 
    local: # 로컬 PV (거의 사용하지 않음 PV)
      path: /node-v
    nodeAffinity:
      required:
        nodeSelectorTerms:
        - matchExpressions:
          - {key: kubernetes.io/hostname, operator: In, values: [k8s-node1]}
  ```
  ```yml
  apiVersion: v1
  kind: PersistentVolumeClaim
  metadata:
    name: pvc-01
  spec:
    accessModes:
    - ReadWriteOnce # 하나의 노드에서만 볼륨을 읽고 쓸수 있게 마운트
    resources:
      requests:
        storage: 1G
    storageClassName: ""
  ```
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: pod-volume-3
  spec:
    containers:
    - name: container
      image: kubetm/init
      volumeMounts:
      - name: pvc-pv
        mountPath: /mount3 # 파트 내 마운트할 경로
    volumes:
    - name : pvc-pv
      persistentVolumeClaim: # PVC 선언
        claimName: pvc-01
  ```
- `ConfigMap`과 `Secret`: ConfigMap은 파드 생성 시에 참조할 일반적인 상수를 모아놓은 오브젝트로 Literal 값이나 File 값으로 설정 가능하다. Secret은 파드 생성 시에 참조할 보안적인 상수를 모아놓은 오브젝트로 Literal 값이나 File 값으로 설정 가능하다. ConfigMap과 달리 메모리에 데이터를 저장되고 하나의 Secret 당 1MB까지만 저장 가능하다.
  - ConfigMap과 Secret 생성 및 활용 - `Literal` 예시
  ```yml
  apiVersion: v1
  kind: ConfigMap
  metadata:
    name: cm-dev
  data:
    SSH: 'false'
    User: dev
  ```
  ```yml
  apiVersion: v1
  kind: Secret
  metadata:
    name: sec-dev
  data:
    Key: MTIzNA==
  ```
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: pod-1
  spec:
    containers:
    - name: container
      image: kubetm/init
      envFrom:
      - configMapRef:
          name: cm-dev
      - secretRef:
          name: sec-dev
  ```
  - ConfigMap과 Secret 생성 및 활용 - `볼륨 마운트 + File` 예시
  ```sh
  # file-c.txt 라는 파일로 cm-file라는 이름의 ConfigMap 생성
  $ kubectl create configmap cm-file --from-file=./file-c.txt
  # key1:value1 라는 상수로 cm-file라는 이름의 ConfigMap 생성
  $kubectl create configmap cm-file --from-literal=key1=value1
  # 여러 key:value로 cm-file라는 이름의 ConfigMap 생성 
  $ kubectl create configmap cm-file --from-literal=key1=value1 --from-literal=key2=value2
  ```
  ```sh
  # file-s.txt 라는 파일로 sec-file라는 이름의 Secret 생성
  $ kubectl create secret generic sec-file --from-file=./file-s.txt
  # key1:value1 라는 상수로 sec-file라는 이름의 Secret 생성
  $ kubectl create secret generic sec-file --from-literal=key1=value1
  ```
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: pod-mount
  spec:
    containers:
    - name: container
      image: kubetm/init
      volumeMounts:
      - name: file-volume
        mountPath: /mount
    volumes:
    - name: file-volume
      configMap:
        name: cm-file
  ```
- `Namespace`: 쿠버네티스 클러스터 하나를 용도 및 사용자에 따라 여러 개의 논리적인 단위로 나누어서 사용하는 것이다.
  - 기본 Namespace
    - default: 기본 네임스페이스, 쿠버네티스에서 명령을 실행할 때 별도의 네임스페이스를 지정하지 않는다면 항상 defaul 네임스페이스에 명령을 적용
    - kube-system: 쿠버네티스 시스템에서 관리하는 네임스페이스, 이 네임스페이스에는 쿠버네티스 관리용 파드나 설정이 있다.
    - kube-public: 클러스터 안 모든 사용자가 읽을 수 있는 네임스페이스, 보통 클러스터 사용량 같은 정보를 이 네임스페이스에서 관리한다.
    - kube-node-lease : 각 노드의 임대 오브젝트(Lease Object)들을 관리하는 네임스페이스이다.
  - `ResourceQuota`: `Namespace마다` 제한하는 자원을 명시하는 기능으로 `오브젝트의 숫자` 및 `CPU`와 `Memory` 그리고 `Storage`를 제한한다. 최소 자원을 나타내는 requests와 최대 제한을 나타내는 limits로 구성된다.
  - `LimitRange`: ResourceQuota가 정해진 Namespace 내에서 `파드와 컨테이너마다` 자원의 상한을 설정
  - ResourceQuota 예시
    ```yml
    apiVersion: v1
    kind: ResourceQuota
    metadata:
      name: rq-1
      namespace: nm-3
    spec:
      hard:
        requests.memory: 1Gi
        limits.memory: 1Gi
    ```
  - LimitRange 예시
    ```yml
    apiVersion: v1
    kind: LimitRange
    metadata:
      name: lr-1
    spec:
      limits:
      - type: Container
        min:
          memory: 0.1Gi
        max:
          memory: 0.4Gi
        maxLimitRequestRatio:
          memory: 3
        defaultRequest:
          memory: 0.1Gi
        default:
          memory: 0.2Gi
    ```

Controller
=======
- `쿠버네티스 컨트롤러`
  - Deployment
  - ReplicaSet
  - DaemonSet
  - Job
  - CronJob
  - StatefulSet
  - Ingress
  - Autoscaler
- `ReplicaSet`: 레플리케이션 컨트롤러의 상위 버전으로 같은 스펙을 갖는 파드를 여러 개 생성하고 관리하는 역할을 한다. 
  - ReplicaSet 예시
    ```yml
    apiVersion: v1
    kind: Pod
    metadata:
      name: pod1
      labels: # 라벨
        type: web
    spec:
      containers:
      - name: container
        image: kubetm/app:v1
      terminationGracePeriodSeconds: 0
    ```
    ```yaml
    apiVersion: apps/v1
    kind: ReplicaSet
    metadata:
      name: replica2
    spec:
      # 복제본 수
      replicas: 2
      # 셀렉터 - 
      selector:
        matchLabels:
          cascade: "false"
      # 템플릿 - 새로 생성해야할 때 어떤 Pod 을 만들지 정의
      template:
        metadata:
          labels:
            cascade: "false"
        spec:
          containers:
          - name: container
            image: kubetm/app:v1
    ```
- `Deployment`: ReplicaSet + Pod + history로 ReplicaSet 기능에서 롤링 업데이트 및 히스토리 확인과 롤백 기능을 하는 컨트롤러이다.
  - Deployment 예시
    ```yaml
    apiVersion: apps/v1
    kind: Deployment
    metadata:
      name: deployment-2
    spec:
      selector:
        matchLabels:
          type: app2
      replicas: 2
      strategy:
        type: RollingUpdate # 배포 전략 설정(기본값도 RollingUpdate)
      minReadySeconds: 10
      template:
        metadata:
          labels:
            type: app2
        spec:
          containers:
          - name: container
            image: kubetm/app:v1
          terminationGracePeriodSeconds: 0
    ```
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
      name: svc-2
    spec:
      selector:
        type: app2
      ports:
      - port: 8080
        protocol: TCP
        targetPort: 8080
    ```
  - Recreate: Deployment 업그레이드 방식 중 하나로 Pod v1을 만들고 recreate를 하면 Pod v1를 삭제하고 Pod v2를 만든 이후 업그레이드를 한다. Downtime 존재하는 단점이 있다. {디플로이먼트 이름}.yaml 파일 안에 `spec의 strategy 옵션`을 통해 정의가 가능하다.
  - Rolling Update: Deployment 업그레이드 방식 중 하나로 Pod v1을 만들고 rolling update를 하면 Pod v2를 1개씩 만들고 하나씩 옮기는 방식이다. Downtime 존재하지 않는다. {디플로이먼트 이름}.yaml 파일 안에 `spec의 strategy 옵션`을 통해 정의가 가능하다.
- `Job`: 상주 실행을 목적으로 하지 않는 파드를 여러 개 생성하고 정상적인 종료를 보장한다.
  - Job 예시
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
          # 파드의 status 정책 설정 -> Job이므로 재시작 Never 설정 필요
          restartPolicy: Never  
          containers:  
          - name: container  
            image: kubetm/init  
            command: ["sh",  "-c",  "echo 'job start';sleep 20; echo 'job end'"] 
            terminationGracePeriodSeconds: 0
    ```
- `CronJob`: 크론 문법으로 스케줄링되는 잡이다.
  - CronJob 예시
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
      schedule: "-/1 - - - -"  
      # 잡에 대한 상세한 정의
      jobTemplate:  
        spec:
          # 파드에 대한 정의
          template:  
            spec:
            # 파드의 status 정책 설정 -> Job이므로 재시작 Never 설정 필요
            restartPolicy: Never  
            containers:  
            - name: container  
              image: kubetm/init  
              command: ["sh",  "-c",  "echo 'job start';sleep 20; echo 'job end'"]  
              terminationGracePeriodSeconds: 0
    ```

Pod
=======
- `Lifecycle`: 파드는 생성부터 삭제까지의 과정에 생명 주기가 있으며 Lifecycle이 현재 어느 단계에 있는지를 알려주는 `Phase`와 현재 Pod가 서비스를 제공할 수 있는지 순서대로 점검한 `Conditions`를 가짐
  - 파드의 Phase 단계
    - Pending: Pod 생성 요청을 받았지만 하나 이상의 container가 실행 준비를 마치지 못한 상태이다. 컨테이너 이미지를 다운로드하는 시간도 이 Phase에 포함된다.
    - Running: Node가 배정되었고, 모든 컨테이너가 생성된 상태이다. 최소한 하나 이상의 컨테이너가 실행 중이거나 시작 또는 재시작 중이다.
    - Succeeded: Pod의 모든 컨테이너가 성공적으로 종료되었으며, 재시작할 필요가 없다.
    - Failed: 모든 컨테이너가 종료되었으나, 하나 이상의 컨테이너가 0이 아닌 값을 반환하였거나 시스템에 의해 강제로 종료되어 실패로 끝난 경우이다. 
    - Unknown: k8s가 Pod의 상태 정보를 읽어오지 못하는 상태이며, 일반적으로 kubelet과 API 서버간의 통신에 문제가 있는 경우가 많다.
  - 파드의 Conditions 종류
    - PodScheduled: Pod가 Node에 배정된지에 대한 여부이다.
    - ContainersReady: Pod가 모든 컨테이너에 ready 상태인지 여부이다.
    - Initialized: 모든 `init container`가 성공적으로 실행 여부이다.
    - Ready: Pod이 서비스를 제공할 수 있는 상태 여부이다. ReadinessProbe를 통해 결정되며, 이를 통과해야 Endpoint가 할당되어 Service를 통해 로드밸런싱이 이루어진다.
  - 컨테이너의 State와 Reason
    - 파드의 Phase가 Running이여도 내부 컨테이너가 Running이 아닐 수 있으니 파드의 Conditions을 보고 컨테이너도 확인해야함
    - State: Waiting, Running, Terminated
    - Reason: ContainerCreating, CrashLoopBackOff, Error, Completed
  - describe pob 예시
  ```yml
  [root@k8s-master ~]# kubectl describe pods nginx-deployment-69cfdf5bc7-gcpd2
  Name:         nginx-deployment-69cfdf5bc7-gcpd2
  Namespace:    default
  Priority:     0
  Node:         k8s-node2/192.168.56.32
  Start Time:   Fri, 07 Jan 2022 13:35:49 +0000
  Labels:       app=nginx-deployment
                pod-template-hash=69cfdf5bc7
  Annotations:  cni.projectcalico.org/containerID: b55493deca71e924b1f262af9656954acd426c220b1c026a86de2f640688822f
                cni.projectcalico.org/podIP: 20.109.131.22/32
                cni.projectcalico.org/podIPs: 20.109.131.22/32
  Status:       Running # phase

  Conditions: # coditions
    Type              Status
    Initialized       True 
    Ready             True 
    ContainersReady   True 
    PodScheduled      True
  ```
- `ReadinessProbe`와 `LivenessProbe`: `ReadinessProbe`는 Pod의 생명주기 중 Pending 상태에서의 동작 및 서비스 요청에 응답이 가능한지 확인하고 LivenessProbe는 Pod의 생명주기 중 Running 상태에서의 동작 컨테이너가 정상 실행 중 인지 확인한다.
  - ReadinessProbe
    - Service와 연결된 Pod를 확인하여 ReadinessProbe에 대해 응답이 없거나 실패 응답을 보낸다면 해당 Pod를 사용 불가능한 상태라고 판단하여 서비스 목록에서 제외 -> `애플리케이션이 시작할 준비가 되었는지 체크`하여 애플리케이션 구동 순간에 차이에 따른 트래픽 실패를 없앰
  - LivenessProbe
    - 컨테이너의 상태를 주기적으로 체크하여 응답이 없다면 컨테이너를 자동으로 `재시작` -> `애플리케이션이 응답 가능한지 확인`하여 애플리케이션 장애에 대응
  - ReadinessProbe/LivenessProbe 3가지 방식
    - httpGet: 가장 많이 사용하는 Probe 방식으로 HTTP GET을 이용하여 컨테이너 상태 체크, 리턴되는 HTTP 응답코드가 200~3xx이라면 정상으로 판단
    - Exec: 쉘 명령으로 수행한 결과에 따라 컨테이너 정상 여부를 체크, 결과값이 0이면 성공 0이 아니면 실패로 간주
    - tcpSocket: 지정된 포트에 TCP 연결을 시도하여 컨테이너 상태 체크, 연결이 성공되면 컨테이너가 정상인것으로 판단
  - ReadinessProbe/LivenessProbe 옵션
    - initialDelaySeconds(default=0):	최초 Probe 전의 지연 시간이다.
    - periodSeconds(default=10): Probe를 체크하는 시간 간격이다.
    - timeoutSeconds(default=1): 결과를 대기하는 시간까지의 시간이다.
    - successThreshold(default=1): ReadinessProbe에서 사용하며 몇번의 성공 결과를 수신해야 성공으로 인정하는지에 대한 값이다.
    - failureThreshold(default=3): LivenessProbe에서 사용하며 몇번의 실패 결과를 수신해야 실패하고 인정하는지에 대한 값이다.
  - ReadinessProbe 예시
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
      name: svc-readiness
    spec:
      selector:
        app: readiness
      ports:
      - port: 8080
        targetPort: 8080
    ```
    ```yml
    apiVersion: v1
    kind: Pod
    metadata:
      name: pod-readiness-exec1
      labels:
        app: readiness  
    spec:
      containers:
      - name: readiness
        image: kubetm/app
        ports:
        - containerPort: 8080	
        readinessProbe:
          exec:
            command: ["cat", "/readiness/ready.txt"]
          initialDelaySeconds: 5
          periodSeconds: 10
          successThreshold: 3
        volumeMounts:
        - name: host-path
          mountPath: /readiness
      volumes:
      - name : host-path
        hostPath:
          path: /tmp/readiness
          type: DirectoryOrCreate
      terminationGracePeriodSeconds: 0
    ```
  - LivenessProbe 예시
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
      name: svc-liveness
    spec:
      selector:
        app: liveness
      ports:
      - port: 8080
        targetPort: 8080
    ```
    ```yml
    apiVersion: v1
    kind: Pod
    metadata:
      name: pod-liveness-httpget1
      labels:
        app: liveness
    spec:
      containers:
      - name: liveness
        image: kubetm/app
        ports:
        - containerPort: 8080
        livenessProbe:
          httpGet:
            path: /health
            port: 8080
          initialDelaySeconds: 5
          periodSeconds: 10
          failureThreshold: 3
      terminationGracePeriodSeconds: 0
    ```
- `QoS classes`: QoS(Quality of Service)는 Pod 생성 시 설정하는 Requests와 limits에 따라 지정되는 `앱의 중요도`에 따라 자원 배정을 관리하게 해주는 설정으로 노드에 있는 Pod가 모든 자원을 사용하고 있을 때 특정 Pod에서 추가 자원이 필요한 경우 중요도에 따라 자원을 배분한다.
  - QoS classes 종류
    - `Guaranteed class`: 파드 내의 모든 Container에 Request와 Limit이 설정되어 있고 수치가 같음
    - `Burstable class`: 파드 내의 Container마다 Request와 Limit은 설정되어 있지만 수치가 같지 않음
    - `BestEffort class`: 파드 내의 어떤 Container 내에도 Request, Limit이 미설정 
  - QoS classes와 우선순위
    - 기본적인 클래스 별 우선순위: `Guarnteed > Burstable > BestEffort`
    - Burstable 내에서의 우선순위: Request와 실제 사용에 따른 메모리 사용량인 `OOM Score` 낮을수록 우선순위가 높음
- `Node Scheduling`: Pod를 생성할 경우 생성할 Pod가 어떤 노드에 할당되어야할지 쿠버네티스에서 자동할당 해주는데 운영자가 특정 노드를 지정하고 싶을 때 사용하는 기능이다.
  - 특정 Node를 선택하는 방법
    - `NodeSelector`: Node의 Label(Key, Value)을 지정하여 해당 Node에 할당
    - `NodeAffinity`: NodeSelector를 보완하여 사용하는 기능으로 matchExpressions와 해당 조건에 반드시 부합하는 Node에만 할당하는 `Required`와 Required에 비해 유연한 선택을 하는 `Preferred`의 옵션을 이용하여 복잡/세부적인 조건 구성
  - 특정 Node에 대해 할당을 제한하는 방법
    - `Toleration와 Taint`: Taint가 있는 노드에 Toleration으로 조건을 부합하는 경우에만 파드 할당
  - Node가 아닌 Pod를 기준으로 할당을 집중 분산하는 방법
    - `Pod Affinity`: 같은 PV 호스트패스를 사용한다면 Master Pod가 최초 할당된 Node에 Slave도 함께 생성한다.
    - `Anti-Affinity`: Master와 Slave를 서로 다른 Node에 생성한다.

Service
=======
- `Headless`: `클러스터 IP가 없는 ClusterIP 타입의 서비스`로 Pod 간의 통신같이 로드밸런싱이 필요없거나 단일 서비스 IP가 필요 없는 경우에 사용한다.
  - Headless 서비스를 nslookup으로 조회하면 해당 Headless 서비스와 연결된 파드들의 IP를 얻을 수 있다.
  - 동적으로 변하는 IP에 대하여 대하여 대응이 필요하기 때문에 파드를 Headless 서비스와 연결하기 위해 hostname 속성과 subdomain 속성을 설정하면 nslookup으로 조회할 때 `hostname.subdomain`으로 해당 파드의 IP를 얻을 수 있음
  - Headless 예시
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
      name: headless1
    spec:
      selector:
        svc: headless
      ports:
        - port: 80
          targetPort: 8080    
      clusterIP: None
    ```
    ```yml
    apiVersion: v1
    kind: Pod
    metadata:
      name: pod4
      labels:
        svc: headless
    spec:
      hostname: pod-a # hostname
      subdomain: headless1 # subdomain
      containers:
      - name: container
        image: kubetm/app
    ```
- `Endpoints`: 서비스는 아니지만 각 서비스에 의해 도달하는 종착 주소로 서비스 생성 시 자동 생성되나 서비스와 같은 이름으로 수동 생성하여 연결 정보를 매핑하는데 사용한다.
  - Endpoints 예시
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
      name: endpoint2
    spec:
      ports:
      - port: 8080
    ```
    ```yml
    apiVersion: v1
    kind: Endpoints
    metadata:
      name: endpoint2
    subsets:
    - addresses:
      - ip: 20.109.5.12 # endpoint 지정
      ports:
      - port: 8080
    ```
- `ExternalName`: Endpoint를 사용하여 IP를 지정하면 외부에 있는 도메인의 경우 IP가 바뀔 수 있기 때문에 외부 도메인과 연결할 때 사용하는 서비스이다.
  - ExternalName 예시
    ```yml
    apiVersion: v1
    kind: Service
    metadata:
    name: externalname1
    spec:
    type: ExternalName
    externalName: github.github.io
    ``` 

Ingress
=======
- `Ingress`: 외부에서 쿠버네티스 클러스터 내부로 들어오는 네트워크 요청을 어떻게 처리할지 정의하여 외부에서 쿠버네티스에서 실행 중인 Deployment와 Service에 접근하기 위한 일종의 관문같은 역할을 담당한다. 보통 `Nginx Ingress Controller`를 사용한다.
  - Ingress 기능
    - 외부 요청에 대한 로드 밸런싱
    - TLS/SSL 인증서 처리
    - 특정 HTTP 경로의 라우팅
  - Ingress 예시
    ```yml
    apiVersion: networking.k8s.io/v1
    kind: Ingress
    metadata:
      name: service-loadbalancing
    spec:
      ingressClassName: nginx
      rules:
      - http:
          paths:
          - path: /
            pathType: Prefix
            backend:
              service:
                name: svc-shopping
                port:
                  number: 8080
          - path: /customer
            pathType: Prefix
            backend:
              service:
                name: svc-customer
                port:
                  number: 8080
          - path: /order
            pathType: Prefix
            backend:
              service:
                name: svc-order
                port:
                  number: 8080
    ```

Autoscaler
=======
- `Autoscaler`: 
  - Autoscaler 종류
    - HPA(Horizontal Pod Autoscaler): Stateless App에서 오토 스케일링하는 기능으로 요청이 증가하면 파드의 개수를 늘린다. -> `Scale Out`
    - VPA(Vertical Pod Autoscaler): Statefule App에서 오토 스케일링하는 기능으로 요청이 증가하면 파드의 리소스를 증가시킨다. -> `Scale Up`
    - CA(Cluster Autoscaler): 클러스터에 노드를 추가한다.
  - `HPA`
  - Autoscaler 예시
    ```yml
    apiVersion: apps/v1
    kind: Deployment
    metadata:
    name: stateless-cpu1
    spec:
    selector:
      matchLabels:
          resource: cpu
    replicas: 2
    template:
      metadata:
        labels:
          resource: cpu
      spec:
        containers:
        - name: container
          image: kubetm/app:v1
          resources:
            requests:
              cpu: 10m
            limits:
              cpu: 20m
    ---
    apiVersion: v1
    kind: Service
    metadata:
    name: stateless-svc1
    spec:
    selector:
        resource: cpu
    ports:
      - port: 8080
        targetPort: 8080
        nodePort: 30001
    type: NodePort
    ```
    ```yml
    apiVersion: autoscaling/v2beta2
    kind: HorizontalPodAutoscaler
    metadata:
      name: hpa-resource-cpu
    spec:
      maxReplicas: 10
      minReplicas: 2
      scaleTargetRef:
        apiVersion: apps/v1
        kind: Deployment
        name: stateless-cpu1
      metrics:
      - type: Resource 
        resource:
          name: cpu
          target:
            type: Utilization
            averageUtilization: 50
    ```
  - Autoscaler 예시2
    ```yml
    apiVersion: apps/v1
    kind: Deployment
    metadata:
    name: stateless-memory1
    spec:
    selector:
      matchLabels:
          resource: memory
    replicas: 2
    template:
      metadata:
        labels:
          resource: memory
      spec:
        containers:
        - name: container
          image: kubetm/app:v1
          resources:
            requests:
              memory: 10Mi
            limits:
              memory: 20Mi
    ---
    apiVersion: v1
    kind: Service
    metadata:
    name: stateless-svc2
    spec:
    selector:
        resource: memory
    ports:
      - port: 8080
        targetPort: 8080
        nodePort: 30002
    type: NodePort
    ```
    ```yml
    apiVersion: autoscaling/v2beta2
    kind: HorizontalPodAutoscaler
    metadata:
      name: hpa-resource-memory
    spec:
      maxReplicas: 10
      minReplicas: 2
      scaleTargetRef:
        apiVersion: apps/v1
        kind: Deployment
        name: stateless-memory1
      metrics:
      - type: Resource 
        resource:
          name: memory
          target:
            type: AverageValue
            averageValue: 5Mi
    ```
