# Kubernetes 정리 자료
그림으로 배우는 쿠버네티스 강의를 정리하여 만들었습니다.

Table of Contents
=================
<!--ts-->
   * [쿠버네티스를 배우기 위한 사전 준비 작업](#쿠버네티스를-배우기-위한-사전-준비-작업)
   * [애플리케이션 배포법](#애플리케이션-배포법)
   * [애플리케이션 노출법](#애플리케이션-노출법)
   * [애플리케이션 볼륨 사용법](#애플리케이션-볼륨-사용법)
   * [효과적인 애플리케이션 구성 및 관리](#효과적인-애플리케이션-구성-및-관리)
<!--te-->

쿠버네티스를 배우기 위한 사전 준비 작업
=======
- `혼동되는 용어 정리`
  - 파드: 1개 이상의 컨테이너가 캡슐화 되어 클러스터 안에서 배포되는 가장 작은 단위의 객체
  - 애플리케이션: 파드와 컨테이너와 관계 없는 `기능적인 단위`로 파드가 여러 개 하나의 애플리케이션을 이룰 수도 있음
- `자주 쓰이는 kubectl 기본 명령어 정리`
  - get: 오브젝트 조회
  - run, create, apply: 오브젝트 생성
  - delete: 오브젝트 삭제
  - exec: 파드 내부에 컨테이너 접속
  - scale: 파드 갯수를 늘리거나 줄임
  - edit: 배포된 오브젝트를 수정
- `자주 쓰이는 kubectl 명령어 옵션 정리`
  - `-o yaml`: 배포된 오브젝트의 실제 yaml 코드를 콘솔, 파일 등으로 지정하여 출력
  - `--dry-run=client`: 코드에 이상이 없는지 실제로 한번 테스트 실행
- `자주 쓰이는 kubectl 상태 관련 명령어 정리`
  - describe: 오브젝트에 연관된 정보 출력
  - logs: 파드의 컨테이너의 자세한 로그 정보 출력

애플리케이션 배포법
=======
- `파드`: 1개 이상의 컨테이너가 캡슐화 되어 클러스터 안에서 배포되는 가장 작은 단위의 객체
  - 파드를 이루는 코드
  ```yml
  apiVersion: v1 # v1.22에서 v1을 apiVersion을 선택
  kind: Pod # 오브젝트
  metadata: # 파드 이름 및 레이블(별칭)
    labels:
      run: po-nginx
    name: po-nginx
  spec: # 파드의 실제 컨테이너 정보
    cotainer:
     image: nginx
     name: nginx
  ```
- `디플로이먼트`: ReplicaSet + Pod + history로 ReplicaSet 기능에서 롤링 업데이트 및 히스토리 확인과 롤백 기능을 하는 컨트롤러
  - 디플로이먼트를 이루는 코드
  ```yml
  apiVersion: apps/v1 # v1.22에서 apps/v1을 apiVersion을 선택
  kind: Deployment # 컨트롤러
  metadata:
    labels:
      app: deploy-nginx
    name: deploy-nginx
  spec:
    replicas: 3
    selector:
      matchLabels: 
        app: po-nginx # selector가 template을 선택하므로 template와 이름이 동일해야함
    template: # template의 파드의 구조를 그대로 따라감
      meatadata:
        labels:
          app: po-nginx
      spec:
        cotainers:
        - name: nginx
        iamge: nginx
  ```
- `레플리카셋`: rolling update를 위해 대부분 단독으로 쓰이지 않고 디플로이먼트에 의해 사용됨
  - 레플리카셋을 이루는 코드
  ```yml
  apiVersion: apps/v1 # v1.22에서 apps/v1을 apiVersion을 선택
  kind: ReplicaSet # 오브젝트
  metadata:
    labels:
      app: rs-nginx
    name: rs-nginx
  spec:
    replicas: 3
    selector:
      matchLabels: 
        app: po-nginx # selector가 template을 선택하므로 template와 이름이 동일해야함
    template: # template의 파드의 구조를 그대로 따라감
      meatadata:
        labels:
          app: po-nginx
      spec:
        cotainers:
        - name: nginx
        iamge: nginx
  ``` 
- `스테이트풀셋`: 상태 값을 가지고 있는 파드로 생성 및 삭제에서 순서를 갖으며 고정된 이름을 가짐
  - 스테이트풀셋을 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: StatefulSet
  metadata:
    name: sts-chk-hn
  spec:
    replicas: 3
    serviceName: sts-svc-domain # statefulset need it
    selector:
    matchLabels:
      app: sts
    template:
      metadata:
        labels:
          app: sts
      spec:
        containers:
        - name: chk-hn
          image: sysnet4admin/chk-hn
  ```

애플리케이션 노출법
=======
- `NodePort`: 노드의 포트에 연결한 지정한 포트를 외부에 노출하는 서비스
  - NodePort와 이를 배포하는 Deployment를 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-nginx
    labels:
      app: deploy-nginx
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-nginx
    template:
      metadata:
        labels:
          app: deploy-nginx
      spec:
        containers:
        - name: nginx
          image: nginx
  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: np-nginx # 서비스의 이름
  spec:
    selector:
      app: deploy-nginx # 노출할 deployment 이름
    ports:
      - name: http
        port: 80 # 노드 -> 서비스에 대한 포트
        targetPort: 80 # 서비스 -> 파드에 대한 포트
        nodePort: 30000 # 노출할 포트
    type: NodePort
  ```
- `LoadBalancer`: EXTERNAL IP를 만들고 이를 통해 외부에 노출하는 서비스
  - LoadBalancer와 이를 배포하는 Deployment를 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-nginx
    labels:
      app: deploy-nginx
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-nginx
    template:
      metadata:
        labels:
          app: deploy-nginx
      spec:
        containers:
        - name: nginx
          image: nginx
  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: lb-nginx
  spec:
    selector:
      app: deploy-nginx
    ports:
      - name: http
        port: 80 
        targetPort: 80 
    type: LoadBalancer
  ```
- `ExternalName`: 외부에 있는 도메인에 쿠버네티스 내에서 연결할 때 별칭을 지을 때 사용하는 서비스
  - ExternalName를 이루는 코드
  ```yml
  apiVersion: v1
  kind: Service
  metadata:
    name: ex-url-1 # 서비스 이름
    namespace: default
  spec:
    type: ExternalName
    externalName: sysnet4admin.github.io # 와부 도메인
  ```
- `ClusterIP`: 파드와 파드의 연결을 위한 클러스터 내부의 IP를 설정하는 서비스
  - ClusterIP와 이를 배포하는 Deployment를 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-nginx
    labels:
      app: deploy-nginx
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-nginx
    template:
      metadata:
        labels:
          app: deploy-nginx
      spec:
        cotainers:
        - name: nginx
          image: nginx
  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: cl-nginx
  spec:
    selector:
      app: deploy-nginx
    ports:
      - name: http
        port: 80 
        targetPort: 80 
    type: ClusterIP
  ```
- `Headless`: CLUSTER-IP가 없는 ClusterIP 타입의 서비스로 IP 없이 도메인으로 연결할 때 스테이트풀셋과 함께 사용
  - Headless와 이를 배포하는 Deployment를 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: StatefulSet
  metadata:
    name: sts-chk-hn
  spec:
    replicas: 3
    serviceName: sts-svc-domain # statefulset need it
    selector:
      matchLabels:
        app: sts
    template:
      metadata:
        labels:
          app: sts
      spec:
        containers:
        - name: chk-hn
          image: sysnet4admin/chk-hn
  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: sts-svc-domain
  spec:
    selector:
      app: sts
    ports:
      - port: 80
    clusterIP: None
  ```
- `Endpoints`: 서비스는 아니지만 각 서비스에 의해 도달하는 종착 주소로 서비스 생성 시 자동 생성되나 수동 생성도 가능
  - 서비스와 직접 만든 앤드포인트를 이루는 코드
  ```yml
  apiVersion: v1
  kind: Service
  metadata:
    name: external-data
  spec:
    ports:
      - name: http
        port: 80
        targetPort: 80
  ---
  apiVersion: v1
  kind: Endpoints
  metadata:
    name: external-data
  subsets:
    - addresses:
        - ip: 192.168.1.11 # endpoint 지정
      ports:
        - name: http
          port: 80
  ```
- `Ingress`: 서비스는 아니지만 각 서비스에 의해 동작되며 HTTP(S)기반의 L7 로드밸런싱 기능을 제공하여 URL에 따라서 라우팅시키는 컴포넌트
  - 서비스와 디플로이먼트를 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-ip
    labels:
      app: deploy-ip
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-ip
    template:
      metadata:
        labels:
          app: deploy-ip
      spec:
        containers:
        - name: chk-ip
          image: sysnet4admin/chk-ip
  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: ing-ip 
  spec:
    selector:
      app: deploy-ip  
    ports:
      - name: http
        port: 80
        targetPort: 80
    type: ClusterIP # 클러스터 IP 서비스
  ```
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-nginx
    labels:
      app: deploy-nginx
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-nginx
    template:
      metadata:
        labels:
          app: deploy-nginx 
      spec:
        containers:
        - name: nginx
          image: nginx
  ---
  apiVersion: v1
  kind: Service
  metadata:
    name: ing-default 
  spec:
    selector:
      app: deploy-nginx  
    ports:
      - name: http
        port: 80
        targetPort: 80
    type: ClusterIP # 클러스터 IP 서비스
  ```
  - 인그레스를 이루는 코드
  ```yml
  apiVersion: networking.k8s.io/v1
  kind: Ingress
  metadata:
    name: nginx-ingress
    annotations: # 시스템에 인식시키기 위해 만든 주석
      nginx.ingress.kubernetes.io/rewrite-target: / # 전체 path를 받음
  spec:
    rules:
    - http:
        paths:
        - path: / # path 매칭
          pathType: Prefix
          backend:
            service:
              name: ing-default # 서비스 이름
              port:
                number: 80
        - path: /ip # path 매칭
          pathType: Prefix
          backend:
            service:
              name: ing-ip # 서비스 이름
              port:
                number: 80
  ```

애플리케이션 볼륨 사용법
=======
- `emptyDir`: 간단하게 파드 내에서 컨테이너 끼리 디렉토리 공유할 때 사용, 파드가 사라지면 emptyDir에 할당해서 사용했던 볼륨의 데이터도 함께 사라져서 주로 메모리와 디스크를 함께 이용하는 대용량 데이터 계산에 사용
  - emptyDir을 이루는 코드
  ```yml
  apiVersion: v1
  kind: Pod
  metadata:
    name: pod-emptydir
    labels:
      app: nginx
  spec:
    containers:
    - name: web-page
      image: nginx
      volumeMounts:
      - mountPath: /usr/share/nginx/html
        name: empty-directory

    - name: html-builder
      image: alpine
      volumeMounts:
      - mountPath: /html-dir
        name: empty-directory
      command: ["/bin/sh", "-c"]
      args:
        - echo "This page created on $(date +%Y-%m-%d)" > /html-dir/index.html;
        sleep infinity;

  volumes:
  - name: empty-directory
    emptyDir: {}
  ```
- `hostPath`: 호스트의 실제 파일이나 경로를 파드의 볼륨으로 마운트할 때 사용, 데몬셋을 통해서 한 노드 당 한개씩 배포하여 각 노드마다 확인도 가능
  - hostPath를 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-hostpath
    labels:
      app: deploy-hostpath
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-hostpath
    template:
      metadata:
        labels:
          app: deploy-hostpath
      spec:
        containers:
        - name: host-mon
          image: sysnet4admin/sleepy
          volumeMounts:
          - mountPath: /host-log # pod 내의 /host-log로 hostPath를 마운트
            name: hostpath-directory
        volumes:
        - name: hostpath-directory
          hostPath: # hostPath 설정
            path: /var/log
  ```

- `NFS`
  - NFS 서버를 이용해서 파드에 볼륨을 마운트
  - `/etc/exports`에서 어떤 디렉토리를 어떤 호스트에 제공할지 NFS 서버 설정
  ```sh
  /nfs_shared/nfs-vol 192.168.1.10/24(rw,sync,no_root_squash)
  ```
  - 공유 옵션
    - ro: 읽기 권한 부여 한다.
    - rw: 읽기 쓰기 권한 부여 한다.
    - root_squash: 클라이언트에서 root를 서버상의 nobody 계정으로 매핑한다.
    - no_root_squash: 클라이언트 및 서버 모두 root 계정 사용한다.
    - sync: 파일시스템이 변경되면 즉시 동기화한다.
    - all_squash: root 계정이 아닌 다른 계정도 사용 할  수 있게 한다.
  - NFS 볼륨을 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-nfs
    labels:
      app: deploy-nfs
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-nfs
    template:
      metadata:
        labels:
          app: deploy-nfs
      spec:
        containers:
        - name: chk-log
          image: sysnet4admin/chk-log
          volumeMounts:
          - name: nfs-vol 
            mountPath: /audit # 파드의 /audit에 nfs-vol을 마운트
        volumes:
        - name: nfs-vol
          nfs:
            server: 192.168.1.10
            path: /nfs_shared/nfs-vol
  ```
- `퍼시스턴트볼륨(PV)와 퍼시스턴트볼륨클레임(PVC)`
  - PV는 볼륨 자체를 뜻하며 클러스터 안에서 자원으로 다루며, 파드와는 별개로 관리되고 별도의 생명 주기(LifeCycle)가 있음
  - PVC는 사용자가 PV에 하는 요청으로 사용하고 싶은 용량, Read/Write 모드 등을 설정해서 요청하여 쿠버네티스는 볼륨을 파드에 직접 할당하지 않고 중간에 PVC를 두어 파드와 파드가 사용할 스토리지를 분리
  - 퍼시스턴트볼륨을 이루는 코드
  ```yml
  apiVersion: v1
  kind: PersistentVolume
  metadata:
    name: pv-nfs
  spec:
    capacity:
      stroage: 100Mi
    accessModes:
      - ReadWriteMany # 여러 개의 노드가 읽고 쓸 수 있도록 마운트 (접근 모드)
    persistentVolumeReclaimPolicy: Retain # PVC 삭제 시에도 PV를 보존 (반환 정책)
    nfs:
      server: 192.168.1.10
      path: /nfs_shared/pvc-vol
  ```
  - 퍼시스턴트볼륨클레임을 이루는 코드
  ```yml
  apiVersion: v1
  kind: PersistentVolumeClaim
  metadata:
    name: pvc-nfs
  spec:
    accessModes:
      - ReadWriteMany # 접근 모드
    resources:
      requests:
        stroage: 10Mi
  ```
  - pvc 배포를 하는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-pvc
    labels:
      app: deploy-pvc
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-pvc
    template:
      metadata:
        labels:
          app: deploy-pvc
      spec:
        containers:
        - name: chk-log
          image: sysnet4admin/chk-log
          volumeMounts:
          - name: pvc-vol
            mountPath: /audit
        volumes:
        - name: pvc-vol
          persistentVolumeClaim:
            claimName: pvc-nfs
  ```
  - PV 접근 모드
    - ReadWriteOnce: 하나의 노드에서만 볼륨을 읽고 쓸수 있게 마운트
    - ReadOnlyMany: 여러 개의 노드가 읽도록 마운트
    - ReadWriteMany: 여러 개의 노드가 읽고 쓸수 있도록 마운트
  - PV 반환 정책
    - Retain: PVC 삭제 시에도 PV를 보존
    - Delete: PVC 삭제 시에 PV도 삭제
  - 볼륨과 클레임에 대한 생명 주기
    - 프로비저닝(Provisioning)
      - PV를 만드는 단계, PV를 미리 만들어 두고 사용하는 `정적 방법`과 요청이 있을 때마다 PV를 만드는 `동적 방법`이 존재
    - 바인딩(Binding)
      - 프로비저닝으로 만들어진 PV를 PVC와 바인딩하는 단계
      - PVC에서 원하는 용량, 접근 방법을 명시해서 요청하면 거기에 맞는 PV 할당
      - 요청에 실패하면 원하는 PV가 있을 때까지 대기함
      - PV와 PVC의 매핑은 1:1 관계
    - 사용(Using)
      - PVC가 파드에 설정되고 파드는 PVC를 볼륨으로 인식해서 사용
      - 할당된 PVC는 파드를 유지하는 동안 계속 사용하며 시스템에서 임의로 삭제 불가
    - 반환(Reclaiming)
      - 사용이 끝난 PVC는 삭제되고 PVC를 사용하던 PV를 초기화하는 과정
      - 반환 정책은 Retain, Delete가 있음
- `StorageClass`
  - PV를 미리 만들어 두고 PVC에서 할당 요청을 하는 방식에서는 PV가 선행적으로 생성되어 있어야하는데, 스토리지 클래스는 PVC에서 요청 시에 이 요건에 맞는 PV를 동적으로 할당
  - 동적 프로비저닝에는 이미 많은 스토리지들에서 Privisioner가 제공
    - AWS EBS - provisioner: kubernetes.io/aws-ebs
    - GCE PD - provisioner: kubernetes.io/gce-pd
    - Glusterfs - provisioner: kubernetes.io/glusterfs
    - NFS - provisioner: example.com/external-nfs
    - OpenStack Cinder - provisioner: kubernetes.io/cinder
    - vSphere - provisioner: csi.vsphere.vmware.com / provisioner: kubernetes.io/vsphere-volume
    - Ceph RBD - provisioner: kubernetes.io/rbd
    - Quobyte - provisioner: kubernetes.io/quobyte
    - Azure Disk - provisioner: kubernetes.io/azure-disk
    - Azure File - provisioner: kubernetes.io/azure-file
    - Portworx Volume - provisioner: kubernetes.io/portworx-volume
    - ScaleIO - provisioner: kubernetes.io/scaleio
    - StorageOS - provisioner: kubernetes.io/storageos
    - Local - provisioner: kubernetes.io/no-provisioner
  - StorageClass를 이루는 코드
  ```yml
  apiVersion: storage.k8s.io/v1
  kind: StorageClass
  metadata:
    name: managed-nfs-storage
  provisioner: k8s-sig.io/nfs-subdir-external-provisioner # nfs provisioner 사용
  parameters:
    pathPattern: "${.PVC.namespace}/${.PVC.annotations.nfs.io/storage-path}"
    onDelete: delete
  ```
  - provisioner 배포를 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: Deployment
  metadata:
    name: deploy-pvc
    labels:
      app: deploy-pvc
  spec:
    replicas: 3
    selector:
      matchLabels:
        app: deploy-pvc
    template:
      metadata:
        labels:
          app: deploy-pvc
      spec:
        containers:
        - name: chk-log
          image: sysnet4admin/chk-log
          volumeMounts:
          - name: pvc-vol
            mountPath: /audit
        volumes:
        - name: pvc-vol
          persistentVolumeClaim:
            claimName: pvc-dynamic
  ```
  - 퍼시스턴트볼륨클레임을 이루는 코드
  ```yml
  apiVersion: v1
  kind: PersistentVolumeClaim
  metadata:
    name: pvc-dynamic
  spec:
    accessModes:
      - ReadWriteMany # 접근 모드
    resources:
      requests:
        storage: 10Gi
    storageClassName: managed-nfs-storage
  ```
- `volumeClaimTemplates`
  - 스테이트풀셋은 각각의 파드가 각각의 상태를 가지고 있어서 볼륨클레임템플릿을 활용하면 파드마다 각각 고유한 PV를 가질 수 있기 때문에 볼륨클레임템플릿은 스테이트풀셋에서만 사용 가능
  - 스테이트풀셋이라도 꼭 볼륨클레임템플릿으로 PV를 할당 받지 않아도 됨
  - 디플로이먼트의 경우 파드가 상태를 가지고 있지 않기 때문에 PV를 받아서 사용하는 방식
  - 볼륨클레임템플릿을 이루는 코드
  ```yml
  apiVersion: apps/v1
  kind: StatefulSet # 스테이트풀셋
  metadata:
    name: sts
  spec:
    replicas: 3
    serviceName: sts-svc-domain 
    selector:
      matchLabels:
        app: sts
    template:
      metadata:
        labels:
          app: sts
      spec:
        containers:
        - name: chk-hn
          image: sysnet4admin/chk-hn
          volumeMounts:
          - name: each-sts-backup
            mountPath: /backup_data
    volumeClaimTemplates: # 볼륨클레임템플릿
  - metadata:
      name: each-sts-backup
    spec:
      accessModes: [ "ReadWriteOnce" ] # 각각의 파드가 독립
      storageClassName: "managed-nfs-storage"
      resources:
        requests:
          storage: 20Gi
  ```

효과적인 애플리케이션 구성 및 관리
=======
