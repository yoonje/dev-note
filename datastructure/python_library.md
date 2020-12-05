# Python Library
파이썬에서 자료구조 사용을 편하게 만들어주는 내장 라이브러리에 대한 활용법을 설명합니다.

### 유용한 내장 함수
 - sort(객체,Key=?,reverse=?): 객체를 내부적으로 정렬한다. Key 함수를 통해서 정렬 옵션을 선택할 수 있고 reverse 매개변수를 통해서 True는 내림차순, False는 오름차순으로 정할 수 있다.
 - sorted(객체,Key=?,reverse=?): 객체를 내부적으로 정렬한 뒤 리턴한다. Key 함수를 통해서 정렬 옵션을 선택할 수 있고 reverse 매개변수를 통해서 True는 내림차순, False는 오름차순으로 정할 수 있다.
 - min(객체): 갹체 안에서 최소 값을 리턴한다. Key 함수를 통해서 탐색 옵션을 선택할 수 있다.
 - max(객체): 객체 안에서 최대 값을 리턴한다. Key 함수를 통해서 탐색 옵션을 선택할 수 있다.
 - len(객체): 객체의 전체 길이를 리턴한다.
 - del 객체: 파이썬의 모든 자료 형은 객체인데 이 객체를 삭제한다.
 - 객체.clear(): 객체를 삭제한다.
 - 변수 = copy.deepcopy(객체): 객체 간의 깊은 복사를 이용할 때 사용한다.

### List(Vector)
- 리스트는 파이썬의 내장 자료형으로 이름과 달리 내부적으로는 Linked List 방식이 아닌 벡터 형태를 띄고 있는 동적 배열이다.
- 파이썬에도 linked list를 라이브러리로 사용할 수 있으나 일반적으로 linked list보다 list(vector)가 일반적으로 성능이 더 좋기 때문에 linked list는 본 문서에서는 따로 설명하지 않을 것이다.
- 생성 관련 함수
  - list(): 비어 있는 리스트를 생성한다.
  - []: 비어 있는 리스트를 생성한다.
- 삽입 관련 함수
  - list.append(a): a를 list의 맨 뒤에 삽입한다.
  - list.insert(a,b): a번째 위치에 b를 삽입한다.
- 삭제 관련 함수
  - list.remove(a): 앞에서부터 탐색해가며 a라는 값이 나오면 삭제한다.
  - list.pop(): list의 맨 마지막 값을 삭제하고 리턴한다.
- 참조 관련 함수
  - list[idx]: 해당 인덱스에 있는 리스트의 원소를 리턴한다.
- 탐색 관련 함수
  - list.index(a): a라는 값이 있으면 그 값의 위치 인덱스를 리턴한다.
- 기타 함수
  - list.reverse(): 리스트를 역순으로 뒤집는다.
  - list.count(a): 리스트 안에 a가 몇개 들어 있는지 카운트한다.
  - list.extend(list2): list에 list2를 이어 확장한다.
  - list + list2: list에 list2를 이어 확장한다.

### Stack, Queue
- `collections.deque`를 통해서 LIFO 형태로 사용하면 쉽게 빠른 stack을 구현할 수 있고 FIFO 형태로 사용하면 Queue를 구현할 수 있다. 이 문서에서는 가장 일반적이고 성능이 좋은 collection.deque를 기반으로 설명할 것이다.
- 스택은 내장 자료형인 list를 LIFO 형태로 사용해도 구현할 수 있으나 linked list 형태로 구현된 collections.deque가 성능에서 더 이점이 있다.
- 큐는 내장 자료형인 list를 FIFO 형태로 사용해도 구현할 수 있으나 linked list 형태로 구현되지 않아서 collections.deque를 사용할 때보다 Head 삭제 시의 O(n)의 복잡도가 추가되어 매우 성능이 떨어진다.
- `병렬 컴퓨팅` 상황에서 스택과 큐 사용에서는 스택은 `queue.LifoQueue`를 큐는 `queue.Queue`를 사용하여 모듈이 지원하는 lock 매커니즘의 내부적인 구현을 활용한다.
- 생성 관련 함수
  - collections.deque(): 비어있는 deque를 생성한다.
- 삽입 관련 함수
  - deque.append(a): a를 deque의 맨 오른쪽에 삽입한다.
  - deque.appendleft(a): a를 deque의 맨 왼쪽에 삽입한다.
  - deque.insert(a,b): a번째 위치에 b를 삽입한다.
