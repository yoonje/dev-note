# Kubernetes Helm 정리 자료
대세는 쿠버네티스 Helm 강의를 정리하여 만들었습니다.

Table of Contents
=================
<!--ts-->
   - [Helm](#Helm)
   - [Helm Chart](#Helm-Chart)
<!--te-->


Helm
=======
- `Helm`: 환경 및 리소스 별로 정젹 yaml 파일이 생겨서 yaml 파일에 대한 유지보수가 어려워져서 template을 통해서 yaml 파일을 동적으로 생성하게 해주는 툴
- `Helm 명령어`
  - 버전 및 설치 확인
    - `$ helm version`
  - 차트 조회 - 허브에서 조회, 로컬 저장소에서 조회
    - `$ helm search hub [keyword]`
    - `$ helm search repo [keyword]`
  - 레포지토리 관리 - 레포지토리 등록, 레포지토리 리스트 조회, 레포지토리 업데이트, 레포지토리 삭제
    - `$ helm repo add [name] [url]` 
    - `$ helm repo list`
    - `$ helm repo update`
    - `$ helm repo remove [name]`
  - 사용자 정의 차트 생성
    - `$ helm create [name]`
  - 배포 관리 - 확인, 배포, 배포 리스트 조회, 배포 상태 확인, 업그레이드, 삭제
    - `$ helm template [chart]` 
    - `$ helm install [name] [chart]` 
    - `$ helm list`
    - `$ helm status [name]` 
    - `$ helm upgrade [name] [chart]` 
    - `$ helm uninstall [name]` or `$ helm delete [name]`
  - 차트 조회 - 차트에 대한 모든 정보, 차트 정의 정보, 차트의 README 파일 정보, 차트의 values.yaml 파일 정보
    - `$ helm show all [CHART] [flags]`
    - `$ helm show chart [CHART] [flags]`
    - `$ helm show readme [CHART] [flags]`
    - `$ helm show values [CHART] [flags]`
  - 릴리즈 조회 - 릴리스에 대한 모든 정보, 명명된 릴리스의 차트에서 제공하는 노트 정보, 릴리스에 대한 값에 대한 정보, 릴리스에 대해 생성된 매니페스트 정보
    - `$ helm get all RELEASE_NAME [flags]`
    - `$ helm get notes RELEASE_NAME [flags]`
    - `$ helm get values RELEASE_NAME [flags]`
    - `$ helm get manifest RELEASE_NAME [flags]`

Helm Chart
=======
- `Helm Chart 만들기`
  - 기본 구조: `$ helm create <chart-name>` 실행 시에 `template.`, `values.yaml`, `Chart.yaml`, README.md 등 파일들이 chart-name 디렉토리에 생성
    - 내장 객체
      - Values: values.yaml 파일 및 사용자 정의 파일에서 템플릿으로 전달될 값
      - Chart: Chart.yaml 파일의 내용으로 chart의 전반적인 정보
      - Template: 실행 중인 현재 템플릿에 대한 정보로 쿠버네티스 리소스
        - Name: 현재 템플릿에 대한 네임스페이스 파일 경로 (예: mychart/templates/mytemplate.yaml)
        - BasePath: 현재 차트의 템플릿 디렉토리에 대한 네임스페이스 경로 (예: mychart/templates)
      - Relesase: 릴리스 자체
        - Release.Name: 릴리스 이름
        - Release.Namespace: 릴리스될 네임스페이스 (manifest에서 오버라이드하지 않은 경우)
        - Release.IsUpgrade: 현재 작업이 업그레이드 또는 롤백인 경우 true 로 설정
        - Release.IsInstall: 현재 작업이 설치일 경우 true 로 설정
        - Release.Revision: 이 릴리스의 리비전 번호로 설치 시에는 이 값이 1이며 업그레이드나 롤백을 수행할 때마다 증가
        - Release.Service: 현재 템플릿을 렌더링하는 서비스로 Helm 에서는 항상 Helm
    - 변수 주입: `{{ }}` 는 변수를 의미하고 `.(dot)`은 전체 스콥을 의미
      ```yml
      # values.yaml
      replicaCount: 1
      image:
      repository: nginx
      service:
      type: ClusterIP
      ```
      ```yml
      # Chart.yaml
      name: mychart
      type: application
      version :0.1.0
      ```
      ```yml
      # deployment.yaml
      kind: Deployment
      metadata:
      spec:
      replicas: {{ .Values.replicaCount }}
      containers:
         -name: {{ .Chart.Name }}
      ```
    - 사용자 정의 변수: templates 디렉토리에는 `_helpers.tpl` 이라는 파일이 있고 이 파일을 통해 사용자 정의 키워드를 생성하고 `{{ include "정의한 키워드" . }}` 으로 사용
      ```yml
      # _helpers.tpl
      {{/*
      Expand the name of the chart.
      */}}
      {{- define "mychart.name" -}}
      {{- default .Chart.Name .Values.nameOverride | trunc 63 | trimSuffix "-" }}
      {{- end }}

      {{/*
      Common labels
      */}}
      {{- define "mychart.labels" -}}
      helm.sh/chart: {{ include "mychart.chart" . }}
      {{ include "mychart.selectorLabels" . }}
      {{- if .Chart.AppVersion }}
      app.kubernetes.io/version: {{ .Chart.AppVersion | quote }}
      {{- end }}
      app.kubernetes.io/managed-by: {{ .Release.Service }}
      {{- end }}
      ```
      ```yml
      # service.yaml
      apiVersion: v1
      kind: Service
      metadata:
      name: {{ include "mychart.fullname" . }}
      labels:
         {{- include "mychart.labels" . | nindent 4 }}
      ```
  - function와 pipeline: [템플릿에서 유용하게 사용할 수 있는 함수들](https://helm.sh/ko/docs/chart_template_guide/function_list/#%ec%95%94%ed%98%b8%ed%99%94-%eb%b0%8f-%eb%b3%b4%ec%95%88-%ed%95%a8%ec%88%98)과 연결 도구인 파이프라인이 존재
      ```yml
      # values.yaml
      func:
      enabled: true
      ```
      ```yml
      # 함수 쓰는 법
      {{ Values | functions }}

      {{ .Values.func.enabled | quote }}         # "true"
      {{ .Values.func.enabled | upper | quote }} # "TRUE"
      ```
  - flow control: 템플릿 작성자인 사용자에게 템플릿 생성의 흐름을 제어할 수 있는 기능으로 IF, WITH, RANGE가 존재
      ```yml
      # IF
      apiVersion: v1
      kind: ConfigMap
      metadata:
      name: flow-if
      data:
      dev:
         env: {{ .Values.dev.env }}
         {{- if eq .Values.dev.env "dev" }}
         log: debug
         {{- else if .Values.dev.log }}
         log: {{ .Values.dev.log }}
         {{- else }}
         log: error
         {{ end }}

      qa:
         env: {{ .Values.qa.env }}
         {{- if eq .Values.qa.env "dev" }}
         log: debug
         {{- else if .Values.qa.log }}
         log: {{ .Values.qa.log }}
         {{- else }}
         log: error
         {{- end }}

      prod:
         env: {{ .Values.prod.env }}
         {{ if eq .Values.prod.env "dev" }}
         log: debug
         {{ else if .Values.prod.log }}
         log: {{ .Values.prod.log }}
         {{ else }}
         log: error
         {{ end }}
      ```
      ```yml
      # WITH
      apiVersion: v1
      kind: ConfigMap
      metadata:
      name: flow-with
      data:
      dev:
      {{- with .Values.dev }}
         env: {{ .env }}
         log: {{ .log }}
      {{- end }}

      qa:
      {{- with .Values.qa }}
         env: {{ .env }}
         log: {{ .log }}
      {{- end }}
      
      prod:
      {{- with .Values.prod }}
         env: {{ .env }}
         log: {{ .log }}
      {{- end }}
      ```
      ```yml
      # RANGE
      apiVersion: v1
      kind: ConfigMap
      metadata:
      name: flow-range
      data:
      yaml:
      {{- .Values.data | toYaml | nindent 2 }}

      range:
      {{- range .Values.data }}
      - {{ . }}
      {{- end }}

      range-quote:
      {{- range .Values.data }}
      - {{ . | quote }}
      {{- end }}

      range-upper-quote:
      {{- range .Values.data }}
      - {{ . | upper | quote }}
      {{- end }}
      ```
  - 지역 변수: 사용자 정의 변수는 어떤 파일에서든지 사용이 가능하지만 해당 파일에서만 간단하게 사용하기를 원할 때는 지역 변수를 선언하고 사용
      ```yml
      # with 내부에서 사용
      apiVersion: v1
      kind: ConfigMap
      metadata:
      name: variables-with
      data:
      dev:
      {{- $relname := .Release.Name -}}
      {{- with .Values.dev }}
         env: {{ .env }}
         release: {{ $relname }}
         log: {{ .log }}
      {{- end }}
      ```
      ```yml
      # range와 함께 사용
      apiVersion: v1
      kind: ConfigMap
      metadata:
      name: variables-range
      data:
      # for (int i ; i=list.length ; i++) { printf "i : list[i]" };
      index:
      {{- range $index, $value := .Values.data }}
         {{ $index }}: {{ $value }}
      {{- end }}

      # for (Map<key, value> map : list) { printf "map.key() : map.value()" };
      key-value:
      {{- range $key, $value := .Values.dev }}
         {{ $key }}: {{ $value | quote }}
      {{- end }}
      ```
