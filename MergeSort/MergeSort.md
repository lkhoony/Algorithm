# 합병 정렬

## Outline
- 분할통치법
- 합병 정렬

## 1. 분할 통치법
> 해결하려고 하는 문제를 (크기가 n이라고 함) 크기가 보다 작은 여러 개의 부분 문제로 분할하여 해결하는 일반적인 알고리즘 설계 기법

- 재귀의 베이스 케이스는 상수 크기의 부문제들이 됨

- 점화식(recurrence equations)을 사용하여 분석

### 1-1. 분할(divide)

- 입력 데이터 L을 둘 이상의 분리된 부분집합 L1, L2,...로 나눔

### 1-2. 재귀(recur)

- L1, L2,... 각각에 대한 부문제를 재귀적으로 해결 

### 1-3. 통치(conquer)

- 부문제들에 대한 해결을 합쳐 L의 해결을 구함

## 2. 합병 정렬(merge sort)
> 분할 통치법에 기초한 정렬 알고리즘

- 비교에 기초한 정렬

- O(n*logn)시간에 수행 됨

- 힙 정렬과는 다르게 외부의 우선순위 큐를 사용하지 않음

- 데이터를 순차적 방식으로 접근하여 디스크의 데이터를 정렬하기에 적당

### 2.1. 합병 정렬에서의 분할 통치법

#### 2.1.1. 합병정렬의 분할(divide)

- 무순 리스트 L을 각각 n/2개의 원소를 가진 두 개의 부리스트 L1과 L2로 분할

#### 2.1.2. 합병정렬의 재귀(recur)

- L1, L2를 각각 재귀적으로 정렬

#### 2.1.3. 합병정렬의 통치(conquer)

- L1과 L2를 단일 순서리스트로 합병

```
// 합병정렬의 의사코드

Alg mergeSort(L)
	input list L with n elements
	output sorted list L

1. if (L.size() > 1)
	L1, L2 <- partition(L, n/2)
	mergeSort(L1)
	mergeSort(L2)
	L <- merge(L1, L2)
2. return


// merge(합병) 의사코드

Alg merge(L1, L2)
	input sorted list L1 and L2 with n/2 elements each
	output sorted list of L1∪L2

1. L <- empty list
2. while (!L1.isEmpty() & !L2.isEmpty())
	if (L1.get(1) ≤ L2.get(1))
		L.addLast(L1.removeFirst())
	else
		L.addLast(L2.removeFirst())
3. while (!L1.isEmpty())
	L.addLast(L1.removeFirst())
4. while (!L2.isEmpty())
	L.addLast(L2.removeFirst())
5. return L

```

### 2.2. 합병 정렬 과정

#### 2.2.1. 실행 예를 위한 입력 리스트

- 크기(k)가 8인 연결리스트를 입력

![image](https://user-images.githubusercontent.com/66773320/97070522-f2e1b500-1613-11eb-8b62-c32be94a2c52.png)

#### 2.2.2. 초기 분할

- mergeSort()함수 호출

- 연결리스트의 크기를 k/2로 분할 (partition 함수)

- 각각이 L1, L2가 됨

![image](https://user-images.githubusercontent.com/66773320/97070533-00973a80-1614-11eb-87be-20a71b2f57ca.png)

#### 2.2.3. 분할

- 다시 L1에 대해서 mergeSort 함수를 사용하여 이를 다시 L1, L2로 분할

- 계속해서 partition해서 크기가 1일때 까지 재귀적으로 분할

![image](https://user-images.githubusercontent.com/66773320/97070539-0f7ded00-1614-11eb-8e2e-b3df0b43d50e.png)

#### 2.2.4. 베이스 케이스

- 크기가 1일때 까지 재귀적으로 분할

![image](https://user-images.githubusercontent.com/66773320/97070547-1a388200-1614-11eb-9c47-0f745fee94b2.png)

#### 2.2.5. 합병

- 크기가 1인 분할된 리스트들을 합병(merge)

![image](https://user-images.githubusercontent.com/66773320/97070562-2d4b5200-1614-11eb-8188-49a1977ef3d3.png)

![image](https://user-images.githubusercontent.com/66773320/97070570-3fc58b80-1614-11eb-9208-ca09eaa58fd2.png)

![image](https://user-images.githubusercontent.com/66773320/97070571-47853000-1614-11eb-8607-dcc0db7203bc.png)


### 2.3. 합병 정렬 분석

- 합병 정렬 트리의 높이

	- 합병 정렬 트리의 높이(h) : O(logN)

		- 각 재귀 호출(mergeSort)에서 리스트를 절반으로 나누기 때문
		
- 깊이 i의 노드들에서 이루어지는 총 작업량 : O(N)

	- 각 갚이에서 모든 노드들에 대해서 합병하는 과정(merge)을 거침
	
- 따라서 전체 실행시간은 O(N*logN)