- 삭제 관련 함수
  - deque.pop(): deque의 맨 오른쪽의 값을 삭제하고 리턴한다.
  - deque.popleft(): deque의 맨 왼쪽의 값을 삭제하고 리턴한다. 
  - deque.remove(a): 오른쪽에서부터 탐색해가며 a라는 값이 나오면 삭제한다.
- 기타 함수
  - deque.reverse(): deque를 역순으로 뒤집는다.
  - deque.extend(deque2): 오른쪽으로 deque와 deque2를 확장한다.
  - deque.extendleft(deque2): 왼쪽으로 deque와 deque2를 확장한다.
  - deque.rotate(1): 오른쪽으로 1칸 rotate한다.
  - deque.rotate(-1): 왼쪽으로 1칸 rotate한다.

### Priority_queue
- `heapq`를 통해서 쉽게 빠른 우선순위 큐를 구현할 수 있다. heapq는 최소 힙만을 지원한다. 최대 힙으로 사용하려면 push할때 key를 -를 붙여서 삽입하면 된다. 이 문서에서는 가장 일반적이고 성능이 좋은 heapq를 기반으로 설명할 것이다.
- 생성 관련 함수
  - heapq 모듈은 생성관련 함수는 딱히 없으나 heap 형태로 튜플 데이터를 저장하는 리스트를 미리 선언해야한다.
- 삽입 관련 함수
  - heapq.heappush(list, (key,value)): list에 key와 value로 이뤄진 튜플을 삽입한다.
- 삭제 관련 함수
  - heapq.heappop(list): heapq 모듈에 의해 들어간 (key,value)는 key라는 우선순위에 따라 키값이 낮은 순서대로 리턴한다.
- 참조 관련 함수
  - list[idx]: heapq 모듈로 배열된 순서대로 해당 인덱스에 있는 리스트의 원소를 리턴한다.
- 기타 함수
  - heapq.heapify(list): (key,value) 튜플로 이뤄진 리스트 또는 단일 키값으로 이뤄진 리스트를 힙 정렬하여 반환한다. 


### Dictionary(Map)
- 딕셔너리는 파이썬의 내장 자료형으로 파이썬에서 간단하게 해시테이블 구조의 자료구조를 이용할 때 사용한다.
- 생성 관련 함수
  - dict(): 비어 있는 딕셔너리를 생성한다.
  - {}: 비어 있는 딕셔너리를 생성한다.
- 삽입 관련 함수
  - dict.update(dict2): dict과 dict2를 합친다.
- 삭제 관련 함수
  - dict.pop(key): key에 대한 값을 리턴하고 삭제한다.
- 참조 관련 함수
  - dictionary[key]: 해당 key에 있는 값을 리턴한다.
- 탐색 관련 함수
  - dict.get(key): key에 대한 값을 리턴하는데 입력된 키가 없으면 디폴트 값을 리턴한다.
- 기타 함수
  - dict.items(): 딕셔너리의 키와 값을 (key,value) 쌍의 튜플 목록들로 리턴한다.
  - dict.keys(): 딕셔너리의 키들을 목록으로 리턴한다.
  - dict.values(): 딕셔너리의 값들을 목록으로 리턴한다.
  - json.loads(string): dictionary 형식의 문자열을 딕셔너리 형태로 변환하여 리턴한다.
  - json.dumps(dict): dictionary를 문자열 형태로 변환하여 리턴한다.


### Set
- 셋은 파이썬의 내장 자료형으로 중복 값을 삽입 할 수 없는 리스트로서 파이썬에서 간단하게 집합 연산을 이용할 때 사용한다.
- 생성 관련 함수
  - set()
- 삽입 관련 함수
  - set.add(a): a를 set에 삽입한다.
  - set.update(a): a(container)를 set에 삽입한다.
- 삭제 관련 함수
  - set.remove(a): set에서 a를 삭제하는데 a가 set에 존재하지 않으면 예외를 일으킨다.
  - set.discard(a): set에서 a를 삭제하는데 a가 set에 존재하지 않아도 예외를 일으키지 않는다.
- 기타 함수
  - set | set2: set와 set2의 합집합을 리턴한다.
  - set & set2: set와 set2의 교집합을 리턴한다.
  - set - set2: set와 set2의 차집합을 리턴한다.
  - set.issubset(set2): set이 set2의 부분 집합이면 True 아니면 False를 리턴한다.
  - set.issuperset(set2): set이 set2의 슈퍼 집합이면 True 아니면 False를 리턴한다.
  - set.isdisjoint(set2): set과 set2 사이에 교집합이 있으면 True 없으면 False를 리턴한다.
